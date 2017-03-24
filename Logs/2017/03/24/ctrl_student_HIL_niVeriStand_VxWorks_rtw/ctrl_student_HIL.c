/*
 * ctrl_student_HIL.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ctrl_student_HIL".
 *
 * Model version              : 1.237
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Fri Mar 24 14:35:24 2017
 *
 * Target selection: NIVeriStand_VxWorks.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ctrl_student_HIL.h"
#include "ctrl_student_HIL_private.h"

/* Block signals (auto storage) */
B_ctrl_student_HIL_T ctrl_student_HIL_B;

/* Continuous states */
X_ctrl_student_HIL_T ctrl_student_HIL_X;

/* Block states (auto storage) */
DW_ctrl_student_HIL_T ctrl_student_HIL_DW;

/* Real-time model */
RT_MODEL_ctrl_student_HIL_T ctrl_student_HIL_M_;
RT_MODEL_ctrl_student_HIL_T *const ctrl_student_HIL_M = &ctrl_student_HIL_M_;

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 12;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  ctrl_student_HIL_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  ctrl_student_HIL_output();
  ctrl_student_HIL_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  ctrl_student_HIL_output();
  ctrl_student_HIL_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  ctrl_student_HIL_output();
  ctrl_student_HIL_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * Output and update for atomic system:
 *    '<S10>/MATLAB Function'
 *    '<S22>/MATLAB Function'
 *    '<S34>/MATLAB Function'
 */
void ctrl_student_HIL_MATLABFunction(real_T rtu_nu, real_T rtu_nu_g, real_T
  rtu_nu_f, const real_T rtu_alpha_dot[3], const real_T rtu_z_1[3],
  B_MATLABFunction_ctrl_student_T *localB)
{
  static const real_T a[9] = { 16.79, 0.0, 0.0, 0.0, 24.79, 0.55462499999999992,
    0.0, 0.55462499999999992, 2.76 };

  real_T tmp[9];
  real_T tmp_0[3];
  real_T a_0[3];
  int32_T i;

  /* SignalConversion: '<S14>/TmpSignal ConversionAt SFunction Inport1' */
  /* MATLAB Function 'Ellipse/Control law1/MATLAB Function': '<S14>:1' */
  /* % Parameters */
  /*  Rigid body and added mass */
  /*  y_g = 0.0; */
  /*  Max Values in Surge X, Sway Y and Yaw N */
  /*  X_max = 1.03; %[N] */
  /*  N_max = 2.50; %[N] */
  /*  Y_max = 0.98; %[N] */
  /*  Hydro surge, Hydro sway and Hydro Yaw Parameters */
  /*  NB! We don't need most of them for now, that why they are commented */
  /*  out, but don't remove them!! */
  /* '<S14>:1:22' */
  /* '<S14>:1:25' */
  /* % Matrixes */
  /* '<S14>:1:32' */
  /*  I need a test values;  */
  /* '<S14>:1:40' */
  /* '<S14>:1:41' */
  /* '<S14>:1:42' */
  /* '<S14>:1:43' */
  /* '<S14>:1:44' */
  /*  The total damping matrix from the handbook page 53 */
  /* '<S14>:1:47' */
  /* '<S14>:1:49' */
  tmp[0] = (0.6555 - 0.3545 * fabs(rtu_nu)) - rtu_nu * rtu_nu * -3.787;
  tmp[3] = 0.0;
  tmp[6] = 0.0;
  tmp[1] = 0.0;

  /* SignalConversion: '<S14>/TmpSignal ConversionAt SFunction Inport1' */
  tmp[4] = ((1.33 - -2.776 * fabs(rtu_nu_g)) - rtu_nu_g * rtu_nu_g * -64.91) -
    0.805 * fabs(rtu_nu_f);
  tmp[7] = ((7.25 - -0.845 * fabs(rtu_nu_g)) - -3.45 * fabs(rtu_nu_f)) -
    rtu_nu_f * rtu_nu_f * 0.0;
  tmp[2] = 0.0;

  /* SignalConversion: '<S14>/TmpSignal ConversionAt SFunction Inport1' */
  tmp[5] = ((-0.0 - -0.2088 * fabs(rtu_nu_g)) - rtu_nu_g * rtu_nu_g * 0.0) -
    0.13 * fabs(rtu_nu_f);
  tmp[8] = ((1.9 - 0.08 * fabs(rtu_nu_g)) - 0.75 * fabs(rtu_nu_f)) - rtu_nu_f *
    rtu_nu_f * 0.0;
  for (i = 0; i < 3; i++) {
    /* SignalConversion: '<S14>/TmpSignal ConversionAt SFunction Inport1' */
    tmp_0[i] = tmp[i + 6] * rtu_nu_f + (tmp[i + 3] * rtu_nu_g + tmp[i] * rtu_nu);
  }

  for (i = 0; i < 3; i++) {
    a_0[i] = a[i + 6] * rtu_alpha_dot[2] + (a[i + 3] * rtu_alpha_dot[1] + a[i] *
      rtu_alpha_dot[0]);
  }

  localB->tau[0] = (tmp_0[0] + a_0[0]) - rtu_z_1[0];
  localB->tau[1] = (tmp_0[1] + a_0[1]) - rtu_z_1[1];
  localB->tau[2] = (tmp_0[2] + a_0[2]) - rtu_z_1[2];
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Output and update for atomic system:
 *    '<S10>/MATLAB Function2'
 *    '<S22>/MATLAB Function2'
 *    '<S34>/MATLAB Function2'
 */
void ctrl_student_HI_MATLABFunction2(const real_T rtu_eta_d[3], real_T rtu_eta,
  real_T rtu_eta_n, real_T rtu_eta_h, B_MATLABFunction2_ctrl_studen_T *localB)
{
  real_T r;
  real_T tmp[9];
  int32_T i;
  real_T z_1_a_idx_0;
  real_T z_1_a_idx_1;

  /* SignalConversion: '<S16>/TmpSignal ConversionAt SFunction Inport2' */
  /* MATLAB Function 'Ellipse/Control law1/MATLAB Function2': '<S16>:1' */
  /* '<S16>:1:2' */
  /* '<S16>:1:3' */
  /* '<S16>:1:6' */
  z_1_a_idx_0 = rtu_eta - rtu_eta_d[0];
  z_1_a_idx_1 = rtu_eta_n - rtu_eta_d[1];

  /* z_1_psi = angdiff(eta_d(3), eta(3)); */
  /* '<S16>:1:8' */
  /* '<S16>:1:9' */
  r = ((rtu_eta_h - rtu_eta_d[2]) + 3.1415926535897931) / 6.2831853071795862;
  if (fabs(r - rt_roundd_snf(r)) <= 2.2204460492503131E-16 * fabs(r)) {
    r = 0.0;
  } else {
    r = (r - floor(r)) * 6.2831853071795862;
  }

  /* SignalConversion: '<S16>/TmpSignal ConversionAt SFunction Inport2' */
  /* '<S16>:1:10' */
  /* '<S16>:1:11' */
  tmp[0] = cos(rtu_eta_h);
  tmp[1] = -sin(rtu_eta_h);
  tmp[2] = 0.0;

  /* SignalConversion: '<S16>/TmpSignal ConversionAt SFunction Inport2' */
  tmp[3] = sin(rtu_eta_h);
  tmp[4] = cos(rtu_eta_h);
  tmp[5] = 0.0;
  tmp[6] = 0.0;
  tmp[7] = 0.0;
  tmp[8] = 1.0;
  for (i = 0; i < 3; i++) {
    localB->z_1[i] = 0.0;
    localB->z_1[i] += tmp[i] * z_1_a_idx_0;
    localB->z_1[i] += tmp[i + 3] * z_1_a_idx_1;
    localB->z_1[i] += tmp[i + 6] * (r - 3.1415926535897931);
  }
}

/*
 * Output and update for atomic system:
 *    '<S13>/Update Law'
 *    '<S25>/Update Law'
 */
void ctrl_student_HIL_UpdateLaw(real_T rtu_U_s, real_T rtu_mu, const real_T
  rtu_eta_d_s[3], const real_T rtu_eta_d[3], real_T rtu_eta, real_T rtu_eta_k,
  real_T rtu_eta_ke, B_UpdateLaw_ctrl_student_HIL_T *localB)
{
  real_T r;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T diff_idx_2;

  /* SignalConversion: '<S21>/TmpSignal ConversionAt SFunction Inport5' */
  /* MATLAB Function 'Ellipse/Update Law/Update Law': '<S21>:1' */
  /* '<S21>:1:2' */
  /* '<S21>:1:3' */
  /* '<S21>:1:4' */
  r = ((rtu_eta_ke - rtu_eta_d[2]) + 3.1415926535897931) / 6.2831853071795862;
  if (fabs(r - rt_roundd_snf(r)) <= 2.2204460492503131E-16 * fabs(r)) {
    r = 0.0;
  } else {
    r = (r - floor(r)) * 6.2831853071795862;
  }

  diff_idx_2 = r - 3.1415926535897931;

  /* diff(3) = angdiff(eta_d(3), eta(3)); % Order is important here */
  /* '<S21>:1:6' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(rtu_eta_d_s[0]);
  if (absxk > 2.2250738585072014E-308) {
    r = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    r = t * t;
  }

  absxk = fabs(rtu_eta_d_s[1]);
  if (absxk > scale) {
    t = scale / absxk;
    r = r * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    r += t * t;
  }

  absxk = fabs(rtu_eta_d_s[2]);
  if (absxk > scale) {
    t = scale / absxk;
    r = r * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    r += t * t;
  }

  r = scale * sqrt(r);
  r = rtu_mu / r;

  /* SignalConversion: '<S21>/TmpSignal ConversionAt SFunction Inport5' */
  localB->s_dot = rtu_U_s - ((-(rtu_eta - rtu_eta_d[0]) * r * rtu_eta_d_s[0] +
    -(rtu_eta_k - rtu_eta_d[1]) * r * rtu_eta_d_s[1]) + r * -diff_idx_2 *
    rtu_eta_d_s[2]);
}

/*
 * Output and update for atomic system:
 *    '<S22>/MATLAB Function1'
 *    '<S34>/MATLAB Function1'
 */
void ctrl_student_HI_MATLABFunction1(real_T rtu_eta, real_T rtu_eta_l, real_T
  rtu_eta_d, const real_T rtu_eta_d_n[3], const real_T rtu_eta_d_s[3], real_T
  rtu_nu, real_T rtu_nu_l, real_T rtu_nu_o, real_T rtu_s_dot,
  B_MATLABFunction1_ctrl_studen_T *localB)
{
  real_T R[9];
  real_T r;
  real_T rtb_TmpSignalConversionAtSFu_je[3];
  real_T tmp[9];
  real_T R_0[3];
  int32_T i;
  real_T R_1[3];
  real_T z_1_a_idx_0;
  real_T z_1_a_idx_1;

  /* SignalConversion: '<S27>/TmpSignal ConversionAt SFunction Inport4' */
  rtb_TmpSignalConversionAtSFu_je[0] = rtu_nu;
  rtb_TmpSignalConversionAtSFu_je[1] = rtu_nu_l;
  rtb_TmpSignalConversionAtSFu_je[2] = rtu_nu_o;

  /* SignalConversion: '<S27>/TmpSignal ConversionAt SFunction Inport1' */
  /* MATLAB Function 'Line System 1-6 (DP line)/Control law/MATLAB Function1': '<S27>:1' */
  /* '<S27>:1:2' */
  /* '<S27>:1:3' */
  /* '<S27>:1:5' */
  /* '<S27>:1:6' */
  R[0] = cos(rtu_eta_d);
  R[3] = -sin(rtu_eta_d);
  R[6] = 0.0;

  /* SignalConversion: '<S27>/TmpSignal ConversionAt SFunction Inport1' */
  R[1] = sin(rtu_eta_d);
  R[4] = cos(rtu_eta_d);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* SignalConversion: '<S27>/TmpSignal ConversionAt SFunction Inport1' */
  /* '<S27>:1:10' */
  z_1_a_idx_0 = rtu_eta - rtu_eta_d_n[0];
  z_1_a_idx_1 = rtu_eta_l - rtu_eta_d_n[1];

  /*  Here is where our eta_d would jump because of the parametrization. */
  /*  Instead of doing something hacky, we can redefine the control */
  /*  law such that it has the exact same gain. */
  /*  To compute the angular difference, we use angdiff: */
  /* z_1_psi = angdiff(eta_d(3), eta(3)); */
  /* '<S27>:1:16' */
  /* '<S27>:1:17' */
  r = ((rtu_eta_d - rtu_eta_d_n[2]) + 3.1415926535897931) / 6.2831853071795862;
  if (fabs(r - rt_roundd_snf(r)) <= 2.2204460492503131E-16 * fabs(r)) {
    r = 0.0;
  } else {
    r = (r - floor(r)) * 6.2831853071795862;
  }

  /* '<S27>:1:18' */
  /* '<S27>:1:19' */
  /* '<S27>:1:20' */
  tmp[0] = 0.0;

  /* SignalConversion: '<S27>/TmpSignal ConversionAt SFunction Inport4' */
  tmp[1] = -rtu_nu_o;
  tmp[2] = 0.0;

  /* SignalConversion: '<S27>/TmpSignal ConversionAt SFunction Inport4' */
  tmp[3] = rtu_nu_o;
  tmp[4] = 0.0;
  tmp[5] = 0.0;
  tmp[6] = 0.0;
  tmp[7] = 0.0;
  tmp[8] = 0.0;
  for (i = 0; i < 3; i++) {
    R_0[i] = R[3 * i + 2] * (r - 3.1415926535897931) + (R[3 * i + 1] *
      z_1_a_idx_1 + R[3 * i] * z_1_a_idx_0);
  }

  for (i = 0; i < 3; i++) {
    R_1[i] = R[3 * i + 2] * rtu_eta_d_s[2] + (R[3 * i + 1] * rtu_eta_d_s[1] + R
      [3 * i] * rtu_eta_d_s[0]);
  }

  for (i = 0; i < 3; i++) {
    localB->z_1_dot[i] = (((tmp[i + 3] * R_0[1] + tmp[i] * R_0[0]) + 0.0 * R_0[2])
                          + rtb_TmpSignalConversionAtSFu_je[i]) - R_1[i] *
      rtu_s_dot;
  }
}

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

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = (rtNaN);
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model output function */
void ctrl_student_HIL_output(void)
{
  /* local block i/o variables */
  real_T rtb_Integrator_e;
  real_T rtb_Integrator_g;
  real_T rtb_eta_d[3];
  real_T rtb_eta_d_s[3];
  real_T rtb_alpha_1_dot[3];
  real_T rtb_eta_d_l[3];
  real_T rtb_eta_d_s_n[3];
  real_T rtb_alpha_1_dot_c[3];
  real_T rtb_U_s_i;
  real_T rtb_eta_d_s_c[3];
  real_T rtb_alpha_1_dot_k[3];
  real_T L1[9];
  real_T L2[9];
  real_T L3[9];
  real_T R[9];
  static const real_T a[9] = { 0.059559261465157838, -0.0, 0.0, -0.0,
    0.04052100686778741, -0.0081423733365488769, -0.0, -0.0081423733365488769,
    0.36395498559871381 };

  static const real_T b_a[9] = { -4.088, -0.0, -0.0, -0.0, -68.211, -0.0788,
    -0.0, -0.0, -1.07 };

  real_T psi_d;
  real_T t;
  real_T rtb_U_s_s;
  real_T rtb_U_s;
  int32_T i;
  real_T R_0[3];
  real_T L1_0[3];
  real_T b_a_0[3];
  real_T tmp[9];
  real_T tmp_0[9];
  real_T tmp_1[9];
  int32_T i_0;
  real_T eta_bar_idx_2;
  real_T eta_bar_idx_1;
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
    /* MATLAB Function: '<S46>/MATLAB Function' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<S5>/Step size'
     *  Memory: '<S46>/counter'
     */
    /* MATLAB Function 'Noise generator/Downsample	signal/MATLAB Function': '<S49>:1' */
    /* '<S49>:1:3' */
    if ((ctrl_student_HIL_DW.counter_PreviousInput + 1.0) *
        ctrl_student_HIL_P.Stepsize_Value >= 1.0 /
        ctrl_student_HIL_P.Constant4_Value) {
      /* '<S49>:1:4' */
      /* '<S49>:1:5' */
      ctrl_student_HIL_B.count = 0.0;
    } else {
      /* '<S49>:1:7' */
      ctrl_student_HIL_B.count = ctrl_student_HIL_DW.counter_PreviousInput + 1.0;
    }

    /* End of MATLAB Function: '<S46>/MATLAB Function' */
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* RandomNumber: '<S52>/White Noise' */
    ctrl_student_HIL_B.WhiteNoise = ctrl_student_HIL_DW.NextOutput;

    /* RandomNumber: '<S53>/White Noise' */
    ctrl_student_HIL_B.WhiteNoise_e = ctrl_student_HIL_DW.NextOutput_c;
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* RandomNumber: '<S51>/White Noise' */
    ctrl_student_HIL_B.WhiteNoise_m = ctrl_student_HIL_DW.NextOutput_p;
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Memory: '<S47>/Hold' */
    ctrl_student_HIL_B.Hold[0] = ctrl_student_HIL_DW.Hold_PreviousInput[0];
    ctrl_student_HIL_B.Hold[1] = ctrl_student_HIL_DW.Hold_PreviousInput[1];
    ctrl_student_HIL_B.Hold[2] = ctrl_student_HIL_DW.Hold_PreviousInput[2];
  }

  /* MATLAB Function: '<S47>/MATLAB Function1' incorporates:
   *  Constant: '<S5>/Step size'
   *  Product: '<S51>/Divide'
   *  Product: '<S51>/Product'
   *  Product: '<S52>/Divide'
   *  Product: '<S52>/Product'
   *  Product: '<S53>/Divide'
   *  Product: '<S53>/Product'
   *  Sqrt: '<S51>/Sqrt'
   *  Sqrt: '<S52>/Sqrt'
   *  Sqrt: '<S53>/Sqrt'
   *  Sum: '<S5>/Sum'
   */
  /* MATLAB Function 'Noise generator/Sample & hold/MATLAB Function1': '<S50>:1' */
  if (ctrl_student_HIL_B.count == 0.0) {
    /* '<S50>:1:4' */
    /* '<S50>:1:5' */
    ctrl_student_HIL_B.output[0] = sqrt(ctrl_student_HIL_B.noisepos /
      ctrl_student_HIL_P.Stepsize_Value) * ctrl_student_HIL_B.WhiteNoise +
      ctrl_student_HIL_B.x_in;
    ctrl_student_HIL_B.output[1] = sqrt(ctrl_student_HIL_B.noisepos /
      ctrl_student_HIL_P.Stepsize_Value) * ctrl_student_HIL_B.WhiteNoise_e +
      ctrl_student_HIL_B.y_in;
    ctrl_student_HIL_B.output[2] = sqrt(ctrl_student_HIL_B.noisehead /
      ctrl_student_HIL_P.Stepsize_Value) * ctrl_student_HIL_B.WhiteNoise_m +
      ctrl_student_HIL_B.psi_in;
  } else {
    /* '<S50>:1:7' */
    ctrl_student_HIL_B.output[0] = ctrl_student_HIL_B.Hold[0];
    ctrl_student_HIL_B.output[1] = ctrl_student_HIL_B.Hold[1];
    ctrl_student_HIL_B.output[2] = ctrl_student_HIL_B.Hold[2];
  }

  /* End of MATLAB Function: '<S47>/MATLAB Function1' */

  /* Switch: '<S5>/Switch' */
  if (ctrl_student_HIL_B.enablenoise != 0.0) {
    ctrl_student_HIL_B.Switch[0] = ctrl_student_HIL_B.output[0];
    ctrl_student_HIL_B.Switch[1] = ctrl_student_HIL_B.output[1];
    ctrl_student_HIL_B.Switch[2] = ctrl_student_HIL_B.output[2];
  } else {
    ctrl_student_HIL_B.Switch[0] = ctrl_student_HIL_B.x_in;
    ctrl_student_HIL_B.Switch[1] = ctrl_student_HIL_B.y_in;
    ctrl_student_HIL_B.Switch[2] = ctrl_student_HIL_B.psi_in;
  }

  /* End of Switch: '<S5>/Switch' */

  /* MATLAB Function: '<S11>/Ellipse Mapper' incorporates:
   *  Constant: '<S11>/Constant'
   *  Constant: '<S11>/Constant1'
   *  Integrator: '<S13>/Integrator'
   */
  /* MATLAB Function 'Ellipse/Ellipse Mapper /Ellipse Mapper': '<S19>:1' */
  /* '<S19>:1:2' */
  /* '<S19>:1:3' */
  /* 0;]; */
  /* '<S19>:1:5' */
  ctrl_student_HIL_B.eta_d[0] = ctrl_student_HIL_P.R[0] * cos
    (ctrl_student_HIL_X.Integrator_CSTATE) + ctrl_student_HIL_P.C[0];
  ctrl_student_HIL_B.eta_d[1] = ctrl_student_HIL_P.R[3] * sin
    (ctrl_student_HIL_X.Integrator_CSTATE) + ctrl_student_HIL_P.C[1];
  ctrl_student_HIL_B.eta_d[2] = rt_atan2d_snf(ctrl_student_HIL_P.R[3] * cos
    (ctrl_student_HIL_X.Integrator_CSTATE), -ctrl_student_HIL_P.R[0] * sin
    (ctrl_student_HIL_X.Integrator_CSTATE));

  /*  + floor((s+2*pi-pi/2)/2/pi)*2*pi]; */
  /* 0;]; */
  /* '<S19>:1:10' */
  rtb_U_s_s = cos(ctrl_student_HIL_X.Integrator_CSTATE);
  psi_d = sin(ctrl_student_HIL_X.Integrator_CSTATE);
  rtb_eta_d_s_c[0] = -ctrl_student_HIL_P.R[0] * sin
    (ctrl_student_HIL_X.Integrator_CSTATE);
  rtb_eta_d_s_c[1] = ctrl_student_HIL_P.R[3] * cos
    (ctrl_student_HIL_X.Integrator_CSTATE);
  rtb_eta_d_s_c[2] = ctrl_student_HIL_P.R[0] * ctrl_student_HIL_P.R[3] /
    (ctrl_student_HIL_P.R[3] * ctrl_student_HIL_P.R[3] * (rtb_U_s_s * rtb_U_s_s)
     + ctrl_student_HIL_P.R[0] * ctrl_student_HIL_P.R[0] * (psi_d * psi_d));

  /* '<S19>:1:14' */
  rtb_U_s_s = cos(ctrl_student_HIL_X.Integrator_CSTATE);
  psi_d = sin(ctrl_student_HIL_X.Integrator_CSTATE);
  t = ctrl_student_HIL_P.R[3] * ctrl_student_HIL_P.R[3] * (rtb_U_s_s * rtb_U_s_s)
    + ctrl_student_HIL_P.R[0] * ctrl_student_HIL_P.R[0] * (psi_d * psi_d);
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
  }

  /* Integrator: '<S1>/Integrator' */
  ctrl_student_HIL_B.Integrator[0] = ctrl_student_HIL_X.Integrator_CSTATE_m[0];
  ctrl_student_HIL_B.Integrator[1] = ctrl_student_HIL_X.Integrator_CSTATE_m[1];
  ctrl_student_HIL_B.Integrator[2] = ctrl_student_HIL_X.Integrator_CSTATE_m[2];

  /* Integrator: '<S1>/Integrator1' */
  ctrl_student_HIL_B.Integrator1[0] = ctrl_student_HIL_X.Integrator1_CSTATE[0];
  ctrl_student_HIL_B.Integrator1[1] = ctrl_student_HIL_X.Integrator1_CSTATE[1];
  ctrl_student_HIL_B.Integrator1[2] = ctrl_student_HIL_X.Integrator1_CSTATE[2];
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
  /* MATLAB Function 'DP Observer /Observer ': '<S9>:1' */
  /*  if(first == 1) */
  /*  eta_hat = zeros(3,1) ;  */
  /*  nu_hat = zeros(3,1);  */
  /*  b_hau = zeros(3,1) */
  /*  first_out = 0;  */
  /*  end */
  /* '<S9>:1:8' */
  for (i = 0; i < 9; i++) {
    L1[i] = 0.0;
    L2[i] = 0.0;
    L3[i] = 0.0;
  }

  L1[0] = ctrl_student_HIL_B.L1_diag[0];
  L1[4] = ctrl_student_HIL_B.L1_diag[1];
  L1[8] = ctrl_student_HIL_B.L1_diag[2];

  /* '<S9>:1:9' */
  L2[0] = ctrl_student_HIL_B.L2_diag[0];
  L2[4] = ctrl_student_HIL_B.L2_diag[1];
  L2[8] = ctrl_student_HIL_B.L2_diag[2];

  /* '<S9>:1:10' */
  L3[0] = ctrl_student_HIL_B.L3_diag[0];
  L3[4] = ctrl_student_HIL_B.L3_diag[1];
  L3[8] = ctrl_student_HIL_B.L3_diag[2];

  /*  The total damping matrix from the handbook page 53 */
  /* '<S9>:1:19' */
  psi_d = ctrl_student_HIL_B.Switch[0] - ctrl_student_HIL_B.Memory4[0];
  eta_bar_idx_1 = ctrl_student_HIL_B.Switch[1] - ctrl_student_HIL_B.Memory4[1];
  eta_bar_idx_2 = ctrl_student_HIL_B.Switch[2] - ctrl_student_HIL_B.Memory4[2];

  /* '<S9>:1:20' */
  ctrl_student_HIL_B.x_bar = psi_d;

  /* '<S9>:1:21' */
  ctrl_student_HIL_B.y_bar = eta_bar_idx_1;

  /* '<S9>:1:22' */
  ctrl_student_HIL_B.psi_bar = eta_bar_idx_2;

  /* '<S9>:1:23' */
  /* '<S9>:1:24' */
  R[0] = cos(ctrl_student_HIL_B.Switch[2]);
  R[3] = sin(ctrl_student_HIL_B.Switch[2]);
  R[6] = 0.0;
  R[1] = -sin(ctrl_student_HIL_B.Switch[2]);
  R[4] = cos(ctrl_student_HIL_B.Switch[2]);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* '<S9>:1:28' */
  /* '<S9>:1:29' */
  for (i = 0; i < 3; i++) {
    R_0[i] = R[i + 6] * ctrl_student_HIL_B.Memory3[2] + (R[i + 3] *
      ctrl_student_HIL_B.Memory3[1] + R[i] * ctrl_student_HIL_B.Memory3[0]);
  }

  for (i = 0; i < 3; i++) {
    L1_0[i] = L1[i + 6] * eta_bar_idx_2 + (L1[i + 3] * eta_bar_idx_1 + L1[i] *
      psi_d);
  }

  ctrl_student_HIL_B.eta_hat_dot[0] = R_0[0] + L1_0[0];
  ctrl_student_HIL_B.eta_hat_dot[1] = R_0[1] + L1_0[1];
  ctrl_student_HIL_B.eta_hat_dot[2] = R_0[2] + L1_0[2];

  /* '<S9>:1:31' */
  for (i = 0; i < 3; i++) {
    ctrl_student_HIL_B.b_hat_dot[i] = ((L3[i + 3] * eta_bar_idx_1 + L3[i] *
      psi_d) + L3[i + 6] * eta_bar_idx_2) + ctrl_student_HIL_B.b;
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
    b_a_0[i] = ((L1[i + 3] * eta_bar_idx_1 + L1[i] * psi_d) + L1[i + 6] *
                eta_bar_idx_2) + (L1_0[i] + R_0[i]);
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

  /* MATLAB Function: '<S12>/Ellipse' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S12>/Constant'
   *  Integrator: '<S13>/Integrator'
   */
  /* MATLAB Function 'Ellipse/Ellipse Speed Gauge/Ellipse': '<S20>:1' */
  /* '<S20>:1:2' */
  rtb_U_s_s = ctrl_student_HIL_P.r[0] * sin(ctrl_student_HIL_X.Integrator_CSTATE);
  psi_d = ctrl_student_HIL_P.r[1] * cos(ctrl_student_HIL_X.Integrator_CSTATE);
  rtb_U_s_i = 0.1 * ctrl_student_HIL_P.U_max / sqrt(rtb_U_s_s * rtb_U_s_s +
    psi_d * psi_d);

  /* '<S20>:1:3' */
  rtb_U_s_s = cos(ctrl_student_HIL_X.Integrator_CSTATE);
  psi_d = sin(ctrl_student_HIL_X.Integrator_CSTATE);
  rtb_U_s_s = -(ctrl_student_HIL_P.r[0] * ctrl_student_HIL_P.r[0] * cos
                (ctrl_student_HIL_X.Integrator_CSTATE) * sin
                (ctrl_student_HIL_X.Integrator_CSTATE) - ctrl_student_HIL_P.r[1]
                * ctrl_student_HIL_P.r[1] * cos
                (ctrl_student_HIL_X.Integrator_CSTATE) * sin
                (ctrl_student_HIL_X.Integrator_CSTATE)) * (0.1 *
    ctrl_student_HIL_P.U_max) / rt_powd_snf(ctrl_student_HIL_P.r[1] *
    ctrl_student_HIL_P.r[1] * (rtb_U_s_s * rtb_U_s_s) + ctrl_student_HIL_P.r[0] *
    ctrl_student_HIL_P.r[0] * (psi_d * psi_d), 1.5);

  /* MATLAB Function: '<S13>/Update Law' */
  ctrl_student_HIL_UpdateLaw(rtb_U_s_i, ctrl_student_HIL_B.mu, rtb_eta_d_s_c,
    ctrl_student_HIL_B.eta_d, ctrl_student_HIL_B.x_in, ctrl_student_HIL_B.y_in,
    ctrl_student_HIL_B.psi_in, &ctrl_student_HIL_B.sf_UpdateLaw);

  /* Saturate: '<S13>/Saturation' */
  if (ctrl_student_HIL_B.sf_UpdateLaw.s_dot >
      ctrl_student_HIL_P.Saturation_UpperSat) {
    ctrl_student_HIL_B.Saturation = ctrl_student_HIL_P.Saturation_UpperSat;
  } else if (ctrl_student_HIL_B.sf_UpdateLaw.s_dot <
             ctrl_student_HIL_P.Saturation_LowerSat) {
    ctrl_student_HIL_B.Saturation = ctrl_student_HIL_P.Saturation_LowerSat;
  } else {
    ctrl_student_HIL_B.Saturation = ctrl_student_HIL_B.sf_UpdateLaw.s_dot;
  }

  /* End of Saturate: '<S13>/Saturation' */

  /* MATLAB Function: '<S10>/MATLAB Function4' incorporates:
   *  Constant: '<S10>/K_p'
   *  SignalConversion: '<S18>/TmpSignal ConversionAt SFunction Inport3'
   *  SignalConversion: '<S18>/TmpSignal ConversionAt SFunction Inport5'
   */
  /* MATLAB Function 'Ellipse/Control law1/MATLAB Function1': '<S15>:1' */
  /*  Here is where our eta_d would jump because of the parametrization. */
  /*  Instead of doing something hacky, we can redefine the control */
  /*  law such that it has the exact same gain. */
  /*  To compute the angular difference, we use angdiff: */
  /* z_1_psi = angdiff(eta_d(3), eta(3)); */
  /* '<S15>:1:21' */
  /* MATLAB Function 'Ellipse/Control law1/MATLAB Function4': '<S18>:1' */
  /* '<S18>:1:2' */
  /* '<S18>:1:3' */
  /* '<S18>:1:4' */
  /* '<S18>:1:5' */
  R[0] = cos(ctrl_student_HIL_B.psi_in);
  R[3] = -sin(ctrl_student_HIL_B.psi_in);
  R[6] = 0.0;
  R[1] = sin(ctrl_student_HIL_B.psi_in);
  R[4] = cos(ctrl_student_HIL_B.psi_in);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* '<S18>:1:9' */
  for (i = 0; i < 3; i++) {
    L1[3 * i] = -ctrl_student_HIL_P.K_p[3 * i];
    L1[1 + 3 * i] = -ctrl_student_HIL_P.K_p[3 * i + 1];
    L1[2 + 3 * i] = -ctrl_student_HIL_P.K_p[3 * i + 2];
  }

  tmp[0] = 0.0;
  tmp[1] = -ctrl_student_HIL_B.r_in;
  tmp[2] = 0.0;
  tmp[3] = ctrl_student_HIL_B.r_in;
  tmp[4] = 0.0;
  tmp[5] = 0.0;
  tmp[6] = 0.0;
  tmp[7] = 0.0;
  tmp[8] = 0.0;
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      L3[i + 3 * i_0] = 0.0;
      L3[i + 3 * i_0] += tmp[i] * R[i_0];
      L3[i + 3 * i_0] += tmp[i + 3] * R[i_0 + 3];
    }
  }

  for (i = 0; i < 3; i++) {
    L1_0[i] = L3[i + 6] * rtb_eta_d_s_c[2] + (L3[i + 3] * rtb_eta_d_s_c[1] +
      L3[i] * rtb_eta_d_s_c[0]);
  }

  /* MATLAB Function: '<S11>/Ellipse Mapper' incorporates:
   *  Constant: '<S11>/Constant'
   *  Integrator: '<S13>/Integrator'
   */
  eta_bar_idx_1 = -ctrl_student_HIL_P.R[0] * cos
    (ctrl_student_HIL_X.Integrator_CSTATE);
  eta_bar_idx_2 = -ctrl_student_HIL_P.R[3] * sin
    (ctrl_student_HIL_X.Integrator_CSTATE);
  psi_d = (ctrl_student_HIL_P.R[0] * ctrl_student_HIL_P.R[0] * cos
           (ctrl_student_HIL_X.Integrator_CSTATE) * sin
           (ctrl_student_HIL_X.Integrator_CSTATE) - ctrl_student_HIL_P.R[3] *
           ctrl_student_HIL_P.R[3] * cos(ctrl_student_HIL_X.Integrator_CSTATE) *
           sin(ctrl_student_HIL_X.Integrator_CSTATE)) * -2.0 *
    ctrl_student_HIL_P.R[0] * ctrl_student_HIL_P.R[3] / (t * t);

  /* MATLAB Function: '<S10>/MATLAB Function4' incorporates:
   *  MATLAB Function: '<S10>/MATLAB Function1'
   */
  for (i = 0; i < 3; i++) {
    R_0[i] = R[3 * i + 2] * psi_d + (R[3 * i + 1] * eta_bar_idx_2 + R[3 * i] *
      eta_bar_idx_1);
  }

  for (i = 0; i < 3; i++) {
    b_a_0[i] = R[3 * i + 2] * rtb_eta_d_s_c[2] + (R[3 * i + 1] * rtb_eta_d_s_c[1]
      + R[3 * i] * rtb_eta_d_s_c[0]);
  }

  for (i = 0; i < 3; i++) {
    rtb_alpha_1_dot_k[i] = ((((L1[i + 3] * 0.0 + L1[i] * 0.0) + L1[i + 6] * 0.0)
      + L1_0[i] * rtb_U_s_i) + R_0[i] * ctrl_student_HIL_B.Saturation *
      rtb_U_s_i) + b_a_0[i] * rtb_U_s_s * ctrl_student_HIL_B.Saturation;
  }

  /* MATLAB Function: '<S10>/MATLAB Function2' */
  ctrl_student_HI_MATLABFunction2(ctrl_student_HIL_B.eta_d,
    ctrl_student_HIL_B.x_in, ctrl_student_HIL_B.y_in, ctrl_student_HIL_B.psi_in,
    &ctrl_student_HIL_B.sf_MATLABFunction2);

  /* MATLAB Function: '<S10>/MATLAB Function' */
  ctrl_student_HIL_MATLABFunction(ctrl_student_HIL_B.u_in,
    ctrl_student_HIL_B.v_in, ctrl_student_HIL_B.r_in, rtb_alpha_1_dot_k,
    ctrl_student_HIL_B.sf_MATLABFunction2.z_1,
    &ctrl_student_HIL_B.sf_MATLABFunction_e);

  /* Saturate: '<S10>/Saturation' */
  if (ctrl_student_HIL_B.sf_MATLABFunction_e.tau[0] >
      ctrl_student_HIL_P.Saturation_UpperSat_d[0]) {
    ctrl_student_HIL_B.Saturation_d[0] =
      ctrl_student_HIL_P.Saturation_UpperSat_d[0];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_e.tau[0] <
             ctrl_student_HIL_P.Saturation_LowerSat_h[0]) {
    ctrl_student_HIL_B.Saturation_d[0] =
      ctrl_student_HIL_P.Saturation_LowerSat_h[0];
  } else {
    ctrl_student_HIL_B.Saturation_d[0] =
      ctrl_student_HIL_B.sf_MATLABFunction_e.tau[0];
  }

  if (ctrl_student_HIL_B.sf_MATLABFunction_e.tau[1] >
      ctrl_student_HIL_P.Saturation_UpperSat_d[1]) {
    ctrl_student_HIL_B.Saturation_d[1] =
      ctrl_student_HIL_P.Saturation_UpperSat_d[1];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_e.tau[1] <
             ctrl_student_HIL_P.Saturation_LowerSat_h[1]) {
    ctrl_student_HIL_B.Saturation_d[1] =
      ctrl_student_HIL_P.Saturation_LowerSat_h[1];
  } else {
    ctrl_student_HIL_B.Saturation_d[1] =
      ctrl_student_HIL_B.sf_MATLABFunction_e.tau[1];
  }

  if (ctrl_student_HIL_B.sf_MATLABFunction_e.tau[2] >
      ctrl_student_HIL_P.Saturation_UpperSat_d[2]) {
    ctrl_student_HIL_B.Saturation_d[2] =
      ctrl_student_HIL_P.Saturation_UpperSat_d[2];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_e.tau[2] <
             ctrl_student_HIL_P.Saturation_LowerSat_h[2]) {
    ctrl_student_HIL_B.Saturation_d[2] =
      ctrl_student_HIL_P.Saturation_LowerSat_h[2];
  } else {
    ctrl_student_HIL_B.Saturation_d[2] =
      ctrl_student_HIL_B.sf_MATLABFunction_e.tau[2];
  }

  /* End of Saturate: '<S10>/Saturation' */

  /* Integrator: '<S25>/Integrator'
   *
   * Regarding '<S25>/Integrator':
   *  Limited Integrator
   */
  if (ctrl_student_HIL_X.Integrator_CSTATE_h >=
      ctrl_student_HIL_P.Integrator_UpperSat ) {
    ctrl_student_HIL_X.Integrator_CSTATE_h =
      ctrl_student_HIL_P.Integrator_UpperSat;
  } else if (ctrl_student_HIL_X.Integrator_CSTATE_h <=
             ctrl_student_HIL_P.Integrator_LowerSat ) {
    ctrl_student_HIL_X.Integrator_CSTATE_h =
      ctrl_student_HIL_P.Integrator_LowerSat;
  }

  rtb_Integrator_e = ctrl_student_HIL_X.Integrator_CSTATE_h;

  /* MATLAB Function: '<S23>/MATLAB Function' incorporates:
   *  Constant: '<S23>/P_d'
   */
  /* MATLAB Function 'Line System 1-6 (DP line)/Line Mapper/MATLAB Function': '<S31>:1' */
  /* '<S31>:1:2' */
  /* '<S31>:1:3' */
  /* '<S31>:1:5' */
  /* '<S31>:1:6' */
  /* '<S31>:1:8' */
  rtb_eta_d_l[0] = (ctrl_student_HIL_P.P_d[1] - ctrl_student_HIL_P.P_d[0]) *
    rtb_Integrator_e + ctrl_student_HIL_P.P_d[0];
  rtb_eta_d_l[1] = (ctrl_student_HIL_P.P_d[3] - ctrl_student_HIL_P.P_d[2]) *
    rtb_Integrator_e + ctrl_student_HIL_P.P_d[2];
  rtb_eta_d_l[2] = rt_atan2d_snf(ctrl_student_HIL_P.P_d[3] -
    ctrl_student_HIL_P.P_d[2], ctrl_student_HIL_P.P_d[1] -
    ctrl_student_HIL_P.P_d[0]);

  /* '<S31>:1:9' */
  rtb_eta_d_s_n[0] = ctrl_student_HIL_P.P_d[1] - ctrl_student_HIL_P.P_d[0];
  rtb_eta_d_s_n[1] = ctrl_student_HIL_P.P_d[3] - ctrl_student_HIL_P.P_d[2];
  rtb_eta_d_s_n[2] = 0.0;
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* MATLAB Function: '<S24>/Line' incorporates:
     *  Constant: '<Root>/Constant5'
     *  Constant: '<S24>/Constant'
     */
    /* MATLAB Function 'Line System 1-6 (DP line)/Line Speed Gauge/Line': '<S32>:1' */
    /* '<S32>:1:2' */
    psi_d = ctrl_student_HIL_P.P_d[2] - ctrl_student_HIL_P.P_d[0];
    eta_bar_idx_1 = ctrl_student_HIL_P.P_d[3] - ctrl_student_HIL_P.P_d[1];
    ctrl_student_HIL_B.U_s = ctrl_student_HIL_P.U_ref / sqrt(psi_d * psi_d +
      eta_bar_idx_1 * eta_bar_idx_1);

    /* '<S32>:1:3' */
    ctrl_student_HIL_B.U_s_s = 0.0;
  }

  /* MATLAB Function: '<S25>/Update Law' */
  ctrl_student_HIL_UpdateLaw(ctrl_student_HIL_B.U_s, ctrl_student_HIL_B.mu,
    rtb_eta_d_s_n, rtb_eta_d_l, ctrl_student_HIL_B.x_in, ctrl_student_HIL_B.y_in,
    ctrl_student_HIL_B.psi_in, &ctrl_student_HIL_B.sf_UpdateLaw_o);

  /* Saturate: '<S25>/Saturation' */
  if (ctrl_student_HIL_B.sf_UpdateLaw_o.s_dot >
      ctrl_student_HIL_P.Saturation_UpperSat_a) {
    ctrl_student_HIL_B.Saturation_b = ctrl_student_HIL_P.Saturation_UpperSat_a;
  } else if (ctrl_student_HIL_B.sf_UpdateLaw_o.s_dot <
             ctrl_student_HIL_P.Saturation_LowerSat_n) {
    ctrl_student_HIL_B.Saturation_b = ctrl_student_HIL_P.Saturation_LowerSat_n;
  } else {
    ctrl_student_HIL_B.Saturation_b = ctrl_student_HIL_B.sf_UpdateLaw_o.s_dot;
  }

  /* End of Saturate: '<S25>/Saturation' */

  /* MATLAB Function: '<S22>/MATLAB Function1' */
  ctrl_student_HI_MATLABFunction1(ctrl_student_HIL_B.x_in,
    ctrl_student_HIL_B.y_in, ctrl_student_HIL_B.psi_in, rtb_eta_d_l,
    rtb_eta_d_s_n, ctrl_student_HIL_B.u_in, ctrl_student_HIL_B.v_in,
    ctrl_student_HIL_B.r_in, ctrl_student_HIL_B.Saturation_b,
    &ctrl_student_HIL_B.sf_MATLABFunction1_h);

  /* MATLAB Function: '<S22>/MATLAB Function4' incorporates:
   *  Constant: '<S22>/K_p'
   *  Constant: '<S3>/Constant'
   *  SignalConversion: '<S30>/TmpSignal ConversionAt SFunction Inport3'
   *  SignalConversion: '<S30>/TmpSignal ConversionAt SFunction Inport5'
   */
  /* MATLAB Function 'Line System 1-6 (DP line)/Control law/MATLAB Function4': '<S30>:1' */
  /* '<S30>:1:2' */
  /* '<S30>:1:3' */
  /* '<S30>:1:4' */
  /* '<S30>:1:5' */
  R[0] = cos(ctrl_student_HIL_B.psi_in);
  R[3] = -sin(ctrl_student_HIL_B.psi_in);
  R[6] = 0.0;
  R[1] = sin(ctrl_student_HIL_B.psi_in);
  R[4] = cos(ctrl_student_HIL_B.psi_in);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* '<S30>:1:9' */
  for (i = 0; i < 3; i++) {
    L1[3 * i] = -ctrl_student_HIL_P.K_p[3 * i];
    L1[1 + 3 * i] = -ctrl_student_HIL_P.K_p[3 * i + 1];
    L1[2 + 3 * i] = -ctrl_student_HIL_P.K_p[3 * i + 2];
  }

  tmp_0[0] = 0.0;
  tmp_0[1] = -ctrl_student_HIL_B.r_in;
  tmp_0[2] = 0.0;
  tmp_0[3] = ctrl_student_HIL_B.r_in;
  tmp_0[4] = 0.0;
  tmp_0[5] = 0.0;
  tmp_0[6] = 0.0;
  tmp_0[7] = 0.0;
  tmp_0[8] = 0.0;
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      tmp[i + 3 * i_0] = 0.0;
      tmp[i + 3 * i_0] += tmp_0[i] * R[i_0];
      tmp[i + 3 * i_0] += tmp_0[i + 3] * R[i_0 + 3];
    }
  }

  for (i = 0; i < 3; i++) {
    L1_0[i] = tmp[i + 6] * rtb_eta_d_s_n[2] + (tmp[i + 3] * rtb_eta_d_s_n[1] +
      tmp[i] * rtb_eta_d_s_n[0]);
  }

  for (i = 0; i < 3; i++) {
    R_0[i] = R[3 * i + 2] * ctrl_student_HIL_P.Constant_Value[2] + (R[3 * i + 1]
      * ctrl_student_HIL_P.Constant_Value[1] + R[3 * i] *
      ctrl_student_HIL_P.Constant_Value[0]);
  }

  for (i = 0; i < 3; i++) {
    b_a_0[i] = R[3 * i + 2] * rtb_eta_d_s_n[2] + (R[3 * i + 1] * rtb_eta_d_s_n[1]
      + R[3 * i] * rtb_eta_d_s_n[0]);
  }

  for (i = 0; i < 3; i++) {
    rtb_alpha_1_dot_c[i] = ((((L1[i + 3] *
      ctrl_student_HIL_B.sf_MATLABFunction1_h.z_1_dot[1] + L1[i] *
      ctrl_student_HIL_B.sf_MATLABFunction1_h.z_1_dot[0]) + L1[i + 6] *
      ctrl_student_HIL_B.sf_MATLABFunction1_h.z_1_dot[2]) + L1_0[i] *
      ctrl_student_HIL_B.U_s) + R_0[i] * ctrl_student_HIL_B.Saturation_b *
      ctrl_student_HIL_B.U_s) + b_a_0[i] * ctrl_student_HIL_B.U_s_s *
      ctrl_student_HIL_B.Saturation_b;
  }

  /* End of MATLAB Function: '<S22>/MATLAB Function4' */

  /* MATLAB Function: '<S22>/MATLAB Function2' */
  ctrl_student_HI_MATLABFunction2(rtb_eta_d_l, ctrl_student_HIL_B.x_in,
    ctrl_student_HIL_B.y_in, ctrl_student_HIL_B.psi_in,
    &ctrl_student_HIL_B.sf_MATLABFunction2_n);

  /* MATLAB Function: '<S22>/MATLAB Function' */
  ctrl_student_HIL_MATLABFunction(ctrl_student_HIL_B.u_in,
    ctrl_student_HIL_B.v_in, ctrl_student_HIL_B.r_in, rtb_alpha_1_dot_c,
    ctrl_student_HIL_B.sf_MATLABFunction2_n.z_1,
    &ctrl_student_HIL_B.sf_MATLABFunction_g);

  /* Saturate: '<S22>/Saturation' */
  if (ctrl_student_HIL_B.sf_MATLABFunction_g.tau[0] >
      ctrl_student_HIL_P.Saturation_UpperSat_f[0]) {
    ctrl_student_HIL_B.Saturation_o[0] =
      ctrl_student_HIL_P.Saturation_UpperSat_f[0];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_g.tau[0] <
             ctrl_student_HIL_P.Saturation_LowerSat_f[0]) {
    ctrl_student_HIL_B.Saturation_o[0] =
      ctrl_student_HIL_P.Saturation_LowerSat_f[0];
  } else {
    ctrl_student_HIL_B.Saturation_o[0] =
      ctrl_student_HIL_B.sf_MATLABFunction_g.tau[0];
  }

  if (ctrl_student_HIL_B.sf_MATLABFunction_g.tau[1] >
      ctrl_student_HIL_P.Saturation_UpperSat_f[1]) {
    ctrl_student_HIL_B.Saturation_o[1] =
      ctrl_student_HIL_P.Saturation_UpperSat_f[1];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_g.tau[1] <
             ctrl_student_HIL_P.Saturation_LowerSat_f[1]) {
    ctrl_student_HIL_B.Saturation_o[1] =
      ctrl_student_HIL_P.Saturation_LowerSat_f[1];
  } else {
    ctrl_student_HIL_B.Saturation_o[1] =
      ctrl_student_HIL_B.sf_MATLABFunction_g.tau[1];
  }

  if (ctrl_student_HIL_B.sf_MATLABFunction_g.tau[2] >
      ctrl_student_HIL_P.Saturation_UpperSat_f[2]) {
    ctrl_student_HIL_B.Saturation_o[2] =
      ctrl_student_HIL_P.Saturation_UpperSat_f[2];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_g.tau[2] <
             ctrl_student_HIL_P.Saturation_LowerSat_f[2]) {
    ctrl_student_HIL_B.Saturation_o[2] =
      ctrl_student_HIL_P.Saturation_LowerSat_f[2];
  } else {
    ctrl_student_HIL_B.Saturation_o[2] =
      ctrl_student_HIL_B.sf_MATLABFunction_g.tau[2];
  }

  /* End of Saturate: '<S22>/Saturation' */

  /* Integrator: '<S37>/Integrator'
   *
   * Regarding '<S37>/Integrator':
   *  Limited Integrator
   */
  if (ctrl_student_HIL_X.Integrator_CSTATE_c >=
      ctrl_student_HIL_P.Integrator_UpperSat_a ) {
    ctrl_student_HIL_X.Integrator_CSTATE_c =
      ctrl_student_HIL_P.Integrator_UpperSat_a;
  } else if (ctrl_student_HIL_X.Integrator_CSTATE_c <=
             ctrl_student_HIL_P.Integrator_LowerSat_f ) {
    ctrl_student_HIL_X.Integrator_CSTATE_c =
      ctrl_student_HIL_P.Integrator_LowerSat_f;
  }

  rtb_Integrator_g = ctrl_student_HIL_X.Integrator_CSTATE_c;
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Memory: '<S35>/Memory' */
    ctrl_student_HIL_B.Memory = ctrl_student_HIL_DW.Memory_PreviousInput;
  }

  /* MATLAB Function: '<S35>/MATLAB Function' incorporates:
   *  Constant: '<S35>/P_d'
   */
  /* MATLAB Function 'Line System 2-6 (Man.line)/Line Mapper/MATLAB Function': '<S43>:1' */
  /* '<S43>:1:2' */
  rtb_U_s_s = rtb_Integrator_g / 2.0;
  eta_bar_idx_1 = fabs((rtb_Integrator_g - floor(rtb_U_s_s) * 2.0) - 1.0);
  rtb_U_s_s = 1.0 - fabs((rtb_Integrator_g - floor(rtb_U_s_s) * 2.0) - 1.0);

  /* '<S43>:1:3' */
  /* '<S43>:1:4' */
  psi_d = rt_atan2d_snf(ctrl_student_HIL_P.P_d[3] - ctrl_student_HIL_P.P_d[2],
                        ctrl_student_HIL_P.P_d[1] - ctrl_student_HIL_P.P_d[0]);
  if (ctrl_student_HIL_B.Memory - (1.0 - eta_bar_idx_1) < 0.0) {
    /* '<S43>:1:5' */
    /* '<S43>:1:6' */
    psi_d = 3.1415926535897931 - psi_d;
  }

  /* '<S43>:1:8' */
  /* '<S43>:1:9' */
  /* '<S43>:1:13' */
  rtb_eta_d[0] = (ctrl_student_HIL_P.P_d[1] - ctrl_student_HIL_P.P_d[0]) *
    rtb_U_s_s + ctrl_student_HIL_P.P_d[0];
  rtb_eta_d[1] = (ctrl_student_HIL_P.P_d[3] - ctrl_student_HIL_P.P_d[2]) *
    rtb_U_s_s + ctrl_student_HIL_P.P_d[2];
  rtb_eta_d[2] = psi_d;

  /* '<S43>:1:14' */
  rtb_eta_d_s[0] = ctrl_student_HIL_P.P_d[1] - ctrl_student_HIL_P.P_d[0];
  rtb_eta_d_s[1] = ctrl_student_HIL_P.P_d[3] - ctrl_student_HIL_P.P_d[2];
  rtb_eta_d_s[2] = 0.0;

  /* '<S43>:1:16' */
  ctrl_student_HIL_B.s_proc = 1.0 - eta_bar_idx_1;

  /* End of MATLAB Function: '<S35>/MATLAB Function' */

  /* MATLAB Function: '<S36>/Line' incorporates:
   *  Constant: '<S36>/Constant'
   */
  /* MATLAB Function 'Line System 2-6 (Man.line)/Line Speed Gauge/Line': '<S44>:1' */
  /* '<S44>:1:2' */
  psi_d = ctrl_student_HIL_P.P_d[2] - ctrl_student_HIL_P.P_d[0];
  eta_bar_idx_1 = ctrl_student_HIL_P.P_d[3] - ctrl_student_HIL_P.P_d[1];
  rtb_U_s = ctrl_student_HIL_B.Uref / sqrt(psi_d * psi_d + eta_bar_idx_1 *
    eta_bar_idx_1);

  /* MATLAB Function: '<S37>/Update Law' incorporates:
   *  SignalConversion: '<S45>/TmpSignal ConversionAt SFunction Inport5'
   */
  /* MATLAB Function 'Line System 2-6 (Man.line)/Update Law1/Update Law': '<S45>:1' */
  /* '<S45>:1:2' */
  /* diff(3) = angdiff(eta_d(3), eta(3)); % Order is important here */
  /* '<S45>:1:4' */
  /* '<S45>:1:5' */
  psi_d = ((ctrl_student_HIL_B.psi_in - rtb_eta_d[2]) + 3.1415926535897931) /
    6.2831853071795862;
  if (fabs(psi_d - rt_roundd_snf(psi_d)) <= 2.2204460492503131E-16 * fabs(psi_d))
  {
    psi_d = 0.0;
  } else {
    psi_d = (psi_d - floor(psi_d)) * 6.2831853071795862;
  }

  eta_bar_idx_2 = psi_d - 3.1415926535897931;

  /* '<S45>:1:6' */
  rtb_U_s_s = 2.2250738585072014E-308;
  psi_d = fabs(rtb_eta_d_s[0]);
  if (psi_d > 2.2250738585072014E-308) {
    eta_bar_idx_1 = 1.0;
    rtb_U_s_s = psi_d;
  } else {
    t = psi_d / 2.2250738585072014E-308;
    eta_bar_idx_1 = t * t;
  }

  psi_d = fabs(rtb_eta_d_s[1]);
  if (psi_d > rtb_U_s_s) {
    t = rtb_U_s_s / psi_d;
    eta_bar_idx_1 = eta_bar_idx_1 * t * t + 1.0;
    rtb_U_s_s = psi_d;
  } else {
    t = psi_d / rtb_U_s_s;
    eta_bar_idx_1 += t * t;
  }

  psi_d = fabs(rtb_eta_d_s[2]);
  if (psi_d > rtb_U_s_s) {
    t = rtb_U_s_s / psi_d;
    eta_bar_idx_1 = eta_bar_idx_1 * t * t + 1.0;
    rtb_U_s_s = psi_d;
  } else {
    t = psi_d / rtb_U_s_s;
    eta_bar_idx_1 += t * t;
  }

  eta_bar_idx_1 = rtb_U_s_s * sqrt(eta_bar_idx_1);
  psi_d = ctrl_student_HIL_B.mu / eta_bar_idx_1;
  psi_d = rtb_U_s - ((-(ctrl_student_HIL_B.x_in - rtb_eta_d[0]) * psi_d *
                      rtb_eta_d_s[0] + -(ctrl_student_HIL_B.y_in - rtb_eta_d[1])
                      * psi_d * rtb_eta_d_s[1]) + psi_d * -eta_bar_idx_2 *
                     rtb_eta_d_s[2]);

  /* End of MATLAB Function: '<S37>/Update Law' */

  /* Saturate: '<S37>/Saturation' */
  if (psi_d > ctrl_student_HIL_P.Saturation_UpperSat_c) {
    ctrl_student_HIL_B.Saturation_g = ctrl_student_HIL_P.Saturation_UpperSat_c;
  } else if (psi_d < ctrl_student_HIL_P.Saturation_LowerSat_nv) {
    ctrl_student_HIL_B.Saturation_g = ctrl_student_HIL_P.Saturation_LowerSat_nv;
  } else {
    ctrl_student_HIL_B.Saturation_g = psi_d;
  }

  /* End of Saturate: '<S37>/Saturation' */

  /* MATLAB Function: '<S34>/MATLAB Function1' */
  ctrl_student_HI_MATLABFunction1(ctrl_student_HIL_B.x_in,
    ctrl_student_HIL_B.y_in, ctrl_student_HIL_B.psi_in, rtb_eta_d, rtb_eta_d_s,
    ctrl_student_HIL_B.u_in, ctrl_student_HIL_B.v_in, ctrl_student_HIL_B.r_in,
    ctrl_student_HIL_B.Saturation_g, &ctrl_student_HIL_B.sf_MATLABFunction1_d);

  /* MATLAB Function: '<S34>/MATLAB Function4' incorporates:
   *  Constant: '<S34>/K_p'
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant1'
   *  SignalConversion: '<S42>/TmpSignal ConversionAt SFunction Inport3'
   *  SignalConversion: '<S42>/TmpSignal ConversionAt SFunction Inport5'
   */
  /* MATLAB Function 'Line System 2-6 (Man.line)/Control law1/MATLAB Function4': '<S42>:1' */
  /* '<S42>:1:2' */
  /* '<S42>:1:3' */
  /* '<S42>:1:4' */
  /* '<S42>:1:5' */
  R[0] = cos(ctrl_student_HIL_B.psi_in);
  R[3] = -sin(ctrl_student_HIL_B.psi_in);
  R[6] = 0.0;
  R[1] = sin(ctrl_student_HIL_B.psi_in);
  R[4] = cos(ctrl_student_HIL_B.psi_in);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* '<S42>:1:9' */
  for (i = 0; i < 3; i++) {
    L1[3 * i] = -ctrl_student_HIL_P.K_p[3 * i];
    L1[1 + 3 * i] = -ctrl_student_HIL_P.K_p[3 * i + 1];
    L1[2 + 3 * i] = -ctrl_student_HIL_P.K_p[3 * i + 2];
  }

  tmp_1[0] = 0.0;
  tmp_1[1] = -ctrl_student_HIL_B.r_in;
  tmp_1[2] = 0.0;
  tmp_1[3] = ctrl_student_HIL_B.r_in;
  tmp_1[4] = 0.0;
  tmp_1[5] = 0.0;
  tmp_1[6] = 0.0;
  tmp_1[7] = 0.0;
  tmp_1[8] = 0.0;
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      tmp[i + 3 * i_0] = 0.0;
      tmp[i + 3 * i_0] += tmp_1[i] * R[i_0];
      tmp[i + 3 * i_0] += tmp_1[i + 3] * R[i_0 + 3];
    }
  }

  for (i = 0; i < 3; i++) {
    L1_0[i] = tmp[i + 6] * rtb_eta_d_s[2] + (tmp[i + 3] * rtb_eta_d_s[1] + tmp[i]
      * rtb_eta_d_s[0]);
  }

  for (i = 0; i < 3; i++) {
    R_0[i] = R[3 * i + 2] * ctrl_student_HIL_P.Constant_Value_i[2] + (R[3 * i +
      1] * ctrl_student_HIL_P.Constant_Value_i[1] + R[3 * i] *
      ctrl_student_HIL_P.Constant_Value_i[0]);
  }

  for (i = 0; i < 3; i++) {
    b_a_0[i] = R[3 * i + 2] * rtb_eta_d_s[2] + (R[3 * i + 1] * rtb_eta_d_s[1] +
      R[3 * i] * rtb_eta_d_s[0]);
  }

  for (i = 0; i < 3; i++) {
    rtb_alpha_1_dot[i] = ((((L1[i + 3] *
      ctrl_student_HIL_B.sf_MATLABFunction1_d.z_1_dot[1] + L1[i] *
      ctrl_student_HIL_B.sf_MATLABFunction1_d.z_1_dot[0]) + L1[i + 6] *
      ctrl_student_HIL_B.sf_MATLABFunction1_d.z_1_dot[2]) + L1_0[i] * rtb_U_s) +
                          R_0[i] * ctrl_student_HIL_B.Saturation_g * rtb_U_s) +
      b_a_0[i] * ctrl_student_HIL_P.Constant1_Value *
      ctrl_student_HIL_B.Saturation_g;
  }

  /* End of MATLAB Function: '<S34>/MATLAB Function4' */

  /* MATLAB Function: '<S34>/MATLAB Function2' */
  ctrl_student_HI_MATLABFunction2(rtb_eta_d, ctrl_student_HIL_B.x_in,
    ctrl_student_HIL_B.y_in, ctrl_student_HIL_B.psi_in,
    &ctrl_student_HIL_B.sf_MATLABFunction2_d);

  /* MATLAB Function: '<S34>/MATLAB Function' */
  ctrl_student_HIL_MATLABFunction(ctrl_student_HIL_B.u_in,
    ctrl_student_HIL_B.v_in, ctrl_student_HIL_B.r_in, rtb_alpha_1_dot,
    ctrl_student_HIL_B.sf_MATLABFunction2_d.z_1,
    &ctrl_student_HIL_B.sf_MATLABFunction_l);

  /* Saturate: '<S34>/Saturation' */
  if (ctrl_student_HIL_B.sf_MATLABFunction_l.tau[0] >
      ctrl_student_HIL_P.Saturation_UpperSat_b[0]) {
    ctrl_student_HIL_B.Saturation_m[0] =
      ctrl_student_HIL_P.Saturation_UpperSat_b[0];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_l.tau[0] <
             ctrl_student_HIL_P.Saturation_LowerSat_c[0]) {
    ctrl_student_HIL_B.Saturation_m[0] =
      ctrl_student_HIL_P.Saturation_LowerSat_c[0];
  } else {
    ctrl_student_HIL_B.Saturation_m[0] =
      ctrl_student_HIL_B.sf_MATLABFunction_l.tau[0];
  }

  if (ctrl_student_HIL_B.sf_MATLABFunction_l.tau[1] >
      ctrl_student_HIL_P.Saturation_UpperSat_b[1]) {
    ctrl_student_HIL_B.Saturation_m[1] =
      ctrl_student_HIL_P.Saturation_UpperSat_b[1];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_l.tau[1] <
             ctrl_student_HIL_P.Saturation_LowerSat_c[1]) {
    ctrl_student_HIL_B.Saturation_m[1] =
      ctrl_student_HIL_P.Saturation_LowerSat_c[1];
  } else {
    ctrl_student_HIL_B.Saturation_m[1] =
      ctrl_student_HIL_B.sf_MATLABFunction_l.tau[1];
  }

  if (ctrl_student_HIL_B.sf_MATLABFunction_l.tau[2] >
      ctrl_student_HIL_P.Saturation_UpperSat_b[2]) {
    ctrl_student_HIL_B.Saturation_m[2] =
      ctrl_student_HIL_P.Saturation_UpperSat_b[2];
  } else if (ctrl_student_HIL_B.sf_MATLABFunction_l.tau[2] <
             ctrl_student_HIL_P.Saturation_LowerSat_c[2]) {
    ctrl_student_HIL_B.Saturation_m[2] =
      ctrl_student_HIL_P.Saturation_LowerSat_c[2];
  } else {
    ctrl_student_HIL_B.Saturation_m[2] =
      ctrl_student_HIL_B.sf_MATLABFunction_l.tau[2];
  }

  /* End of Saturate: '<S34>/Saturation' */

  /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
   *  Constant: '<Root>/Constant3'
   */
  switch ((int32_T)ctrl_student_HIL_P.Constant3_Value) {
   case 1:
    ctrl_student_HIL_B.MultiportSwitch[0] = ctrl_student_HIL_B.Saturation_d[0];
    ctrl_student_HIL_B.MultiportSwitch[1] = ctrl_student_HIL_B.Saturation_d[1];
    ctrl_student_HIL_B.MultiportSwitch[2] = ctrl_student_HIL_B.Saturation_d[2];
    break;

   case 2:
    ctrl_student_HIL_B.MultiportSwitch[0] = ctrl_student_HIL_B.Saturation_o[0];
    ctrl_student_HIL_B.MultiportSwitch[1] = ctrl_student_HIL_B.Saturation_o[1];
    ctrl_student_HIL_B.MultiportSwitch[2] = ctrl_student_HIL_B.Saturation_o[2];
    break;

   default:
    ctrl_student_HIL_B.MultiportSwitch[0] = ctrl_student_HIL_B.Saturation_m[0];
    ctrl_student_HIL_B.MultiportSwitch[1] = ctrl_student_HIL_B.Saturation_m[1];
    ctrl_student_HIL_B.MultiportSwitch[2] = ctrl_student_HIL_B.Saturation_m[2];
    break;
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
  }
}

/* Model update function */
void ctrl_student_HIL_update(void)
{
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Update for Memory: '<S46>/counter' */
    ctrl_student_HIL_DW.counter_PreviousInput = ctrl_student_HIL_B.count;

    /* Update for RandomNumber: '<S52>/White Noise' */
    ctrl_student_HIL_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&ctrl_student_HIL_DW.RandSeed) * ctrl_student_HIL_P.WhiteNoise_StdDev +
      ctrl_student_HIL_P.WhiteNoise_Mean;

    /* Update for RandomNumber: '<S53>/White Noise' */
    ctrl_student_HIL_DW.NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf
      (&ctrl_student_HIL_DW.RandSeed_j) * ctrl_student_HIL_P.WhiteNoise_StdDev_d
      + ctrl_student_HIL_P.WhiteNoise_Mean_h;

    /* Update for RandomNumber: '<S51>/White Noise' */
    ctrl_student_HIL_DW.NextOutput_p = rt_nrand_Upu32_Yd_f_pw_snf
      (&ctrl_student_HIL_DW.RandSeed_c) * ctrl_student_HIL_P.WhiteNoise_StdDev_g
      + ctrl_student_HIL_P.WhiteNoise_Mean_f;

    /* Update for Memory: '<S47>/Hold' */
    ctrl_student_HIL_DW.Hold_PreviousInput[0] = ctrl_student_HIL_B.output[0];
    ctrl_student_HIL_DW.Hold_PreviousInput[1] = ctrl_student_HIL_B.output[1];
    ctrl_student_HIL_DW.Hold_PreviousInput[2] = ctrl_student_HIL_B.output[2];

    /* Update for Memory: '<S1>/Memory4' */
    ctrl_student_HIL_DW.Memory4_PreviousInput[0] =
      ctrl_student_HIL_B.Integrator[0];
    ctrl_student_HIL_DW.Memory4_PreviousInput[1] =
      ctrl_student_HIL_B.Integrator[1];
    ctrl_student_HIL_DW.Memory4_PreviousInput[2] =
      ctrl_student_HIL_B.Integrator[2];

    /* Update for Memory: '<S1>/Memory3' */
    ctrl_student_HIL_DW.Memory3_PreviousInput[0] =
      ctrl_student_HIL_B.Integrator1[0];
    ctrl_student_HIL_DW.Memory3_PreviousInput[1] =
      ctrl_student_HIL_B.Integrator1[1];
    ctrl_student_HIL_DW.Memory3_PreviousInput[2] =
      ctrl_student_HIL_B.Integrator1[2];

    /* Update for Memory: '<S1>/Memory2' */
    ctrl_student_HIL_DW.Memory2_PreviousInput[0] =
      ctrl_student_HIL_B.Integrator2[0];
    ctrl_student_HIL_DW.Memory2_PreviousInput[1] =
      ctrl_student_HIL_B.Integrator2[1];
    ctrl_student_HIL_DW.Memory2_PreviousInput[2] =
      ctrl_student_HIL_B.Integrator2[2];
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Update for Memory: '<S35>/Memory' */
    ctrl_student_HIL_DW.Memory_PreviousInput = ctrl_student_HIL_B.s_proc;
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    rt_ertODEUpdateContinuousStates(&ctrl_student_HIL_M->solverInfo);
  }

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

  ctrl_student_HIL_M->Timing.t[0] = rtsiGetSolverStopTime
    (&ctrl_student_HIL_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++ctrl_student_HIL_M->Timing.clockTick1)) {
      ++ctrl_student_HIL_M->Timing.clockTickH1;
    }

    ctrl_student_HIL_M->Timing.t[1] = ctrl_student_HIL_M->Timing.clockTick1 *
      ctrl_student_HIL_M->Timing.stepSize1 +
      ctrl_student_HIL_M->Timing.clockTickH1 *
      ctrl_student_HIL_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void ctrl_student_HIL_derivatives(void)
{
  XDot_ctrl_student_HIL_T *_rtXdot;
  _rtXdot = ((XDot_ctrl_student_HIL_T *) ctrl_student_HIL_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S13>/Integrator' */
  _rtXdot->Integrator_CSTATE = ctrl_student_HIL_B.Saturation;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE_m[0] = ctrl_student_HIL_B.eta_hat_dot[0];
  _rtXdot->Integrator_CSTATE_m[1] = ctrl_student_HIL_B.eta_hat_dot[1];
  _rtXdot->Integrator_CSTATE_m[2] = ctrl_student_HIL_B.eta_hat_dot[2];

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = ctrl_student_HIL_B.nu_hat_dot[0];
  _rtXdot->Integrator1_CSTATE[1] = ctrl_student_HIL_B.nu_hat_dot[1];
  _rtXdot->Integrator1_CSTATE[2] = ctrl_student_HIL_B.nu_hat_dot[2];

  /* Derivatives for Integrator: '<S1>/Integrator2' */
  _rtXdot->Integrator2_CSTATE[0] = ctrl_student_HIL_B.b_hat_dot[0];
  _rtXdot->Integrator2_CSTATE[1] = ctrl_student_HIL_B.b_hat_dot[1];
  _rtXdot->Integrator2_CSTATE[2] = ctrl_student_HIL_B.b_hat_dot[2];

  /* Derivatives for Integrator: '<S25>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( ctrl_student_HIL_X.Integrator_CSTATE_h <=
            ctrl_student_HIL_P.Integrator_LowerSat );
    usat = ( ctrl_student_HIL_X.Integrator_CSTATE_h >=
            ctrl_student_HIL_P.Integrator_UpperSat );
    if ((!lsat && !usat) ||
        (lsat && (ctrl_student_HIL_B.Saturation_b > 0)) ||
        (usat && (ctrl_student_HIL_B.Saturation_b < 0)) ) {
      ((XDot_ctrl_student_HIL_T *) ctrl_student_HIL_M->ModelData.derivs)
        ->Integrator_CSTATE_h = ctrl_student_HIL_B.Saturation_b;
    } else {
      /* in saturation */
      ((XDot_ctrl_student_HIL_T *) ctrl_student_HIL_M->ModelData.derivs)
        ->Integrator_CSTATE_h = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S37>/Integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( ctrl_student_HIL_X.Integrator_CSTATE_c <=
            ctrl_student_HIL_P.Integrator_LowerSat_f );
    usat = ( ctrl_student_HIL_X.Integrator_CSTATE_c >=
            ctrl_student_HIL_P.Integrator_UpperSat_a );
    if ((!lsat && !usat) ||
        (lsat && (ctrl_student_HIL_B.Saturation_g > 0)) ||
        (usat && (ctrl_student_HIL_B.Saturation_g < 0)) ) {
      ((XDot_ctrl_student_HIL_T *) ctrl_student_HIL_M->ModelData.derivs)
        ->Integrator_CSTATE_c = ctrl_student_HIL_B.Saturation_g;
    } else {
      /* in saturation */
      ((XDot_ctrl_student_HIL_T *) ctrl_student_HIL_M->ModelData.derivs)
        ->Integrator_CSTATE_c = 0.0;
    }
  }
}

/* Model initialize function */
void ctrl_student_HIL_initialize(void)
{
  {
    uint32_T tseed;
    int32_T r;
    int32_T t;
    real_T tmp;

    /* InitializeConditions for Memory: '<S46>/counter' */
    ctrl_student_HIL_DW.counter_PreviousInput = ctrl_student_HIL_P.counter_X0;

    /* InitializeConditions for RandomNumber: '<S52>/White Noise' */
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

    /* End of InitializeConditions for RandomNumber: '<S52>/White Noise' */

    /* InitializeConditions for RandomNumber: '<S53>/White Noise' */
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

    /* End of InitializeConditions for RandomNumber: '<S53>/White Noise' */

    /* InitializeConditions for RandomNumber: '<S51>/White Noise' */
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

    /* End of InitializeConditions for RandomNumber: '<S51>/White Noise' */

    /* InitializeConditions for Memory: '<S47>/Hold' */
    ctrl_student_HIL_DW.Hold_PreviousInput[0] = ctrl_student_HIL_P.Hold_X0;
    ctrl_student_HIL_DW.Hold_PreviousInput[1] = ctrl_student_HIL_P.Hold_X0;
    ctrl_student_HIL_DW.Hold_PreviousInput[2] = ctrl_student_HIL_P.Hold_X0;

    /* InitializeConditions for Integrator: '<S13>/Integrator' */
    ctrl_student_HIL_X.Integrator_CSTATE = ctrl_student_HIL_P.Integrator_IC;

    /* InitializeConditions for Integrator: '<S1>/Integrator' */
    ctrl_student_HIL_X.Integrator_CSTATE_m[0] =
      ctrl_student_HIL_P.Integrator_IC_d;
    ctrl_student_HIL_X.Integrator_CSTATE_m[1] =
      ctrl_student_HIL_P.Integrator_IC_d;
    ctrl_student_HIL_X.Integrator_CSTATE_m[2] =
      ctrl_student_HIL_P.Integrator_IC_d;

    /* InitializeConditions for Integrator: '<S1>/Integrator1' */
    ctrl_student_HIL_X.Integrator1_CSTATE[0] = ctrl_student_HIL_P.Integrator1_IC;
    ctrl_student_HIL_X.Integrator1_CSTATE[1] = ctrl_student_HIL_P.Integrator1_IC;
    ctrl_student_HIL_X.Integrator1_CSTATE[2] = ctrl_student_HIL_P.Integrator1_IC;

    /* InitializeConditions for Memory: '<S1>/Memory4' */
    ctrl_student_HIL_DW.Memory4_PreviousInput[0] =
      ctrl_student_HIL_P.Memory4_X0[0];
    ctrl_student_HIL_DW.Memory4_PreviousInput[1] =
      ctrl_student_HIL_P.Memory4_X0[1];
    ctrl_student_HIL_DW.Memory4_PreviousInput[2] =
      ctrl_student_HIL_P.Memory4_X0[2];

    /* InitializeConditions for Memory: '<S1>/Memory3' */
    ctrl_student_HIL_DW.Memory3_PreviousInput[0] =
      ctrl_student_HIL_P.Memory3_X0[0];
    ctrl_student_HIL_DW.Memory3_PreviousInput[1] =
      ctrl_student_HIL_P.Memory3_X0[1];
    ctrl_student_HIL_DW.Memory3_PreviousInput[2] =
      ctrl_student_HIL_P.Memory3_X0[2];

    /* InitializeConditions for Memory: '<S1>/Memory2' */
    ctrl_student_HIL_DW.Memory2_PreviousInput[0] =
      ctrl_student_HIL_P.Memory2_X0[0];
    ctrl_student_HIL_DW.Memory2_PreviousInput[1] =
      ctrl_student_HIL_P.Memory2_X0[1];
    ctrl_student_HIL_DW.Memory2_PreviousInput[2] =
      ctrl_student_HIL_P.Memory2_X0[2];

    /* InitializeConditions for Integrator: '<S1>/Integrator2' */
    ctrl_student_HIL_X.Integrator2_CSTATE[0] = ctrl_student_HIL_P.Integrator2_IC;
    ctrl_student_HIL_X.Integrator2_CSTATE[1] = ctrl_student_HIL_P.Integrator2_IC;
    ctrl_student_HIL_X.Integrator2_CSTATE[2] = ctrl_student_HIL_P.Integrator2_IC;

    /* InitializeConditions for Integrator: '<S25>/Integrator' */
    ctrl_student_HIL_X.Integrator_CSTATE_h = ctrl_student_HIL_P.Integrator_IC_l;

    /* InitializeConditions for Integrator: '<S37>/Integrator' */
    ctrl_student_HIL_X.Integrator_CSTATE_c = ctrl_student_HIL_P.Integrator_IC_m;

    /* InitializeConditions for Memory: '<S35>/Memory' */
    ctrl_student_HIL_DW.Memory_PreviousInput = ctrl_student_HIL_P.Memory_X0;
  }
}

/* Model terminate function */
void ctrl_student_HIL_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

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

  /* non-finite (run-time) assignments */
  ctrl_student_HIL_P.Saturation_UpperSat = rtInf;
  ctrl_student_HIL_P.Saturation_UpperSat_a = rtInf;
  ctrl_student_HIL_P.Saturation_UpperSat_c = rtInf;

  /* initialize real-time model */
  (void) memset((void *)ctrl_student_HIL_M, 0,
                sizeof(RT_MODEL_ctrl_student_HIL_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ctrl_student_HIL_M->solverInfo,
                          &ctrl_student_HIL_M->Timing.simTimeStep);
    rtsiSetTPtr(&ctrl_student_HIL_M->solverInfo, &rtmGetTPtr(ctrl_student_HIL_M));
    rtsiSetStepSizePtr(&ctrl_student_HIL_M->solverInfo,
                       &ctrl_student_HIL_M->Timing.stepSize0);
    rtsiSetdXPtr(&ctrl_student_HIL_M->solverInfo,
                 &ctrl_student_HIL_M->ModelData.derivs);
    rtsiSetContStatesPtr(&ctrl_student_HIL_M->solverInfo, (real_T **)
                         &ctrl_student_HIL_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&ctrl_student_HIL_M->solverInfo,
      &ctrl_student_HIL_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&ctrl_student_HIL_M->solverInfo, (&rtmGetErrorStatus
      (ctrl_student_HIL_M)));
    rtsiSetRTModelPtr(&ctrl_student_HIL_M->solverInfo, ctrl_student_HIL_M);
  }

  rtsiSetSimTimeStep(&ctrl_student_HIL_M->solverInfo, MAJOR_TIME_STEP);
  ctrl_student_HIL_M->ModelData.intgData.y = ctrl_student_HIL_M->ModelData.odeY;
  ctrl_student_HIL_M->ModelData.intgData.f[0] =
    ctrl_student_HIL_M->ModelData.odeF[0];
  ctrl_student_HIL_M->ModelData.intgData.f[1] =
    ctrl_student_HIL_M->ModelData.odeF[1];
  ctrl_student_HIL_M->ModelData.intgData.f[2] =
    ctrl_student_HIL_M->ModelData.odeF[2];
  ctrl_student_HIL_M->ModelData.intgData.f[3] =
    ctrl_student_HIL_M->ModelData.odeF[3];
  ctrl_student_HIL_M->ModelData.contStates = ((real_T *) &ctrl_student_HIL_X);
  rtsiSetSolverData(&ctrl_student_HIL_M->solverInfo, (void *)
                    &ctrl_student_HIL_M->ModelData.intgData);
  rtsiSetSolverName(&ctrl_student_HIL_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = ctrl_student_HIL_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    ctrl_student_HIL_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    ctrl_student_HIL_M->Timing.sampleTimes =
      (&ctrl_student_HIL_M->Timing.sampleTimesArray[0]);
    ctrl_student_HIL_M->Timing.offsetTimes =
      (&ctrl_student_HIL_M->Timing.offsetTimesArray[0]);

    /* task periods */
    ctrl_student_HIL_M->Timing.sampleTimes[0] = (0.0);
    ctrl_student_HIL_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    ctrl_student_HIL_M->Timing.offsetTimes[0] = (0.0);
    ctrl_student_HIL_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(ctrl_student_HIL_M, &ctrl_student_HIL_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = ctrl_student_HIL_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    ctrl_student_HIL_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(ctrl_student_HIL_M, -1);
  ctrl_student_HIL_M->Timing.stepSize0 = 0.01;
  ctrl_student_HIL_M->Timing.stepSize1 = 0.01;

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

  /* states (continuous) */
  {
    real_T *x = (real_T *) &ctrl_student_HIL_X;
    ctrl_student_HIL_M->ModelData.contStates = (x);
    (void) memset((void *)&ctrl_student_HIL_X, 0,
                  sizeof(X_ctrl_student_HIL_T));
  }

  /* states (dwork) */
  ctrl_student_HIL_M->ModelData.dwork = ((void *) &ctrl_student_HIL_DW);
  (void) memset((void *)&ctrl_student_HIL_DW, 0,
                sizeof(DW_ctrl_student_HIL_T));

  /* Initialize Sizes */
  ctrl_student_HIL_M->Sizes.numContStates = (12);/* Number of continuous states */
  ctrl_student_HIL_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  ctrl_student_HIL_M->Sizes.numY = (0);/* Number of model outputs */
  ctrl_student_HIL_M->Sizes.numU = (0);/* Number of model inputs */
  ctrl_student_HIL_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  ctrl_student_HIL_M->Sizes.numSampTimes = (2);/* Number of sample times */
  ctrl_student_HIL_M->Sizes.numBlocks = (167);/* Number of blocks */
  ctrl_student_HIL_M->Sizes.numBlockIO = (69);/* Number of block outputs */
  ctrl_student_HIL_M->Sizes.numBlockPrms = (392);/* Sum of parameter "widths" */
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
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 19:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 20:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 21:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 22:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 23:
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 26:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 27:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 28:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 29:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 41:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 42:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 19:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 20:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 21:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 22:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 23:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 26:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 27:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 28:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 29:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 41:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 42:
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

  // noise pos
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.noisepos, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // noise head
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.noisehead, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // y_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.y_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // x_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.x_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // psi_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.psi_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // enable noise
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.enablenoise, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // r_in
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

  // Reset
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.Reset, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // mu
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.mu, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // DP Observer /L1_diag
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L1_diag, 0, data[index++], 18, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L1_diag, 1, data[index++], 18, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L1_diag, 2, data[index++], 18, 0);
  } else {
    index += 3;
  }

  // DP Observer /L2_diag
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L2_diag, 0, data[index++], 18, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L2_diag, 1, data[index++], 18, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L2_diag, 2, data[index++], 18, 0);
  } else {
    index += 3;
  }

  // DP Observer /L3_diag
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L3_diag, 0, data[index++], 18, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L3_diag, 1, data[index++], 18, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L3_diag, 2, data[index++], 18, 0);
  } else {
    index += 3;
  }

  // DP Observer /b
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.b, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Uref
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.Uref, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/L2_continuous
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L2_continuous, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // joystick/PosXRight
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosXRight, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/PosYRight
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosYRight, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/R2_continuous
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.R2_continuous, 0, data[index++],
      0, 0);
  } else {
    index += 1;
  }

  // joystick/PosXLeft
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosXLeft, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/PosYLeft
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.PosYLeft, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/L1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.L1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/R1
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.R1, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/ArrowDown
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowDown, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/ArrowUp
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowUp, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // joystick/ArrowLeft
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowLeft, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }

  // joystick/ArrowRight
  if (TaskSampleHit[1]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.ArrowRight, 0, data[index++], 0,
      0);
  } else {
    index += 1;
  }
}                                      /* of SetExternalInputs */

long NumInputPorts(void)
{
  return 34;
}

double ni_extout[22];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

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

  // psi_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,2,17,
      0);
  } else {
    index += 1;
  }

  // x_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,0,17,
      0);
  } else {
    index += 1;
  }

  // y_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,1,17,
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

  // tau to CSE mocell (only use for HIL testing)/N_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_B.MultiportSwitch,2,18,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/X_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_B.MultiportSwitch,0,18,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/Y_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_B.MultiportSwitch,1,18,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/integrator reset model: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Reset,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/psi_0 : Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_P.Constant2_Value,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/x_0: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_P.Constant_Value_i2,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/y_0: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_P.Constant1_Value_h,0,0,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 22;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // x_m: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,0,17,0);

  // psi_m: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,2,17,0);

  // y_m: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Switch,1,17,0);

  // psi_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,2,17,0);

  // x_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,0,17,0);

  // y_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,1,17,0);

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

  // tau to CSE mocell (only use for HIL testing)/N_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_B.MultiportSwitch,2,18,0);

  // tau to CSE mocell (only use for HIL testing)/X_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_B.MultiportSwitch,0,18,0);

  // tau to CSE mocell (only use for HIL testing)/Y_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_B.MultiportSwitch,1,18,0);

  // tau to CSE mocell (only use for HIL testing)/integrator reset model: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Reset,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/psi_0 : Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant2_Value,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/x_0: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant_Value_i2,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/y_0: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant1_Value_h,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_student_hil/Ellipse/Ellipse Mapper /Constant1/Value", offsetof
    (P_ctrl_student_HIL_T, C), 26, 2, 2, 0, 0 },

  { 1, "ctrl_student_hil/Ellipse/Control law1/K_p/Value", offsetof
    (P_ctrl_student_HIL_T, K_p), 20, 9, 2, 2, 0 },

  { 2, "ctrl_student_hil/Line System 1-6 (DP line)/Control law/K_p/Value",
    offsetof(P_ctrl_student_HIL_T, K_p), 20, 9, 2, 4, 0 },

  { 3, "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/K_p/Value",
    offsetof(P_ctrl_student_HIL_T, K_p), 20, 9, 2, 6, 0 },

  { 4, "ctrl_student_hil/Line System 1-6 (DP line)/Line Mapper/P_d/Value",
    offsetof(P_ctrl_student_HIL_T, P_d), 21, 4, 2, 8, 0 },

  { 5,
    "ctrl_student_hil/Line System 1-6 (DP line)/Line Speed Gauge/Constant/Value",
    offsetof(P_ctrl_student_HIL_T, P_d), 21, 4, 2, 10, 0 },

  { 6, "ctrl_student_hil/Line System 2-6 (Man.line)/Line Mapper/P_d/Value",
    offsetof(P_ctrl_student_HIL_T, P_d), 21, 4, 2, 12, 0 },

  { 7,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Line Speed Gauge/Constant/Value",
    offsetof(P_ctrl_student_HIL_T, P_d), 21, 4, 2, 14, 0 },

  { 8, "ctrl_student_hil/Ellipse/Ellipse Mapper /Constant/Value", offsetof
    (P_ctrl_student_HIL_T, R), 21, 4, 2, 16, 0 },

  { 9, "ctrl_student_hil/Constant1/Value", offsetof(P_ctrl_student_HIL_T, U_max),
    41, 1, 2, 18, 0 },

  { 10, "ctrl_student_hil/Constant5/Value", offsetof(P_ctrl_student_HIL_T, U_ref),
    41, 1, 2, 20, 0 },

  { 11, "ctrl_student_hil/Ellipse/Ellipse Speed Gauge/Constant/Value", offsetof
    (P_ctrl_student_HIL_T, r), 26, 2, 2, 22, 0 },

  { 12, "ctrl_student_hil/Constant4/Value", offsetof(P_ctrl_student_HIL_T,
    Constant4_Value), 41, 1, 2, 24, 0 },

  { 13, "ctrl_student_hil/Noise generator/Step size/Value", offsetof
    (P_ctrl_student_HIL_T, Stepsize_Value), 41, 1, 2, 26, 0 },

  { 14, "ctrl_student_hil/Noise generator/Downsamplesignal/counter/X0", offsetof
    (P_ctrl_student_HIL_T, counter_X0), 41, 1, 2, 28, 0 },

  { 15,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/Mean",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean), 41, 1, 2, 30, 0 },

  { 16,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev), 41, 1, 2, 32, 0 },

  { 17,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed), 41, 1, 2, 34, 0 },

  { 18,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/Mean",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean_h), 41, 1, 2, 36, 0 },

  { 19,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev_d), 41, 1, 2, 38, 0 },

  { 20,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed_b), 41, 1, 2, 40, 0 },

  { 21,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/Mean",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Mean_f), 41, 1, 2, 42, 0 },

  { 22,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/StdDev",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_StdDev_g), 41, 1, 2, 44, 0 },

  { 23,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise psi/White Noise/Seed",
    offsetof(P_ctrl_student_HIL_T, WhiteNoise_Seed_l), 41, 1, 2, 46, 0 },

  { 24, "ctrl_student_hil/Noise generator/Sample & hold/Hold/X0", offsetof
    (P_ctrl_student_HIL_T, Hold_X0), 41, 1, 2, 48, 0 },

  { 25, "ctrl_student_hil/Ellipse/Update Law/Integrator/InitialCondition",
    offsetof(P_ctrl_student_HIL_T, Integrator_IC), 41, 1, 2, 50, 0 },

  { 26, "ctrl_student_hil/DP Observer /Integrator/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator_IC_d), 41, 1, 2, 52, 0 },

  { 27, "ctrl_student_hil/DP Observer /Integrator1/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator1_IC), 41, 1, 2, 54, 0 },

  { 28, "ctrl_student_hil/DP Observer /Memory4/X0", offsetof
    (P_ctrl_student_HIL_T, Memory4_X0), 18, 3, 2, 56, 0 },

  { 29, "ctrl_student_hil/DP Observer /Memory3/X0", offsetof
    (P_ctrl_student_HIL_T, Memory3_X0), 18, 3, 2, 58, 0 },

  { 30, "ctrl_student_hil/DP Observer /Memory2/X0", offsetof
    (P_ctrl_student_HIL_T, Memory2_X0), 18, 3, 2, 60, 0 },

  { 31, "ctrl_student_hil/DP Observer /Integrator2/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator2_IC), 41, 1, 2, 62, 0 },

  { 32, "ctrl_student_hil/Ellipse/Update Law/Saturation/UpperLimit", offsetof
    (P_ctrl_student_HIL_T, Saturation_UpperSat), 41, 1, 2, 64, 0 },

  { 33, "ctrl_student_hil/Ellipse/Update Law/Saturation/LowerLimit", offsetof
    (P_ctrl_student_HIL_T, Saturation_LowerSat), 41, 1, 2, 66, 0 },

  { 34, "ctrl_student_hil/Ellipse/Control law1/Saturation/UpperLimit", offsetof
    (P_ctrl_student_HIL_T, Saturation_UpperSat_d), 18, 3, 2, 68, 0 },

  { 35, "ctrl_student_hil/Ellipse/Control law1/Saturation/LowerLimit", offsetof
    (P_ctrl_student_HIL_T, Saturation_LowerSat_h), 18, 3, 2, 70, 0 },

  { 36,
    "ctrl_student_hil/Line System 1-6 (DP line)/Update Law/Integrator/InitialCondition",
    offsetof(P_ctrl_student_HIL_T, Integrator_IC_l), 41, 1, 2, 72, 0 },

  { 37,
    "ctrl_student_hil/Line System 1-6 (DP line)/Update Law/Integrator/UpperSaturationLimit",
    offsetof(P_ctrl_student_HIL_T, Integrator_UpperSat), 41, 1, 2, 74, 0 },

  { 38,
    "ctrl_student_hil/Line System 1-6 (DP line)/Update Law/Integrator/LowerSaturationLimit",
    offsetof(P_ctrl_student_HIL_T, Integrator_LowerSat), 41, 1, 2, 76, 0 },

  { 39,
    "ctrl_student_hil/Line System 1-6 (DP line)/Update Law/Saturation/UpperLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_UpperSat_a), 41, 1, 2, 78, 0 },

  { 40,
    "ctrl_student_hil/Line System 1-6 (DP line)/Update Law/Saturation/LowerLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_LowerSat_n), 41, 1, 2, 80, 0 },

  { 41, "ctrl_student_hil/Line System 1-6 (DP line)/Constant/Value", offsetof
    (P_ctrl_student_HIL_T, Constant_Value), 18, 3, 2, 82, 0 },

  { 42,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/Saturation/UpperLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_UpperSat_f), 18, 3, 2, 84, 0 },

  { 43,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/Saturation/LowerLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_LowerSat_f), 18, 3, 2, 86, 0 },

  { 44,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Update Law1/Integrator/InitialCondition",
    offsetof(P_ctrl_student_HIL_T, Integrator_IC_m), 41, 1, 2, 88, 0 },

  { 45,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Update Law1/Integrator/UpperSaturationLimit",
    offsetof(P_ctrl_student_HIL_T, Integrator_UpperSat_a), 41, 1, 2, 90, 0 },

  { 46,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Update Law1/Integrator/LowerSaturationLimit",
    offsetof(P_ctrl_student_HIL_T, Integrator_LowerSat_f), 41, 1, 2, 92, 0 },

  { 47, "ctrl_student_hil/Line System 2-6 (Man.line)/Line Mapper/Memory/X0",
    offsetof(P_ctrl_student_HIL_T, Memory_X0), 41, 1, 2, 94, 0 },

  { 48, "ctrl_student_hil/Constant3/Value", offsetof(P_ctrl_student_HIL_T,
    Constant3_Value), 41, 1, 2, 96, 0 },

  { 49,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Update Law1/Saturation/UpperLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_UpperSat_c), 41, 1, 2, 98, 0 },

  { 50,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Update Law1/Saturation/LowerLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_LowerSat_nv), 41, 1, 2, 100, 0 },

  { 51, "ctrl_student_hil/Line System 2-6 (Man.line)/Constant1/Value", offsetof
    (P_ctrl_student_HIL_T, Constant1_Value), 41, 1, 2, 102, 0 },

  { 52, "ctrl_student_hil/Line System 2-6 (Man.line)/Constant/Value", offsetof
    (P_ctrl_student_HIL_T, Constant_Value_i), 18, 3, 2, 104, 0 },

  { 53,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/Saturation/UpperLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_UpperSat_b), 18, 3, 2, 106, 0 },

  { 54,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/Saturation/LowerLimit",
    offsetof(P_ctrl_student_HIL_T, Saturation_LowerSat_c), 18, 3, 2, 108, 0 },

  { 55,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant2/Value",
    offsetof(P_ctrl_student_HIL_T, Constant2_Value), 41, 1, 2, 110, 0 },

  { 56,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant/Value",
    offsetof(P_ctrl_student_HIL_T, Constant_Value_i2), 41, 1, 2, 112, 0 },

  { 57,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant1/Value",
    offsetof(P_ctrl_student_HIL_T, Constant1_Value_h), 41, 1, 2, 114, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 58;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  2, 1,                                /* Parameter at index 0 */
  3, 3,                                /* Parameter at index 1 */
  3, 3,                                /* Parameter at index 2 */
  3, 3,                                /* Parameter at index 3 */
  2, 2,                                /* Parameter at index 4 */
  2, 2,                                /* Parameter at index 5 */
  2, 2,                                /* Parameter at index 6 */
  2, 2,                                /* Parameter at index 7 */
  2, 2,                                /* Parameter at index 8 */
  1, 1,                                /* Parameter at index 9 */
  1, 1,                                /* Parameter at index 10 */
  2, 1,                                /* Parameter at index 11 */
  1, 1,                                /* Parameter at index 12 */
  1, 1,                                /* Parameter at index 13 */
  1, 1,                                /* Parameter at index 14 */
  1, 1,                                /* Parameter at index 15 */
  1, 1,                                /* Parameter at index 16 */
  1, 1,                                /* Parameter at index 17 */
  1, 1,                                /* Parameter at index 18 */
  1, 1,                                /* Parameter at index 19 */
  1, 1,                                /* Parameter at index 20 */
  1, 1,                                /* Parameter at index 21 */
  1, 1,                                /* Parameter at index 22 */
  1, 1,                                /* Parameter at index 23 */
  1, 1,                                /* Parameter at index 24 */
  1, 1,                                /* Parameter at index 25 */
  1, 1,                                /* Parameter at index 26 */
  1, 1,                                /* Parameter at index 27 */
  3, 1,                                /* Parameter at index 28 */
  3, 1,                                /* Parameter at index 29 */
  3, 1,                                /* Parameter at index 30 */
  1, 1,                                /* Parameter at index 31 */
  1, 1,                                /* Parameter at index 32 */
  1, 1,                                /* Parameter at index 33 */
  3, 1,                                /* Parameter at index 34 */
  3, 1,                                /* Parameter at index 35 */
  1, 1,                                /* Parameter at index 36 */
  1, 1,                                /* Parameter at index 37 */
  1, 1,                                /* Parameter at index 38 */
  1, 1,                                /* Parameter at index 39 */
  1, 1,                                /* Parameter at index 40 */
  3, 1,                                /* Parameter at index 41 */
  3, 1,                                /* Parameter at index 42 */
  3, 1,                                /* Parameter at index 43 */
  1, 1,                                /* Parameter at index 44 */
  1, 1,                                /* Parameter at index 45 */
  1, 1,                                /* Parameter at index 46 */
  1, 1,                                /* Parameter at index 47 */
  1, 1,                                /* Parameter at index 48 */
  1, 1,                                /* Parameter at index 49 */
  1, 1,                                /* Parameter at index 50 */
  1, 1,                                /* Parameter at index 51 */
  3, 1,                                /* Parameter at index 52 */
  3, 1,                                /* Parameter at index 53 */
  3, 1,                                /* Parameter at index 54 */
  1, 1,                                /* Parameter at index 55 */
  1, 1,                                /* Parameter at index 56 */
  1, 1,                                /* Parameter at index 57 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "ctrl_student_hil/noise pos", 0, "", offsetof(B_ctrl_student_HIL_T,
    noisepos)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise x/White Noise",
    0, "", offsetof(B_ctrl_student_HIL_T, WhiteNoise)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 2, 0 },

  { 2,
    "ctrl_student_hil/Noise generator/noise generator/Band-limited white noise y/White Noise",
    0, "", offsetof(B_ctrl_student_HIL_T, WhiteNoise_e)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 4, 0 },

  { 3, "ctrl_student_hil/noise head", 0, "", offsetof(B_ctrl_student_HIL_T,
    noisehead)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 6, 0 },

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

  { 11, "ctrl_student_hil/enable noise", 0, "", offsetof(B_ctrl_student_HIL_T,
    enablenoise)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

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

  { 18, "ctrl_student_hil/Reset", 0, "", offsetof(B_ctrl_student_HIL_T, Reset)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 36, 0 },

  { 19, "ctrl_student_hil/mu", 0, "", offsetof(B_ctrl_student_HIL_T, mu)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 38, 0 },

  { 20, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    40, 0 },

  { 21, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    42, 0 },

  { 22, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    44, 0 },

  { 23, "ctrl_student_hil/DP Observer /L1_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 46,
    0 },

  { 24, "ctrl_student_hil/DP Observer /L1_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 48,
    0 },

  { 25, "ctrl_student_hil/DP Observer /L1_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 50,
    0 },

  { 26, "ctrl_student_hil/DP Observer /L2_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 52,
    0 },

  { 27, "ctrl_student_hil/DP Observer /L2_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 54,
    0 },

  { 28, "ctrl_student_hil/DP Observer /L2_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 56,
    0 },

  { 29, "ctrl_student_hil/DP Observer /L3_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 58,
    0 },

  { 30, "ctrl_student_hil/DP Observer /L3_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 60,
    0 },

  { 31, "ctrl_student_hil/DP Observer /L3_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 62,
    0 },

  { 32, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    64, 0 },

  { 33, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    66, 0 },

  { 34, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    68, 0 },

  { 35, "ctrl_student_hil/DP Observer /b", 0, "", offsetof(B_ctrl_student_HIL_T,
    b)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 70, 0 },

  { 36, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 72,
    0 },

  { 37, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 74,
    0 },

  { 38, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 76,
    0 },

  { 39, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 78,
    0 },

  { 40, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 80,
    0 },

  { 41, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 82,
    0 },

  { 42, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 84,
    0 },

  { 43, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 86,
    0 },

  { 44, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 88,
    0 },

  { 45, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    90, 0 },

  { 46, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    92, 0 },

  { 47, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    94, 0 },

  { 48, "ctrl_student_hil/Ellipse/Update Law/Saturation", 0, "", offsetof
    (B_ctrl_student_HIL_T, Saturation)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    96, 0 },

  { 49, "ctrl_student_hil/Ellipse/Control law1/Saturation", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Saturation_d)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2,
    98, 0 },

  { 50, "ctrl_student_hil/Ellipse/Control law1/Saturation", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, Saturation_d)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2,
    100, 0 },

  { 51, "ctrl_student_hil/Ellipse/Control law1/Saturation", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, Saturation_d)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2,
    102, 0 },

  { 52, "ctrl_student_hil/Line System 1-6 (DP line)/Update Law/Saturation", 0,
    "", offsetof(B_ctrl_student_HIL_T, Saturation_b)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 104, 0 },

  { 53, "ctrl_student_hil/Line System 1-6 (DP line)/Control law/Saturation", 0,
    "(1,1)", offsetof(B_ctrl_student_HIL_T, Saturation_o)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 106, 0 },

  { 54, "ctrl_student_hil/Line System 1-6 (DP line)/Control law/Saturation", 0,
    "(1,2)", offsetof(B_ctrl_student_HIL_T, Saturation_o)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 108, 0 },

  { 55, "ctrl_student_hil/Line System 1-6 (DP line)/Control law/Saturation", 0,
    "(1,3)", offsetof(B_ctrl_student_HIL_T, Saturation_o)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 110, 0 },

  { 56, "ctrl_student_hil/Line System 2-6 (Man.line)/Line Mapper/Memory", 0, "",
    offsetof(B_ctrl_student_HIL_T, Memory)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1,
    2, 112, 0 },

  { 57, "ctrl_student_hil/Uref", 0, "", offsetof(B_ctrl_student_HIL_T, Uref)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 114, 0 },

  { 58, "ctrl_student_hil/Line System 2-6 (Man.line)/Update Law1/Saturation", 0,
    "", offsetof(B_ctrl_student_HIL_T, Saturation_g)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 116, 0 },

  { 59, "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/Saturation", 0,
    "(1,1)", offsetof(B_ctrl_student_HIL_T, Saturation_m)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 118, 0 },

  { 60, "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/Saturation", 0,
    "(1,2)", offsetof(B_ctrl_student_HIL_T, Saturation_m)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 120, 0 },

  { 61, "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/Saturation", 0,
    "(1,3)", offsetof(B_ctrl_student_HIL_T, Saturation_m)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 122, 0 },

  { 62, "ctrl_student_hil/Multiport Switch", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, MultiportSwitch)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 124, 0 },

  { 63, "ctrl_student_hil/Multiport Switch", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, MultiportSwitch)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 126, 0 },

  { 64, "ctrl_student_hil/Multiport Switch", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, MultiportSwitch)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1,
    2, 128, 0 },

  { 65, "ctrl_student_hil/joystick/L2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, L2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    130, 0 },

  { 66, "ctrl_student_hil/joystick/PosXRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    132, 0 },

  { 67, "ctrl_student_hil/joystick/PosYRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    134, 0 },

  { 68, "ctrl_student_hil/joystick/R2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, R2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    136, 0 },

  { 69, "ctrl_student_hil/joystick/PosXLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 138,
    0 },

  { 70, "ctrl_student_hil/joystick/PosYLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 140,
    0 },

  { 71, "ctrl_student_hil/joystick/L1", 0, "", offsetof(B_ctrl_student_HIL_T, L1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 142, 0 },

  { 72, "ctrl_student_hil/joystick/R1", 0, "", offsetof(B_ctrl_student_HIL_T, R1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 144, 0 },

  { 73, "ctrl_student_hil/joystick/ArrowDown", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowDown)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    146, 0 },

  { 74, "ctrl_student_hil/joystick/ArrowUp", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowUp)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 148,
    0 },

  { 75, "ctrl_student_hil/joystick/ArrowLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    150, 0 },

  { 76, "ctrl_student_hil/joystick/ArrowRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    152, 0 },

  { 77, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,1)", offsetof(B_ctrl_student_HIL_T, output)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 154, 0 },

  { 78, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,2)", offsetof(B_ctrl_student_HIL_T, output)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 156, 0 },

  { 79, "ctrl_student_hil/Noise generator/Sample & hold/MATLAB Function1", 0,
    "output(1,3)", offsetof(B_ctrl_student_HIL_T, output)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 158, 0 },

  { 80, "ctrl_student_hil/Noise generator/Downsamplesignal/MATLAB Function", 0,
    "count", offsetof(B_ctrl_student_HIL_T, count)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 160, 0 },

  { 81,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Line Mapper/MATLAB Function", 2,
    "s_proc", offsetof(B_ctrl_student_HIL_T, s_proc)+0*sizeof(real_T),
    BLOCKIO_SIG, 0, 1, 2, 162, 0 },

  { 82, "ctrl_student_hil/Line System 1-6 (DP line)/Line Speed Gauge/Line", 0,
    "U_s", offsetof(B_ctrl_student_HIL_T, U_s)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 164, 0 },

  { 83, "ctrl_student_hil/Line System 1-6 (DP line)/Line Speed Gauge/Line", 1,
    "U_s_s", offsetof(B_ctrl_student_HIL_T, U_s_s)+0*sizeof(real_T), BLOCKIO_SIG,
    0, 1, 2, 166, 0 },

  { 84, "ctrl_student_hil/Ellipse/Ellipse Mapper /Ellipse Mapper", 0,
    "eta_d(1,1)", offsetof(B_ctrl_student_HIL_T, eta_d)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 168, 0 },

  { 85, "ctrl_student_hil/Ellipse/Ellipse Mapper /Ellipse Mapper", 0,
    "eta_d(1,2)", offsetof(B_ctrl_student_HIL_T, eta_d)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 170, 0 },

  { 86, "ctrl_student_hil/Ellipse/Ellipse Mapper /Ellipse Mapper", 0,
    "eta_d(1,3)", offsetof(B_ctrl_student_HIL_T, eta_d)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 172, 0 },

  { 87, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,1)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 174, 0 },

  { 88, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,2)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 176, 0 },

  { 89, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,3)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 178, 0 },

  { 90, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,1)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    180, 0 },

  { 91, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,2)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    182, 0 },

  { 92, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,3)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    184, 0 },

  { 93, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,1)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    186, 0 },

  { 94, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,2)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    188, 0 },

  { 95, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,3)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    190, 0 },

  { 96, "ctrl_student_hil/DP Observer /Observer", 3, "x_bar", offsetof
    (B_ctrl_student_HIL_T, x_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 192, 0
  },

  { 97, "ctrl_student_hil/DP Observer /Observer", 4, "y_bar", offsetof
    (B_ctrl_student_HIL_T, y_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 194, 0
  },

  { 98, "ctrl_student_hil/DP Observer /Observer", 5, "psi_bar", offsetof
    (B_ctrl_student_HIL_T, psi_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 196,
    0 },

  { 99,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function2",
    0, "z_1(1,1)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2_d.z_1)+0*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 198, 0 },

  { 100,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function2",
    0, "z_1(1,2)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2_d.z_1)+1*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 200, 0 },

  { 101,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function2",
    0, "z_1(1,3)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2_d.z_1)+2*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 202, 0 },

  { 102,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function1",
    0, "z_1_dot(1,1)", offsetof(B_ctrl_student_HIL_T,
    sf_MATLABFunction1_d.z_1_dot)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 204,
    0 },

  { 103,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function1",
    0, "z_1_dot(1,2)", offsetof(B_ctrl_student_HIL_T,
    sf_MATLABFunction1_d.z_1_dot)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 206,
    0 },

  { 104,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function1",
    0, "z_1_dot(1,3)", offsetof(B_ctrl_student_HIL_T,
    sf_MATLABFunction1_d.z_1_dot)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 208,
    0 },

  { 105,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function",
    0, "tau(1,1)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_l.tau)+0*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 210, 0 },

  { 106,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function",
    0, "tau(1,2)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_l.tau)+1*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 212, 0 },

  { 107,
    "ctrl_student_hil/Line System 2-6 (Man.line)/Control law1/MATLAB Function",
    0, "tau(1,3)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_l.tau)+2*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 214, 0 },

  { 108, "ctrl_student_hil/Line System 1-6 (DP line)/Update Law/Update Law", 0,
    "s_dot", offsetof(B_ctrl_student_HIL_T, sf_UpdateLaw_o.s_dot)+0*sizeof
    (real_T), BLOCKIO_SIG, 0, 1, 2, 216, 0 },

  { 109,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function2", 0,
    "z_1(1,1)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2_n.z_1)+0*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 218, 0 },

  { 110,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function2", 0,
    "z_1(1,2)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2_n.z_1)+1*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 220, 0 },

  { 111,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function2", 0,
    "z_1(1,3)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2_n.z_1)+2*
    sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 222, 0 },

  { 112,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function1", 0,
    "z_1_dot(1,1)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction1_h.z_1_dot)
    +0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 224, 0 },

  { 113,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function1", 0,
    "z_1_dot(1,2)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction1_h.z_1_dot)
    +1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 226, 0 },

  { 114,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function1", 0,
    "z_1_dot(1,3)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction1_h.z_1_dot)
    +2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 228, 0 },

  { 115,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function", 0,
    "tau(1,1)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_g.tau)+0*sizeof
    (real_T), BLOCKIO_SIG, 17, 1, 2, 230, 0 },

  { 116,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function", 0,
    "tau(1,2)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_g.tau)+1*sizeof
    (real_T), BLOCKIO_SIG, 17, 1, 2, 232, 0 },

  { 117,
    "ctrl_student_hil/Line System 1-6 (DP line)/Control law/MATLAB Function", 0,
    "tau(1,3)", offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_g.tau)+2*sizeof
    (real_T), BLOCKIO_SIG, 17, 1, 2, 234, 0 },

  { 118, "ctrl_student_hil/Ellipse/Update Law/Update Law", 0, "s_dot", offsetof
    (B_ctrl_student_HIL_T, sf_UpdateLaw.s_dot)+0*sizeof(real_T), BLOCKIO_SIG, 0,
    1, 2, 236, 0 },

  { 119, "ctrl_student_hil/Ellipse/Control law1/MATLAB Function2", 0, "z_1(1,1)",
    offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2.z_1)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 238, 0 },

  { 120, "ctrl_student_hil/Ellipse/Control law1/MATLAB Function2", 0, "z_1(1,2)",
    offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2.z_1)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 240, 0 },

  { 121, "ctrl_student_hil/Ellipse/Control law1/MATLAB Function2", 0, "z_1(1,3)",
    offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction2.z_1)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 242, 0 },

  { 122, "ctrl_student_hil/Ellipse/Control law1/MATLAB Function", 0, "tau(1,1)",
    offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_e.tau)+0*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 244, 0 },

  { 123, "ctrl_student_hil/Ellipse/Control law1/MATLAB Function", 0, "tau(1,2)",
    offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_e.tau)+1*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 246, 0 },

  { 124, "ctrl_student_hil/Ellipse/Control law1/MATLAB Function", 0, "tau(1,3)",
    offsetof(B_ctrl_student_HIL_T, sf_MATLABFunction_e.tau)+2*sizeof(real_T),
    BLOCKIO_SIG, 17, 1, 2, 248, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 125;
static int NI_VirtualBlockSources[1][1];
static int NI_VirtualBlockOffsets[1][1];
static int NI_VirtualBlockLengths[1][1];
static int NI_SigDimList[] DataSection(".NIVS.sigdimlist") =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 50;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "noise pos", 0, EXT_IN, 1, 1, 1 },

  { 1, "noise head", 0, EXT_IN, 1, 1, 1 },

  { 2, "y_in", 0, EXT_IN, 1, 1, 1 },

  { 3, "x_in", 0, EXT_IN, 1, 1, 1 },

  { 4, "psi_in", 0, EXT_IN, 1, 1, 1 },

  { 5, "enable noise", 0, EXT_IN, 1, 1, 1 },

  { 6, "r_in", 0, EXT_IN, 1, 1, 1 },

  { 7, "u_in", 0, EXT_IN, 1, 1, 1 },

  { 8, "v_in", 0, EXT_IN, 1, 1, 1 },

  { 9, "Reset", 1, EXT_IN, 1, 1, 1 },

  { 10, "mu", 0, EXT_IN, 1, 1, 1 },

  { 11, "DP Observer /L1_diag", 0, EXT_IN, 3, 3, 1 },

  { 12, "DP Observer /L2_diag ", 0, EXT_IN, 3, 3, 1 },

  { 13, "DP Observer /L3_diag", 0, EXT_IN, 3, 3, 1 },

  { 14, "DP Observer /b", 0, EXT_IN, 1, 1, 1 },

  { 15, "Uref", 0, EXT_IN, 1, 1, 1 },

  { 16, "joystick/L2_continuous", 1, EXT_IN, 1, 1, 1 },

  { 17, "joystick/PosXRight", 1, EXT_IN, 1, 1, 1 },

  { 18, "joystick/PosYRight", 1, EXT_IN, 1, 1, 1 },

  { 19, "joystick/R2_continuous", 1, EXT_IN, 1, 1, 1 },

  { 20, "joystick/PosXLeft", 1, EXT_IN, 1, 1, 1 },

  { 21, "joystick/PosYLeft", 1, EXT_IN, 1, 1, 1 },

  { 22, "joystick/L1", 1, EXT_IN, 1, 1, 1 },

  { 23, "joystick/R1", 1, EXT_IN, 1, 1, 1 },

  { 24, "joystick/ArrowDown", 1, EXT_IN, 1, 1, 1 },

  { 25, "joystick/ArrowUp", 1, EXT_IN, 1, 1, 1 },

  { 26, "joystick/ArrowLeft", 1, EXT_IN, 1, 1, 1 },

  { 27, "joystick/ArrowRight", 1, EXT_IN, 1, 1, 1 },

  { 0, "x_m", 0, EXT_OUT, 1, 1, 1 },

  { 1, "psi_m", 0, EXT_OUT, 1, 1, 1 },

  { 2, "y_m", 0, EXT_OUT, 1, 1, 1 },

  { 3, "psi_d", 0, EXT_OUT, 1, 1, 1 },

  { 4, "x_d", 0, EXT_OUT, 1, 1, 1 },

  { 5, "y_d", 0, EXT_OUT, 1, 1, 1 },

  { 6, "DP Observer /x_hat", 0, EXT_OUT, 1, 1, 1 },

  { 7, "DP Observer /psi_hat", 0, EXT_OUT, 1, 1, 1 },

  { 8, "DP Observer /y_hat", 0, EXT_OUT, 1, 1, 1 },

  { 9, "DP Observer /r_dot", 0, EXT_OUT, 1, 1, 1 },

  { 10, "DP Observer /u_dot", 0, EXT_OUT, 1, 1, 1 },

  { 11, "DP Observer /v_dot", 0, EXT_OUT, 1, 1, 1 },

  { 12, "DP Observer /y_bar", 0, EXT_OUT, 1, 1, 1 },

  { 13, "DP Observer /psi_bar", 0, EXT_OUT, 1, 1, 1 },

  { 14, "DP Observer /x_bar", 0, EXT_OUT, 1, 1, 1 },

  { 15, "tau to CSE mocell (only use for HIL testing)/N_d", 0, EXT_OUT, 1, 1, 1
  },

  { 16, "tau to CSE mocell (only use for HIL testing)/X_d", 0, EXT_OUT, 1, 1, 1
  },

  { 17, "tau to CSE mocell (only use for HIL testing)/Y_d", 0, EXT_OUT, 1, 1, 1
  },

  { 18, "tau to CSE mocell (only use for HIL testing)/integrator reset model", 1,
    EXT_OUT, 1, 1, 1 },

  { 19, "tau to CSE mocell (only use for HIL testing)/psi_0 ", 1, EXT_OUT, 1, 1,
    1 },

  { 20, "tau to CSE mocell (only use for HIL testing)/x_0", 1, EXT_OUT, 1, 1, 1
  },

  { 21, "tau to CSE mocell (only use for HIL testing)/y_0", 1, EXT_OUT, 1, 1, 1
  },

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
static char* NI_CompiledModelVersion = "1.237";
static char* NI_CompiledModelDateTime = "Fri Mar 24 14:35:24 2017";
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
      *numContStates = 12;
      *numDiscStates = 1010;
      *numClockTicks = NUMST - TID01EQ;
      return NI_OK;
    }
  }

  if (contStates && contStatesNames) {
    idx = 0;
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator_CSTATE, 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator_CSTATE_m[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE_m");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator_CSTATE_m[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE_m");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator_CSTATE_m[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE_m");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator1_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator1_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator1_CSTATE[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator1_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator2_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator2_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator2_CSTATE[0], 2, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator2_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator_CSTATE_h, 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE_h");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.Integrator_CSTATE_c, 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE_c");
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.counter_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.counter_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.noisepos_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.noisepos_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput_c,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput_c");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.noisehead_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.noisehead_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.NextOutput_p,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.NextOutput_p");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_in_DWORK1");
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
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.enablenoise_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.enablenoise_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_m_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.psi_m_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_m_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_m_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.psi_d_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Reset_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Reset_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.mu_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.mu_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L1_diag_DWORK1, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L1_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L1_diag_DWORK1, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L1_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L1_diag_DWORK1, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L1_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.psi_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.psi_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L2_diag_DWORK1, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L2_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L2_diag_DWORK1, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L2_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L2_diag_DWORK1, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L2_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L3_diag_DWORK1, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L3_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L3_diag_DWORK1, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L3_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.L3_diag_DWORK1, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.L3_diag_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_dot_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.b_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.b_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory4_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory4_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory4_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory4_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory4_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory4_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory3_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory3_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory3_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory3_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory2_PreviousInput, 0, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory2_PreviousInput, 1, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory2_PreviousInput, 2, 17, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory2_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_bar_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_bar_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.psi_bar_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.psi_bar_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_bar_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_bar_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Memory_PreviousInput, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Memory_PreviousInput");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Uref_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Uref_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.N_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.X_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Y_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.integratorresetmodel_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.integratorresetmodel_DWORK1");
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
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Scope_PWORK,
      0, 11, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Scope_PWORK");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Scope2_PWORK,
      0, 11, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Scope2_PWORK");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Scope_PWORK_i,
      0, 11, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Scope_PWORK_i");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Scope2_PWORK_i, 0, 11, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Scope2_PWORK_i");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Scope_PWORK_k,
      0, 11, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Scope_PWORK_k");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Scope2_PWORK_h, 0, 11, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Scope2_PWORK_h");
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
        (&ctrl_student_HIL_DW.noisepos_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.noisepos_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.noisehead_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.noisehead_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_in_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.enablenoise_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.enablenoise_DWORK2");
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
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_d_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_in_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_d_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.Reset_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.Reset_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.mu_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.mu_DWORK2");
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
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.r_dot_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.r_dot_DWORK2");
    }

    for (count = 0; count < 17; count++) {
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
        (&ctrl_student_HIL_DW.v_dot_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.v_dot_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.y_bar_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.y_bar_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_bar_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_bar_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.x_bar_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.x_bar_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Uref_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Uref_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.N_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.X_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Y_d_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.integratorresetmodel_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.integratorresetmodel_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_0_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_0_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_0_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_0_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_0_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_0_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L2_continuous_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L2_continuous_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosXRight_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosXRight_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosYRight_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosYRight_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.R2_continuous_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.R2_continuous_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosXLeft_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosXLeft_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.PosYLeft_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.PosYLeft_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.L1_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.L1_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.R1_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.R1_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowDown_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowDown_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowUp_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowUp_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowLeft_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowLeft_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.ArrowRight_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.ArrowRight_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK1, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK1");
    }

    for (count = 0; count < 60; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK3, count, 23, 0);
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
  if (contStates) {
    idx = 0;
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator_CSTATE, 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator_CSTATE_m[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator_CSTATE_m[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator_CSTATE_m[0], 2,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator1_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator1_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator1_CSTATE[0], 2,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator2_CSTATE[0], 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator2_CSTATE[0], 1,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator2_CSTATE[0], 2,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator_CSTATE_h, 0,
      contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator_CSTATE_c, 0,
      contStates[idx++], 0, 0);
  }

  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.counter_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.noisepos_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput_c, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.noisehead_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NextOutput_p, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Hold_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Hold_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Hold_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.enablenoise_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_m_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_m_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_m_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_d_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Reset_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.mu_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK1, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK1, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK1, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK1, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK1, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK1, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK1, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK1, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK1, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_dot_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.b_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory4_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory4_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory4_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory3_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory3_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory3_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory2_PreviousInput, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory2_PreviousInput, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory2_PreviousInput, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_bar_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_bar_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_bar_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory_PreviousInput, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Uref_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.integratorresetmodel_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_0_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_0_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_0_DWORK1, 0, discStates[idx++],
      0, 0);
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
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Scope_PWORK, 0, discStates[idx
      ++], 11, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Scope2_PWORK, 0, discStates[idx
      ++], 11, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Scope_PWORK_i, 0,
      discStates[idx++], 11, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Scope2_PWORK_i, 0,
      discStates[idx++], 11, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Scope_PWORK_k, 0,
      discStates[idx++], 11, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Scope2_PWORK_h, 0,
      discStates[idx++], 11, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK2,
      0, discStates[idx++], 6, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.RandSeed, 0, discStates[idx++],
      7, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.RandSeed_j, 0, discStates[idx++],
      7, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.RandSeed_c, 0, discStates[idx++],
      7, 0);
    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.noisepos_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.noisehead_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.enablenoise_DWORK2, count,
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
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_d_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_d_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Reset_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.mu_DWORK2, count,
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
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_dot_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.b_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_bar_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_bar_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_bar_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Uref_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.N_d_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.X_d_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Y_d_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.integratorresetmodel_DWORK2,
        count, discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_0_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_0_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_0_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_continuous_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosXRight_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosYRight_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.R2_continuous_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosXLeft_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.PosYLeft_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.R1_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowDown_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowUp_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowLeft_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.ArrowRight_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK1,
        count, discStates[idx++], 19, 0);
    }

    for (count = 0; count < 60; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK3,
        count, discStates[idx++], 23, 0);
    }
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
    S->Timing.clockTick1 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_ctrl_student_HIL
