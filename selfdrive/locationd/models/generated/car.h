#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_6433130627326874982);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3138288845059688603);
void car_H_mod_fun(double *state, double *out_2631933678919632655);
void car_f_fun(double *state, double dt, double *out_9189844871466255928);
void car_F_fun(double *state, double dt, double *out_489679421654219892);
void car_h_25(double *state, double *unused, double *out_6718979456210751944);
void car_H_25(double *state, double *unused, double *out_7893472361816059156);
void car_h_24(double *state, double *unused, double *out_514715250792527294);
void car_H_24(double *state, double *unused, double *out_4335546763013736020);
void car_h_30(double *state, double *unused, double *out_5364170639196983811);
void car_H_30(double *state, double *unused, double *out_5375139403308810529);
void car_h_26(double *state, double *unused, double *out_4196426838120842074);
void car_H_26(double *state, double *unused, double *out_6811768393019436236);
void car_h_27(double *state, double *unused, double *out_283783247582313835);
void car_H_27(double *state, double *unused, double *out_7549902715109235440);
void car_h_29(double *state, double *unused, double *out_8176722742466837194);
void car_H_29(double *state, double *unused, double *out_4864908058994418345);
void car_h_28(double *state, double *unused, double *out_3320569299026646520);
void car_H_28(double *state, double *unused, double *out_8499436997645602697);
void car_h_31(double *state, double *unused, double *out_2857295979782250292);
void car_H_31(double *state, double *unused, double *out_6185560290786084760);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}