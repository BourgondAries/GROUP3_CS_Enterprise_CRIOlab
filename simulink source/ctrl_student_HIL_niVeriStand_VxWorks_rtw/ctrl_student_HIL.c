/*
 * ctrl_student_HIL.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ctrl_student_HIL".
 *
<<<<<<< HEAD
 * Model version              : 1.85
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Mon Mar 20 17:42:15 2017
=======
 * Model version              : 1.159
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Thu Mar 09 17:27:09 2017
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ctrl_student_HIL.h"
#include "ctrl_student_HIL_private.h"

const real_T ctrl_student_HIL_RGND = 0.0;/* real_T ground */

/* Block signals (auto storage) */
B_ctrl_student_HIL_T ctrl_student_HIL_B;

/* Block states (auto storage) */
DW_ctrl_student_HIL_T ctrl_student_HIL_DW;

/* Real-time model */
RT_MODEL_ctrl_student_HIL_T ctrl_student_HIL_M_;
RT_MODEL_ctrl_student_HIL_T *const ctrl_student_HIL_M = &ctrl_student_HIL_M_;
real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T lo;
  uint32_T hi;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T y;
  real_T sr;
  real_T si;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

/* Model output function */
static void ctrl_student_HIL_output(void)
{
<<<<<<< HEAD
  /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
   *  Constant: '<S1>/Step size'
   *  Memory: '<S4>/counter'
   */
  /* MATLAB Function 'Noise generator/Downsample	signal/MATLAB Function': '<S7>:1' */
  /* '<S7>:1:3' */
  if ((ctrl_student_HIL_DW.counter_PreviousInput + 1.0) *
      ctrl_student_HIL_P.Stepsize_Value >= (rtInf)) {
    /* '<S7>:1:4' */
    /* '<S7>:1:5' */
    ctrl_student_HIL_B.count = 0.0;
  } else {
    /* '<S7>:1:7' */
    ctrl_student_HIL_B.count = ctrl_student_HIL_DW.counter_PreviousInput + 1.0;
  }

  /* End of MATLAB Function: '<S4>/MATLAB Function' */

  /* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
   *  Constant: '<S1>/Step size'
   *  Memory: '<S5>/Hold'
   *  Product: '<S10>/Divide'
   *  Product: '<S10>/Product'
   *  Product: '<S11>/Divide'
   *  Product: '<S11>/Product'
   *  Product: '<S9>/Divide'
   *  Product: '<S9>/Product'
   *  RandomNumber: '<S10>/White Noise'
   *  RandomNumber: '<S11>/White Noise'
   *  RandomNumber: '<S9>/White Noise'
   *  Sqrt: '<S10>/Sqrt'
   *  Sqrt: '<S11>/Sqrt'
   *  Sqrt: '<S9>/Sqrt'
   *  Sum: '<S1>/Sum'
   */
  /* MATLAB Function 'Noise generator/Sample & hold/MATLAB Function1': '<S8>:1' */
  if (ctrl_student_HIL_B.count == 0.0) {
    /* '<S8>:1:4' */
    /* '<S8>:1:5' */
    ctrl_student_HIL_B.output[0] = sqrt(0.0 / ctrl_student_HIL_P.Stepsize_Value)
      * ctrl_student_HIL_DW.NextOutput + ctrl_student_HIL_B.x_in;
    ctrl_student_HIL_B.output[1] = sqrt(0.0 / ctrl_student_HIL_P.Stepsize_Value)
      * ctrl_student_HIL_DW.NextOutput_c + ctrl_student_HIL_B.y_in;
    ctrl_student_HIL_B.output[2] = sqrt(0.0 / ctrl_student_HIL_P.Stepsize_Value)
      * ctrl_student_HIL_DW.NextOutput_p + ctrl_student_HIL_B.psi_in;
  } else {
    /* '<S8>:1:7' */
    ctrl_student_HIL_B.output[0] = ctrl_student_HIL_DW.Hold_PreviousInput[0];
    ctrl_student_HIL_B.output[1] = ctrl_student_HIL_DW.Hold_PreviousInput[1];
    ctrl_student_HIL_B.output[2] = ctrl_student_HIL_DW.Hold_PreviousInput[2];
  }

  /* End of MATLAB Function: '<S5>/MATLAB Function1' */
=======
  real_T L1[9];
  real_T L2[9];
  real_T L3[9];
  real_T R[9];
  static const real_T a[9] = { 0.059559261465157838, -0.0, 0.0, -0.0,
    0.04052100686778741, -0.0081423733365488769, -0.0, -0.0081423733365488769,
    0.36395498559871381 };

  static const real_T b_a[9] = { -4.088, -0.0, -0.0, -0.0, -68.211, -0.0788,
    -0.0, -0.0, -1.07 };

  int32_T i;
  real_T R_0[3];
  real_T L1_0[3];
  int32_T i_0;
  real_T b_a_0[3];
  real_T eta_bar_idx_0;
  real_T eta_bar_idx_1;
  real_T eta_bar_idx_2;
  real_T eta_idx_2;
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* set solver stop time */
    if (!(ctrl_student_HIL_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&ctrl_student_HIL_M->solverInfo,
                            ((ctrl_student_HIL_M->Timing.clockTickH0 + 1) *
        ctrl_student_HIL_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&ctrl_student_HIL_M->solverInfo,
                            ((ctrl_student_HIL_M->Timing.clockTick0 + 1) *
        ctrl_student_HIL_M->Timing.stepSize0 +
        ctrl_student_HIL_M->Timing.clockTickH0 *
        ctrl_student_HIL_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(ctrl_student_HIL_M)) {
    ctrl_student_HIL_M->Timing.t[0] = rtsiGetT(&ctrl_student_HIL_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<S2>/Step size'
     *  Memory: '<S6>/counter'
     */
    /* MATLAB Function 'Noise generator/Downsample	signal/MATLAB Function': '<S9>:1' */
    /* '<S9>:1:3' */
    if ((ctrl_student_HIL_DW.counter_PreviousInput + 1.0) *
        ctrl_student_HIL_P.Stepsize_Value >= 1.0 /
        ctrl_student_HIL_P.Constant4_Value) {
      /* '<S9>:1:4' */
      /* '<S9>:1:5' */
      ctrl_student_HIL_B.count = 0.0;
    } else {
      /* '<S9>:1:7' */
      ctrl_student_HIL_B.count = ctrl_student_HIL_DW.counter_PreviousInput + 1.0;
    }

    /* End of MATLAB Function: '<S6>/MATLAB Function' */
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* RandomNumber: '<S12>/White Noise' */
    ctrl_student_HIL_B.WhiteNoise = ctrl_student_HIL_DW.NextOutput;

    /* RandomNumber: '<S13>/White Noise' */
    ctrl_student_HIL_B.WhiteNoise_e = ctrl_student_HIL_DW.NextOutput_c;
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* RandomNumber: '<S11>/White Noise' */
    ctrl_student_HIL_B.WhiteNoise_m = ctrl_student_HIL_DW.NextOutput_p;
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Memory: '<S7>/Hold' */
    ctrl_student_HIL_B.Hold[0] = ctrl_student_HIL_DW.Hold_PreviousInput[0];
    ctrl_student_HIL_B.Hold[1] = ctrl_student_HIL_DW.Hold_PreviousInput[1];
    ctrl_student_HIL_B.Hold[2] = ctrl_student_HIL_DW.Hold_PreviousInput[2];
  }

  /* MATLAB Function: '<S7>/MATLAB Function1' incorporates:
   *  Constant: '<S2>/Step size'
   *  Product: '<S11>/Divide'
   *  Product: '<S11>/Product'
   *  Product: '<S12>/Divide'
   *  Product: '<S12>/Product'
   *  Product: '<S13>/Divide'
   *  Product: '<S13>/Product'
   *  Sqrt: '<S11>/Sqrt'
   *  Sqrt: '<S12>/Sqrt'
   *  Sqrt: '<S13>/Sqrt'
   *  Sum: '<S2>/Sum'
   */
  /* MATLAB Function 'Noise generator/Sample & hold/MATLAB Function1': '<S10>:1' */
  if (ctrl_student_HIL_B.count == 0.0) {
    /* '<S10>:1:4' */
    /* '<S10>:1:5' */
    ctrl_student_HIL_B.output[0] = sqrt(ctrl_student_HIL_B.Noisepowerpos /
      ctrl_student_HIL_P.Stepsize_Value) * ctrl_student_HIL_B.WhiteNoise +
      ctrl_student_HIL_B.x_in;
    ctrl_student_HIL_B.output[1] = sqrt(ctrl_student_HIL_B.Noisepowerpos /
      ctrl_student_HIL_P.Stepsize_Value) * ctrl_student_HIL_B.WhiteNoise_e +
      ctrl_student_HIL_B.y_in;
    ctrl_student_HIL_B.output[2] = sqrt(ctrl_student_HIL_B.Noiseposerhead /
      ctrl_student_HIL_P.Stepsize_Value) * ctrl_student_HIL_B.WhiteNoise_m +
      ctrl_student_HIL_B.psi_in;
  } else {
    /* '<S10>:1:7' */
    ctrl_student_HIL_B.output[0] = ctrl_student_HIL_B.Hold[0];
    ctrl_student_HIL_B.output[1] = ctrl_student_HIL_B.Hold[1];
    ctrl_student_HIL_B.output[2] = ctrl_student_HIL_B.Hold[2];
  }

  /* End of MATLAB Function: '<S7>/MATLAB Function1' */

  /* Switch: '<S2>/Switch' */
  if (ctrl_student_HIL_B.Enablenoise != 0.0) {
    ctrl_student_HIL_B.Switch[0] = ctrl_student_HIL_B.output[0];
    ctrl_student_HIL_B.Switch[1] = ctrl_student_HIL_B.output[1];
    ctrl_student_HIL_B.Switch[2] = ctrl_student_HIL_B.output[2];
  } else {
    ctrl_student_HIL_B.Switch[0] = ctrl_student_HIL_B.x_in;
    ctrl_student_HIL_B.Switch[1] = ctrl_student_HIL_B.y_in;
    ctrl_student_HIL_B.Switch[2] = ctrl_student_HIL_B.psi_in;
  }

  /* End of Switch: '<S2>/Switch' */
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
  }

  /* Integrator: '<S1>/Integrator' */
  ctrl_student_HIL_B.Integrator[0] = ctrl_student_HIL_X.Integrator_CSTATE[0];
  ctrl_student_HIL_B.Integrator[1] = ctrl_student_HIL_X.Integrator_CSTATE[1];
  ctrl_student_HIL_B.Integrator[2] = ctrl_student_HIL_X.Integrator_CSTATE[2];

  /* Integrator: '<S1>/Integrator1' */
  ctrl_student_HIL_B.Integrator1[0] = ctrl_student_HIL_X.Integrator1_CSTATE[0];
  ctrl_student_HIL_B.Integrator1[1] = ctrl_student_HIL_X.Integrator1_CSTATE[1];
  ctrl_student_HIL_B.Integrator1[2] = ctrl_student_HIL_X.Integrator1_CSTATE[2];
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Memory: '<S1>/Memory4' */
    ctrl_student_HIL_B.Memory4[0] = ctrl_student_HIL_DW.Memory4_PreviousInput[0];
    ctrl_student_HIL_B.Memory4[1] = ctrl_student_HIL_DW.Memory4_PreviousInput[1];
    ctrl_student_HIL_B.Memory4[2] = ctrl_student_HIL_DW.Memory4_PreviousInput[2];

    /* Memory: '<S1>/Memory3' */
    ctrl_student_HIL_B.Memory3[0] = ctrl_student_HIL_DW.Memory3_PreviousInput[0];
    ctrl_student_HIL_B.Memory3[1] = ctrl_student_HIL_DW.Memory3_PreviousInput[1];
    ctrl_student_HIL_B.Memory3[2] = ctrl_student_HIL_DW.Memory3_PreviousInput[2];

    /* Memory: '<S1>/Memory2' */
    ctrl_student_HIL_B.Memory2[0] = ctrl_student_HIL_DW.Memory2_PreviousInput[0];
    ctrl_student_HIL_B.Memory2[1] = ctrl_student_HIL_DW.Memory2_PreviousInput[1];
    ctrl_student_HIL_B.Memory2[2] = ctrl_student_HIL_DW.Memory2_PreviousInput[2];
  }

  /* MATLAB Function: '<S1>/Observer ' */
  eta_bar_idx_1 = ctrl_student_HIL_B.Switch[0];
  eta_bar_idx_2 = ctrl_student_HIL_B.Switch[1];
  eta_idx_2 = ctrl_student_HIL_B.Switch[2];

  /* MATLAB Function 'DP Observer /Observer ': '<S5>:1' */
  /*  if(first == 1) */
  /*  eta_hat = zeros(3,1) ;  */
  /*  nu_hat = zeros(3,1);  */
  /*  b_hau = zeros(3,1) */
  /*  first_out = 0;  */
  /*  end */
  /* '<S5>:1:8' */
  for (i = 0; i < 9; i++) {
    L1[i] = 0.0;
    L2[i] = 0.0;
    L3[i] = 0.0;
  }

  L1[0] = ctrl_student_HIL_B.L1_diag[0];
  L1[4] = ctrl_student_HIL_B.L1_diag[1];
  L1[8] = ctrl_student_HIL_B.L1_diag[2];

  /* '<S5>:1:9' */
  L2[0] = ctrl_student_HIL_B.L2_diag[0];
  L2[4] = ctrl_student_HIL_B.L2_diag[1];
  L2[8] = ctrl_student_HIL_B.L2_diag[2];

  /* '<S5>:1:10' */
  L3[0] = ctrl_student_HIL_B.L3_diag[0];
  L3[4] = ctrl_student_HIL_B.L3_diag[1];
  L3[8] = ctrl_student_HIL_B.L3_diag[2];

  /* '<S5>:1:12' */
  /*  The total damping matrix from the handbook page 53 */
  if (!(1.0 - ctrl_student_HIL_B.signalloss != 0.0)) {
    /* '<S5>:1:17' */
    /* '<S5>:1:18' */
    eta_bar_idx_1 = ctrl_student_HIL_B.Memory4[0];
    eta_bar_idx_2 = ctrl_student_HIL_B.Memory4[1];
    eta_idx_2 = ctrl_student_HIL_B.Memory4[2];
  }

  /* '<S5>:1:22' */
  eta_bar_idx_0 = eta_bar_idx_1 - ctrl_student_HIL_B.Memory4[0];
  eta_bar_idx_1 = eta_bar_idx_2 - ctrl_student_HIL_B.Memory4[1];
  eta_bar_idx_2 = eta_idx_2 - ctrl_student_HIL_B.Memory4[2];

  /* '<S5>:1:23' */
  ctrl_student_HIL_B.x_bar = eta_bar_idx_0;

  /* '<S5>:1:24' */
  ctrl_student_HIL_B.y_bar = eta_bar_idx_1;

  /* '<S5>:1:25' */
  ctrl_student_HIL_B.psi_bar = eta_bar_idx_2;

  /* '<S5>:1:26' */
  /* '<S5>:1:27' */
  R[0] = cos(eta_idx_2);
  R[3] = sin(eta_idx_2);
  R[6] = 0.0;
  R[1] = -sin(eta_idx_2);
  R[4] = cos(eta_idx_2);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* '<S5>:1:31' */
  /* '<S5>:1:32' */
  for (i = 0; i < 3; i++) {
    R_0[i] = R[i + 6] * ctrl_student_HIL_B.Memory3[2] + (R[i + 3] *
      ctrl_student_HIL_B.Memory3[1] + R[i] * ctrl_student_HIL_B.Memory3[0]);
  }

  for (i = 0; i < 3; i++) {
    L1_0[i] = L1[i + 6] * eta_bar_idx_2 + (L1[i + 3] * eta_bar_idx_1 + L1[i] *
      eta_bar_idx_0);
  }

  ctrl_student_HIL_B.eta_hat_dot[0] = R_0[0] + L1_0[0];
  ctrl_student_HIL_B.eta_hat_dot[1] = R_0[1] + L1_0[1];
  ctrl_student_HIL_B.eta_hat_dot[2] = R_0[2] + L1_0[2];

  /* '<S5>:1:34' */
  for (i = 0; i < 3; i++) {
    ctrl_student_HIL_B.b_hat_dot[i] = ((L3[i + 3] * eta_bar_idx_1 + L3[i] *
      eta_bar_idx_0) + L3[i + 6] * eta_bar_idx_2) + ctrl_student_HIL_B.b;
  }

  for (i = 0; i < 3; i++) {
    L1_0[i] = b_a[i + 6] * ctrl_student_HIL_B.Memory3[2] + (b_a[i + 3] *
      ctrl_student_HIL_B.Memory3[1] + b_a[i] * ctrl_student_HIL_B.Memory3[0]);
  }

  for (i = 0; i < 3; i++) {
    R_0[i] = R[3 * i + 2] * ctrl_student_HIL_B.Memory2[2] + (R[3 * i + 1] *
      ctrl_student_HIL_B.Memory2[1] + R[3 * i] * ctrl_student_HIL_B.Memory2[0]);
  }

  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      L1[i + 3 * i_0] = 0.0;
      L1[i + 3 * i_0] += R[3 * i] * L2[3 * i_0];
      L1[i + 3 * i_0] += R[3 * i + 1] * L2[3 * i_0 + 1];
      L1[i + 3 * i_0] += R[3 * i + 2] * L2[3 * i_0 + 2];
    }
  }

  for (i = 0; i < 3; i++) {
    b_a_0[i] = ((L1[i + 3] * eta_bar_idx_1 + L1[i] * eta_bar_idx_0) + L1[i + 6] *
                eta_bar_idx_2) + ((L1_0[i] + R_0[i]) +
      ctrl_student_HIL_B.PosXRight);
  }

  for (i = 0; i < 3; i++) {
    ctrl_student_HIL_B.nu_hat_dot[i] = 0.0;
    ctrl_student_HIL_B.nu_hat_dot[i] += a[i] * b_a_0[0];
    ctrl_student_HIL_B.nu_hat_dot[i] += a[i + 3] * b_a_0[1];
    ctrl_student_HIL_B.nu_hat_dot[i] += a[i + 6] * b_a_0[2];
  }

  /* End of MATLAB Function: '<S1>/Observer ' */

  /* Integrator: '<S1>/Integrator2' */
  ctrl_student_HIL_B.Integrator2[0] = ctrl_student_HIL_X.Integrator2_CSTATE[0];
  ctrl_student_HIL_B.Integrator2[1] = ctrl_student_HIL_X.Integrator2_CSTATE[1];
  ctrl_student_HIL_B.Integrator2[2] = ctrl_student_HIL_X.Integrator2_CSTATE[2];
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Sum: '<Root>/Sum' */
    ctrl_student_HIL_B.Sum = ctrl_student_HIL_B.L2_continuous -
      ctrl_student_HIL_B.R2_continuous;
  }
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
}

/* Model update function */
static void ctrl_student_HIL_update(void)
{
  /* Update for Memory: '<S4>/counter' */
  ctrl_student_HIL_DW.counter_PreviousInput = ctrl_student_HIL_B.count;

  /* Update for Memory: '<S5>/Hold' */
  ctrl_student_HIL_DW.Hold_PreviousInput[0] = ctrl_student_HIL_B.output[0];
  ctrl_student_HIL_DW.Hold_PreviousInput[1] = ctrl_student_HIL_B.output[1];
  ctrl_student_HIL_DW.Hold_PreviousInput[2] = ctrl_student_HIL_B.output[2];

  /* Update for RandomNumber: '<S10>/White Noise' */
  ctrl_student_HIL_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
    (&ctrl_student_HIL_DW.RandSeed) * ctrl_student_HIL_P.WhiteNoise_StdDev +
    ctrl_student_HIL_P.WhiteNoise_Mean;

  /* Update for RandomNumber: '<S11>/White Noise' */
  ctrl_student_HIL_DW.NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf
    (&ctrl_student_HIL_DW.RandSeed_j) * ctrl_student_HIL_P.WhiteNoise_StdDev_d +
    ctrl_student_HIL_P.WhiteNoise_Mean_h;

  /* Update for RandomNumber: '<S9>/White Noise' */
  ctrl_student_HIL_DW.NextOutput_p = rt_nrand_Upu32_Yd_f_pw_snf
    (&ctrl_student_HIL_DW.RandSeed_c) * ctrl_student_HIL_P.WhiteNoise_StdDev_g +
    ctrl_student_HIL_P.WhiteNoise_Mean_f;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++ctrl_student_HIL_M->Timing.clockTick0)) {
    ++ctrl_student_HIL_M->Timing.clockTickH0;
  }

  ctrl_student_HIL_M->Timing.t[0] = ctrl_student_HIL_M->Timing.clockTick0 *
    ctrl_student_HIL_M->Timing.stepSize0 +
    ctrl_student_HIL_M->Timing.clockTickH0 *
    ctrl_student_HIL_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
static void ctrl_student_HIL_initialize(void)
{
  {
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T tmp;

    /* InitializeConditions for Memory: '<S4>/counter' */
    ctrl_student_HIL_DW.counter_PreviousInput = ctrl_student_HIL_P.counter_X0;

    /* InitializeConditions for Memory: '<S5>/Hold' */
    ctrl_student_HIL_DW.Hold_PreviousInput[0] = ctrl_student_HIL_P.Hold_X0;
    ctrl_student_HIL_DW.Hold_PreviousInput[1] = ctrl_student_HIL_P.Hold_X0;
    ctrl_student_HIL_DW.Hold_PreviousInput[2] = ctrl_student_HIL_P.Hold_X0;

    /* InitializeConditions for RandomNumber: '<S10>/White Noise' */
    tmp = floor(ctrl_student_HIL_P.WhiteNoise_Seed);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + t) << 16U) + t) + r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    ctrl_student_HIL_DW.RandSeed = tseed;
    ctrl_student_HIL_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&ctrl_student_HIL_DW.RandSeed) * ctrl_student_HIL_P.WhiteNoise_StdDev +
      ctrl_student_HIL_P.WhiteNoise_Mean;

    /* End of InitializeConditions for RandomNumber: '<S10>/White Noise' */

    /* InitializeConditions for RandomNumber: '<S11>/White Noise' */
    tmp = floor(ctrl_student_HIL_P.WhiteNoise_Seed_b);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + t) << 16U) + t) + r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    ctrl_student_HIL_DW.RandSeed_j = tseed;
    ctrl_student_HIL_DW.NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf
      (&ctrl_student_HIL_DW.RandSeed_j) * ctrl_student_HIL_P.WhiteNoise_StdDev_d
      + ctrl_student_HIL_P.WhiteNoise_Mean_h;

    /* End of InitializeConditions for RandomNumber: '<S11>/White Noise' */

    /* InitializeConditions for RandomNumber: '<S9>/White Noise' */
    tmp = floor(ctrl_student_HIL_P.WhiteNoise_Seed_l);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 4.294967296E+9);
    }

    tseed = tmp < 0.0 ? (uint32_T)-(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
    r = (int32_T)(tseed >> 16U);
    t = (int32_T)(tseed & 32768U);
    tseed = ((((tseed - ((uint32_T)r << 16U)) + t) << 16U) + t) + r;
    if (tseed < 1U) {
      tseed = 1144108930U;
    } else {
      if (tseed > 2147483646U) {
        tseed = 2147483646U;
      }
    }

    ctrl_student_HIL_DW.RandSeed_c = tseed;
    ctrl_student_HIL_DW.NextOutput_p = rt_nrand_Upu32_Yd_f_pw_snf
      (&ctrl_student_HIL_DW.RandSeed_c) * ctrl_student_HIL_P.WhiteNoise_StdDev_g
      + ctrl_student_HIL_P.WhiteNoise_Mean_f;

    /* End of InitializeConditions for RandomNumber: '<S9>/White Noise' */
  }
}

/* Model terminate function */
static void ctrl_student_HIL_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  ctrl_student_HIL_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  ctrl_student_HIL_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  ctrl_student_HIL_initialize();
}

void MdlTerminate(void)
{
  ctrl_student_HIL_terminate();
}

/* Registration function */
RT_MODEL_ctrl_student_HIL_T *ctrl_student_HIL(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)ctrl_student_HIL_M, 0,
                sizeof(RT_MODEL_ctrl_student_HIL_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ctrl_student_HIL_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    ctrl_student_HIL_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ctrl_student_HIL_M->Timing.sampleTimes =
      (&ctrl_student_HIL_M->Timing.sampleTimesArray[0]);
    ctrl_student_HIL_M->Timing.offsetTimes =
      (&ctrl_student_HIL_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ctrl_student_HIL_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    ctrl_student_HIL_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(ctrl_student_HIL_M, &ctrl_student_HIL_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ctrl_student_HIL_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    ctrl_student_HIL_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ctrl_student_HIL_M, -1);
  ctrl_student_HIL_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    ctrl_student_HIL_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(ctrl_student_HIL_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(ctrl_student_HIL_M->rtwLogInfo, (NULL));
    rtliSetLogT(ctrl_student_HIL_M->rtwLogInfo, "tout");
    rtliSetLogX(ctrl_student_HIL_M->rtwLogInfo, "");
    rtliSetLogXFinal(ctrl_student_HIL_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(ctrl_student_HIL_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(ctrl_student_HIL_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(ctrl_student_HIL_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(ctrl_student_HIL_M->rtwLogInfo, 1);
    rtliSetLogY(ctrl_student_HIL_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(ctrl_student_HIL_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(ctrl_student_HIL_M->rtwLogInfo, (NULL));
  }

  ctrl_student_HIL_M->solverInfoPtr = (&ctrl_student_HIL_M->solverInfo);
  ctrl_student_HIL_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&ctrl_student_HIL_M->solverInfo, 0.01);
  rtsiSetSolverMode(&ctrl_student_HIL_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  ctrl_student_HIL_M->ModelData.blockIO = ((void *) &ctrl_student_HIL_B);
  (void) memset(((void *) &ctrl_student_HIL_B), 0,
                sizeof(B_ctrl_student_HIL_T));

  /* parameters */
  ctrl_student_HIL_M->ModelData.defaultParam = ((real_T *)&ctrl_student_HIL_P);

  /* states (dwork) */
  ctrl_student_HIL_M->ModelData.dwork = ((void *) &ctrl_student_HIL_DW);
  (void) memset((void *)&ctrl_student_HIL_DW, 0,
                sizeof(DW_ctrl_student_HIL_T));

  /* Initialize Sizes */
  ctrl_student_HIL_M->Sizes.numContStates = (0);/* Number of continuous states */
  ctrl_student_HIL_M->Sizes.numY = (0);/* Number of model outputs */
  ctrl_student_HIL_M->Sizes.numU = (0);/* Number of model inputs */
  ctrl_student_HIL_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
<<<<<<< HEAD
  ctrl_student_HIL_M->Sizes.numSampTimes = (1);/* Number of sample times */
  ctrl_student_HIL_M->Sizes.numBlocks = (49);/* Number of blocks */
  ctrl_student_HIL_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  ctrl_student_HIL_M->Sizes.numBlockPrms = (166);/* Sum of parameter "widths" */
=======
  ctrl_student_HIL_M->Sizes.numSampTimes = (2);/* Number of sample times */
  ctrl_student_HIL_M->Sizes.numBlocks = (80);/* Number of blocks */
  ctrl_student_HIL_M->Sizes.numBlockIO = (46);/* Number of block outputs */
  ctrl_student_HIL_M->Sizes.numBlockPrms = (299);/* Sum of parameter "widths" */
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
  return ctrl_student_HIL_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

/*========================================================================*
 * NI VeriStand Generated Code                                            *
 *========================================================================*
 * This file contains automatically generated code for functions
 * to update the inports and outports of a Simulink/Realtime Workshop
 * model. Calls to these functions should be made before each step is taken
 * (inports, call SetExternalInputs) and after each step is taken
 * (outports, call SetExternalOutputs.)
 */
#ifdef NI_ROOTMODEL_ctrl_student_HIL
#include "model_info.h"
#include <stddef.h>
#include <stdlib.h>
#include <float.h>

unsigned char ReadSideDirtyFlag = 0, WriteSideDirtyFlag = 0;
double NIRT_GetValueByDataType(void* ptr,int subindex, int type, int Complex)
{
  switch (type)
  {
   case 0:
    return (double)(((real_T*)ptr)[subindex]);

   case 1:
    return (double)(((real32_T*)ptr)[subindex]);

   case 2:
    return (double)(((int8_T*)ptr)[subindex]);

   case 3:
    return (double)(((uint8_T*)ptr)[subindex]);

   case 4:
    return (double)(((int16_T*)ptr)[subindex]);

   case 5:
    return (double)(((uint16_T*)ptr)[subindex]);

   case 6:
    return (double)(((int32_T*)ptr)[subindex]);

   case 7:
    return (double)(((uint32_T*)ptr)[subindex]);

   case 8:
    return (double)(((boolean_T*)ptr)[subindex]);

   case 10:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 13:
    return NIRT_GetValueByDataType(ptr,subindex,7,Complex);

   case 15:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 16:
    return NIRT_GetValueByDataType(ptr,subindex,6,Complex);

   case 17:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 18:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 19:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 24:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 25:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);
  }

  // return ((double *)ptr)[subindex];
  return rtNaN;
}

long NIRT_SetValueByDataType(void* ptr,int subindex, double value, int type, int
  Complex)
{
  //Complex is only used for R14.3 and down
  switch (type)
  {
   case 0:
    ((real_T *)ptr)[subindex] = (real_T)value;
    return NI_OK;

   case 1:
    ((real32_T *)ptr)[subindex] = (real32_T)value;
    return NI_OK;

   case 2:
    ((int8_T *)ptr)[subindex] = (int8_T)value;
    return NI_OK;

   case 3:
    ((uint8_T *)ptr)[subindex] = (uint8_T)value;
    return NI_OK;

   case 4:
    ((int16_T *)ptr)[subindex] = (int16_T)value;
    return NI_OK;

   case 5:
    ((uint16_T *)ptr)[subindex] = (uint16_T)value;
    return NI_OK;

   case 6:
    ((int32_T *)ptr)[subindex] = (int32_T)value;
    return NI_OK;

   case 7:
    ((uint32_T *)ptr)[subindex] = (uint32_T)value;
    return NI_OK;

   case 8:
    ((boolean_T *)ptr)[subindex] = (boolean_T)value;
    return NI_OK;

   case 10:
    //Type is renamed. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 13:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,7,Complex);

   case 15:
    //Type is enum. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 16:
    //Type is enum. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,6,Complex);

   case 17:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 18:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 24:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 25:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);
  }

  //No matching datatype conversion
  return NI_ERROR;
}

extern ctrl_student_HIL_rtModel *S;
extern _SITexportglobals SITexportglobals;
void SetExternalInputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

  // Noise power pos
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.Noisepowerpos, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // Noise poser head
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.Noiseposerhead, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // y_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.y_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // psi_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.psi_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // x_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.x_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

<<<<<<< HEAD
  // r_in
=======
  // Enable noise
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.Enablenoise, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // r_in
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.r_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // u_in
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.u_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // v_in
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.v_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // DP Observer /L1_diag
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.r_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // u_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.u_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // v_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.v_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // DP Observer /b
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.b, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // DP Observer /signal loss
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.signalloss, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/L2_continuous
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L2_continuous, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // joystick/PosXRight
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosXRight, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/PosYRight
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosYRight, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/R2_continuous
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.R2_continuous, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // joystick/PosXLeft
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosXLeft, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/PosYLeft
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosYLeft, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/L1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/R1
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.R1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/ArrowDown
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowDown, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/ArrowUp
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowUp, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/ArrowLeft
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowLeft, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/ArrowRight
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowRight, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
<<<<<<< HEAD
  return 18;
=======
  return 32;
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
}

double ni_extout[7];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

<<<<<<< HEAD
=======
  // x_m: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,0,17,
      0);
  } else {
    index += 1;
  }

  // psi_m: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,2,17,
      0);
  } else {
    index += 1;
  }

  // y_m: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,1,17,
      0);
  } else {
    index += 1;
  }

  // DP Observer /x_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,
      0,17,0);
  } else {
    index += 1;
  }

  // DP Observer /psi_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,
      2,17,0);
  } else {
    index += 1;
  }

  // DP Observer /y_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,
      1,17,0);
  } else {
    index += 1;
  }

  // DP Observer /r_dot: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator1,
      2,17,0);
  } else {
    index += 1;
  }

  // DP Observer /u_dot: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator1,
      0,17,0);
  } else {
    index += 1;
  }

  // DP Observer /v_dot: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator1,
      1,17,0);
  } else {
    index += 1;
  }

  // DP Observer /y_bar: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.y_bar,0,0,0);
  } else {
    index += 1;
  }

  // DP Observer /psi_bar: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.psi_bar,0,0,
      0);
  } else {
    index += 1;
  }

  // DP Observer /x_bar: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.x_bar,0,0,0);
  } else {
    index += 1;
  }

>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
  // tau to CSE mocell (only use for HIL testing)/X_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.PosXRight,0,
      0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/N_d: Virtual Signal # 0
<<<<<<< HEAD
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType((real_T*)&ctrl_student_HIL_RGND,
      0,0,0);
=======
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Sum,0,0,0);
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/Y_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType((real_T*)&ctrl_student_HIL_RGND,
      0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/psi_0 : Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_P.Constant2_Value,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/x_0: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_P.Constant_Value,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/y_0: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_P.Constant1_Value,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/integrator reset model: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType((real_T*)&ctrl_student_HIL_RGND,
      0,0,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 7;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

<<<<<<< HEAD
=======
  // x_m: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,0,17,0);

  // psi_m: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,2,17,0);

  // y_m: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,1,17,0);

  // DP Observer /x_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,0,
    17,0);

  // DP Observer /psi_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,2,
    17,0);

  // DP Observer /y_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,1,
    17,0);

  // DP Observer /r_dot: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator1,2,
    17,0);

  // DP Observer /u_dot: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator1,0,
    17,0);

  // DP Observer /v_dot: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator1,1,
    17,0);

  // DP Observer /y_bar: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.y_bar,0,0,0);

  // DP Observer /psi_bar: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.psi_bar,0,0,0);

  // DP Observer /x_bar: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.x_bar,0,0,0);

>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
  // tau to CSE mocell (only use for HIL testing)/X_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.PosXRight,0,0,
    0);

  // tau to CSE mocell (only use for HIL testing)/N_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Sum,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/Y_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType((real_T*)&ctrl_student_HIL_RGND,0,
    0,0);

  // tau to CSE mocell (only use for HIL testing)/psi_0 : Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant2_Value,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/x_0: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant_Value,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/y_0: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant1_Value,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/integrator reset model: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType((real_T*)&ctrl_student_HIL_RGND,0,
    0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_student_hil/Noise generator/Step size/Value", offsetof
    (P_ctrl_student_HIL_T, Stepsize_Value), 24, 1, 2, 0, 0 },

  { 1, "ctrl_student_hil/Noise generator/Downsamplesignal/counter/X0", offsetof
    (P_ctrl_student_HIL_T, counter_X0), 24, 1, 2, 2, 0 },

  { 2, "ctrl_student_hil/Noise generator/Sample & hold/Hold/X0", offsetof
    (P_ctrl_student_HIL_T, Hold_X0), 24, 1, 2, 4, 0 },

  { 3,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/Mean",
<<<<<<< HEAD
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean), 24, 1, 2, 6, 0 },

  { 4,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev), 24, 1, 2, 8, 0 },

  { 5,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed), 24, 1, 2, 10, 0 },

  { 6,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/Mean",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean_h), 24, 1, 2, 12, 0 },

  { 7,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev_d), 24, 1, 2, 14, 0 },

  { 8,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed_b), 24, 1, 2, 16, 0 },

  { 9,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/Mean",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean_f), 24, 1, 2, 18, 0 },

  { 10,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev_g), 24, 1, 2, 20, 0 },

  { 11,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed_l), 24, 1, 2, 22, 0 },

  { 12,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant2/Value",
    offsetof(P_ctrl_student_HIL_T, Constant2_Value), 24, 1, 2, 24, 0 },

  { 13,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant/Value",
    offsetof(P_ctrl_student_HIL_T, Constant_Value), 24, 1, 2, 26, 0 },

  { 14,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant1/Value",
    offsetof(P_ctrl_student_HIL_T, Constant1_Value), 24, 1, 2, 28, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 15;
=======
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean), 29, 1, 2, 6, 0 },

  { 4,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev), 29, 1, 2, 8, 0 },

  { 5,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed), 29, 1, 2, 10, 0 },

  { 6,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/Mean",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean_h), 29, 1, 2, 12, 0 },

  { 7,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev_d), 29, 1, 2, 14, 0 },

  { 8,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed_b), 29, 1, 2, 16, 0 },

  { 9,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/Mean",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean_f), 29, 1, 2, 18, 0 },

  { 10,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev_g), 29, 1, 2, 20, 0 },

  { 11,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed_l), 29, 1, 2, 22, 0 },

  { 12, "ctrl_student_hil/Noise generator/Sample & hold/Hold/X0", offsetof
    (P_ctrl_student_HIL_T, Hold_X0), 29, 1, 2, 24, 0 },

  { 13, "ctrl_student_hil/DP Observer /Integrator/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator_IC), 29, 1, 2, 26, 0 },

  { 14, "ctrl_student_hil/DP Observer /Integrator1/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator1_IC), 29, 1, 2, 28, 0 },

  { 15, "ctrl_student_hil/DP Observer /Memory4/X0", offsetof
    (P_ctrl_student_HIL_T, Memory4_X0), 18, 3, 2, 30, 0 },

  { 16, "ctrl_student_hil/DP Observer /Memory3/X0", offsetof
    (P_ctrl_student_HIL_T, Memory3_X0), 18, 3, 2, 32, 0 },

  { 17, "ctrl_student_hil/DP Observer /Memory2/X0", offsetof
    (P_ctrl_student_HIL_T, Memory2_X0), 18, 3, 2, 34, 0 },

  { 18, "ctrl_student_hil/DP Observer /Integrator2/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator2_IC), 29, 1, 2, 36, 0 },

  { 19,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant2/Value",
    offsetof(P_ctrl_student_HIL_T, Constant2_Value), 29, 1, 2, 38, 0 },

  { 20,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant/Value",
    offsetof(P_ctrl_student_HIL_T, Constant_Value), 29, 1, 2, 40, 0 },

  { 21,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant1/Value",
    offsetof(P_ctrl_student_HIL_T, Constant1_Value), 29, 1, 2, 42, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 22;
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
  1, 1,                                /* Parameter at index 1 */
  1, 1,                                /* Parameter at index 2 */
  1, 1,                                /* Parameter at index 3 */
  1, 1,                                /* Parameter at index 4 */
  1, 1,                                /* Parameter at index 5 */
  1, 1,                                /* Parameter at index 6 */
  1, 1,                                /* Parameter at index 7 */
  1, 1,                                /* Parameter at index 8 */
  1, 1,                                /* Parameter at index 9 */
  1, 1,                                /* Parameter at index 10 */
  1, 1,                                /* Parameter at index 11 */
  1, 1,                                /* Parameter at index 12 */
  1, 1,                                /* Parameter at index 13 */
  1, 1,                                /* Parameter at index 14 */
<<<<<<< HEAD
=======
  3, 1,                                /* Parameter at index 15 */
  3, 1,                                /* Parameter at index 16 */
  3, 1,                                /* Parameter at index 17 */
  1, 1,                                /* Parameter at index 18 */
  1, 1,                                /* Parameter at index 19 */
  1, 1,                                /* Parameter at index 20 */
  1, 1,                                /* Parameter at index 21 */
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
<<<<<<< HEAD
  { 0, "ctrl_student_hil/y_in", 0, "", offsetof(B_ctrl_student_HIL_T, y_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "ctrl_student_hil/psi_in", 0, "", offsetof(B_ctrl_student_HIL_T, psi_in)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2, "ctrl_student_hil/x_in", 0, "", offsetof(B_ctrl_student_HIL_T, x_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "ctrl_student_hil/r_in", 0, "", offsetof(B_ctrl_student_HIL_T, r_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4, "ctrl_student_hil/u_in", 0, "", offsetof(B_ctrl_student_HIL_T, u_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "ctrl_student_hil/v_in", 0, "", offsetof(B_ctrl_student_HIL_T, v_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "ctrl_student_hil/joystick/L2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, L2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    12, 0 },

  { 7, "ctrl_student_hil/joystick/PosXRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 14,
    0 },

  { 8, "ctrl_student_hil/joystick/PosYRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 16,
    0 },

  { 9, "ctrl_student_hil/joystick/R2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, R2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    18, 0 },

  { 10, "ctrl_student_hil/joystick/PosXLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 20,
    0 },

  { 11, "ctrl_student_hil/joystick/PosYLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 22,
    0 },

  { 12, "ctrl_student_hil/joystick/L1", 0, "", offsetof(B_ctrl_student_HIL_T, L1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "ctrl_student_hil/joystick/R1", 0, "", offsetof(B_ctrl_student_HIL_T, R1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "ctrl_student_hil/joystick/ArrowDown", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowDown)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 28,
    0 },

  { 15, "ctrl_student_hil/joystick/ArrowUp", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowUp)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 30,
    0 },

  { 16, "ctrl_student_hil/joystick/ArrowLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 32,
    0 },

  { 17, "ctrl_student_hil/joystick/ArrowRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    34, 0 },

  { 18, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,1)", offsetof(B_ctrl_student_HIL_T, output)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 36, 0 },

  { 19, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,2)", offsetof(B_ctrl_student_HIL_T, output)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 38, 0 },

  { 20, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,3)", offsetof(B_ctrl_student_HIL_T, output)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 40, 0 },

  { 21, "ctrl_student_hil/Noise generator/Downsamplesignal/MATLAB Function", 0,
    "count", offsetof(B_ctrl_student_HIL_T, count)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 42, 0 },
=======
  { 0, "ctrl_student_hil/Noise power pos", 0, "", offsetof(B_ctrl_student_HIL_T,
    Noisepowerpos)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise",
    0, "", offsetof(B_ctrl_student_HIL_T, WhiteNoise)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise",
    0, "", offsetof(B_ctrl_student_HIL_T, WhiteNoise_e)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "ctrl_student_hil/Noise poser head", 0, "", offsetof(B_ctrl_student_HIL_T,
    Noiseposerhead)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

  { 4,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise",
    0, "", offsetof(B_ctrl_student_HIL_T, WhiteNoise_m)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 8, 0 },

  { 5, "ctrl_student_hil/y_in", 0, "", offsetof(B_ctrl_student_HIL_T, y_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 10, 0 },

  { 6, "ctrl_student_hil/x_in", 0, "", offsetof(B_ctrl_student_HIL_T, x_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 12, 0 },

  { 7, "ctrl_student_hil/psi_in", 0, "", offsetof(B_ctrl_student_HIL_T, psi_in)+
    0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 14, 0 },

  { 8, "ctrl_student_hil/Noise generator/Sample & hold/Hold", 0, "(1,1)",
    offsetof(B_ctrl_student_HIL_T, Hold)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    16, 0 },

  { 9, "ctrl_student_hil/Noise generator/Sample & hold/Hold", 0, "(1,2)",
    offsetof(B_ctrl_student_HIL_T, Hold)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    18, 0 },

  { 10, "ctrl_student_hil/Noise generator/Sample & hold/Hold", 0, "(1,3)",
    offsetof(B_ctrl_student_HIL_T, Hold)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    20, 0 },

  { 11, "ctrl_student_hil/Enable noise", 0, "", offsetof(B_ctrl_student_HIL_T,
    Enablenoise)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "ctrl_student_hil/Noise generator/Switch", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Switch)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 24,
    0 },

  { 13, "ctrl_student_hil/Noise generator/Switch", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Switch)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 26,
    0 },

  { 14, "ctrl_student_hil/Noise generator/Switch", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Switch)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 28,
    0 },

  { 15, "ctrl_student_hil/r_in", 0, "", offsetof(B_ctrl_student_HIL_T, r_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "ctrl_student_hil/u_in", 0, "", offsetof(B_ctrl_student_HIL_T, u_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 32, 0 },

  { 17, "ctrl_student_hil/v_in", 0, "", offsetof(B_ctrl_student_HIL_T, v_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 34, 0 },

  { 18, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    36, 0 },

  { 19, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    38, 0 },

  { 20, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    40, 0 },

  { 21, "ctrl_student_hil/DP Observer /L1_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 42,
    0 },

  { 22, "ctrl_student_hil/DP Observer /L1_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 44,
    0 },

  { 23, "ctrl_student_hil/DP Observer /L1_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 46,
    0 },

  { 24, "ctrl_student_hil/DP Observer /L2_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 48,
    0 },

  { 25, "ctrl_student_hil/DP Observer /L2_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 50,
    0 },

  { 26, "ctrl_student_hil/DP Observer /L2_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 52,
    0 },

  { 27, "ctrl_student_hil/DP Observer /L3_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 54,
    0 },

  { 28, "ctrl_student_hil/DP Observer /L3_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 56,
    0 },

  { 29, "ctrl_student_hil/DP Observer /L3_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 58,
    0 },

  { 30, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    60, 0 },

  { 31, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    62, 0 },

  { 32, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    64, 0 },

  { 33, "ctrl_student_hil/DP Observer /b", 0, "", offsetof(B_ctrl_student_HIL_T,
    b)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 66, 0 },

  { 34, "ctrl_student_hil/DP Observer /signal loss", 0, "", offsetof
    (B_ctrl_student_HIL_T, signalloss)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    68, 0 },

  { 35, "ctrl_student_hil/joystick/L2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, L2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    70, 0 },

  { 36, "ctrl_student_hil/joystick/PosXRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 72,
    0 },

  { 37, "ctrl_student_hil/joystick/PosYRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 74,
    0 },

  { 38, "ctrl_student_hil/joystick/R2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, R2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    76, 0 },

  { 39, "ctrl_student_hil/joystick/PosXLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 78,
    0 },

  { 40, "ctrl_student_hil/joystick/PosYLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 80,
    0 },

  { 41, "ctrl_student_hil/joystick/L1", 0, "", offsetof(B_ctrl_student_HIL_T, L1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 82, 0 },

  { 42, "ctrl_student_hil/joystick/R1", 0, "", offsetof(B_ctrl_student_HIL_T, R1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 84, 0 },

  { 43, "ctrl_student_hil/joystick/ArrowDown", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowDown)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 86,
    0 },

  { 44, "ctrl_student_hil/joystick/ArrowUp", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowUp)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 88,
    0 },

  { 45, "ctrl_student_hil/joystick/ArrowLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 90,
    0 },

  { 46, "ctrl_student_hil/joystick/ArrowRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    92, 0 },

  { 47, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 94,
    0 },

  { 48, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 96,
    0 },

  { 49, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 98,
    0 },

  { 50, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 100,
    0 },

  { 51, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 102,
    0 },

  { 52, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 104,
    0 },

  { 53, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 106,
    0 },

  { 54, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 108,
    0 },

  { 55, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 110,
    0 },

  { 56, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    112, 0 },

  { 57, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    114, 0 },

  { 58, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    116, 0 },

  { 59, "ctrl_student_hil/Sum", 0, "", offsetof(B_ctrl_student_HIL_T, Sum)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 118, 0 },

  { 60, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,1)", offsetof(B_ctrl_student_HIL_T, output)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 120, 0 },

  { 61, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,2)", offsetof(B_ctrl_student_HIL_T, output)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 122, 0 },

  { 62, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,3)", offsetof(B_ctrl_student_HIL_T, output)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 124, 0 },

  { 63, "ctrl_student_hil/Noise generator/Downsamplesignal/MATLAB Function", 0,
    "count", offsetof(B_ctrl_student_HIL_T, count)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 126, 0 },

  { 64, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,1)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 128, 0 },

  { 65, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,2)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 130, 0 },

  { 66, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,3)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 132, 0 },

  { 67, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,1)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    134, 0 },

  { 68, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,2)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    136, 0 },

  { 69, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,3)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    138, 0 },

  { 70, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,1)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    140, 0 },

  { 71, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,2)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    142, 0 },

  { 72, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,3)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    144, 0 },

  { 73, "ctrl_student_hil/DP Observer /Observer", 3, "x_bar", offsetof
    (B_ctrl_student_HIL_T, x_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 146, 0
  },

  { 74, "ctrl_student_hil/DP Observer /Observer", 4, "y_bar", offsetof
    (B_ctrl_student_HIL_T, y_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 148, 0
  },

  { 75, "ctrl_student_hil/DP Observer /Observer", 5, "psi_bar", offsetof
    (B_ctrl_student_HIL_T, psi_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 150,
    0 },
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2

  { -1, "", -1, "", 0, 0, 0 }
};

<<<<<<< HEAD
static int NI_SigListSize DataSection(".NIVS.siglistsize") = 22;
=======
static int NI_SigListSize DataSection(".NIVS.siglistsize") = 76;
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
<<<<<<< HEAD
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 25;
=======
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 45;
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "Noise power pos", 0, EXT_IN, 1, 1, 1 },

  { 1, "Noise poser head", 0, EXT_IN, 1, 1, 1 },

  { 2, "y_in", 0, EXT_IN, 1, 1, 1 },

  { 3, "x_in", 0, EXT_IN, 1, 1, 1 },

  { 4, "psi_in", 0, EXT_IN, 1, 1, 1 },

  { 5, "Enable noise", 0, EXT_IN, 1, 1, 1 },

<<<<<<< HEAD
  { 1, "psi_in", 0, EXT_IN, 1, 1, 1 },

  { 2, "x_in", 0, EXT_IN, 1, 1, 1 },

  { 3, "r_in", 0, EXT_IN, 1, 1, 1 },

  { 4, "u_in", 0, EXT_IN, 1, 1, 1 },

  { 5, "v_in", 0, EXT_IN, 1, 1, 1 },

  { 6, "joystick/L2_continuous", 0, EXT_IN, 1, 1, 1 },
=======
  { 6, "r_in", 1, EXT_IN, 1, 1, 1 },

  { 7, "u_in", 1, EXT_IN, 1, 1, 1 },

  { 8, "v_in", 1, EXT_IN, 1, 1, 1 },

  { 9, "DP Observer /L1_diag", 0, EXT_IN, 3, 3, 1 },

  { 10, "DP Observer /L2_diag ", 0, EXT_IN, 3, 3, 1 },

  { 11, "DP Observer /L3_diag", 0, EXT_IN, 3, 3, 1 },
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2

  { 12, "DP Observer /b", 0, EXT_IN, 1, 1, 1 },

<<<<<<< HEAD
  { 8, "joystick/PosYRight", 0, EXT_IN, 1, 1, 1 },

  { 9, "joystick/R2_continuous", 0, EXT_IN, 1, 1, 1 },
=======
  { 13, "DP Observer /signal loss", 0, EXT_IN, 1, 1, 1 },

  { 14, "joystick/L2_continuous", 1, EXT_IN, 1, 1, 1 },

  { 15, "joystick/PosXRight", 0, EXT_IN, 1, 1, 1 },

  { 16, "joystick/PosYRight", 1, EXT_IN, 1, 1, 1 },

  { 17, "joystick/R2_continuous", 1, EXT_IN, 1, 1, 1 },

  { 18, "joystick/PosXLeft", 1, EXT_IN, 1, 1, 1 },

  { 19, "joystick/PosYLeft", 1, EXT_IN, 1, 1, 1 },

  { 20, "joystick/L1", 1, EXT_IN, 1, 1, 1 },

  { 21, "joystick/R1", 1, EXT_IN, 1, 1, 1 },

  { 22, "joystick/ArrowDown", 1, EXT_IN, 1, 1, 1 },

  { 23, "joystick/ArrowUp", 1, EXT_IN, 1, 1, 1 },

  { 24, "joystick/ArrowLeft", 1, EXT_IN, 1, 1, 1 },

  { 25, "joystick/ArrowRight", 1, EXT_IN, 1, 1, 1 },
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2

  { 10, "joystick/PosXLeft", 0, EXT_IN, 1, 1, 1 },

  { 11, "joystick/PosYLeft", 0, EXT_IN, 1, 1, 1 },

<<<<<<< HEAD
  { 12, "joystick/L1", 0, EXT_IN, 1, 1, 1 },

  { 13, "joystick/R1", 0, EXT_IN, 1, 1, 1 },

  { 14, "joystick/ArrowDown", 0, EXT_IN, 1, 1, 1 },

  { 15, "joystick/ArrowUp", 0, EXT_IN, 1, 1, 1 },

  { 16, "joystick/ArrowLeft", 0, EXT_IN, 1, 1, 1 },

  { 17, "joystick/ArrowRight", 0, EXT_IN, 1, 1, 1 },

  { 0, "tau to CSE mocell (only use for HIL testing)/X_d", 0, EXT_OUT, 1, 1, 1 },

  { 1, "tau to CSE mocell (only use for HIL testing)/N_d", 0, EXT_OUT, 1, 1, 1 },

  { 2, "tau to CSE mocell (only use for HIL testing)/Y_d", 0, EXT_OUT, 1, 1, 1 },

  { 3, "tau to CSE mocell (only use for HIL testing)/psi_0 ", 0, EXT_OUT, 1, 1,
    1 },

  { 4, "tau to CSE mocell (only use for HIL testing)/x_0", 0, EXT_OUT, 1, 1, 1 },

  { 5, "tau to CSE mocell (only use for HIL testing)/y_0", 0, EXT_OUT, 1, 1, 1 },

  { 6, "tau to CSE mocell (only use for HIL testing)/integrator reset model", 0,
=======
  { 2, "y_m", 0, EXT_OUT, 1, 1, 1 },

  { 3, "DP Observer /x_hat", 0, EXT_OUT, 1, 1, 1 },

  { 4, "DP Observer /psi_hat", 0, EXT_OUT, 1, 1, 1 },

  { 5, "DP Observer /y_hat", 0, EXT_OUT, 1, 1, 1 },

  { 6, "DP Observer /r_dot", 0, EXT_OUT, 1, 1, 1 },

  { 7, "DP Observer /u_dot", 0, EXT_OUT, 1, 1, 1 },

  { 8, "DP Observer /v_dot", 0, EXT_OUT, 1, 1, 1 },

  { 9, "DP Observer /y_bar", 0, EXT_OUT, 1, 1, 1 },

  { 10, "DP Observer /psi_bar", 0, EXT_OUT, 1, 1, 1 },

  { 11, "DP Observer /x_bar", 0, EXT_OUT, 1, 1, 1 },

  { 12, "tau to CSE mocell (only use for HIL testing)/X_d", 0, EXT_OUT, 1, 1, 1
  },

  { 13, "tau to CSE mocell (only use for HIL testing)/N_d", 1, EXT_OUT, 1, 1, 1
  },

  { 14, "tau to CSE mocell (only use for HIL testing)/Y_d", 1, EXT_OUT, 1, 1, 1
  },

  { 15, "tau to CSE mocell (only use for HIL testing)/psi_0 ", 1, EXT_OUT, 1, 1,
    1 },

  { 16, "tau to CSE mocell (only use for HIL testing)/x_0", 1, EXT_OUT, 1, 1, 1
  },

  { 17, "tau to CSE mocell (only use for HIL testing)/y_0", 1, EXT_OUT, 1, 1, 1
  },

  { 18, "tau to CSE mocell (only use for HIL testing)/integrator reset model", 1,
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    EXT_OUT, 1, 1, 1 },

  { -1, "", 0, 0, 0, 0, 0 }
};

/* This Task List is generated to allow access to the task specs without
 * initializing the model.
 * 0th entry is for scheduler (base rate)
 * rest for multirate model's tasks.
 */
NI_Task NI_TaskList[] DataSection(".NIVS.tasklist") =
{
  { 0, 0.01, 0 }
};

int NI_NumTasks DataSection(".NIVS.numtasks") = 1;
static char* NI_CompiledModelName DataSection(".NIVS.compiledmodelname") =
  "ctrl_student_hil";
<<<<<<< HEAD
static char* NI_CompiledModelVersion = "1.85";
static char* NI_CompiledModelDateTime = "Mon Mar 20 17:42:15 2017";
=======
static char* NI_CompiledModelVersion = "1.159";
static char* NI_CompiledModelDateTime = "Thu Mar 09 17:27:09 2017";
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
static char* NI_builder DataSection(".NIVS.builder") =
  "NI VeriStand 2014.0.0.82 (2014) RTW Build";
static char* NI_BuilderVersion DataSection(".NIVS.builderversion") =
  "2014.0.0.82";

/* Model Information Query fucntions for MATLAB
 */
/* dll information
 * Returns 1 for RTW DLL
 *		   2 for AutoCode DLL
 */
DLL_EXPORT long NIRT_GetBuildInfo(char* detail, long* len)
{
  // There are no console properties to set for VxWorks, because the console is simply serial output data.
  // Just do printf for VxWorks and ignore all console properties.
#if ! defined (VXWORKS) && ! defined (kNIOSLinux)

  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY | FOREGROUND_BLUE |
    FOREGROUND_GREEN | FOREGROUND_RED);

#endif

  printf("\n*******************************************************************************\n");
  printf("%s\nModel Name: %s\nModel Version: %s\nCompiled On: %s",
         NI_builder, NI_CompiledModelName, NI_CompiledModelVersion,
         NI_CompiledModelDateTime);
  printf("\n*******************************************************************************\n");

#if ! defined (VXWORKS) && ! defined (kNIOSLinux)

  SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN |
    FOREGROUND_RED);

#endif

  if (*len>=(long)strlen(NI_builder))
    *len = strlen(NI_builder)+1;
  strncpy(detail,NI_builder,*len);
  return 1;
}

/*
 * Distinction between Index and ID:
 * Index is a long datatype (used to set parameter/probe signals).
 * ID on the other hand is a string (tag "2-3-2-12" for MatrixX/ Full path "f14/Gain/Gain" for Matlab).
 * If Bus support is added then signal path from the block name is added to the end of the port number (Model/subsystem1:1/X/A)
 * where X/A is the path from the block
 * NOTE: ID may not be the same as Paramname or signal name.
 */

/* signal information
   NOTE: signal ID == the blockname and port that feeds it extended with /sinalname.

   The port number in Simulation Environment is 1 indexed.. but on RT is 0 indexed.
 */
DLL_EXPORT long NIRT_GetSignalSpec(long* sidx, char* ID, long* ID_len, char
  * blkname, long *bnlen,
  long *portnum, char* signame, long *snlen, long *dattype, long* dims, long
  * numdim)
{
  long sigidx = *sidx;
  int i = 0;
  char *IDblk = 0;
  int IDport = 0;
  if (sigidx<0) {
    // check if ID has been specified.
    if (ID && *ID_len>0) {
      // parse ID into blkname and port
      i = strrchr(ID, ':') - ID;

      // malformed ID
      if (i<=0)
        return NI_SigListSize;

      //ID[i] = 0;
      IDblk = ID;
      IDport = atoi(ID+i+1);

      // lookup the table for matching ID
      // Bus support
      for (i=0;i<NI_SigListSize;i++) {
        char *tempID = (char *)calloc(strlen(NI_SigList[i].blockname)+strlen
          (NI_SigList[i].signalname)+ 11, sizeof(char));

        //sprintf(tempID,"%s%s%s",NI_SigList[i].blockname,"/",NI_SigList[i].signalname);
        if (strlen(NI_SigList[i].signalname)>0)
          sprintf(tempID,"%s:%d%s%s",NI_SigList[i].blockname,NI_SigList[i].
                  portno+1,"/",NI_SigList[i].signalname);
        else
          sprintf(tempID,"%s:%d",NI_SigList[i].blockname,NI_SigList[i].portno+1);
        if (!strcmp(IDblk,tempID) && IDport==(NI_SigList[i].portno+1))
          break;
        free(tempID);
      }

      if (i<NI_SigListSize)
        sigidx = *sidx = i;
      else
        return NI_SigListSize;
    } else                             // no index or ID specified.
      return NI_SigListSize;
  }

  if (sigidx>=0 && sigidx<NI_SigListSize) {
    if (ID) {
      // no need for return string to be null terminated!
      // 11 to accomodate ':','/', port number and null character
      char *tempID = (char *)calloc(strlen(NI_SigList[sigidx].blockname)+strlen
        (NI_SigList[sigidx].signalname)+ 11, sizeof(char));
      if (strlen(NI_SigList[sigidx].signalname)>0)
        sprintf(tempID,"%s:%d%s%s",NI_SigList[sigidx].blockname,
                NI_SigList[sigidx].portno+1,"/",NI_SigList[sigidx].signalname);
      else
        sprintf(tempID,"%s:%d",NI_SigList[sigidx].blockname,NI_SigList[sigidx].
                portno+1);
      if ((long)strlen(tempID)<*ID_len)
        *ID_len = strlen(tempID);
      strncpy(ID, tempID, *ID_len);
      free(tempID);
    }

    if (blkname) {
      // no need for return string to be null terminated!
      if ((long)strlen(NI_SigList[sigidx].blockname)<*bnlen)
        *bnlen = strlen(NI_SigList[sigidx].blockname);
      strncpy(blkname, NI_SigList[sigidx].blockname, *bnlen);
    }

    if (signame) {
      // no need for return string to be null terminated!
      if ((long)strlen(NI_SigList[sigidx].signalname)<*snlen)
        *snlen = strlen(NI_SigList[sigidx].signalname);
      strncpy(signame, NI_SigList[sigidx].signalname, *snlen);
    }

    if (portnum)
      *portnum = NI_SigList[sigidx].portno;
    if (dattype)
      *dattype = NI_SigList[sigidx].datatype;
    if (dims && *numdim>=NI_SigList[sigidx].numofdims) {
      *numdim = NI_SigList[sigidx].numofdims;
      for (i=0;i < *numdim; i++)
        dims[i] = NI_SigDimList[NI_SigList[sigidx].dimListOffset +i];
    } else
      *numdim = 0;                     // set numdim to 0 to indicate that no enough memory to return the info.
    return 0;
  }

  return NI_SigListSize;
}

/*
 * Get parameter indices
 */
DLL_EXPORT long NIRT_GetParameterIndices(long* indices, long* len)
{
  long i;
  for (i=0;i<NI_ParamListSize && i<*len;i++)
    indices[i] = NI_ParamList[i].idx;
  *len = i;
  return NI_OK;
}

/*
 * parameter information
 *
 * if *pidx < 0, Lookup parameter by ID if ID != NULL.
 * if ID == NULL or no matching ID found, return number of parameters.
 *
 * plen  -> size of path
 * pnlen -> size of paramname
 * numdim -> size of dims array
 */
DLL_EXPORT long NIRT_GetParameterSpec(long* pidx, char* ID, long* ID_len, char
  * paramname, long *pnlen,
  long *dattype, long* dims, long* numdim)
{
  int i= 0;
  int paramidx = *pidx;
  if (paramidx<0) {
    // check if ID has been specified.
    if (ID && *ID_len>0) {
      // lookup the table for matching ID
      for (i=0;i<NI_ParamListSize;i++) {
        if (!strcmp(ID,NI_ParamList[i].paramname))
          break;
      }

      if (i<NI_ParamListSize)
        paramidx = *pidx = i;
      else
        return NI_ParamListSize;
    } else                             // no index or ID specified.
      return NI_ParamListSize;
  }

  if (paramidx>=0 && paramidx<NI_ParamListSize) {
    if (ID) {
      if ((long)strlen(NI_ParamList[paramidx].paramname)<*ID_len)
        *ID_len = strlen(NI_ParamList[paramidx].paramname);
      strncpy(ID, NI_ParamList[paramidx].paramname, *ID_len);
    }

    if (paramname) {
      // no need for return string to be null terminated!
      if ((long)strlen(NI_ParamList[paramidx].paramname)<*pnlen)
        *pnlen = strlen(NI_ParamList[paramidx].paramname);
      strncpy(paramname, NI_ParamList[paramidx].paramname, *pnlen);
    }

    if (dattype)
      *dattype = NI_ParamList[paramidx].datatype;
    if (!numdim)
      return 0;
    if (*numdim>=NI_ParamList[paramidx].numofdims) {
      *numdim = NI_ParamList[paramidx].numofdims;
      for (i=0;i < *numdim; i++)
        dims[i] = NI_ParamDimList[NI_ParamList[paramidx].dimListOffset +i];
    } else
      *numdim = 0;                     // set numdim to 0 to indicate that no enough memory to return the info.
    return 0;
  }

  return NI_ParamListSize;
}

/*
 * DEPRECATED.
 */
DLL_EXPORT long NIRT_GetParameterExpression(long paramidx, char* expression,
  long *exp_len)
{
  return 0;
}

/*
 * DEPRECATED.
 */
DLL_EXPORT long NIRT_GetVariableName(long varidx, char* variable_name, long
  *var_len)
{
  return 0;
}

/*
 * NIRT_GetExtIOSpec
 *
 * Inputs:
 *		index: index of the task
 * Outputs:
 *		idx:  idx of the IO.
 *		name: Name of the IO block
 *		tid: task id
 *		type: EXT_IN or EXT_OUT
 *		dimX: size of 0th dimension
 *		dimY: size of 1th dimension
 * Return value: 0 if no error. (if index == -1, return number of tasks in the model)
 */
DLL_EXPORT long NIRT_GetExtIOSpec(long index, long *idx, char* name, long* tid,
  long *type, long *dims, long* numdims)
{
  if (index==-1)
    return NI_ExtListSize;
  if (idx)
    *idx = NI_ExtList[index].idx;
  if (name) {
    int sz = strlen(name);
    strncpy(name, NI_ExtList[index].name, sz-1);
    name[sz-1]= 0;
  }

  if (tid)
    *tid = NI_ExtList[index].TID;
  if (type)
    *type = NI_ExtList[index].type;
  if (numdims && dims) {
    if (*numdims>=2) {
      *numdims= 2;
      dims[0] = NI_ExtList[index].dimX;
      dims[1] = NI_ExtList[index].dimY;
    } else
      *numdims= 0;
  }

  return 0;
}

/* Helper function to probe one	signal. baseaddr must NOT be VIRTUAL_SIG */
static long NI_ProbeOneSignal(long idx, double *value, long len, long *count,
  long vOffset, long vLength)
{
  char *ptr = (char*)((NI_SigList[idx].baseaddr == BLOCKIO_SIG) ?
                      S->ModelData.blockIO : S->ModelData.inputs) + (int)
    NI_SigList[idx].addr;
  long subindex = (vLength == -1) ? 0 : vOffset;
  long sublength = (vLength == -1) ? NI_SigList[idx].width : (vLength + vOffset);
  while ((subindex < sublength) && (*count < len))
    value[(*count)++] = NIRT_GetValueByDataType(ptr, subindex++, NI_SigList[idx]
      .datatype, NI_SigList[idx].IsComplex);
  return *count;
}

/*
 * NIRT_ProbeSignals
 *
 * Inputs:
 *		sigindices: indeces of signals
 *		numsigs: number of signals
 *		len: total length of all signals
 * Outputs:
 *		value: probed signal data
 *		len: length of data (may vary from input)
 * Return value: equal to len
 */
DLL_EXPORT long NIRT_ProbeSignals(long* sigindices, long numsigs,
  double* value, long* len)
{
  int i, j, idx;
  long count = 0;
  if (!SITexportglobals.inCriticalSection)
    SetSITErrorMessage("SignalProbe should only be called between ScheduleTasks and PostOutputs",
                       1);
  if ((*len > 1) && (numsigs > 0)) {
    value[count++] = sigindices[0];
    value[count++] = 0;
  }

  for (i = 1; (i < numsigs) && (count < *len); i++) {
    idx = sigindices[i];
    if (idx < 0)
      break;
    if (idx < NI_SigListSize) {
      if (NI_SigList[idx].baseaddr == VIRTUAL_SIG) {
        for (j = 0; j < 2; j++) {
          long vidx = NI_VirtualBlockSources[NI_SigList[idx].addr][j];
          long voff = NI_VirtualBlockOffsets[NI_SigList[idx].addr][j];
          long vlen = NI_VirtualBlockLengths[NI_SigList[idx].addr][j];
          if (vidx == -1)
            break;
          NI_ProbeOneSignal(vidx, value, *len, &count, voff, vlen);
        }
      } else
        NI_ProbeOneSignal(idx, value, *len, &count, 0, -1);
    }
  }

  *len = count;
  return count;
}

/* Copy the	statically initialized params into our copy of the param struct
   The undef allows us to access the real ctrl_student_HIL_P
   In the rest of the code ctrl_student_HIL_P is redefine to be the read-side
   of rtParameter.
 */
#undef ctrl_student_HIL_P

int NI_InitializeParamStruct()
{
  memcpy(&rtParameter[0], &ctrl_student_HIL_P, sizeof(P_ctrl_student_HIL_T));
  return NI_OK;
}

/*  After the model has initialized and updated the parameters in
   rtParameter[0] (aka ctrl_student_HIL_P) we make a copy to rtParameter[1] so
   that it is double buffered. We also do a memcpy to each task's copy.
 */
int NI_InitParamDoubleBuf()
{
  int idx = 1;

#ifdef MULTITASKING

  for (; idx <= NUMST - TID01EQ; idx++)
#endif

    memcpy(&rtParameter[idx], &rtParameter[0], sizeof(P_ctrl_student_HIL_T));
  return NI_OK;
}

static int NI_SetParamTxStatus = NI_OK;

// This function is called by the BGL to set parameters.  When a commit is requested (index < 0),
// the code enters a critical section shared with the TCL. This ensures that the flip occurs only
// when safe, and acts as a messaging scheme for us to copy back the parameters.
DLL_EXPORT long NIRT_SetParameter(long index, long subindex, double value)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (index < 0) {
    if (ReadSideDirtyFlag == 1) {
      memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
             (P_ctrl_student_HIL_T));
      ReadSideDirtyFlag = 0;
      if (WriteSideDirtyFlag == 0)
        return NI_OK;
      SetSITErrorMessage("Parameters have been set inline and from the background loop at the same time. Parameters written from the background loop since the last commit have been lost.",
                         1);
      WriteSideDirtyFlag = 0;
      return NI_ERROR;
    }

    if (NI_SetParamTxStatus==NI_ERROR) {
      // fail the transaction.
      // copy old	list of parameters to the failed TX buffer
      if (WriteSideDirtyFlag == 1)
        memcpy(&rtParameter[READSIDE], &rtParameter[1-READSIDE], sizeof
               (P_ctrl_student_HIL_T));

      // reset the status.
      NI_SetParamTxStatus = NI_OK;
      WriteSideDirtyFlag = 0;
      return NI_ERROR;
    }

    /*Do nothing if no new parameters were written after last commit*/
    if (WriteSideDirtyFlag == 0)
      return NI_OK;

    // commit changes
    S->ModelData.defaultParam = (double *)&rtParameter[1-READSIDE];
    WaitForSingleObject(SITexportglobals.flipCriticalSection, INFINITE);
    READSIDE = 1 - READSIDE;
    SITexportglobals.copyTaskBitfield = 0xFFFFFFFF;
    ReleaseSemaphore(SITexportglobals.flipCriticalSection, 1, NULL);

    // Copy back the newly set parameters to the writeside.
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_ctrl_student_HIL_T));
    WriteSideDirtyFlag = 0;
    return NI_OK;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_ctrl_student_HIL_T));
    ReadSideDirtyFlag = 0;
  }

  ptr = (char *)(&rtParameter[1-READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  WriteSideDirtyFlag = 1;
  return NIRT_SetValueByDataType(ptr,subindex,value,NI_ParamList[index].datatype,
    NI_ParamList[index].IsComplex);
}

DLL_EXPORT long NIRT_SetVectorParameter( unsigned long index, const double
  * paramvalues, unsigned long paramlength)
{
  unsigned int i = 0;
  long retval= NI_OK, temp_retval;
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  // verify that subindex is within bounds.
  if (paramlength!=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter length is incorrect.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  if (ReadSideDirtyFlag == 1) {
    memcpy(&rtParameter[1-READSIDE], &rtParameter[READSIDE], sizeof
           (P_ctrl_student_HIL_T));
    ReadSideDirtyFlag = 0;
  }

  ptr = (char *)(&rtParameter[1-READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  while (i<paramlength) {
    if (temp_retval = NIRT_SetValueByDataType(ptr, i, paramvalues[i],
         NI_ParamList[index].datatype, NI_ParamList[index].IsComplex))//assignment intended in if condition
      retval= temp_retval;
    i++;
  }

  WriteSideDirtyFlag = 1;
  return retval;
}

DLL_EXPORT long NIRT_SetScalarParameterInline( unsigned long index, unsigned
  long subindex, double paramvalue)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize) {
    SetSITErrorMessage("Parameter index is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width) {
    SetSITErrorMessage("Parameter subindex is out of bounds.",1);
    return NI_SetParamTxStatus= NI_ERROR;
  }

  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  ReadSideDirtyFlag = 1;
  return NIRT_SetValueByDataType(ptr,subindex,paramvalue,NI_ParamList[index].
    datatype,NI_ParamList[index].IsComplex);
}

DLL_EXPORT long NIRT_GetParameter(long index, long subindex, double *value)
{
  char* ptr = NULL;
  if (index>=NI_ParamListSize || index < 0)
    return NI_ERROR;

  // verify that subindex is within bounds.
  if (subindex>=NI_ParamList[index].width)
    return NI_ERROR;
  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  *value = NIRT_GetValueByDataType(ptr,subindex,NI_ParamList[index].datatype,
    NI_ParamList[index].IsComplex);
  return NI_OK;
}

DLL_EXPORT long NIRT_GetVectorParameter(unsigned long index, double* paramvalues,
  unsigned long paramlength)
{
  char* ptr = NULL;
  unsigned int i = 0;
  if (index>=NI_ParamListSize || index < 0)
    return NI_ERROR;

  // verify that subindex is within bounds.
  if (paramlength!=NI_ParamList[index].width)
    return NI_ERROR;
  ptr = (char *)(&rtParameter[READSIDE]);
  ptr += (int)NI_ParamList[index].addr;
  while (i<paramlength) {
    paramvalues[i] = NIRT_GetValueByDataType(ptr, i, NI_ParamList[index].
      datatype, NI_ParamList[index].IsComplex);
    i++;
  }

  return NI_OK;
}

DLL_EXPORT long NIRT_GetSimState(long* numContStates, char* contStatesNames,
  double* contStates, long* numDiscStates, char* discStatesNames, double
  * discStates, long* numClockTicks, char* clockTicksNames, long* clockTicks)
{
  long count, idx;
  if (numContStates && numDiscStates && numClockTicks) {
    if (*numContStates < 0 || *numDiscStates < 0 || *numClockTicks < 0) {
<<<<<<< HEAD
      *numContStates = 0;
      *numDiscStates = 538;
=======
      *numContStates = 9;
      *numDiscStates = 913;
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (discStates && discStatesNames) {
    idx = 0;
<<<<<<< HEAD
=======
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.counter_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.counter_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Noisepowerpos_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Noisepowerpos_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput_c,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput_c");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Noiseposerhead_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Noiseposerhead_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput_p,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput_p");
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.counter_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.counter_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Hold_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Hold_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Hold_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Hold_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Hold_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Hold_PreviousInput");
<<<<<<< HEAD
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput, 0,
=======
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Enablenoise_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Enablenoise_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_m_DWORK1, 0,
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput_c,
      0, 0, 0);
<<<<<<< HEAD
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput_c");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput_p,
=======
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_m_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK1,
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput_p");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1,
      0, 0, 0);
<<<<<<< HEAD
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1,
=======
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.b_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.b_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.signalloss_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.signalloss_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK1,
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L2_continuous_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L2_continuous_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.PosXRight_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.PosXRight_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.PosYRight_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.PosYRight_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.R2_continuous_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.R2_continuous_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.PosXLeft_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.PosXLeft_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.PosYLeft_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.PosYLeft_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.L1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.L1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.R1_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.R1_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.ArrowDown_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.ArrowDown_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.ArrowUp_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.ArrowUp_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.ArrowLeft_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.ArrowLeft_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.ArrowRight_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.ArrowRight_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.X_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.N_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Y_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.psi_0_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_0_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_0_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_0_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_0_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_0_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.integratorresetmodel_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.integratorresetmodel_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK2, 0, 6, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK2");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.RandSeed, 0,
      7, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.RandSeed");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.RandSeed_j, 0,
      7, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.RandSeed_j");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.RandSeed_c, 0,
      7, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.RandSeed_c");
    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.Noisepowerpos_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.Noisepowerpos_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.Noiseposerhead_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.Noiseposerhead_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_in_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
<<<<<<< HEAD
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_in_DWORK2");
=======
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.Enablenoise_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.Enablenoise_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_m_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_m_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_m_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_m_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_m_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_m_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.x_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.x_hat_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L1_diag_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L1_diag_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_hat_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L2_diag_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L2_diag_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.y_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.y_hat_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L3_diag_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L3_diag_DWORK2");
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
<<<<<<< HEAD
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_in_DWORK2");
=======
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.b_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.b_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.u_dot_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.u_dot_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.signalloss_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.signalloss_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.v_dot_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.v_dot_DWORK2");
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L2_continuous_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L2_continuous_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosXRight_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosXRight_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosYRight_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosYRight_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.R2_continuous_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.R2_continuous_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosXLeft_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosXLeft_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosYLeft_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosYLeft_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.L1_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.L1_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.R1_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.R1_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowDown_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowDown_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowUp_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowUp_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowLeft_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowLeft_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowRight_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowRight_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.X_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.N_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Y_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_0_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_0_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_0_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_0_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_0_DWORK2,
        count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_0_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.integratorresetmodel_DWORK2, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.integratorresetmodel_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK1, count, 18, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK1");
    }

    for (count = 0; count < 60; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK3, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK3");
    }
  }

  if (clockTicks && clockTicksNames) {
    clockTicks[0] = S->Timing.clockTick0;
    strcpy(clockTicksNames, "clockTick0");
  }

  return NI_OK;
}

DLL_EXPORT long NIRT_SetSimState(double* contStates, double* discStates, long
  * clockTicks)
{
  long count, idx;
  if (discStates) {
    idx = 0;
<<<<<<< HEAD
=======
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.counter_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Noisepowerpos_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput_c, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Noiseposerhead_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput_p, 0, discStates[idx
      ++], 0, 0);
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.counter_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Hold_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Hold_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Hold_PreviousInput, 2,
      discStates[idx++], 17, 0);
<<<<<<< HEAD
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput, 0, discStates[idx++],
=======
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Enablenoise_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_m_DWORK1, 0, discStates[idx++],
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput_c, 0, discStates[idx
      ++], 0, 0);
<<<<<<< HEAD
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput_p, 0, discStates[idx
=======
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_m_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK1, 0, discStates[idx
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
<<<<<<< HEAD
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1, 0, discStates[idx
=======
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.b_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.signalloss_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK1, 0, discStates[idx
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_continuous_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosXRight_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosYRight_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.R2_continuous_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosXLeft_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosYLeft_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.R1_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowDown_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowUp_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowLeft_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowRight_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_0_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_0_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_0_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.integratorresetmodel_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK2,
      0, discStates[idx++], 6, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.RandSeed, 0, discStates[idx++],
      7, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.RandSeed_j, 0, discStates[idx++],
      7, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.RandSeed_c, 0, discStates[idx++],
      7, 0);
    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Noisepowerpos_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Noiseposerhead_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK2, count,
<<<<<<< HEAD
        discStates[idx++], 18, 0);
=======
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Enablenoise_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_m_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_m_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_m_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_hat_DWORK2, count,
        discStates[idx++], 19, 0);
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
<<<<<<< HEAD
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK2, count,
        discStates[idx++], 18, 0);
=======
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.b_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.signalloss_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK2, count,
        discStates[idx++], 19, 0);
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_continuous_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosXRight_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosYRight_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.R2_continuous_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosXLeft_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosYLeft_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.R1_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowDown_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowUp_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowLeft_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowRight_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_0_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_0_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_0_DWORK2, count,
        discStates[idx++], 18, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.integratorresetmodel_DWORK2,
<<<<<<< HEAD
        count, discStates[idx++], 18, 0);
=======
        count, discStates[idx++], 19, 0);
>>>>>>> 36131a4df6b7a33ef16fb81cb1b9b1ddb1e9dbe2
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK1,
        count, discStates[idx++], 18, 0);
    }

    for (count = 0; count < 60; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK3,
        count, discStates[idx++], 19, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_ctrl_student_HIL
