#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7620083208430612448) {
   out_7620083208430612448[0] = delta_x[0] + nom_x[0];
   out_7620083208430612448[1] = delta_x[1] + nom_x[1];
   out_7620083208430612448[2] = delta_x[2] + nom_x[2];
   out_7620083208430612448[3] = delta_x[3] + nom_x[3];
   out_7620083208430612448[4] = delta_x[4] + nom_x[4];
   out_7620083208430612448[5] = delta_x[5] + nom_x[5];
   out_7620083208430612448[6] = delta_x[6] + nom_x[6];
   out_7620083208430612448[7] = delta_x[7] + nom_x[7];
   out_7620083208430612448[8] = delta_x[8] + nom_x[8];
   out_7620083208430612448[9] = delta_x[9] + nom_x[9];
   out_7620083208430612448[10] = delta_x[10] + nom_x[10];
   out_7620083208430612448[11] = delta_x[11] + nom_x[11];
   out_7620083208430612448[12] = delta_x[12] + nom_x[12];
   out_7620083208430612448[13] = delta_x[13] + nom_x[13];
   out_7620083208430612448[14] = delta_x[14] + nom_x[14];
   out_7620083208430612448[15] = delta_x[15] + nom_x[15];
   out_7620083208430612448[16] = delta_x[16] + nom_x[16];
   out_7620083208430612448[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5582676530876115798) {
   out_5582676530876115798[0] = -nom_x[0] + true_x[0];
   out_5582676530876115798[1] = -nom_x[1] + true_x[1];
   out_5582676530876115798[2] = -nom_x[2] + true_x[2];
   out_5582676530876115798[3] = -nom_x[3] + true_x[3];
   out_5582676530876115798[4] = -nom_x[4] + true_x[4];
   out_5582676530876115798[5] = -nom_x[5] + true_x[5];
   out_5582676530876115798[6] = -nom_x[6] + true_x[6];
   out_5582676530876115798[7] = -nom_x[7] + true_x[7];
   out_5582676530876115798[8] = -nom_x[8] + true_x[8];
   out_5582676530876115798[9] = -nom_x[9] + true_x[9];
   out_5582676530876115798[10] = -nom_x[10] + true_x[10];
   out_5582676530876115798[11] = -nom_x[11] + true_x[11];
   out_5582676530876115798[12] = -nom_x[12] + true_x[12];
   out_5582676530876115798[13] = -nom_x[13] + true_x[13];
   out_5582676530876115798[14] = -nom_x[14] + true_x[14];
   out_5582676530876115798[15] = -nom_x[15] + true_x[15];
   out_5582676530876115798[16] = -nom_x[16] + true_x[16];
   out_5582676530876115798[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7715066790722213833) {
   out_7715066790722213833[0] = 1.0;
   out_7715066790722213833[1] = 0.0;
   out_7715066790722213833[2] = 0.0;
   out_7715066790722213833[3] = 0.0;
   out_7715066790722213833[4] = 0.0;
   out_7715066790722213833[5] = 0.0;
   out_7715066790722213833[6] = 0.0;
   out_7715066790722213833[7] = 0.0;
   out_7715066790722213833[8] = 0.0;
   out_7715066790722213833[9] = 0.0;
   out_7715066790722213833[10] = 0.0;
   out_7715066790722213833[11] = 0.0;
   out_7715066790722213833[12] = 0.0;
   out_7715066790722213833[13] = 0.0;
   out_7715066790722213833[14] = 0.0;
   out_7715066790722213833[15] = 0.0;
   out_7715066790722213833[16] = 0.0;
   out_7715066790722213833[17] = 0.0;
   out_7715066790722213833[18] = 0.0;
   out_7715066790722213833[19] = 1.0;
   out_7715066790722213833[20] = 0.0;
   out_7715066790722213833[21] = 0.0;
   out_7715066790722213833[22] = 0.0;
   out_7715066790722213833[23] = 0.0;
   out_7715066790722213833[24] = 0.0;
   out_7715066790722213833[25] = 0.0;
   out_7715066790722213833[26] = 0.0;
   out_7715066790722213833[27] = 0.0;
   out_7715066790722213833[28] = 0.0;
   out_7715066790722213833[29] = 0.0;
   out_7715066790722213833[30] = 0.0;
   out_7715066790722213833[31] = 0.0;
   out_7715066790722213833[32] = 0.0;
   out_7715066790722213833[33] = 0.0;
   out_7715066790722213833[34] = 0.0;
   out_7715066790722213833[35] = 0.0;
   out_7715066790722213833[36] = 0.0;
   out_7715066790722213833[37] = 0.0;
   out_7715066790722213833[38] = 1.0;
   out_7715066790722213833[39] = 0.0;
   out_7715066790722213833[40] = 0.0;
   out_7715066790722213833[41] = 0.0;
   out_7715066790722213833[42] = 0.0;
   out_7715066790722213833[43] = 0.0;
   out_7715066790722213833[44] = 0.0;
   out_7715066790722213833[45] = 0.0;
   out_7715066790722213833[46] = 0.0;
   out_7715066790722213833[47] = 0.0;
   out_7715066790722213833[48] = 0.0;
   out_7715066790722213833[49] = 0.0;
   out_7715066790722213833[50] = 0.0;
   out_7715066790722213833[51] = 0.0;
   out_7715066790722213833[52] = 0.0;
   out_7715066790722213833[53] = 0.0;
   out_7715066790722213833[54] = 0.0;
   out_7715066790722213833[55] = 0.0;
   out_7715066790722213833[56] = 0.0;
   out_7715066790722213833[57] = 1.0;
   out_7715066790722213833[58] = 0.0;
   out_7715066790722213833[59] = 0.0;
   out_7715066790722213833[60] = 0.0;
   out_7715066790722213833[61] = 0.0;
   out_7715066790722213833[62] = 0.0;
   out_7715066790722213833[63] = 0.0;
   out_7715066790722213833[64] = 0.0;
   out_7715066790722213833[65] = 0.0;
   out_7715066790722213833[66] = 0.0;
   out_7715066790722213833[67] = 0.0;
   out_7715066790722213833[68] = 0.0;
   out_7715066790722213833[69] = 0.0;
   out_7715066790722213833[70] = 0.0;
   out_7715066790722213833[71] = 0.0;
   out_7715066790722213833[72] = 0.0;
   out_7715066790722213833[73] = 0.0;
   out_7715066790722213833[74] = 0.0;
   out_7715066790722213833[75] = 0.0;
   out_7715066790722213833[76] = 1.0;
   out_7715066790722213833[77] = 0.0;
   out_7715066790722213833[78] = 0.0;
   out_7715066790722213833[79] = 0.0;
   out_7715066790722213833[80] = 0.0;
   out_7715066790722213833[81] = 0.0;
   out_7715066790722213833[82] = 0.0;
   out_7715066790722213833[83] = 0.0;
   out_7715066790722213833[84] = 0.0;
   out_7715066790722213833[85] = 0.0;
   out_7715066790722213833[86] = 0.0;
   out_7715066790722213833[87] = 0.0;
   out_7715066790722213833[88] = 0.0;
   out_7715066790722213833[89] = 0.0;
   out_7715066790722213833[90] = 0.0;
   out_7715066790722213833[91] = 0.0;
   out_7715066790722213833[92] = 0.0;
   out_7715066790722213833[93] = 0.0;
   out_7715066790722213833[94] = 0.0;
   out_7715066790722213833[95] = 1.0;
   out_7715066790722213833[96] = 0.0;
   out_7715066790722213833[97] = 0.0;
   out_7715066790722213833[98] = 0.0;
   out_7715066790722213833[99] = 0.0;
   out_7715066790722213833[100] = 0.0;
   out_7715066790722213833[101] = 0.0;
   out_7715066790722213833[102] = 0.0;
   out_7715066790722213833[103] = 0.0;
   out_7715066790722213833[104] = 0.0;
   out_7715066790722213833[105] = 0.0;
   out_7715066790722213833[106] = 0.0;
   out_7715066790722213833[107] = 0.0;
   out_7715066790722213833[108] = 0.0;
   out_7715066790722213833[109] = 0.0;
   out_7715066790722213833[110] = 0.0;
   out_7715066790722213833[111] = 0.0;
   out_7715066790722213833[112] = 0.0;
   out_7715066790722213833[113] = 0.0;
   out_7715066790722213833[114] = 1.0;
   out_7715066790722213833[115] = 0.0;
   out_7715066790722213833[116] = 0.0;
   out_7715066790722213833[117] = 0.0;
   out_7715066790722213833[118] = 0.0;
   out_7715066790722213833[119] = 0.0;
   out_7715066790722213833[120] = 0.0;
   out_7715066790722213833[121] = 0.0;
   out_7715066790722213833[122] = 0.0;
   out_7715066790722213833[123] = 0.0;
   out_7715066790722213833[124] = 0.0;
   out_7715066790722213833[125] = 0.0;
   out_7715066790722213833[126] = 0.0;
   out_7715066790722213833[127] = 0.0;
   out_7715066790722213833[128] = 0.0;
   out_7715066790722213833[129] = 0.0;
   out_7715066790722213833[130] = 0.0;
   out_7715066790722213833[131] = 0.0;
   out_7715066790722213833[132] = 0.0;
   out_7715066790722213833[133] = 1.0;
   out_7715066790722213833[134] = 0.0;
   out_7715066790722213833[135] = 0.0;
   out_7715066790722213833[136] = 0.0;
   out_7715066790722213833[137] = 0.0;
   out_7715066790722213833[138] = 0.0;
   out_7715066790722213833[139] = 0.0;
   out_7715066790722213833[140] = 0.0;
   out_7715066790722213833[141] = 0.0;
   out_7715066790722213833[142] = 0.0;
   out_7715066790722213833[143] = 0.0;
   out_7715066790722213833[144] = 0.0;
   out_7715066790722213833[145] = 0.0;
   out_7715066790722213833[146] = 0.0;
   out_7715066790722213833[147] = 0.0;
   out_7715066790722213833[148] = 0.0;
   out_7715066790722213833[149] = 0.0;
   out_7715066790722213833[150] = 0.0;
   out_7715066790722213833[151] = 0.0;
   out_7715066790722213833[152] = 1.0;
   out_7715066790722213833[153] = 0.0;
   out_7715066790722213833[154] = 0.0;
   out_7715066790722213833[155] = 0.0;
   out_7715066790722213833[156] = 0.0;
   out_7715066790722213833[157] = 0.0;
   out_7715066790722213833[158] = 0.0;
   out_7715066790722213833[159] = 0.0;
   out_7715066790722213833[160] = 0.0;
   out_7715066790722213833[161] = 0.0;
   out_7715066790722213833[162] = 0.0;
   out_7715066790722213833[163] = 0.0;
   out_7715066790722213833[164] = 0.0;
   out_7715066790722213833[165] = 0.0;
   out_7715066790722213833[166] = 0.0;
   out_7715066790722213833[167] = 0.0;
   out_7715066790722213833[168] = 0.0;
   out_7715066790722213833[169] = 0.0;
   out_7715066790722213833[170] = 0.0;
   out_7715066790722213833[171] = 1.0;
   out_7715066790722213833[172] = 0.0;
   out_7715066790722213833[173] = 0.0;
   out_7715066790722213833[174] = 0.0;
   out_7715066790722213833[175] = 0.0;
   out_7715066790722213833[176] = 0.0;
   out_7715066790722213833[177] = 0.0;
   out_7715066790722213833[178] = 0.0;
   out_7715066790722213833[179] = 0.0;
   out_7715066790722213833[180] = 0.0;
   out_7715066790722213833[181] = 0.0;
   out_7715066790722213833[182] = 0.0;
   out_7715066790722213833[183] = 0.0;
   out_7715066790722213833[184] = 0.0;
   out_7715066790722213833[185] = 0.0;
   out_7715066790722213833[186] = 0.0;
   out_7715066790722213833[187] = 0.0;
   out_7715066790722213833[188] = 0.0;
   out_7715066790722213833[189] = 0.0;
   out_7715066790722213833[190] = 1.0;
   out_7715066790722213833[191] = 0.0;
   out_7715066790722213833[192] = 0.0;
   out_7715066790722213833[193] = 0.0;
   out_7715066790722213833[194] = 0.0;
   out_7715066790722213833[195] = 0.0;
   out_7715066790722213833[196] = 0.0;
   out_7715066790722213833[197] = 0.0;
   out_7715066790722213833[198] = 0.0;
   out_7715066790722213833[199] = 0.0;
   out_7715066790722213833[200] = 0.0;
   out_7715066790722213833[201] = 0.0;
   out_7715066790722213833[202] = 0.0;
   out_7715066790722213833[203] = 0.0;
   out_7715066790722213833[204] = 0.0;
   out_7715066790722213833[205] = 0.0;
   out_7715066790722213833[206] = 0.0;
   out_7715066790722213833[207] = 0.0;
   out_7715066790722213833[208] = 0.0;
   out_7715066790722213833[209] = 1.0;
   out_7715066790722213833[210] = 0.0;
   out_7715066790722213833[211] = 0.0;
   out_7715066790722213833[212] = 0.0;
   out_7715066790722213833[213] = 0.0;
   out_7715066790722213833[214] = 0.0;
   out_7715066790722213833[215] = 0.0;
   out_7715066790722213833[216] = 0.0;
   out_7715066790722213833[217] = 0.0;
   out_7715066790722213833[218] = 0.0;
   out_7715066790722213833[219] = 0.0;
   out_7715066790722213833[220] = 0.0;
   out_7715066790722213833[221] = 0.0;
   out_7715066790722213833[222] = 0.0;
   out_7715066790722213833[223] = 0.0;
   out_7715066790722213833[224] = 0.0;
   out_7715066790722213833[225] = 0.0;
   out_7715066790722213833[226] = 0.0;
   out_7715066790722213833[227] = 0.0;
   out_7715066790722213833[228] = 1.0;
   out_7715066790722213833[229] = 0.0;
   out_7715066790722213833[230] = 0.0;
   out_7715066790722213833[231] = 0.0;
   out_7715066790722213833[232] = 0.0;
   out_7715066790722213833[233] = 0.0;
   out_7715066790722213833[234] = 0.0;
   out_7715066790722213833[235] = 0.0;
   out_7715066790722213833[236] = 0.0;
   out_7715066790722213833[237] = 0.0;
   out_7715066790722213833[238] = 0.0;
   out_7715066790722213833[239] = 0.0;
   out_7715066790722213833[240] = 0.0;
   out_7715066790722213833[241] = 0.0;
   out_7715066790722213833[242] = 0.0;
   out_7715066790722213833[243] = 0.0;
   out_7715066790722213833[244] = 0.0;
   out_7715066790722213833[245] = 0.0;
   out_7715066790722213833[246] = 0.0;
   out_7715066790722213833[247] = 1.0;
   out_7715066790722213833[248] = 0.0;
   out_7715066790722213833[249] = 0.0;
   out_7715066790722213833[250] = 0.0;
   out_7715066790722213833[251] = 0.0;
   out_7715066790722213833[252] = 0.0;
   out_7715066790722213833[253] = 0.0;
   out_7715066790722213833[254] = 0.0;
   out_7715066790722213833[255] = 0.0;
   out_7715066790722213833[256] = 0.0;
   out_7715066790722213833[257] = 0.0;
   out_7715066790722213833[258] = 0.0;
   out_7715066790722213833[259] = 0.0;
   out_7715066790722213833[260] = 0.0;
   out_7715066790722213833[261] = 0.0;
   out_7715066790722213833[262] = 0.0;
   out_7715066790722213833[263] = 0.0;
   out_7715066790722213833[264] = 0.0;
   out_7715066790722213833[265] = 0.0;
   out_7715066790722213833[266] = 1.0;
   out_7715066790722213833[267] = 0.0;
   out_7715066790722213833[268] = 0.0;
   out_7715066790722213833[269] = 0.0;
   out_7715066790722213833[270] = 0.0;
   out_7715066790722213833[271] = 0.0;
   out_7715066790722213833[272] = 0.0;
   out_7715066790722213833[273] = 0.0;
   out_7715066790722213833[274] = 0.0;
   out_7715066790722213833[275] = 0.0;
   out_7715066790722213833[276] = 0.0;
   out_7715066790722213833[277] = 0.0;
   out_7715066790722213833[278] = 0.0;
   out_7715066790722213833[279] = 0.0;
   out_7715066790722213833[280] = 0.0;
   out_7715066790722213833[281] = 0.0;
   out_7715066790722213833[282] = 0.0;
   out_7715066790722213833[283] = 0.0;
   out_7715066790722213833[284] = 0.0;
   out_7715066790722213833[285] = 1.0;
   out_7715066790722213833[286] = 0.0;
   out_7715066790722213833[287] = 0.0;
   out_7715066790722213833[288] = 0.0;
   out_7715066790722213833[289] = 0.0;
   out_7715066790722213833[290] = 0.0;
   out_7715066790722213833[291] = 0.0;
   out_7715066790722213833[292] = 0.0;
   out_7715066790722213833[293] = 0.0;
   out_7715066790722213833[294] = 0.0;
   out_7715066790722213833[295] = 0.0;
   out_7715066790722213833[296] = 0.0;
   out_7715066790722213833[297] = 0.0;
   out_7715066790722213833[298] = 0.0;
   out_7715066790722213833[299] = 0.0;
   out_7715066790722213833[300] = 0.0;
   out_7715066790722213833[301] = 0.0;
   out_7715066790722213833[302] = 0.0;
   out_7715066790722213833[303] = 0.0;
   out_7715066790722213833[304] = 1.0;
   out_7715066790722213833[305] = 0.0;
   out_7715066790722213833[306] = 0.0;
   out_7715066790722213833[307] = 0.0;
   out_7715066790722213833[308] = 0.0;
   out_7715066790722213833[309] = 0.0;
   out_7715066790722213833[310] = 0.0;
   out_7715066790722213833[311] = 0.0;
   out_7715066790722213833[312] = 0.0;
   out_7715066790722213833[313] = 0.0;
   out_7715066790722213833[314] = 0.0;
   out_7715066790722213833[315] = 0.0;
   out_7715066790722213833[316] = 0.0;
   out_7715066790722213833[317] = 0.0;
   out_7715066790722213833[318] = 0.0;
   out_7715066790722213833[319] = 0.0;
   out_7715066790722213833[320] = 0.0;
   out_7715066790722213833[321] = 0.0;
   out_7715066790722213833[322] = 0.0;
   out_7715066790722213833[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3360399432308685597) {
   out_3360399432308685597[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3360399432308685597[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3360399432308685597[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3360399432308685597[3] = dt*state[12] + state[3];
   out_3360399432308685597[4] = dt*state[13] + state[4];
   out_3360399432308685597[5] = dt*state[14] + state[5];
   out_3360399432308685597[6] = state[6];
   out_3360399432308685597[7] = state[7];
   out_3360399432308685597[8] = state[8];
   out_3360399432308685597[9] = state[9];
   out_3360399432308685597[10] = state[10];
   out_3360399432308685597[11] = state[11];
   out_3360399432308685597[12] = state[12];
   out_3360399432308685597[13] = state[13];
   out_3360399432308685597[14] = state[14];
   out_3360399432308685597[15] = state[15];
   out_3360399432308685597[16] = state[16];
   out_3360399432308685597[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3617201388683777182) {
   out_3617201388683777182[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3617201388683777182[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3617201388683777182[2] = 0;
   out_3617201388683777182[3] = 0;
   out_3617201388683777182[4] = 0;
   out_3617201388683777182[5] = 0;
   out_3617201388683777182[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3617201388683777182[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3617201388683777182[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3617201388683777182[9] = 0;
   out_3617201388683777182[10] = 0;
   out_3617201388683777182[11] = 0;
   out_3617201388683777182[12] = 0;
   out_3617201388683777182[13] = 0;
   out_3617201388683777182[14] = 0;
   out_3617201388683777182[15] = 0;
   out_3617201388683777182[16] = 0;
   out_3617201388683777182[17] = 0;
   out_3617201388683777182[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3617201388683777182[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3617201388683777182[20] = 0;
   out_3617201388683777182[21] = 0;
   out_3617201388683777182[22] = 0;
   out_3617201388683777182[23] = 0;
   out_3617201388683777182[24] = 0;
   out_3617201388683777182[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3617201388683777182[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3617201388683777182[27] = 0;
   out_3617201388683777182[28] = 0;
   out_3617201388683777182[29] = 0;
   out_3617201388683777182[30] = 0;
   out_3617201388683777182[31] = 0;
   out_3617201388683777182[32] = 0;
   out_3617201388683777182[33] = 0;
   out_3617201388683777182[34] = 0;
   out_3617201388683777182[35] = 0;
   out_3617201388683777182[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3617201388683777182[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3617201388683777182[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3617201388683777182[39] = 0;
   out_3617201388683777182[40] = 0;
   out_3617201388683777182[41] = 0;
   out_3617201388683777182[42] = 0;
   out_3617201388683777182[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3617201388683777182[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3617201388683777182[45] = 0;
   out_3617201388683777182[46] = 0;
   out_3617201388683777182[47] = 0;
   out_3617201388683777182[48] = 0;
   out_3617201388683777182[49] = 0;
   out_3617201388683777182[50] = 0;
   out_3617201388683777182[51] = 0;
   out_3617201388683777182[52] = 0;
   out_3617201388683777182[53] = 0;
   out_3617201388683777182[54] = 0;
   out_3617201388683777182[55] = 0;
   out_3617201388683777182[56] = 0;
   out_3617201388683777182[57] = 1;
   out_3617201388683777182[58] = 0;
   out_3617201388683777182[59] = 0;
   out_3617201388683777182[60] = 0;
   out_3617201388683777182[61] = 0;
   out_3617201388683777182[62] = 0;
   out_3617201388683777182[63] = 0;
   out_3617201388683777182[64] = 0;
   out_3617201388683777182[65] = 0;
   out_3617201388683777182[66] = dt;
   out_3617201388683777182[67] = 0;
   out_3617201388683777182[68] = 0;
   out_3617201388683777182[69] = 0;
   out_3617201388683777182[70] = 0;
   out_3617201388683777182[71] = 0;
   out_3617201388683777182[72] = 0;
   out_3617201388683777182[73] = 0;
   out_3617201388683777182[74] = 0;
   out_3617201388683777182[75] = 0;
   out_3617201388683777182[76] = 1;
   out_3617201388683777182[77] = 0;
   out_3617201388683777182[78] = 0;
   out_3617201388683777182[79] = 0;
   out_3617201388683777182[80] = 0;
   out_3617201388683777182[81] = 0;
   out_3617201388683777182[82] = 0;
   out_3617201388683777182[83] = 0;
   out_3617201388683777182[84] = 0;
   out_3617201388683777182[85] = dt;
   out_3617201388683777182[86] = 0;
   out_3617201388683777182[87] = 0;
   out_3617201388683777182[88] = 0;
   out_3617201388683777182[89] = 0;
   out_3617201388683777182[90] = 0;
   out_3617201388683777182[91] = 0;
   out_3617201388683777182[92] = 0;
   out_3617201388683777182[93] = 0;
   out_3617201388683777182[94] = 0;
   out_3617201388683777182[95] = 1;
   out_3617201388683777182[96] = 0;
   out_3617201388683777182[97] = 0;
   out_3617201388683777182[98] = 0;
   out_3617201388683777182[99] = 0;
   out_3617201388683777182[100] = 0;
   out_3617201388683777182[101] = 0;
   out_3617201388683777182[102] = 0;
   out_3617201388683777182[103] = 0;
   out_3617201388683777182[104] = dt;
   out_3617201388683777182[105] = 0;
   out_3617201388683777182[106] = 0;
   out_3617201388683777182[107] = 0;
   out_3617201388683777182[108] = 0;
   out_3617201388683777182[109] = 0;
   out_3617201388683777182[110] = 0;
   out_3617201388683777182[111] = 0;
   out_3617201388683777182[112] = 0;
   out_3617201388683777182[113] = 0;
   out_3617201388683777182[114] = 1;
   out_3617201388683777182[115] = 0;
   out_3617201388683777182[116] = 0;
   out_3617201388683777182[117] = 0;
   out_3617201388683777182[118] = 0;
   out_3617201388683777182[119] = 0;
   out_3617201388683777182[120] = 0;
   out_3617201388683777182[121] = 0;
   out_3617201388683777182[122] = 0;
   out_3617201388683777182[123] = 0;
   out_3617201388683777182[124] = 0;
   out_3617201388683777182[125] = 0;
   out_3617201388683777182[126] = 0;
   out_3617201388683777182[127] = 0;
   out_3617201388683777182[128] = 0;
   out_3617201388683777182[129] = 0;
   out_3617201388683777182[130] = 0;
   out_3617201388683777182[131] = 0;
   out_3617201388683777182[132] = 0;
   out_3617201388683777182[133] = 1;
   out_3617201388683777182[134] = 0;
   out_3617201388683777182[135] = 0;
   out_3617201388683777182[136] = 0;
   out_3617201388683777182[137] = 0;
   out_3617201388683777182[138] = 0;
   out_3617201388683777182[139] = 0;
   out_3617201388683777182[140] = 0;
   out_3617201388683777182[141] = 0;
   out_3617201388683777182[142] = 0;
   out_3617201388683777182[143] = 0;
   out_3617201388683777182[144] = 0;
   out_3617201388683777182[145] = 0;
   out_3617201388683777182[146] = 0;
   out_3617201388683777182[147] = 0;
   out_3617201388683777182[148] = 0;
   out_3617201388683777182[149] = 0;
   out_3617201388683777182[150] = 0;
   out_3617201388683777182[151] = 0;
   out_3617201388683777182[152] = 1;
   out_3617201388683777182[153] = 0;
   out_3617201388683777182[154] = 0;
   out_3617201388683777182[155] = 0;
   out_3617201388683777182[156] = 0;
   out_3617201388683777182[157] = 0;
   out_3617201388683777182[158] = 0;
   out_3617201388683777182[159] = 0;
   out_3617201388683777182[160] = 0;
   out_3617201388683777182[161] = 0;
   out_3617201388683777182[162] = 0;
   out_3617201388683777182[163] = 0;
   out_3617201388683777182[164] = 0;
   out_3617201388683777182[165] = 0;
   out_3617201388683777182[166] = 0;
   out_3617201388683777182[167] = 0;
   out_3617201388683777182[168] = 0;
   out_3617201388683777182[169] = 0;
   out_3617201388683777182[170] = 0;
   out_3617201388683777182[171] = 1;
   out_3617201388683777182[172] = 0;
   out_3617201388683777182[173] = 0;
   out_3617201388683777182[174] = 0;
   out_3617201388683777182[175] = 0;
   out_3617201388683777182[176] = 0;
   out_3617201388683777182[177] = 0;
   out_3617201388683777182[178] = 0;
   out_3617201388683777182[179] = 0;
   out_3617201388683777182[180] = 0;
   out_3617201388683777182[181] = 0;
   out_3617201388683777182[182] = 0;
   out_3617201388683777182[183] = 0;
   out_3617201388683777182[184] = 0;
   out_3617201388683777182[185] = 0;
   out_3617201388683777182[186] = 0;
   out_3617201388683777182[187] = 0;
   out_3617201388683777182[188] = 0;
   out_3617201388683777182[189] = 0;
   out_3617201388683777182[190] = 1;
   out_3617201388683777182[191] = 0;
   out_3617201388683777182[192] = 0;
   out_3617201388683777182[193] = 0;
   out_3617201388683777182[194] = 0;
   out_3617201388683777182[195] = 0;
   out_3617201388683777182[196] = 0;
   out_3617201388683777182[197] = 0;
   out_3617201388683777182[198] = 0;
   out_3617201388683777182[199] = 0;
   out_3617201388683777182[200] = 0;
   out_3617201388683777182[201] = 0;
   out_3617201388683777182[202] = 0;
   out_3617201388683777182[203] = 0;
   out_3617201388683777182[204] = 0;
   out_3617201388683777182[205] = 0;
   out_3617201388683777182[206] = 0;
   out_3617201388683777182[207] = 0;
   out_3617201388683777182[208] = 0;
   out_3617201388683777182[209] = 1;
   out_3617201388683777182[210] = 0;
   out_3617201388683777182[211] = 0;
   out_3617201388683777182[212] = 0;
   out_3617201388683777182[213] = 0;
   out_3617201388683777182[214] = 0;
   out_3617201388683777182[215] = 0;
   out_3617201388683777182[216] = 0;
   out_3617201388683777182[217] = 0;
   out_3617201388683777182[218] = 0;
   out_3617201388683777182[219] = 0;
   out_3617201388683777182[220] = 0;
   out_3617201388683777182[221] = 0;
   out_3617201388683777182[222] = 0;
   out_3617201388683777182[223] = 0;
   out_3617201388683777182[224] = 0;
   out_3617201388683777182[225] = 0;
   out_3617201388683777182[226] = 0;
   out_3617201388683777182[227] = 0;
   out_3617201388683777182[228] = 1;
   out_3617201388683777182[229] = 0;
   out_3617201388683777182[230] = 0;
   out_3617201388683777182[231] = 0;
   out_3617201388683777182[232] = 0;
   out_3617201388683777182[233] = 0;
   out_3617201388683777182[234] = 0;
   out_3617201388683777182[235] = 0;
   out_3617201388683777182[236] = 0;
   out_3617201388683777182[237] = 0;
   out_3617201388683777182[238] = 0;
   out_3617201388683777182[239] = 0;
   out_3617201388683777182[240] = 0;
   out_3617201388683777182[241] = 0;
   out_3617201388683777182[242] = 0;
   out_3617201388683777182[243] = 0;
   out_3617201388683777182[244] = 0;
   out_3617201388683777182[245] = 0;
   out_3617201388683777182[246] = 0;
   out_3617201388683777182[247] = 1;
   out_3617201388683777182[248] = 0;
   out_3617201388683777182[249] = 0;
   out_3617201388683777182[250] = 0;
   out_3617201388683777182[251] = 0;
   out_3617201388683777182[252] = 0;
   out_3617201388683777182[253] = 0;
   out_3617201388683777182[254] = 0;
   out_3617201388683777182[255] = 0;
   out_3617201388683777182[256] = 0;
   out_3617201388683777182[257] = 0;
   out_3617201388683777182[258] = 0;
   out_3617201388683777182[259] = 0;
   out_3617201388683777182[260] = 0;
   out_3617201388683777182[261] = 0;
   out_3617201388683777182[262] = 0;
   out_3617201388683777182[263] = 0;
   out_3617201388683777182[264] = 0;
   out_3617201388683777182[265] = 0;
   out_3617201388683777182[266] = 1;
   out_3617201388683777182[267] = 0;
   out_3617201388683777182[268] = 0;
   out_3617201388683777182[269] = 0;
   out_3617201388683777182[270] = 0;
   out_3617201388683777182[271] = 0;
   out_3617201388683777182[272] = 0;
   out_3617201388683777182[273] = 0;
   out_3617201388683777182[274] = 0;
   out_3617201388683777182[275] = 0;
   out_3617201388683777182[276] = 0;
   out_3617201388683777182[277] = 0;
   out_3617201388683777182[278] = 0;
   out_3617201388683777182[279] = 0;
   out_3617201388683777182[280] = 0;
   out_3617201388683777182[281] = 0;
   out_3617201388683777182[282] = 0;
   out_3617201388683777182[283] = 0;
   out_3617201388683777182[284] = 0;
   out_3617201388683777182[285] = 1;
   out_3617201388683777182[286] = 0;
   out_3617201388683777182[287] = 0;
   out_3617201388683777182[288] = 0;
   out_3617201388683777182[289] = 0;
   out_3617201388683777182[290] = 0;
   out_3617201388683777182[291] = 0;
   out_3617201388683777182[292] = 0;
   out_3617201388683777182[293] = 0;
   out_3617201388683777182[294] = 0;
   out_3617201388683777182[295] = 0;
   out_3617201388683777182[296] = 0;
   out_3617201388683777182[297] = 0;
   out_3617201388683777182[298] = 0;
   out_3617201388683777182[299] = 0;
   out_3617201388683777182[300] = 0;
   out_3617201388683777182[301] = 0;
   out_3617201388683777182[302] = 0;
   out_3617201388683777182[303] = 0;
   out_3617201388683777182[304] = 1;
   out_3617201388683777182[305] = 0;
   out_3617201388683777182[306] = 0;
   out_3617201388683777182[307] = 0;
   out_3617201388683777182[308] = 0;
   out_3617201388683777182[309] = 0;
   out_3617201388683777182[310] = 0;
   out_3617201388683777182[311] = 0;
   out_3617201388683777182[312] = 0;
   out_3617201388683777182[313] = 0;
   out_3617201388683777182[314] = 0;
   out_3617201388683777182[315] = 0;
   out_3617201388683777182[316] = 0;
   out_3617201388683777182[317] = 0;
   out_3617201388683777182[318] = 0;
   out_3617201388683777182[319] = 0;
   out_3617201388683777182[320] = 0;
   out_3617201388683777182[321] = 0;
   out_3617201388683777182[322] = 0;
   out_3617201388683777182[323] = 1;
}
void h_4(double *state, double *unused, double *out_795590817763196752) {
   out_795590817763196752[0] = state[6] + state[9];
   out_795590817763196752[1] = state[7] + state[10];
   out_795590817763196752[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6517119308839315729) {
   out_6517119308839315729[0] = 0;
   out_6517119308839315729[1] = 0;
   out_6517119308839315729[2] = 0;
   out_6517119308839315729[3] = 0;
   out_6517119308839315729[4] = 0;
   out_6517119308839315729[5] = 0;
   out_6517119308839315729[6] = 1;
   out_6517119308839315729[7] = 0;
   out_6517119308839315729[8] = 0;
   out_6517119308839315729[9] = 1;
   out_6517119308839315729[10] = 0;
   out_6517119308839315729[11] = 0;
   out_6517119308839315729[12] = 0;
   out_6517119308839315729[13] = 0;
   out_6517119308839315729[14] = 0;
   out_6517119308839315729[15] = 0;
   out_6517119308839315729[16] = 0;
   out_6517119308839315729[17] = 0;
   out_6517119308839315729[18] = 0;
   out_6517119308839315729[19] = 0;
   out_6517119308839315729[20] = 0;
   out_6517119308839315729[21] = 0;
   out_6517119308839315729[22] = 0;
   out_6517119308839315729[23] = 0;
   out_6517119308839315729[24] = 0;
   out_6517119308839315729[25] = 1;
   out_6517119308839315729[26] = 0;
   out_6517119308839315729[27] = 0;
   out_6517119308839315729[28] = 1;
   out_6517119308839315729[29] = 0;
   out_6517119308839315729[30] = 0;
   out_6517119308839315729[31] = 0;
   out_6517119308839315729[32] = 0;
   out_6517119308839315729[33] = 0;
   out_6517119308839315729[34] = 0;
   out_6517119308839315729[35] = 0;
   out_6517119308839315729[36] = 0;
   out_6517119308839315729[37] = 0;
   out_6517119308839315729[38] = 0;
   out_6517119308839315729[39] = 0;
   out_6517119308839315729[40] = 0;
   out_6517119308839315729[41] = 0;
   out_6517119308839315729[42] = 0;
   out_6517119308839315729[43] = 0;
   out_6517119308839315729[44] = 1;
   out_6517119308839315729[45] = 0;
   out_6517119308839315729[46] = 0;
   out_6517119308839315729[47] = 1;
   out_6517119308839315729[48] = 0;
   out_6517119308839315729[49] = 0;
   out_6517119308839315729[50] = 0;
   out_6517119308839315729[51] = 0;
   out_6517119308839315729[52] = 0;
   out_6517119308839315729[53] = 0;
}
void h_10(double *state, double *unused, double *out_3128038460922897567) {
   out_3128038460922897567[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3128038460922897567[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3128038460922897567[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8908850792766836240) {
   out_8908850792766836240[0] = 0;
   out_8908850792766836240[1] = 9.8100000000000005*cos(state[1]);
   out_8908850792766836240[2] = 0;
   out_8908850792766836240[3] = 0;
   out_8908850792766836240[4] = -state[8];
   out_8908850792766836240[5] = state[7];
   out_8908850792766836240[6] = 0;
   out_8908850792766836240[7] = state[5];
   out_8908850792766836240[8] = -state[4];
   out_8908850792766836240[9] = 0;
   out_8908850792766836240[10] = 0;
   out_8908850792766836240[11] = 0;
   out_8908850792766836240[12] = 1;
   out_8908850792766836240[13] = 0;
   out_8908850792766836240[14] = 0;
   out_8908850792766836240[15] = 1;
   out_8908850792766836240[16] = 0;
   out_8908850792766836240[17] = 0;
   out_8908850792766836240[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8908850792766836240[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8908850792766836240[20] = 0;
   out_8908850792766836240[21] = state[8];
   out_8908850792766836240[22] = 0;
   out_8908850792766836240[23] = -state[6];
   out_8908850792766836240[24] = -state[5];
   out_8908850792766836240[25] = 0;
   out_8908850792766836240[26] = state[3];
   out_8908850792766836240[27] = 0;
   out_8908850792766836240[28] = 0;
   out_8908850792766836240[29] = 0;
   out_8908850792766836240[30] = 0;
   out_8908850792766836240[31] = 1;
   out_8908850792766836240[32] = 0;
   out_8908850792766836240[33] = 0;
   out_8908850792766836240[34] = 1;
   out_8908850792766836240[35] = 0;
   out_8908850792766836240[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8908850792766836240[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8908850792766836240[38] = 0;
   out_8908850792766836240[39] = -state[7];
   out_8908850792766836240[40] = state[6];
   out_8908850792766836240[41] = 0;
   out_8908850792766836240[42] = state[4];
   out_8908850792766836240[43] = -state[3];
   out_8908850792766836240[44] = 0;
   out_8908850792766836240[45] = 0;
   out_8908850792766836240[46] = 0;
   out_8908850792766836240[47] = 0;
   out_8908850792766836240[48] = 0;
   out_8908850792766836240[49] = 0;
   out_8908850792766836240[50] = 1;
   out_8908850792766836240[51] = 0;
   out_8908850792766836240[52] = 0;
   out_8908850792766836240[53] = 1;
}
void h_13(double *state, double *unused, double *out_3481125658308717604) {
   out_3481125658308717604[0] = state[3];
   out_3481125658308717604[1] = state[4];
   out_3481125658308717604[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8095869301567711863) {
   out_8095869301567711863[0] = 0;
   out_8095869301567711863[1] = 0;
   out_8095869301567711863[2] = 0;
   out_8095869301567711863[3] = 1;
   out_8095869301567711863[4] = 0;
   out_8095869301567711863[5] = 0;
   out_8095869301567711863[6] = 0;
   out_8095869301567711863[7] = 0;
   out_8095869301567711863[8] = 0;
   out_8095869301567711863[9] = 0;
   out_8095869301567711863[10] = 0;
   out_8095869301567711863[11] = 0;
   out_8095869301567711863[12] = 0;
   out_8095869301567711863[13] = 0;
   out_8095869301567711863[14] = 0;
   out_8095869301567711863[15] = 0;
   out_8095869301567711863[16] = 0;
   out_8095869301567711863[17] = 0;
   out_8095869301567711863[18] = 0;
   out_8095869301567711863[19] = 0;
   out_8095869301567711863[20] = 0;
   out_8095869301567711863[21] = 0;
   out_8095869301567711863[22] = 1;
   out_8095869301567711863[23] = 0;
   out_8095869301567711863[24] = 0;
   out_8095869301567711863[25] = 0;
   out_8095869301567711863[26] = 0;
   out_8095869301567711863[27] = 0;
   out_8095869301567711863[28] = 0;
   out_8095869301567711863[29] = 0;
   out_8095869301567711863[30] = 0;
   out_8095869301567711863[31] = 0;
   out_8095869301567711863[32] = 0;
   out_8095869301567711863[33] = 0;
   out_8095869301567711863[34] = 0;
   out_8095869301567711863[35] = 0;
   out_8095869301567711863[36] = 0;
   out_8095869301567711863[37] = 0;
   out_8095869301567711863[38] = 0;
   out_8095869301567711863[39] = 0;
   out_8095869301567711863[40] = 0;
   out_8095869301567711863[41] = 1;
   out_8095869301567711863[42] = 0;
   out_8095869301567711863[43] = 0;
   out_8095869301567711863[44] = 0;
   out_8095869301567711863[45] = 0;
   out_8095869301567711863[46] = 0;
   out_8095869301567711863[47] = 0;
   out_8095869301567711863[48] = 0;
   out_8095869301567711863[49] = 0;
   out_8095869301567711863[50] = 0;
   out_8095869301567711863[51] = 0;
   out_8095869301567711863[52] = 0;
   out_8095869301567711863[53] = 0;
}
void h_14(double *state, double *unused, double *out_1373823934019708509) {
   out_1373823934019708509[0] = state[6];
   out_1373823934019708509[1] = state[7];
   out_1373823934019708509[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8846836332574863591) {
   out_8846836332574863591[0] = 0;
   out_8846836332574863591[1] = 0;
   out_8846836332574863591[2] = 0;
   out_8846836332574863591[3] = 0;
   out_8846836332574863591[4] = 0;
   out_8846836332574863591[5] = 0;
   out_8846836332574863591[6] = 1;
   out_8846836332574863591[7] = 0;
   out_8846836332574863591[8] = 0;
   out_8846836332574863591[9] = 0;
   out_8846836332574863591[10] = 0;
   out_8846836332574863591[11] = 0;
   out_8846836332574863591[12] = 0;
   out_8846836332574863591[13] = 0;
   out_8846836332574863591[14] = 0;
   out_8846836332574863591[15] = 0;
   out_8846836332574863591[16] = 0;
   out_8846836332574863591[17] = 0;
   out_8846836332574863591[18] = 0;
   out_8846836332574863591[19] = 0;
   out_8846836332574863591[20] = 0;
   out_8846836332574863591[21] = 0;
   out_8846836332574863591[22] = 0;
   out_8846836332574863591[23] = 0;
   out_8846836332574863591[24] = 0;
   out_8846836332574863591[25] = 1;
   out_8846836332574863591[26] = 0;
   out_8846836332574863591[27] = 0;
   out_8846836332574863591[28] = 0;
   out_8846836332574863591[29] = 0;
   out_8846836332574863591[30] = 0;
   out_8846836332574863591[31] = 0;
   out_8846836332574863591[32] = 0;
   out_8846836332574863591[33] = 0;
   out_8846836332574863591[34] = 0;
   out_8846836332574863591[35] = 0;
   out_8846836332574863591[36] = 0;
   out_8846836332574863591[37] = 0;
   out_8846836332574863591[38] = 0;
   out_8846836332574863591[39] = 0;
   out_8846836332574863591[40] = 0;
   out_8846836332574863591[41] = 0;
   out_8846836332574863591[42] = 0;
   out_8846836332574863591[43] = 0;
   out_8846836332574863591[44] = 1;
   out_8846836332574863591[45] = 0;
   out_8846836332574863591[46] = 0;
   out_8846836332574863591[47] = 0;
   out_8846836332574863591[48] = 0;
   out_8846836332574863591[49] = 0;
   out_8846836332574863591[50] = 0;
   out_8846836332574863591[51] = 0;
   out_8846836332574863591[52] = 0;
   out_8846836332574863591[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_7620083208430612448) {
  err_fun(nom_x, delta_x, out_7620083208430612448);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5582676530876115798) {
  inv_err_fun(nom_x, true_x, out_5582676530876115798);
}
void pose_H_mod_fun(double *state, double *out_7715066790722213833) {
  H_mod_fun(state, out_7715066790722213833);
}
void pose_f_fun(double *state, double dt, double *out_3360399432308685597) {
  f_fun(state,  dt, out_3360399432308685597);
}
void pose_F_fun(double *state, double dt, double *out_3617201388683777182) {
  F_fun(state,  dt, out_3617201388683777182);
}
void pose_h_4(double *state, double *unused, double *out_795590817763196752) {
  h_4(state, unused, out_795590817763196752);
}
void pose_H_4(double *state, double *unused, double *out_6517119308839315729) {
  H_4(state, unused, out_6517119308839315729);
}
void pose_h_10(double *state, double *unused, double *out_3128038460922897567) {
  h_10(state, unused, out_3128038460922897567);
}
void pose_H_10(double *state, double *unused, double *out_8908850792766836240) {
  H_10(state, unused, out_8908850792766836240);
}
void pose_h_13(double *state, double *unused, double *out_3481125658308717604) {
  h_13(state, unused, out_3481125658308717604);
}
void pose_H_13(double *state, double *unused, double *out_8095869301567711863) {
  H_13(state, unused, out_8095869301567711863);
}
void pose_h_14(double *state, double *unused, double *out_1373823934019708509) {
  h_14(state, unused, out_1373823934019708509);
}
void pose_H_14(double *state, double *unused, double *out_8846836332574863591) {
  H_14(state, unused, out_8846836332574863591);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
