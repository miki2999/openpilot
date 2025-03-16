#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7620083208430612448);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5582676530876115798);
void pose_H_mod_fun(double *state, double *out_7715066790722213833);
void pose_f_fun(double *state, double dt, double *out_3360399432308685597);
void pose_F_fun(double *state, double dt, double *out_3617201388683777182);
void pose_h_4(double *state, double *unused, double *out_795590817763196752);
void pose_H_4(double *state, double *unused, double *out_6517119308839315729);
void pose_h_10(double *state, double *unused, double *out_3128038460922897567);
void pose_H_10(double *state, double *unused, double *out_8908850792766836240);
void pose_h_13(double *state, double *unused, double *out_3481125658308717604);
void pose_H_13(double *state, double *unused, double *out_8095869301567711863);
void pose_h_14(double *state, double *unused, double *out_1373823934019708509);
void pose_H_14(double *state, double *unused, double *out_8846836332574863591);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}