import json
import os
import sys
import threading
import time
from dataclasses import dataclass
from pathlib import Path

from cereal import messaging
from opendbc.car.interfaces import CarInterfaceBase
from openpilot.common.params import Params
from openpilot.common.realtime import Ratekeeper
from openpilot.common.swaglog import cloudlog
from openpilot.selfdrive.test.process_replay.process_replay import get_custom_params_from_lr, replay_process_with_name
from openpilot.system.manager.process_config import managed_processes
from openpilot.tools.lib.logreader import LogReader
from sunnypilot.nnff_longitudinal_controller.policy_model import LongitudinalLiveTuner


def start():
  cloudlog.info("Starting longitudinal tuner process")
  TunerManager.start_offroad_training()


class TunerManager:
  tuners: dict[str, LongitudinalLiveTuner] = {}
  training_status = {
    'progress': 0.0,
    'active': False,
    'paused': False,
    'source': 'none',  # 'onroad', 'replay', or 'none'
    'training_steps': 0,
    'target_steps': 20 * 60 * 20,
    'current_route': '',
    'routes_completed': 0,
    'routes_total': 0,
    'onroad_enabled': True,
    'offroad_enabled': False,
  }
  replay_routes: list[str] = []
  training_thread: threading.Thread | None = None
  OFFROAD_DAEMON_NAME = 'longitudinalTuner'

  @classmethod
  def get_tuner(cls, car_fingerprint):
    return cls.tuners.get(car_fingerprint)

  @classmethod
  def apply_tuned_params_to_cp(cls, CP):
    tuner = cls.get_tuner(CP.carFingerprint)
    if tuner:
      tuned_params = tuner.get_tuned_params()
      CP.vEgoStopping = tuned_params['vego_stopping']
      CP.vEgoStarting = tuned_params['vego_starting']
      CP.stoppingDecelRate = tuned_params['stopping_decel_rate']
      if hasattr(CP, 'longitudinalTuning'):
        if hasattr(CP.longitudinalTuning, 'kf'):
          CP.longitudinalTuning.kf = tuned_params['kf']
        if len(CP.longitudinalTuning.kpBP) == len(tuned_params['kpBP']):
          CP.longitudinalTuning.kpBP = tuned_params['kpBP']
        if len(CP.longitudinalTuning.kpV) == len(tuned_params['kpV']):
          CP.longitudinalTuning.kpV = tuned_params['kpV']
        if len(CP.longitudinalTuning.kiBP) == len(tuned_params['kiBP']):
          CP.longitudinalTuning.kiBP = tuned_params['kiBP']
        if len(CP.longitudinalTuning.kiV) == len(tuned_params['kiV']):
          CP.longitudinalTuning.kiV = tuned_params['kiV']

  @classmethod
  def create_tuner(cls, CP):
    params = Params()
    if params.get("LongitudinalLiveTuneParams", "none") == "none":
      return None
    if CP.carFingerprint not in cls.tuners:
      tuner = LongitudinalLiveTuner(CP, CP.longitudinalTuning.kpV, CP.longitudinalTuning.kiV)
      cls.tuners[CP.carFingerprint] = tuner
      CP._liveTuner = tuner
    else:
      CP._liveTuner = cls.tuners[CP.carFingerprint]
    cls.apply_tuned_params_to_cp(CP)
    return cls.tuners[CP.carFingerprint]

  @classmethod
  def check_training_status(cls):
    params = Params()
    is_onroad = params.get_bool("IsOnroad")
    mode = params.get("LongitudinalLiveTuneParams", "none")
    if is_onroad and mode != "onroad" and cls.training_status['active'] and cls.training_status['source'] == 'replay':
      cloudlog.info("Onroad: pausing replay training")
      cls.training_status['paused'] = True
    elif not is_onroad and mode == "replay":
      if cls.training_status['paused']:
        cloudlog.info("Offroad: resuming paused training")
        cls.training_status['paused'] = False
      elif not cls.training_status['active']:
        cls.start_offroad_training()

  @classmethod
  def start_offroad_training(cls):
    if cls.training_thread and cls.training_thread.is_alive():
      return
    cls.training_status['active'] = True
    cls.training_status['source'] = 'replay'
    cls.training_thread = threading.Thread(target=cls._offroad_training_loop, daemon=True)
    cls.training_thread.start()
    cloudlog.info("Offroad training started")

  @classmethod
  def _offroad_training_loop(cls):
    routes = cls._find_local_routes()
    if not routes:
      cloudlog.info("No local routes for training")
      cls.training_status['active'] = False
      return
    cls.training_status['routes_total'] = len(routes)
    cls.training_status['routes_completed'] = 0
    route_index = 0
    while route_index < len(routes):
      if cls.training_status.get('paused', False):
        cloudlog.info("Training paused; waiting...")
        time.sleep(10)
        continue
      cls.training_status['current_route'] = routes[route_index]
      cls.training_status['routes_completed'] = route_index
      cloudlog.info(f"Training on: {routes[route_index]}")
      cls._train_on_route(routes[route_index])
      route_index += 1
    cls.training_status['active'] = False
    cls.training_status['routes_completed'] = len(routes)
    cloudlog.info("Offroad training completed")

  @classmethod
  def _find_local_routes(cls):
    routes = []
    processed_logs = cls._load_processed_logs()
    for route_dir in ['/data/media/0/realdata/']:
      if not os.path.exists(route_dir):
        continue
      for route_path in Path(route_dir).glob("*"):
        if route_path.is_dir() and not route_path.name.startswith('.'):
          route_id = route_path.name
          if processed_logs["routes"].get(route_id, {}).get("fully_processed", False):
            continue
          routes.append(str(route_path))
    routes.sort(key=lambda x: os.path.getmtime(x), reverse=True)
    return routes[:10]

  @classmethod
  def _get_processed_logs_file(cls):
    return os.path.join(os.path.expanduser("~/data/openpilot/sunnypilot/nnff_longitudinal_controller"), "processed_nnff_logs.json")

  @classmethod
  def _load_processed_logs(cls):
    processed_logs_file = cls._get_processed_logs_file()
    if os.path.exists(processed_logs_file):
      try:
        with open(processed_logs_file) as f:
          return json.load(f)
      except OSError as e:
        cloudlog.warning(f"Error loading logs: {e}")
    return {"routes": {}, "segments": {}, "last_updated": 0}

  @classmethod
  def _save_processed_logs(cls, processed_logs):
    processed_logs_file = cls._get_processed_logs_file()
    os.makedirs(os.path.dirname(processed_logs_file), exist_ok=True)
    processed_logs["last_updated"] = time.time()
    try:
      with open(processed_logs_file, 'w') as f:
        json.dump(processed_logs, f)
    except OSError as e:
      cloudlog.warning(f"Error saving logs: {e}")

  @classmethod
  def reset_processed_logs(cls):
    processed_logs_file = cls._get_processed_logs_file()
    if os.path.exists(processed_logs_file):
      backup_file = f"{processed_logs_file}.{int(time.time())}.bak"
      try:
        os.rename(processed_logs_file, backup_file)
        cloudlog.info(f"Logs backed up to {backup_file}")
      except OSError as e:
        cloudlog.warning(f"Backup failed: {e}")
      cls._save_processed_logs({"routes": {}, "segments": {}, "last_updated": time.time()})
      return True
    return False

  @classmethod
  def _train_on_route(cls, route):
    cloudlog.info(f"Training on route: {route}")
    processed_logs = cls._load_processed_logs()
    route_id = os.path.basename(route)
    if processed_logs["routes"].get(route_id, {}).get("fully_processed", False):
      cloudlog.info(f"Route {route_id} already processed")
      return
    segment_paths = sorted(Path(route).glob("*"))
    processed_any_segment = False
    if route_id not in processed_logs["routes"]:
      processed_logs["routes"][route_id] = {"path": route, "first_seen": time.time(), "fully_processed": False, "segment_count": len(segment_paths)}
    segment_index = 0
    while segment_index < len(segment_paths):
      if cls.training_status.get('paused', False):
        if processed_any_segment:
          cls._save_processed_logs(processed_logs)
        time.sleep(1)
        continue
      segment_path = segment_paths[segment_index]
      segment_id = os.path.basename(str(segment_path))
      if segment_id in processed_logs.get("segments", {}) and processed_logs["segments"][segment_id].get("processed", False):
        segment_index += 1
        continue
      for log_format in ['rlog', 'rlog.bz2', 'raw_log.bz2', 'rlog.zst', 'qlog', 'qlog.bz2', 'qlog.zst', "fcamera.hevc"]:
        log_path = os.path.join(segment_path, log_format)
        if os.path.exists(log_path):
          try:
            lr = LogReader(log_path)
            car_params_msgs = [m for m in lr if m.which() == 'carParams']
            if not car_params_msgs:
              continue
            car_fingerprint = car_params_msgs[0].carParams.carFingerprint
            custom_params = get_custom_params_from_lr(lr)
            tuner = cls.get_tuner(car_fingerprint)
            if not tuner:
              CP = CarInterfaceBase.get_std_params(car_fingerprint)
              tuner = cls.create_tuner(CP)
            cloudlog.info(f"Replaying data for {car_fingerprint}")
            output_logs = replay_process_with_name(['controlsd', 'plannerd', 'radard'], lr, custom_params=custom_params)
            control_outputs = [m for m in output_logs if m.which() == 'controlsState']
            last_train_idx = 0
            for i, cs in enumerate(control_outputs):
              if i - last_train_idx >= 60:
                tuner.force_update(cs.controlsState.carState, cs.controlsState.actuators)
                last_train_idx = i
                cls.training_status['progress'] = tuner.training_progress
            tuner._save_params()
            processed_logs["segments"][segment_id] = {
                "processed": True,
                "car_fingerprint": car_fingerprint,
                "route_id": route_id,
                "processed_time": time.time(),
                "log_format": log_format,
            }
            processed_any_segment = True
          except Exception as e:
            cloudlog.exception(f"Error on segment {segment_path}: {e}")
            processed_logs["segments"][segment_id] = {"processed": False, "error": str(e), "error_time": time.time()}
          cls._save_processed_logs(processed_logs)
          break
      segment_index += 1
      segments_in_route = [s for s in processed_logs["segments"].values() if s.get("route_id") == route_id and s.get("processed", False)]
      if len(segments_in_route) == len(segment_paths):
        processed_logs["routes"][route_id]["fully_processed"] = True
        cloudlog.info(f"Route {route_id} fully processed")
    if processed_any_segment:
      cls._save_processed_logs(processed_logs)

  @classmethod
  def publish_nnff_status(cls):
    try:
      pm = messaging.PubMaster(['custom.CarControlSP'])
      msg = messaging.new_message('custom.CarControlSP')
      msg.custom.CarControlSP.nnffLongTuning = cls.training_status
      pm.send('custom.CarControlSP', msg)
    except Exception as e:
      cloudlog.exception(f"Error publishing nnff status: {e}")

  @classmethod
  def register_process(cls):
    @dataclass
    class LongitudinalTunerProcessConfig:
      name = "longitudinalTuner"
      enabled = True
      onroad = False
      nice = 10
      def __init__(self):
        mode = Params().get("LongitudinalLiveTuneParams", "none")
        self.enabled = mode in ["onroad", "replay"]
    managed_processes["longitudinal_tuner"] = LongitudinalTunerProcessConfig()

  @classmethod
  def should_run_offroad(cls):
    return Params().get("LongitudinalLiveTuneParams", "none") == "replay"

  @classmethod
  def should_run_onroad(cls):
    return Params().get("LongitudinalLiveTuneParams", "none") == "onroad"


def main():
  if len(sys.argv) > 1 and sys.argv[1] == "--reset-processed-logs":
    print("Resetting processed logs...")
    print("Successfully reset processed logs" if TunerManager.reset_processed_logs() else "No processed logs file found")
    sys.exit(0)
  TunerManager.register_process()
  params = Params()
  prev_onroad = params.get_bool("IsOnroad")
  rk = Ratekeeper(1, print_delay_threshold=None)
  while True:
    is_onroad = params.get_bool("IsOnroad")
    if is_onroad != prev_onroad:
      cloudlog.info(f"Transitioned to {'onroad' if is_onroad else 'offroad'}")
      TunerManager.check_training_status()
      prev_onroad = is_onroad
    if not is_onroad and TunerManager.should_run_offroad() and not TunerManager.training_status['active']:
      TunerManager.start_offroad_training()
    TunerManager.publish_nnff_status()
    rk.keep_time()


if __name__ == "__main__":
  main()
