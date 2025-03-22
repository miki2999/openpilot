from numpy.ma.testutils import assert_equal
from parameterized import parameterized

from opendbc.car.car_helpers import interfaces
from opendbc.car.honda.values import CAR as HONDA
from opendbc.car.hyundai.values import CAR as HYUNDAI
from opendbc.car.toyota.values import CAR as TOYOTA
from openpilot.common.params import Params
from openpilot.selfdrive.car.helpers import convert_to_capnp
from openpilot.selfdrive.controls.lib.latcontrol_torque import LatControlTorque
from openpilot.sunnypilot.selfdrive.car import interfaces as sunnypilot_interfaces


class TestNNTorqueModel:

  @parameterized.expand([(HONDA.HONDA_CIVIC, True), (TOYOTA.TOYOTA_RAV4, True), (HYUNDAI.HYUNDAI_SANTA_CRUZ_1ST_GEN, False)])
  def test_load_model(self, car_name, should_load_model):
    params = Params()
    params.put_bool("NeuralNetworkLateralControl", True)

    CarInterface = interfaces[car_name]
    CP = CarInterface.get_non_essential_params(car_name)
    CP_SP = CarInterface.get_non_essential_params_sp(CP, car_name)
    CI = CarInterface(CP, CP_SP)

    sunnypilot_interfaces.setup_car_interface_sp(CP, CP_SP, params)

    CP_SP = convert_to_capnp(CP_SP)

    controller = LatControlTorque(CP.as_reader(), CP_SP.as_reader(), CI)

    assert_equal(should_load_model, controller.extension.has_nn_model)
