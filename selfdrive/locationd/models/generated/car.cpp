#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6433130627326874982) {
   out_6433130627326874982[0] = delta_x[0] + nom_x[0];
   out_6433130627326874982[1] = delta_x[1] + nom_x[1];
   out_6433130627326874982[2] = delta_x[2] + nom_x[2];
   out_6433130627326874982[3] = delta_x[3] + nom_x[3];
   out_6433130627326874982[4] = delta_x[4] + nom_x[4];
   out_6433130627326874982[5] = delta_x[5] + nom_x[5];
   out_6433130627326874982[6] = delta_x[6] + nom_x[6];
   out_6433130627326874982[7] = delta_x[7] + nom_x[7];
   out_6433130627326874982[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3138288845059688603) {
   out_3138288845059688603[0] = -nom_x[0] + true_x[0];
   out_3138288845059688603[1] = -nom_x[1] + true_x[1];
   out_3138288845059688603[2] = -nom_x[2] + true_x[2];
   out_3138288845059688603[3] = -nom_x[3] + true_x[3];
   out_3138288845059688603[4] = -nom_x[4] + true_x[4];
   out_3138288845059688603[5] = -nom_x[5] + true_x[5];
   out_3138288845059688603[6] = -nom_x[6] + true_x[6];
   out_3138288845059688603[7] = -nom_x[7] + true_x[7];
   out_3138288845059688603[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2631933678919632655) {
   out_2631933678919632655[0] = 1.0;
   out_2631933678919632655[1] = 0.0;
   out_2631933678919632655[2] = 0.0;
   out_2631933678919632655[3] = 0.0;
   out_2631933678919632655[4] = 0.0;
   out_2631933678919632655[5] = 0.0;
   out_2631933678919632655[6] = 0.0;
   out_2631933678919632655[7] = 0.0;
   out_2631933678919632655[8] = 0.0;
   out_2631933678919632655[9] = 0.0;
   out_2631933678919632655[10] = 1.0;
   out_2631933678919632655[11] = 0.0;
   out_2631933678919632655[12] = 0.0;
   out_2631933678919632655[13] = 0.0;
   out_2631933678919632655[14] = 0.0;
   out_2631933678919632655[15] = 0.0;
   out_2631933678919632655[16] = 0.0;
   out_2631933678919632655[17] = 0.0;
   out_2631933678919632655[18] = 0.0;
   out_2631933678919632655[19] = 0.0;
   out_2631933678919632655[20] = 1.0;
   out_2631933678919632655[21] = 0.0;
   out_2631933678919632655[22] = 0.0;
   out_2631933678919632655[23] = 0.0;
   out_2631933678919632655[24] = 0.0;
   out_2631933678919632655[25] = 0.0;
   out_2631933678919632655[26] = 0.0;
   out_2631933678919632655[27] = 0.0;
   out_2631933678919632655[28] = 0.0;
   out_2631933678919632655[29] = 0.0;
   out_2631933678919632655[30] = 1.0;
   out_2631933678919632655[31] = 0.0;
   out_2631933678919632655[32] = 0.0;
   out_2631933678919632655[33] = 0.0;
   out_2631933678919632655[34] = 0.0;
   out_2631933678919632655[35] = 0.0;
   out_2631933678919632655[36] = 0.0;
   out_2631933678919632655[37] = 0.0;
   out_2631933678919632655[38] = 0.0;
   out_2631933678919632655[39] = 0.0;
   out_2631933678919632655[40] = 1.0;
   out_2631933678919632655[41] = 0.0;
   out_2631933678919632655[42] = 0.0;
   out_2631933678919632655[43] = 0.0;
   out_2631933678919632655[44] = 0.0;
   out_2631933678919632655[45] = 0.0;
   out_2631933678919632655[46] = 0.0;
   out_2631933678919632655[47] = 0.0;
   out_2631933678919632655[48] = 0.0;
   out_2631933678919632655[49] = 0.0;
   out_2631933678919632655[50] = 1.0;
   out_2631933678919632655[51] = 0.0;
   out_2631933678919632655[52] = 0.0;
   out_2631933678919632655[53] = 0.0;
   out_2631933678919632655[54] = 0.0;
   out_2631933678919632655[55] = 0.0;
   out_2631933678919632655[56] = 0.0;
   out_2631933678919632655[57] = 0.0;
   out_2631933678919632655[58] = 0.0;
   out_2631933678919632655[59] = 0.0;
   out_2631933678919632655[60] = 1.0;
   out_2631933678919632655[61] = 0.0;
   out_2631933678919632655[62] = 0.0;
   out_2631933678919632655[63] = 0.0;
   out_2631933678919632655[64] = 0.0;
   out_2631933678919632655[65] = 0.0;
   out_2631933678919632655[66] = 0.0;
   out_2631933678919632655[67] = 0.0;
   out_2631933678919632655[68] = 0.0;
   out_2631933678919632655[69] = 0.0;
   out_2631933678919632655[70] = 1.0;
   out_2631933678919632655[71] = 0.0;
   out_2631933678919632655[72] = 0.0;
   out_2631933678919632655[73] = 0.0;
   out_2631933678919632655[74] = 0.0;
   out_2631933678919632655[75] = 0.0;
   out_2631933678919632655[76] = 0.0;
   out_2631933678919632655[77] = 0.0;
   out_2631933678919632655[78] = 0.0;
   out_2631933678919632655[79] = 0.0;
   out_2631933678919632655[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9189844871466255928) {
   out_9189844871466255928[0] = state[0];
   out_9189844871466255928[1] = state[1];
   out_9189844871466255928[2] = state[2];
   out_9189844871466255928[3] = state[3];
   out_9189844871466255928[4] = state[4];
   out_9189844871466255928[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9189844871466255928[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9189844871466255928[7] = state[7];
   out_9189844871466255928[8] = state[8];
}
void F_fun(double *state, double dt, double *out_489679421654219892) {
   out_489679421654219892[0] = 1;
   out_489679421654219892[1] = 0;
   out_489679421654219892[2] = 0;
   out_489679421654219892[3] = 0;
   out_489679421654219892[4] = 0;
   out_489679421654219892[5] = 0;
   out_489679421654219892[6] = 0;
   out_489679421654219892[7] = 0;
   out_489679421654219892[8] = 0;
   out_489679421654219892[9] = 0;
   out_489679421654219892[10] = 1;
   out_489679421654219892[11] = 0;
   out_489679421654219892[12] = 0;
   out_489679421654219892[13] = 0;
   out_489679421654219892[14] = 0;
   out_489679421654219892[15] = 0;
   out_489679421654219892[16] = 0;
   out_489679421654219892[17] = 0;
   out_489679421654219892[18] = 0;
   out_489679421654219892[19] = 0;
   out_489679421654219892[20] = 1;
   out_489679421654219892[21] = 0;
   out_489679421654219892[22] = 0;
   out_489679421654219892[23] = 0;
   out_489679421654219892[24] = 0;
   out_489679421654219892[25] = 0;
   out_489679421654219892[26] = 0;
   out_489679421654219892[27] = 0;
   out_489679421654219892[28] = 0;
   out_489679421654219892[29] = 0;
   out_489679421654219892[30] = 1;
   out_489679421654219892[31] = 0;
   out_489679421654219892[32] = 0;
   out_489679421654219892[33] = 0;
   out_489679421654219892[34] = 0;
   out_489679421654219892[35] = 0;
   out_489679421654219892[36] = 0;
   out_489679421654219892[37] = 0;
   out_489679421654219892[38] = 0;
   out_489679421654219892[39] = 0;
   out_489679421654219892[40] = 1;
   out_489679421654219892[41] = 0;
   out_489679421654219892[42] = 0;
   out_489679421654219892[43] = 0;
   out_489679421654219892[44] = 0;
   out_489679421654219892[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_489679421654219892[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_489679421654219892[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_489679421654219892[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_489679421654219892[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_489679421654219892[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_489679421654219892[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_489679421654219892[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_489679421654219892[53] = -9.8000000000000007*dt;
   out_489679421654219892[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_489679421654219892[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_489679421654219892[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_489679421654219892[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_489679421654219892[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_489679421654219892[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_489679421654219892[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_489679421654219892[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_489679421654219892[62] = 0;
   out_489679421654219892[63] = 0;
   out_489679421654219892[64] = 0;
   out_489679421654219892[65] = 0;
   out_489679421654219892[66] = 0;
   out_489679421654219892[67] = 0;
   out_489679421654219892[68] = 0;
   out_489679421654219892[69] = 0;
   out_489679421654219892[70] = 1;
   out_489679421654219892[71] = 0;
   out_489679421654219892[72] = 0;
   out_489679421654219892[73] = 0;
   out_489679421654219892[74] = 0;
   out_489679421654219892[75] = 0;
   out_489679421654219892[76] = 0;
   out_489679421654219892[77] = 0;
   out_489679421654219892[78] = 0;
   out_489679421654219892[79] = 0;
   out_489679421654219892[80] = 1;
}
void h_25(double *state, double *unused, double *out_6718979456210751944) {
   out_6718979456210751944[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7893472361816059156) {
   out_7893472361816059156[0] = 0;
   out_7893472361816059156[1] = 0;
   out_7893472361816059156[2] = 0;
   out_7893472361816059156[3] = 0;
   out_7893472361816059156[4] = 0;
   out_7893472361816059156[5] = 0;
   out_7893472361816059156[6] = 1;
   out_7893472361816059156[7] = 0;
   out_7893472361816059156[8] = 0;
}
void h_24(double *state, double *unused, double *out_514715250792527294) {
   out_514715250792527294[0] = state[4];
   out_514715250792527294[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4335546763013736020) {
   out_4335546763013736020[0] = 0;
   out_4335546763013736020[1] = 0;
   out_4335546763013736020[2] = 0;
   out_4335546763013736020[3] = 0;
   out_4335546763013736020[4] = 1;
   out_4335546763013736020[5] = 0;
   out_4335546763013736020[6] = 0;
   out_4335546763013736020[7] = 0;
   out_4335546763013736020[8] = 0;
   out_4335546763013736020[9] = 0;
   out_4335546763013736020[10] = 0;
   out_4335546763013736020[11] = 0;
   out_4335546763013736020[12] = 0;
   out_4335546763013736020[13] = 0;
   out_4335546763013736020[14] = 1;
   out_4335546763013736020[15] = 0;
   out_4335546763013736020[16] = 0;
   out_4335546763013736020[17] = 0;
}
void h_30(double *state, double *unused, double *out_5364170639196983811) {
   out_5364170639196983811[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5375139403308810529) {
   out_5375139403308810529[0] = 0;
   out_5375139403308810529[1] = 0;
   out_5375139403308810529[2] = 0;
   out_5375139403308810529[3] = 0;
   out_5375139403308810529[4] = 1;
   out_5375139403308810529[5] = 0;
   out_5375139403308810529[6] = 0;
   out_5375139403308810529[7] = 0;
   out_5375139403308810529[8] = 0;
}
void h_26(double *state, double *unused, double *out_4196426838120842074) {
   out_4196426838120842074[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6811768393019436236) {
   out_6811768393019436236[0] = 0;
   out_6811768393019436236[1] = 0;
   out_6811768393019436236[2] = 0;
   out_6811768393019436236[3] = 0;
   out_6811768393019436236[4] = 0;
   out_6811768393019436236[5] = 0;
   out_6811768393019436236[6] = 0;
   out_6811768393019436236[7] = 1;
   out_6811768393019436236[8] = 0;
}
void h_27(double *state, double *unused, double *out_283783247582313835) {
   out_283783247582313835[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7549902715109235440) {
   out_7549902715109235440[0] = 0;
   out_7549902715109235440[1] = 0;
   out_7549902715109235440[2] = 0;
   out_7549902715109235440[3] = 1;
   out_7549902715109235440[4] = 0;
   out_7549902715109235440[5] = 0;
   out_7549902715109235440[6] = 0;
   out_7549902715109235440[7] = 0;
   out_7549902715109235440[8] = 0;
}
void h_29(double *state, double *unused, double *out_8176722742466837194) {
   out_8176722742466837194[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4864908058994418345) {
   out_4864908058994418345[0] = 0;
   out_4864908058994418345[1] = 1;
   out_4864908058994418345[2] = 0;
   out_4864908058994418345[3] = 0;
   out_4864908058994418345[4] = 0;
   out_4864908058994418345[5] = 0;
   out_4864908058994418345[6] = 0;
   out_4864908058994418345[7] = 0;
   out_4864908058994418345[8] = 0;
}
void h_28(double *state, double *unused, double *out_3320569299026646520) {
   out_3320569299026646520[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8499436997645602697) {
   out_8499436997645602697[0] = 1;
   out_8499436997645602697[1] = 0;
   out_8499436997645602697[2] = 0;
   out_8499436997645602697[3] = 0;
   out_8499436997645602697[4] = 0;
   out_8499436997645602697[5] = 0;
   out_8499436997645602697[6] = 0;
   out_8499436997645602697[7] = 0;
   out_8499436997645602697[8] = 0;
}
void h_31(double *state, double *unused, double *out_2857295979782250292) {
   out_2857295979782250292[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6185560290786084760) {
   out_6185560290786084760[0] = 0;
   out_6185560290786084760[1] = 0;
   out_6185560290786084760[2] = 0;
   out_6185560290786084760[3] = 0;
   out_6185560290786084760[4] = 0;
   out_6185560290786084760[5] = 0;
   out_6185560290786084760[6] = 0;
   out_6185560290786084760[7] = 0;
   out_6185560290786084760[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_6433130627326874982) {
  err_fun(nom_x, delta_x, out_6433130627326874982);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3138288845059688603) {
  inv_err_fun(nom_x, true_x, out_3138288845059688603);
}
void car_H_mod_fun(double *state, double *out_2631933678919632655) {
  H_mod_fun(state, out_2631933678919632655);
}
void car_f_fun(double *state, double dt, double *out_9189844871466255928) {
  f_fun(state,  dt, out_9189844871466255928);
}
void car_F_fun(double *state, double dt, double *out_489679421654219892) {
  F_fun(state,  dt, out_489679421654219892);
}
void car_h_25(double *state, double *unused, double *out_6718979456210751944) {
  h_25(state, unused, out_6718979456210751944);
}
void car_H_25(double *state, double *unused, double *out_7893472361816059156) {
  H_25(state, unused, out_7893472361816059156);
}
void car_h_24(double *state, double *unused, double *out_514715250792527294) {
  h_24(state, unused, out_514715250792527294);
}
void car_H_24(double *state, double *unused, double *out_4335546763013736020) {
  H_24(state, unused, out_4335546763013736020);
}
void car_h_30(double *state, double *unused, double *out_5364170639196983811) {
  h_30(state, unused, out_5364170639196983811);
}
void car_H_30(double *state, double *unused, double *out_5375139403308810529) {
  H_30(state, unused, out_5375139403308810529);
}
void car_h_26(double *state, double *unused, double *out_4196426838120842074) {
  h_26(state, unused, out_4196426838120842074);
}
void car_H_26(double *state, double *unused, double *out_6811768393019436236) {
  H_26(state, unused, out_6811768393019436236);
}
void car_h_27(double *state, double *unused, double *out_283783247582313835) {
  h_27(state, unused, out_283783247582313835);
}
void car_H_27(double *state, double *unused, double *out_7549902715109235440) {
  H_27(state, unused, out_7549902715109235440);
}
void car_h_29(double *state, double *unused, double *out_8176722742466837194) {
  h_29(state, unused, out_8176722742466837194);
}
void car_H_29(double *state, double *unused, double *out_4864908058994418345) {
  H_29(state, unused, out_4864908058994418345);
}
void car_h_28(double *state, double *unused, double *out_3320569299026646520) {
  h_28(state, unused, out_3320569299026646520);
}
void car_H_28(double *state, double *unused, double *out_8499436997645602697) {
  H_28(state, unused, out_8499436997645602697);
}
void car_h_31(double *state, double *unused, double *out_2857295979782250292) {
  h_31(state, unused, out_2857295979782250292);
}
void car_H_31(double *state, double *unused, double *out_6185560290786084760) {
  H_31(state, unused, out_6185560290786084760);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
