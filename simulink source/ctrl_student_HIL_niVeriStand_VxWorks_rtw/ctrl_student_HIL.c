/*
 * ctrl_student_HIL.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ctrl_student_HIL".
 *
 * Model version              : 1.332
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Sat Mar 25 19:37:02 2017
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

/* Previous zero-crossings (trigger) states */
PrevZCX_ctrl_student_HIL_T ctrl_student_HIL_PrevZCX;

/* Real-time model */
RT_MODEL_ctrl_student_HIL_T ctrl_student_HIL_M_;
RT_MODEL_ctrl_student_HIL_T *const ctrl_student_HIL_M = &ctrl_student_HIL_M_;

/* Forward declaration for local functions */
static real_T ctrl_student_HIL_norm(const real_T x[3]);

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
  int_T nXc = 13;
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

/* Function for MATLAB Function: '<Root>/Transfer function' */
static real_T ctrl_student_HIL_norm(const real_T x[3])
{
  real_T y;
  real_T scale;
  real_T absxk;
  real_T t;
  scale = 2.2250738585072014E-308;
  absxk = fabs(x[0]);
  if (absxk > 2.2250738585072014E-308) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  return scale * sqrt(y);
}

/* Model output function */
void ctrl_student_HIL_output(void)
{
  /* local block i/o variables */
  real_T rtb_Integrator_p;
  int_T iS;
  ZCEventType zcEvent;
  real_T U_s;
  real_T U_s_s;
  real_T eta_d_s[3];
  real_T S[9];
  real_T R[9];
  real_T z_1[3];
  real_T diff[3];
  real_T a;
  real_T b_x;
  real_T d_x;
  real_T c_a;
  static const real_T d_a[9] = { 16.79, 0.0, 0.0, 0.0, 24.79,
    0.55462499999999992, 0.0, 0.55462499999999992, 2.76 };

  static const int8_T e_a[9] = { 10, 0, 0, 0, 10, 0, 0, 0, 5 };

  static const real_T f_a[9] = { -0.2, -0.0, -0.0, -0.0, -0.2, -0.0, -0.0, -0.0,
    -0.1 };

  static const real_T limit[4] = { -20.0, -3.225, 20.0, 3.225 };

  real_T L2[9];
  real_T L3[9];
  static const real_T a_0[9] = { 0.059559261465157838, -0.0, 0.0, -0.0,
    0.04052100686778741, -0.0081423733365488769, -0.0, -0.0081423733365488769,
    0.36395498559871381 };

  static const real_T b_a[9] = { -4.088, -0.0, -0.0, -0.0, -68.211, -0.0788,
    -0.0, -0.0, -1.07 };

  real_T k_psi;
  real_T rtb_TmpSignalConversionAtSFun_f[3];
  real_T rtb_TmpSignalConversionAtSFunct[3];
  static const int8_T tmp[2] = { 1, 2 };

  real_T R_0[3];
  real_T S_0[3];
  real_T R_1[3];
  real_T f_a_0[3];
  real_T d_a_0[3];
  int32_T i;
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
    /* Memory: '<S3>/Memory' */
    memcpy(&ctrl_student_HIL_B.Memory[0],
           &ctrl_student_HIL_DW.Memory_PreviousInput[0], 9U * sizeof(real_T));
  }

  /* MATLAB Function: '<S3>/MATLAB Function' incorporates:
   *  SignalConversion: '<S10>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'Dead reckoning/MATLAB Function': '<S10>:1' */
  /* '<S10>:1:2' */
  ctrl_student_HIL_B.dead_x = 0.0;

  /* '<S10>:1:5' */
  for (iS = 0; iS < 9; iS++) {
    S[iS] = ctrl_student_HIL_B.Memory[iS];
    ctrl_student_HIL_B.newmem[iS] = ctrl_student_HIL_B.Memory[iS];
  }

  /*  This value needs to be changed based on the iteration speed */
  if (ctrl_student_HIL_B.Memory[0] - floor(ctrl_student_HIL_B.Memory[0] / 50.0) *
      50.0 == 0.0) {
    /* '<S10>:1:9' */
    /* '<S10>:1:10' */
    S[6] = ctrl_student_HIL_B.Memory[3];

    /* '<S10>:1:11' */
    S[3] = ctrl_student_HIL_B.x_in;

    /* '<S10>:1:12' */
    S[0] = 1.0;
  }

  /* '<S10>:1:14' */
  ctrl_student_HIL_B.newmem[0] = S[0] + 1.0;
  if (S[3] == S[6]) {
    /* '<S10>:1:15' */
    /* '<S10>:1:16' */
    ctrl_student_HIL_B.dead_x = 1.0;
  }

  /* End of MATLAB Function: '<S3>/MATLAB Function' */

  /* SecondOrderIntegrator: '<S3>/Integrator, Second-Order' */
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                       &ctrl_student_HIL_PrevZCX.IntegratorSecondOrder_Reset_ZCE,
                       (ctrl_student_HIL_B.dead_x));
    if (zcEvent != NO_ZCEVENT) {
      ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[0] =
        ctrl_student_HIL_P.IntegratorSecondOrder_ICX;
      ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[1] =
        ctrl_student_HIL_P.IntegratorSecondOrder_ICDXDT;
      ctrl_student_HIL_DW.IntegratorSecondOrder_MODE = 0;
      rtsiSetSolverNeedsReset(&ctrl_student_HIL_M->solverInfo, true);
    }
  }

  /* End of SecondOrderIntegrator: '<S3>/Integrator, Second-Order' */

  /* SignalConversion: '<S11>/TmpSignal ConversionAt SFunction Inport1' incorporates:
   *  MATLAB Function: '<S3>/MATLAB Function1'
   */
  rtb_TmpSignalConversionAtSFun_f[0] = ctrl_student_HIL_B.x_in;
  rtb_TmpSignalConversionAtSFun_f[1] = ctrl_student_HIL_B.y_in;
  rtb_TmpSignalConversionAtSFun_f[2] = ctrl_student_HIL_B.psi_in;

  /* MATLAB Function 'Dead reckoning/MATLAB Function1': '<S11>:1' */
  /* '<S11>:1:7' */

  /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport3' incorporates:
   *  MATLAB Function: '<Root>/Transfer function'
   */
  rtb_TmpSignalConversionAtSFunct[0] = ctrl_student_HIL_B.u_in;
  rtb_TmpSignalConversionAtSFunct[1] = ctrl_student_HIL_B.v_in;
  rtb_TmpSignalConversionAtSFunct[2] = ctrl_student_HIL_B.r_in;

  /* MATLAB Function: '<Root>/Transfer function' incorporates:
   *  Integrator: '<Root>/Integrator'
   *  MATLAB Function: '<S3>/MATLAB Function1'
   *  SignalConversion: '<S11>/TmpSignal ConversionAt SFunction Inport1'
   *  SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport3'
   */
  /* MATLAB Function 'Transfer function': '<S6>:1' */
  /* % Constants */
  /*  Measured from model using max thrust */
  /* % Parameters */
  /*  Rigid body and added mass */
  /*  y_g = 0.0; */
  /*  Max Values in Surge X, Sway Y and Yaw N */
  /* [N] */
  /* [Nm] */
  /*  Hydro surge, Hydro sway and Hydro Yaw Parameters */
  /*  NB! We don't need most of them for now, that why they are commented */
  /*  out, but don't remove them!! */
  /* '<S6>:1:30' */
  /* '<S6>:1:33' */
  /*  Matrices */
  /* '<S6>:1:40' */
  /*  I need a test values;  */
  /* '<S6>:1:48' */
  /* '<S6>:1:49' */
  /* '<S6>:1:50' */
  /* '<S6>:1:51' */
  /* '<S6>:1:52' */
  /*  The total damping matrix from the handbook page 53 */
  /* '<S6>:1:55' */
  /*         %% Ellipse tracking */
  /* '<S6>:1:160' */
  /*         %% Speed mapping */
  /* '<S6>:1:166' */
  a = 10.0 * sin(ctrl_student_HIL_X.Integrator_CSTATE);
  k_psi = 2.0 * cos(ctrl_student_HIL_X.Integrator_CSTATE);
  U_s = 0.057999999999999996 / sqrt(a * a + k_psi * k_psi);

  /* '<S6>:1:167' */
  k_psi = cos(ctrl_student_HIL_X.Integrator_CSTATE);
  b_x = sin(ctrl_student_HIL_X.Integrator_CSTATE);
  U_s_s = -(100.0 * cos(ctrl_student_HIL_X.Integrator_CSTATE) * sin
            (ctrl_student_HIL_X.Integrator_CSTATE) - 4.0 * cos
            (ctrl_student_HIL_X.Integrator_CSTATE) * sin
            (ctrl_student_HIL_X.Integrator_CSTATE)) * 0.057999999999999996 /
    rt_powd_snf(k_psi * k_psi * 4.0 + b_x * b_x * 100.0, 1.5);

  /*         %% Reference mapping */
  /* '<S6>:1:170' */
  /* '<S6>:1:171' */
  /* '<S6>:1:173' */
  /* '<S6>:1:174' */
  a = cos(ctrl_student_HIL_X.Integrator_CSTATE);
  d_x = sin(ctrl_student_HIL_X.Integrator_CSTATE);

  /* '<S6>:1:176' */
  /* '<S6>:1:177' */
  b_x = cos(ctrl_student_HIL_X.Integrator_CSTATE);
  k_psi = sin(ctrl_student_HIL_X.Integrator_CSTATE);
  c_a = b_x * b_x * 4.0 + k_psi * k_psi * 100.0;

  /* '<S6>:1:179' */
  ctrl_student_HIL_B.eta_d[0] = 10.0 * cos(ctrl_student_HIL_X.Integrator_CSTATE);
  ctrl_student_HIL_B.eta_d[1] = 2.0 * sin(ctrl_student_HIL_X.Integrator_CSTATE);
  ctrl_student_HIL_B.eta_d[2] = rt_atan2d_snf(2.0 * cos
    (ctrl_student_HIL_X.Integrator_CSTATE), -10.0 * sin
    (ctrl_student_HIL_X.Integrator_CSTATE));

  /* '<S6>:1:180' */
  eta_d_s[0] = -10.0 * sin(ctrl_student_HIL_X.Integrator_CSTATE);
  eta_d_s[1] = 2.0 * cos(ctrl_student_HIL_X.Integrator_CSTATE);
  eta_d_s[2] = 20.0 / (a * a * 4.0 + d_x * d_x * 100.0);

  /* '<S6>:1:181' */
  /*         %% Update law */
  /* '<S6>:1:184' */
  diff[0] = ctrl_student_HIL_B.x_in - ctrl_student_HIL_B.eta_d[0];
  diff[1] = ctrl_student_HIL_B.y_in - ctrl_student_HIL_B.eta_d[1];

  /* '<S6>:1:184' */
  /* '<S6>:1:221' */
  b_x = ((ctrl_student_HIL_B.psi_in - ctrl_student_HIL_B.eta_d[2]) +
         3.1415926535897931) / 6.2831853071795862;
  if (fabs(b_x - rt_roundd_snf(b_x)) <= 2.2204460492503131E-16 * fabs(b_x)) {
    b_x = 0.0;
  } else {
    b_x = (b_x - floor(b_x)) * 6.2831853071795862;
  }

  if (ctrl_student_HIL_norm(eta_d_s) < 1.0E-5) {
    /* '<S6>:1:186' */
    /* '<S6>:1:187' */
    b_x = U_s - ((0.025 * -diff[0] + 0.025 * -diff[1]) + -(b_x -
      3.1415926535897931) * 0.025) / 1.7320508075688772;
  } else {
    /* '<S6>:1:189' */
    b_x = U_s - ((0.025 * -diff[0] * eta_d_s[0] + 0.025 * -diff[1] * eta_d_s[1])
                 + -(b_x - 3.1415926535897931) * 0.025 * eta_d_s[2]) /
      ctrl_student_HIL_norm(eta_d_s);
  }

  /* % Control law */
  /*  Define z_1 and z_1_dot */
  /* '<S6>:1:198' */
  S[0] = 0.0;
  S[3] = -ctrl_student_HIL_B.r_in;
  S[6] = 0.0;
  S[1] = ctrl_student_HIL_B.r_in;
  S[4] = 0.0;
  S[7] = 0.0;
  S[2] = 0.0;
  S[5] = 0.0;
  S[8] = 0.0;

  /* '<S6>:1:199' */
  /* '<S6>:1:200' */
  R[0] = cos(ctrl_student_HIL_B.psi_in);
  R[3] = -sin(ctrl_student_HIL_B.psi_in);
  R[6] = 0.0;
  R[1] = sin(ctrl_student_HIL_B.psi_in);
  R[4] = cos(ctrl_student_HIL_B.psi_in);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* '<S6>:1:204' */
  diff[0] = ctrl_student_HIL_B.x_in - ctrl_student_HIL_B.eta_d[0];
  diff[1] = ctrl_student_HIL_B.y_in - ctrl_student_HIL_B.eta_d[1];

  /* '<S6>:1:205' */
  /* '<S6>:1:221' */
  k_psi = ((ctrl_student_HIL_B.psi_in - ctrl_student_HIL_B.eta_d[2]) +
           3.1415926535897931) / 6.2831853071795862;
  if (fabs(k_psi - rt_roundd_snf(k_psi)) <= 2.2204460492503131E-16 * fabs(k_psi))
  {
    k_psi = 0.0;
  } else {
    k_psi = (k_psi - floor(k_psi)) * 6.2831853071795862;
  }

  /* '<S6>:1:206' */
  /* '<S6>:1:207' */
  for (iS = 0; iS < 3; iS++) {
    z_1[iS] = R[3 * iS + 2] * (k_psi - 3.1415926535897931) + (R[3 * iS + 1] *
      diff[1] + R[3 * iS] * diff[0]);
  }

  /* '<S6>:1:208' */
  /*  alpha_1, alpha_1_dot, and z_2 */
  /* '<S6>:1:211' */
  /* '<S6>:1:212' */
  /* '<S6>:1:213' */
  /* '<S6>:1:215' */
  /* '<S6>:1:217' */
  L3[0] = (0.6555 - 0.3545 * fabs(ctrl_student_HIL_B.u_in)) -
    ctrl_student_HIL_B.u_in * ctrl_student_HIL_B.u_in * -3.787;
  L3[3] = 0.0;
  L3[6] = 0.0;
  L3[1] = 0.0;
  L3[4] = ((1.33 - -2.776 * fabs(ctrl_student_HIL_B.v_in)) -
           ctrl_student_HIL_B.v_in * ctrl_student_HIL_B.v_in * -64.91) - 0.805 *
    fabs(ctrl_student_HIL_B.r_in);
  L3[7] = ((7.25 - -0.845 * fabs(ctrl_student_HIL_B.v_in)) - -3.45 * fabs
           (ctrl_student_HIL_B.r_in)) - ctrl_student_HIL_B.r_in *
    ctrl_student_HIL_B.r_in * 0.0;
  L3[2] = 0.0;
  L3[5] = ((-0.0 - -0.2088 * fabs(ctrl_student_HIL_B.v_in)) -
           ctrl_student_HIL_B.v_in * ctrl_student_HIL_B.v_in * 0.0) - 0.13 *
    fabs(ctrl_student_HIL_B.r_in);
  L3[8] = ((1.9 - 0.08 * fabs(ctrl_student_HIL_B.v_in)) - 0.75 * fabs
           (ctrl_student_HIL_B.r_in)) - ctrl_student_HIL_B.r_in *
    ctrl_student_HIL_B.r_in * 0.0;
  for (iS = 0; iS < 3; iS++) {
    R_0[iS] = R[3 * iS + 2] * eta_d_s[2] + (R[3 * iS + 1] * eta_d_s[1] + R[3 *
      iS] * eta_d_s[0]);
  }

  for (iS = 0; iS < 3; iS++) {
    diff[iS] = (((S[3 * iS + 1] * z_1[1] + S[3 * iS] * z_1[0]) + S[3 * iS + 2] *
                 z_1[2]) + rtb_TmpSignalConversionAtSFunct[iS]) - R_0[iS] * b_x;
  }

  for (iS = 0; iS < 3; iS++) {
    for (i = 0; i < 3; i++) {
      L2[iS + 3 * i] = 0.0;
      L2[iS + 3 * i] = L2[3 * i + iS] + S[3 * iS] * R[i];
      L2[iS + 3 * i] = S[3 * iS + 1] * R[i + 3] + L2[3 * i + iS];
      L2[iS + 3 * i] = S[3 * iS + 2] * R[i + 6] + L2[3 * i + iS];
    }
  }

  for (iS = 0; iS < 3; iS++) {
    S_0[iS] = L2[iS + 6] * eta_d_s[2] + (L2[iS + 3] * eta_d_s[1] + L2[iS] *
      eta_d_s[0]);
  }

  a = -10.0 * cos(ctrl_student_HIL_X.Integrator_CSTATE);
  d_x = -2.0 * sin(ctrl_student_HIL_X.Integrator_CSTATE);
  k_psi = (100.0 * cos(ctrl_student_HIL_X.Integrator_CSTATE) * sin
           (ctrl_student_HIL_X.Integrator_CSTATE) - 4.0 * cos
           (ctrl_student_HIL_X.Integrator_CSTATE) * sin
           (ctrl_student_HIL_X.Integrator_CSTATE)) * -2.0 * 10.0 * 2.0 / (c_a *
    c_a);
  for (iS = 0; iS < 3; iS++) {
    R_0[iS] = R[3 * iS + 2] * k_psi + (R[3 * iS + 1] * d_x + R[3 * iS] * a);
  }

  for (iS = 0; iS < 3; iS++) {
    R_1[iS] = R[3 * iS + 2] * eta_d_s[2] + (R[3 * iS + 1] * eta_d_s[1] + R[3 *
      iS] * eta_d_s[0]);
  }

  for (iS = 0; iS < 3; iS++) {
    f_a_0[iS] = ((((f_a[iS + 3] * diff[1] + f_a[iS] * diff[0]) + f_a[iS + 6] *
                   diff[2]) + S_0[iS] * U_s) + R_0[iS] * b_x * U_s) + R_1[iS] *
      U_s_s * b_x;
  }

  for (iS = 0; iS < 3; iS++) {
    R_1[iS] = L3[iS + 6] * ctrl_student_HIL_B.r_in + (L3[iS + 3] *
      ctrl_student_HIL_B.v_in + L3[iS] * ctrl_student_HIL_B.u_in);
  }

  for (iS = 0; iS < 3; iS++) {
    d_a_0[iS] = d_a[iS + 6] * f_a_0[2] + (d_a[iS + 3] * f_a_0[1] + d_a[iS] *
      f_a_0[0]);
  }

  for (iS = 0; iS < 3; iS++) {
    R_0[iS] = R[3 * iS + 2] * eta_d_s[2] + (R[3 * iS + 1] * eta_d_s[1] + R[3 *
      iS] * eta_d_s[0]);
  }

  for (iS = 0; iS < 3; iS++) {
    S_0[iS] = rtb_TmpSignalConversionAtSFunct[iS] - (((f_a[iS + 3] * z_1[1] +
      f_a[iS] * z_1[0]) + f_a[iS + 6] * z_1[2]) + R_0[iS] * U_s);
  }

  for (iS = 0; iS < 3; iS++) {
    diff[iS] = ((R_1[iS] + d_a_0[iS]) - z_1[iS]) - (((real_T)e_a[iS + 3] * S_0[1]
      + (real_T)e_a[iS] * S_0[0]) + (real_T)e_a[iS + 6] * S_0[2]);
  }

  if ((0.98 <= diff[1]) || rtIsNaN(diff[1])) {
    k_psi = 0.98;
  } else {
    k_psi = diff[1];
  }

  if ((2.5 <= diff[2]) || rtIsNaN(diff[2])) {
    a = 2.5;
  } else {
    a = diff[2];
  }

  /* '<S6>:1:218' */
  if ((1.03 <= diff[0]) || rtIsNaN(diff[0])) {
    diff[0] = 1.03;
  }

  ctrl_student_HIL_B.s_dot = b_x;

  /* MATLAB Function: '<Root>/Transfer function' */
  if ((-1.03 >= diff[0]) || rtIsNaN(diff[0])) {
    /* MATLAB Function: '<Root>/Boundry prevention' */
    ctrl_student_HIL_B.tau_to_m[0] = -1.03;
  } else {
    /* MATLAB Function: '<Root>/Boundry prevention' */
    ctrl_student_HIL_B.tau_to_m[0] = diff[0];
  }

  if ((-0.98 >= k_psi) || rtIsNaN(k_psi)) {
    /* MATLAB Function: '<Root>/Boundry prevention' */
    ctrl_student_HIL_B.tau_to_m[1] = -0.98;
  } else {
    /* MATLAB Function: '<Root>/Boundry prevention' */
    ctrl_student_HIL_B.tau_to_m[1] = k_psi;
  }

  if ((-2.5 >= a) || rtIsNaN(a)) {
    /* MATLAB Function: '<Root>/Boundry prevention' */
    ctrl_student_HIL_B.tau_to_m[2] = -2.5;
  } else {
    /* MATLAB Function: '<Root>/Boundry prevention' */
    ctrl_student_HIL_B.tau_to_m[2] = a;
  }

  /* MATLAB Function: '<Root>/Boundry prevention' incorporates:
   *  MATLAB Function: '<S3>/MATLAB Function1'
   */
  /* MATLAB Function 'Boundry prevention': '<S1>:1' */
  /* '<S1>:1:2' */
  /*  Axis in the middle of the pool (assumed) */
  /* '<S1>:1:4' */
  for (iS = 0; iS < 2; iS++) {
    /* '<S1>:1:4' */
    if (rtb_TmpSignalConversionAtSFun_f[tmp[iS] - 1] > limit[tmp[iS] + 1] * 0.8)
    {
      /* '<S1>:1:5' */
      /* '<S1>:1:6' */
      ctrl_student_HIL_B.tau_to_m[0] = -ctrl_student_HIL_B.tau_to_m[0];
      ctrl_student_HIL_B.tau_to_m[1] = -ctrl_student_HIL_B.tau_to_m[1];
      ctrl_student_HIL_B.tau_to_m[2] = -ctrl_student_HIL_B.tau_to_m[2];
    }

    if (rtb_TmpSignalConversionAtSFun_f[tmp[iS] - 1] < limit[tmp[iS] - 1] * 0.8)
    {
      /* '<S1>:1:8' */
      /* '<S1>:1:9' */
      ctrl_student_HIL_B.tau_to_m[0] = -ctrl_student_HIL_B.tau_to_m[0];
      ctrl_student_HIL_B.tau_to_m[1] = -ctrl_student_HIL_B.tau_to_m[1];
      ctrl_student_HIL_B.tau_to_m[2] = -ctrl_student_HIL_B.tau_to_m[2];

      /* -tau(direction); */
    }

    /* '<S1>:1:4' */
  }

  /* '<S1>:1:12' */
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Memory: '<S2>/Memory4' */
    ctrl_student_HIL_B.Memory4[0] = ctrl_student_HIL_DW.Memory4_PreviousInput[0];
    ctrl_student_HIL_B.Memory4[1] = ctrl_student_HIL_DW.Memory4_PreviousInput[1];
    ctrl_student_HIL_B.Memory4[2] = ctrl_student_HIL_DW.Memory4_PreviousInput[2];

    /* Memory: '<S2>/Memory3' */
    ctrl_student_HIL_B.Memory3[0] = ctrl_student_HIL_DW.Memory3_PreviousInput[0];
    ctrl_student_HIL_B.Memory3[1] = ctrl_student_HIL_DW.Memory3_PreviousInput[1];
    ctrl_student_HIL_B.Memory3[2] = ctrl_student_HIL_DW.Memory3_PreviousInput[2];

    /* Memory: '<S2>/Memory2' */
    ctrl_student_HIL_B.Memory2[0] = ctrl_student_HIL_DW.Memory2_PreviousInput[0];
    ctrl_student_HIL_B.Memory2[1] = ctrl_student_HIL_DW.Memory2_PreviousInput[1];
    ctrl_student_HIL_B.Memory2[2] = ctrl_student_HIL_DW.Memory2_PreviousInput[2];
  }

  /* MATLAB Function: '<S2>/Observer ' incorporates:
   *  MATLAB Function: '<S3>/MATLAB Function1'
   *  SignalConversion: '<S11>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'DP Observer /Observer ': '<S9>:1' */
  /*  if(first == 1) */
  /*  eta_hat = zeros(3,1) ;  */
  /*  nu_hat = zeros(3,1);  */
  /*  b_hau = zeros(3,1) */
  /*  first_out = 0;  */
  /*  end */
  /* '<S9>:1:8' */
  for (iS = 0; iS < 9; iS++) {
    S[iS] = 0.0;
    L2[iS] = 0.0;
    L3[iS] = 0.0;
  }

  S[0] = ctrl_student_HIL_B.L1_diag[0];
  S[4] = ctrl_student_HIL_B.L1_diag[1];
  S[8] = ctrl_student_HIL_B.L1_diag[2];

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
  rtb_TmpSignalConversionAtSFunct[0] = ctrl_student_HIL_B.x_in -
    ctrl_student_HIL_B.Memory4[0];
  rtb_TmpSignalConversionAtSFunct[1] = ctrl_student_HIL_B.y_in -
    ctrl_student_HIL_B.Memory4[1];
  rtb_TmpSignalConversionAtSFunct[2] = ctrl_student_HIL_B.psi_in -
    ctrl_student_HIL_B.Memory4[2];

  /* '<S9>:1:20' */
  ctrl_student_HIL_B.x_bar = rtb_TmpSignalConversionAtSFunct[0];

  /* '<S9>:1:21' */
  ctrl_student_HIL_B.y_bar = rtb_TmpSignalConversionAtSFunct[1];

  /* '<S9>:1:22' */
  ctrl_student_HIL_B.psi_bar = rtb_TmpSignalConversionAtSFunct[2];

  /* '<S9>:1:23' */
  /* '<S9>:1:24' */
  R[0] = cos(ctrl_student_HIL_B.psi_in);
  R[3] = sin(ctrl_student_HIL_B.psi_in);
  R[6] = 0.0;
  R[1] = -sin(ctrl_student_HIL_B.psi_in);
  R[4] = cos(ctrl_student_HIL_B.psi_in);
  R[7] = 0.0;
  R[2] = 0.0;
  R[5] = 0.0;
  R[8] = 1.0;

  /* '<S9>:1:28' */
  /* '<S9>:1:29' */
  for (iS = 0; iS < 3; iS++) {
    R_0[iS] = R[iS + 6] * ctrl_student_HIL_B.Memory3[2] + (R[iS + 3] *
      ctrl_student_HIL_B.Memory3[1] + R[iS] * ctrl_student_HIL_B.Memory3[0]);
  }

  for (iS = 0; iS < 3; iS++) {
    diff[iS] = S[iS + 6] * rtb_TmpSignalConversionAtSFunct[2] + (S[iS + 3] *
      rtb_TmpSignalConversionAtSFunct[1] + S[iS] *
      rtb_TmpSignalConversionAtSFunct[0]);
  }

  ctrl_student_HIL_B.eta_hat_dot[0] = R_0[0] + diff[0];
  ctrl_student_HIL_B.eta_hat_dot[1] = R_0[1] + diff[1];
  ctrl_student_HIL_B.eta_hat_dot[2] = R_0[2] + diff[2];

  /* '<S9>:1:31' */
  for (iS = 0; iS < 3; iS++) {
    ctrl_student_HIL_B.b_hat_dot[iS] = ((L3[iS + 3] *
      rtb_TmpSignalConversionAtSFunct[1] + L3[iS] *
      rtb_TmpSignalConversionAtSFunct[0]) + L3[iS + 6] *
      rtb_TmpSignalConversionAtSFunct[2]) + ctrl_student_HIL_B.b;
  }

  for (iS = 0; iS < 3; iS++) {
    diff[iS] = b_a[iS + 6] * ctrl_student_HIL_B.Memory3[2] + (b_a[iS + 3] *
      ctrl_student_HIL_B.Memory3[1] + b_a[iS] * ctrl_student_HIL_B.Memory3[0]);
  }

  for (iS = 0; iS < 3; iS++) {
    R_0[iS] = R[3 * iS + 2] * ctrl_student_HIL_B.Memory2[2] + (R[3 * iS + 1] *
      ctrl_student_HIL_B.Memory2[1] + R[3 * iS] * ctrl_student_HIL_B.Memory2[0]);
  }

  for (iS = 0; iS < 3; iS++) {
    for (i = 0; i < 3; i++) {
      L3[iS + 3 * i] = 0.0;
      L3[iS + 3 * i] = L3[3 * i + iS] + R[3 * iS] * L2[3 * i];
      L3[iS + 3 * i] = R[3 * iS + 1] * L2[3 * i + 1] + L3[3 * i + iS];
      L3[iS + 3 * i] = R[3 * iS + 2] * L2[3 * i + 2] + L3[3 * i + iS];
    }
  }

  for (iS = 0; iS < 3; iS++) {
    S_0[iS] = ((L3[iS + 3] * rtb_TmpSignalConversionAtSFunct[1] + L3[iS] *
                rtb_TmpSignalConversionAtSFunct[0]) + L3[iS + 6] *
               rtb_TmpSignalConversionAtSFunct[2]) + ((diff[iS] + R_0[iS]) +
      ctrl_student_HIL_B.tau_to_m[iS]);
  }

  for (iS = 0; iS < 3; iS++) {
    ctrl_student_HIL_B.nu_hat_dot[iS] = 0.0;
    ctrl_student_HIL_B.nu_hat_dot[iS] += a_0[iS] * S_0[0];
    ctrl_student_HIL_B.nu_hat_dot[iS] += a_0[iS + 3] * S_0[1];
    ctrl_student_HIL_B.nu_hat_dot[iS] += a_0[iS + 6] * S_0[2];
  }

  /* End of MATLAB Function: '<S2>/Observer ' */

  /* Integrator: '<S2>/Integrator' */
  ctrl_student_HIL_B.Integrator[0] = ctrl_student_HIL_X.Integrator_CSTATE_m[0];
  ctrl_student_HIL_B.Integrator[1] = ctrl_student_HIL_X.Integrator_CSTATE_m[1];
  ctrl_student_HIL_B.Integrator[2] = ctrl_student_HIL_X.Integrator_CSTATE_m[2];

  /* Integrator: '<S2>/Integrator1' */
  ctrl_student_HIL_B.Integrator1[0] = ctrl_student_HIL_X.Integrator1_CSTATE[0];
  ctrl_student_HIL_B.Integrator1[1] = ctrl_student_HIL_X.Integrator1_CSTATE[1];
  ctrl_student_HIL_B.Integrator1[2] = ctrl_student_HIL_X.Integrator1_CSTATE[2];

  /* Integrator: '<S2>/Integrator2' */
  ctrl_student_HIL_B.Integrator2[0] = ctrl_student_HIL_X.Integrator2_CSTATE[0];
  ctrl_student_HIL_B.Integrator2[1] = ctrl_student_HIL_X.Integrator2_CSTATE[1];
  ctrl_student_HIL_B.Integrator2[2] = ctrl_student_HIL_X.Integrator2_CSTATE[2];

  /* MATLAB Function: '<S5>/the rest ' incorporates:
   *  MATLAB Function: '<S3>/MATLAB Function1'
   *  SignalConversion: '<S11>/TmpSignal ConversionAt SFunction Inport1'
   */
  /* MATLAB Function 'SurgeObserver /the rest ': '<S22>:1' */
  /* '<S22>:1:3' */
  if (sin(ctrl_student_HIL_B.psi_in) + cos(ctrl_student_HIL_B.psi_in) < 0.0) {
    /* '<S22>:1:5' */
    /* '<S22>:1:6' */
    k_psi = -ctrl_student_HIL_B.k_0;
  } else {
    /* '<S22>:1:8' */
    k_psi = ctrl_student_HIL_B.k_0;
  }

  /* '<S22>:1:11' */
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Constant: '<S5>/Constant' */
    ctrl_student_HIL_B.Constant = ctrl_student_HIL_P.Constant_Value;
  }

  /* Integrator: '<S5>/Integrator' */
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    ZCEventType zcEvent;
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &ctrl_student_HIL_PrevZCX.Integrator_Reset_ZCE,
                       ctrl_student_HIL_B.Reset);

    /* evaluate zero-crossings */
    if (zcEvent || ctrl_student_HIL_DW.Integrator_IWORK.IcNeedsLoading) {
      ctrl_student_HIL_X.Integrator_CSTATE_g = ctrl_student_HIL_B.Constant;
    }
  }

  rtb_Integrator_p = ctrl_student_HIL_X.Integrator_CSTATE_g;

  /* Sum: '<S5>/Sum4' incorporates:
   *  MATLAB Function: '<S3>/MATLAB Function1'
   *  MATLAB Function: '<S5>/the rest '
   */
  ctrl_student_HIL_B.u_hat = (rtb_TmpSignalConversionAtSFun_f[0] +
    rtb_TmpSignalConversionAtSFun_f[1]) * k_psi + rtb_Integrator_p;

  /* MATLAB Function: '<S5>/Integration block ' incorporates:
   *  MATLAB Function: '<S3>/MATLAB Function1'
   */
  b_x = ctrl_student_HIL_B.u_hat;

  /* MATLAB Function 'SurgeObserver /Integration block ': '<S21>:1' */
  /* '<S21>:1:2' */
  a = sin(rtb_TmpSignalConversionAtSFun_f[2]) + cos
    (rtb_TmpSignalConversionAtSFun_f[2]);
  if (ctrl_student_HIL_B.Reset != 0.0) {
    /* '<S21>:1:6' */
    b_x = 0.0;
  }

  if (a < 0.0) {
    /* '<S21>:1:9' */
    /* '<S21>:1:10' */
    k_psi = -ctrl_student_HIL_B.k_0;
  } else {
    /* '<S21>:1:12' */
    k_psi = ctrl_student_HIL_B.k_0;
  }

  /* '<S21>:1:15' */
  /* '<S21>:1:17' */
  ctrl_student_HIL_B.y = (-((0.6555 - 0.3545 * fabs(b_x)) + b_x * b_x * 3.787) *
    b_x + ctrl_student_HIL_B.tau_to_m[0]) / 14.79 - k_psi * a * b_x;

  /* End of MATLAB Function: '<S5>/Integration block ' */
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
  }

  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
  }
}

/* Model update function */
void ctrl_student_HIL_update(void)
{
  if (rtmIsMajorTimeStep(ctrl_student_HIL_M)) {
    /* Update for Memory: '<S3>/Memory' */
    memcpy(&ctrl_student_HIL_DW.Memory_PreviousInput[0],
           &ctrl_student_HIL_B.newmem[0], 9U * sizeof(real_T));

    /* Update for Memory: '<S2>/Memory4' */
    ctrl_student_HIL_DW.Memory4_PreviousInput[0] =
      ctrl_student_HIL_B.Integrator[0];
    ctrl_student_HIL_DW.Memory4_PreviousInput[1] =
      ctrl_student_HIL_B.Integrator[1];
    ctrl_student_HIL_DW.Memory4_PreviousInput[2] =
      ctrl_student_HIL_B.Integrator[2];

    /* Update for Memory: '<S2>/Memory3' */
    ctrl_student_HIL_DW.Memory3_PreviousInput[0] =
      ctrl_student_HIL_B.Integrator1[0];
    ctrl_student_HIL_DW.Memory3_PreviousInput[1] =
      ctrl_student_HIL_B.Integrator1[1];
    ctrl_student_HIL_DW.Memory3_PreviousInput[2] =
      ctrl_student_HIL_B.Integrator1[2];

    /* Update for Memory: '<S2>/Memory2' */
    ctrl_student_HIL_DW.Memory2_PreviousInput[0] =
      ctrl_student_HIL_B.Integrator2[0];
    ctrl_student_HIL_DW.Memory2_PreviousInput[1] =
      ctrl_student_HIL_B.Integrator2[1];
    ctrl_student_HIL_DW.Memory2_PreviousInput[2] =
      ctrl_student_HIL_B.Integrator2[2];
  }

  /* Update for Integrator: '<S5>/Integrator' */
  ctrl_student_HIL_DW.Integrator_IWORK.IcNeedsLoading = 0;
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

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = ctrl_student_HIL_B.s_dot;

  /* Derivatives for SecondOrderIntegrator: '<S3>/Integrator, Second-Order' */
  if (ctrl_student_HIL_DW.IntegratorSecondOrder_MODE == 0) {
    _rtXdot->IntegratorSecondOrder_CSTATE[0] =
      ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[1];
    _rtXdot->IntegratorSecondOrder_CSTATE[1] = ctrl_student_HIL_B.u_dot_imu;
  }

  /* End of Derivatives for SecondOrderIntegrator: '<S3>/Integrator, Second-Order' */

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE_m[0] = ctrl_student_HIL_B.eta_hat_dot[0];
  _rtXdot->Integrator_CSTATE_m[1] = ctrl_student_HIL_B.eta_hat_dot[1];
  _rtXdot->Integrator_CSTATE_m[2] = ctrl_student_HIL_B.eta_hat_dot[2];

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = ctrl_student_HIL_B.nu_hat_dot[0];
  _rtXdot->Integrator1_CSTATE[1] = ctrl_student_HIL_B.nu_hat_dot[1];
  _rtXdot->Integrator1_CSTATE[2] = ctrl_student_HIL_B.nu_hat_dot[2];

  /* Derivatives for Integrator: '<S2>/Integrator2' */
  _rtXdot->Integrator2_CSTATE[0] = ctrl_student_HIL_B.b_hat_dot[0];
  _rtXdot->Integrator2_CSTATE[1] = ctrl_student_HIL_B.b_hat_dot[1];
  _rtXdot->Integrator2_CSTATE[2] = ctrl_student_HIL_B.b_hat_dot[2];

  /* Derivatives for Integrator: '<S5>/Integrator' */
  {
    ((XDot_ctrl_student_HIL_T *) ctrl_student_HIL_M->ModelData.derivs)
      ->Integrator_CSTATE_g = ctrl_student_HIL_B.y;
  }
}

/* Model initialize function */
void ctrl_student_HIL_initialize(void)
{
  /* Start for Constant: '<S5>/Constant' */
  ctrl_student_HIL_B.Constant = ctrl_student_HIL_P.Constant_Value;
  ctrl_student_HIL_PrevZCX.IntegratorSecondOrder_Reset_ZCE = UNINITIALIZED_ZCSIG;
  ctrl_student_HIL_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  ctrl_student_HIL_X.Integrator_CSTATE = ctrl_student_HIL_P.Integrator_IC;

  /* InitializeConditions for Memory: '<S3>/Memory' */
  memcpy(&ctrl_student_HIL_DW.Memory_PreviousInput[0],
         &ctrl_student_HIL_P.Memory_X0[0], 9U * sizeof(real_T));

  /* InitializeConditions for SecondOrderIntegrator: '<S3>/Integrator, Second-Order' */
  ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[0] =
    ctrl_student_HIL_P.IntegratorSecondOrder_ICX;
  ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[1] =
    ctrl_student_HIL_P.IntegratorSecondOrder_ICDXDT;
  ctrl_student_HIL_DW.IntegratorSecondOrder_MODE = 0;

  /* InitializeConditions for Memory: '<S2>/Memory4' */
  ctrl_student_HIL_DW.Memory4_PreviousInput[0] = ctrl_student_HIL_P.Memory4_X0[0];
  ctrl_student_HIL_DW.Memory4_PreviousInput[1] = ctrl_student_HIL_P.Memory4_X0[1];
  ctrl_student_HIL_DW.Memory4_PreviousInput[2] = ctrl_student_HIL_P.Memory4_X0[2];

  /* InitializeConditions for Memory: '<S2>/Memory3' */
  ctrl_student_HIL_DW.Memory3_PreviousInput[0] = ctrl_student_HIL_P.Memory3_X0[0];
  ctrl_student_HIL_DW.Memory3_PreviousInput[1] = ctrl_student_HIL_P.Memory3_X0[1];
  ctrl_student_HIL_DW.Memory3_PreviousInput[2] = ctrl_student_HIL_P.Memory3_X0[2];

  /* InitializeConditions for Memory: '<S2>/Memory2' */
  ctrl_student_HIL_DW.Memory2_PreviousInput[0] = ctrl_student_HIL_P.Memory2_X0[0];
  ctrl_student_HIL_DW.Memory2_PreviousInput[1] = ctrl_student_HIL_P.Memory2_X0[1];
  ctrl_student_HIL_DW.Memory2_PreviousInput[2] = ctrl_student_HIL_P.Memory2_X0[2];

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  ctrl_student_HIL_X.Integrator_CSTATE_m[0] = ctrl_student_HIL_P.Integrator_IC_d;
  ctrl_student_HIL_X.Integrator_CSTATE_m[1] = ctrl_student_HIL_P.Integrator_IC_d;
  ctrl_student_HIL_X.Integrator_CSTATE_m[2] = ctrl_student_HIL_P.Integrator_IC_d;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  ctrl_student_HIL_X.Integrator1_CSTATE[0] = ctrl_student_HIL_P.Integrator1_IC;
  ctrl_student_HIL_X.Integrator1_CSTATE[1] = ctrl_student_HIL_P.Integrator1_IC;
  ctrl_student_HIL_X.Integrator1_CSTATE[2] = ctrl_student_HIL_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<S2>/Integrator2' */
  ctrl_student_HIL_X.Integrator2_CSTATE[0] = ctrl_student_HIL_P.Integrator2_IC;
  ctrl_student_HIL_X.Integrator2_CSTATE[1] = ctrl_student_HIL_P.Integrator2_IC;
  ctrl_student_HIL_X.Integrator2_CSTATE[2] = ctrl_student_HIL_P.Integrator2_IC;

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  if (rtmIsFirstInitCond(ctrl_student_HIL_M)) {
    ctrl_student_HIL_X.Integrator_CSTATE_g = 0.0;
  }

  ctrl_student_HIL_DW.Integrator_IWORK.IcNeedsLoading = 1;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(ctrl_student_HIL_M)) {
    rtmSetFirstInitCond(ctrl_student_HIL_M, 0);
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
  rtmSetFirstInitCond(ctrl_student_HIL_M, 1);

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
  ctrl_student_HIL_M->Sizes.numContStates = (13);/* Number of continuous states */
  ctrl_student_HIL_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  ctrl_student_HIL_M->Sizes.numY = (0);/* Number of model outputs */
  ctrl_student_HIL_M->Sizes.numU = (0);/* Number of model inputs */
  ctrl_student_HIL_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  ctrl_student_HIL_M->Sizes.numSampTimes = (2);/* Number of sample times */
  ctrl_student_HIL_M->Sizes.numBlocks = (78);/* Number of blocks */
  ctrl_student_HIL_M->Sizes.numBlockIO = (46);/* Number of block outputs */
  ctrl_student_HIL_M->Sizes.numBlockPrms = (299);/* Sum of parameter "widths" */
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
    return NIRT_GetValueByDataType(ptr,subindex,3,Complex);

   case 23:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 24:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 25:
    return NIRT_GetValueByDataType(ptr,subindex,8,Complex);

   case 33:
    return NIRT_GetValueByDataType(ptr,subindex,0,Complex);

   case 34:
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
    return NIRT_SetValueByDataType(ptr,subindex,value,3,Complex);

   case 23:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 24:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 25:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,8,Complex);

   case 33:
    //Type is matrix. Call SetValueByDataType on its contained type
    return NIRT_SetValueByDataType(ptr,subindex,value,0,Complex);

   case 34:
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

  // r_in
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.r_in, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Reset
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.Reset, 0, data[index++], 0, 0);
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

  // k_0
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.k_0, 0, data[index++], 0, 0);
  } else {
    index += 1;
  }

  // Dead reckoning/u_dot_imu
  if (TaskSampleHit[0]) {
    NIRT_SetValueByDataType(&ctrl_student_HIL_B.u_dot_imu, 0, data[index++], 0,
      0);
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
  return 31;
}

double ni_extout[20];
void SetExternalOutputs(double* data, int* TaskSampleHit)
{
  int index = 0, count = 0;

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

  // DP Observer /psi_bar: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.psi_bar,0,0,
      0);
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

  // DP Observer /x_bar: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.x_bar,0,0,0);
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

  // DP Observer /y_bar: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.y_bar,0,0,0);
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

  // SurgeObserver /u_hat: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.u_hat,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/N_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.tau_to_m,2,
      17,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/X_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.tau_to_m,0,
      17,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/Y_d: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.tau_to_m,1,
      17,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/integrator reset model: Virtual Signal # 0
  if (TaskSampleHit[0]) {              // sample and hold
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
      (&ctrl_student_HIL_P.Constant_Value_i,0,0,0);
  } else {
    index += 1;
  }

  // tau to CSE mocell (only use for HIL testing)/y_0: Virtual Signal # 0
  if (TaskSampleHit[1]) {              // sample and hold
    ni_extout[index++] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_P.Constant1_Value,0,0,0);
  } else {
    index += 1;
  }

  if (data)
    memcpy(&data[0], &ni_extout[0], sizeof(ni_extout));
}

long NumOutputPorts(void)
{
  return 20;
}

int NI_InitExternalOutputs()
{
  int index = 0, count = 0;

  // psi_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,2,17,0);

  // x_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,0,17,0);

  // y_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.eta_d,1,17,0);

  // DP Observer /psi_bar: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.psi_bar,0,0,0);

  // DP Observer /psi_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,2,
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

  // DP Observer /x_bar: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.x_bar,0,0,0);

  // DP Observer /x_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,0,
    17,0);

  // DP Observer /y_bar: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.y_bar,0,0,0);

  // DP Observer /y_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Integrator,1,
    17,0);

  // SurgeObserver /u_hat: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.u_hat,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/N_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.tau_to_m,2,17,
    0);

  // tau to CSE mocell (only use for HIL testing)/X_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.tau_to_m,0,17,
    0);

  // tau to CSE mocell (only use for HIL testing)/Y_d: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.tau_to_m,1,17,
    0);

  // tau to CSE mocell (only use for HIL testing)/integrator reset model: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType(&ctrl_student_HIL_B.Reset,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/psi_0 : Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant2_Value,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/x_0: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant_Value_i,0,0,0);

  // tau to CSE mocell (only use for HIL testing)/y_0: Virtual Signal # 0
  ni_extout[index++] = NIRT_GetValueByDataType
    (&ctrl_student_HIL_P.Constant1_Value,0,0,0);
  return NI_OK;
}

// by default, all elements (inclulding	scalars) have 2 dimensions [1,1]
static NI_Parameter NI_ParamList[] DataSection(".NIVS.paramlist") =
{
  { 0, "ctrl_student_hil/Integrator/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator_IC), 33, 1, 2, 0, 0 },

  { 1, "ctrl_student_hil/Dead reckoning/Memory/X0", offsetof
    (P_ctrl_student_HIL_T, Memory_X0), 20, 9, 2, 2, 0 },

  { 2, "ctrl_student_hil/Dead reckoning/Integrator, Second-Order/ICX", offsetof
    (P_ctrl_student_HIL_T, IntegratorSecondOrder_ICX), 33, 1, 2, 4, 0 },

  { 3, "ctrl_student_hil/Dead reckoning/Integrator, Second-Order/ICDXDT",
    offsetof(P_ctrl_student_HIL_T, IntegratorSecondOrder_ICDXDT), 33, 1, 2, 6, 0
  },

  { 4, "ctrl_student_hil/DP Observer /Memory4/X0", offsetof(P_ctrl_student_HIL_T,
    Memory4_X0), 18, 3, 2, 8, 0 },

  { 5, "ctrl_student_hil/DP Observer /Memory3/X0", offsetof(P_ctrl_student_HIL_T,
    Memory3_X0), 18, 3, 2, 10, 0 },

  { 6, "ctrl_student_hil/DP Observer /Memory2/X0", offsetof(P_ctrl_student_HIL_T,
    Memory2_X0), 18, 3, 2, 12, 0 },

  { 7, "ctrl_student_hil/DP Observer /Integrator/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator_IC_d), 33, 1, 2, 14, 0 },

  { 8, "ctrl_student_hil/DP Observer /Integrator1/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator1_IC), 33, 1, 2, 16, 0 },

  { 9, "ctrl_student_hil/DP Observer /Integrator2/InitialCondition", offsetof
    (P_ctrl_student_HIL_T, Integrator2_IC), 33, 1, 2, 18, 0 },

  { 10, "ctrl_student_hil/SurgeObserver /Constant/Value", offsetof
    (P_ctrl_student_HIL_T, Constant_Value), 33, 1, 2, 20, 0 },

  { 11,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant2/Value",
    offsetof(P_ctrl_student_HIL_T, Constant2_Value), 33, 1, 2, 22, 0 },

  { 12,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant/Value",
    offsetof(P_ctrl_student_HIL_T, Constant_Value_i), 33, 1, 2, 24, 0 },

  { 13,
    "ctrl_student_hil/tau to CSE mocell (only use for HIL testing)/Constant1/Value",
    offsetof(P_ctrl_student_HIL_T, Constant1_Value), 33, 1, 2, 26, 0 },
};

static int NI_ParamListSize DataSection(".NIVS.paramlistsize") = 14;
static int NI_ParamDimList[] DataSection(".NIVS.paramdimlist") =
{
  1, 1,                                /* Parameter at index 0 */
  3, 3,                                /* Parameter at index 1 */
  1, 1,                                /* Parameter at index 2 */
  1, 1,                                /* Parameter at index 3 */
  3, 1,                                /* Parameter at index 4 */
  3, 1,                                /* Parameter at index 5 */
  3, 1,                                /* Parameter at index 6 */
  1, 1,                                /* Parameter at index 7 */
  1, 1,                                /* Parameter at index 8 */
  1, 1,                                /* Parameter at index 9 */
  1, 1,                                /* Parameter at index 10 */
  1, 1,                                /* Parameter at index 11 */
  1, 1,                                /* Parameter at index 12 */
  1, 1,                                /* Parameter at index 13 */
};

static NI_Signal NI_SigList[] DataSection(".NIVS.siglist") =
{
  { 0, "ctrl_student_hil/y_in", 0, "", offsetof(B_ctrl_student_HIL_T, y_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 0, 0 },

  { 1, "ctrl_student_hil/Dead reckoning/Memory", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory)+0*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 2, 0
  },

  { 2, "ctrl_student_hil/Dead reckoning/Memory", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, Memory)+1*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 4, 0
  },

  { 3, "ctrl_student_hil/Dead reckoning/Memory", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, Memory)+2*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 6, 0
  },

  { 4, "ctrl_student_hil/Dead reckoning/Memory", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory)+3*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 8, 0
  },

  { 5, "ctrl_student_hil/Dead reckoning/Memory", 0, "(2,2)", offsetof
    (B_ctrl_student_HIL_T, Memory)+4*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 10,
    0 },

  { 6, "ctrl_student_hil/Dead reckoning/Memory", 0, "(3,2)", offsetof
    (B_ctrl_student_HIL_T, Memory)+5*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 12,
    0 },

  { 7, "ctrl_student_hil/Dead reckoning/Memory", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory)+6*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 14,
    0 },

  { 8, "ctrl_student_hil/Dead reckoning/Memory", 0, "(2,3)", offsetof
    (B_ctrl_student_HIL_T, Memory)+7*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 16,
    0 },

  { 9, "ctrl_student_hil/Dead reckoning/Memory", 0, "(3,3)", offsetof
    (B_ctrl_student_HIL_T, Memory)+8*sizeof(real_T), BLOCKIO_SIG, 20, 1, 2, 18,
    0 },

  { 10, "ctrl_student_hil/x_in", 0, "", offsetof(B_ctrl_student_HIL_T, x_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 20, 0 },

  { 11, "ctrl_student_hil/psi_in", 0, "", offsetof(B_ctrl_student_HIL_T, psi_in)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 22, 0 },

  { 12, "ctrl_student_hil/u_in", 0, "", offsetof(B_ctrl_student_HIL_T, u_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 24, 0 },

  { 13, "ctrl_student_hil/v_in", 0, "", offsetof(B_ctrl_student_HIL_T, v_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 26, 0 },

  { 14, "ctrl_student_hil/r_in", 0, "", offsetof(B_ctrl_student_HIL_T, r_in)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 28, 0 },

  { 15, "ctrl_student_hil/Reset", 0, "", offsetof(B_ctrl_student_HIL_T, Reset)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 30, 0 },

  { 16, "ctrl_student_hil/DP Observer /L1_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 32,
    0 },

  { 17, "ctrl_student_hil/DP Observer /L1_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 34,
    0 },

  { 18, "ctrl_student_hil/DP Observer /L1_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L1_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 36,
    0 },

  { 19, "ctrl_student_hil/DP Observer /L2_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 38,
    0 },

  { 20, "ctrl_student_hil/DP Observer /L2_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 40,
    0 },

  { 21, "ctrl_student_hil/DP Observer /L2_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L2_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 42,
    0 },

  { 22, "ctrl_student_hil/DP Observer /L3_diag", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+0*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 44,
    0 },

  { 23, "ctrl_student_hil/DP Observer /L3_diag", 0, "(2,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+1*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 46,
    0 },

  { 24, "ctrl_student_hil/DP Observer /L3_diag", 0, "(3,1)", offsetof
    (B_ctrl_student_HIL_T, L3_diag)+2*sizeof(real_T), BLOCKIO_SIG, 18, 1, 2, 48,
    0 },

  { 25, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 50,
    0 },

  { 26, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 52,
    0 },

  { 27, "ctrl_student_hil/DP Observer /Memory4", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory4)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 54,
    0 },

  { 28, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 56,
    0 },

  { 29, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 58,
    0 },

  { 30, "ctrl_student_hil/DP Observer /Memory3", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory3)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 60,
    0 },

  { 31, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 62,
    0 },

  { 32, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 64,
    0 },

  { 33, "ctrl_student_hil/DP Observer /Memory2", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Memory2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 66,
    0 },

  { 34, "ctrl_student_hil/DP Observer /b", 0, "", offsetof(B_ctrl_student_HIL_T,
    b)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 68, 0 },

  { 35, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    70, 0 },

  { 36, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    72, 0 },

  { 37, "ctrl_student_hil/DP Observer /Integrator", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    74, 0 },

  { 38, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    76, 0 },

  { 39, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    78, 0 },

  { 40, "ctrl_student_hil/DP Observer /Integrator1", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator1)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    80, 0 },

  { 41, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,1)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    82, 0 },

  { 42, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,2)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    84, 0 },

  { 43, "ctrl_student_hil/DP Observer /Integrator2", 0, "(1,3)", offsetof
    (B_ctrl_student_HIL_T, Integrator2)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    86, 0 },

  { 44, "ctrl_student_hil/k_0", 0, "", offsetof(B_ctrl_student_HIL_T, k_0)+0*
    sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 88, 0 },

  { 45, "ctrl_student_hil/SurgeObserver /Constant", 0, "", offsetof
    (B_ctrl_student_HIL_T, Constant)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 90,
    0 },

  { 46, "ctrl_student_hil/SurgeObserver /Sum4", 0, "u_hat", offsetof
    (B_ctrl_student_HIL_T, u_hat)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 92, 0
  },

  { 47, "ctrl_student_hil/Dead reckoning/u_dot_imu", 0, "", offsetof
    (B_ctrl_student_HIL_T, u_dot_imu)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 94,
    0 },

  { 48, "ctrl_student_hil/joystick/L2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, L2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    96, 0 },

  { 49, "ctrl_student_hil/joystick/PosXRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 98,
    0 },

  { 50, "ctrl_student_hil/joystick/PosYRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    100, 0 },

  { 51, "ctrl_student_hil/joystick/R2_continuous", 0, "", offsetof
    (B_ctrl_student_HIL_T, R2_continuous)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    102, 0 },

  { 52, "ctrl_student_hil/joystick/PosXLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosXLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 104,
    0 },

  { 53, "ctrl_student_hil/joystick/PosYLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, PosYLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 106,
    0 },

  { 54, "ctrl_student_hil/joystick/L1", 0, "", offsetof(B_ctrl_student_HIL_T, L1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 108, 0 },

  { 55, "ctrl_student_hil/joystick/R1", 0, "", offsetof(B_ctrl_student_HIL_T, R1)
    +0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 110, 0 },

  { 56, "ctrl_student_hil/joystick/ArrowDown", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowDown)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    112, 0 },

  { 57, "ctrl_student_hil/joystick/ArrowUp", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowUp)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 114,
    0 },

  { 58, "ctrl_student_hil/joystick/ArrowLeft", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowLeft)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    116, 0 },

  { 59, "ctrl_student_hil/joystick/ArrowRight", 0, "", offsetof
    (B_ctrl_student_HIL_T, ArrowRight)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2,
    118, 0 },

  { 60, "ctrl_student_hil/Transfer function", 0, "s_dot", offsetof
    (B_ctrl_student_HIL_T, s_dot)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 120, 0
  },

  { 61, "ctrl_student_hil/Transfer function", 2, "eta_d(1,1)", offsetof
    (B_ctrl_student_HIL_T, eta_d)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 122,
    0 },

  { 62, "ctrl_student_hil/Transfer function", 2, "eta_d(1,2)", offsetof
    (B_ctrl_student_HIL_T, eta_d)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 124,
    0 },

  { 63, "ctrl_student_hil/Transfer function", 2, "eta_d(1,3)", offsetof
    (B_ctrl_student_HIL_T, eta_d)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2, 126,
    0 },

  { 64, "ctrl_student_hil/SurgeObserver /Integration block", 0, "y", offsetof
    (B_ctrl_student_HIL_T, y)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 128, 0 },

  { 65, "ctrl_student_hil/Dead reckoning/MATLAB Function", 0, "dead_x", offsetof
    (B_ctrl_student_HIL_T, dead_x)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 130,
    0 },

  { 66, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(1,1)",
    offsetof(B_ctrl_student_HIL_T, newmem)+0*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 132, 0 },

  { 67, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(2,1)",
    offsetof(B_ctrl_student_HIL_T, newmem)+1*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 134, 0 },

  { 68, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(3,1)",
    offsetof(B_ctrl_student_HIL_T, newmem)+2*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 136, 0 },

  { 69, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(1,2)",
    offsetof(B_ctrl_student_HIL_T, newmem)+3*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 138, 0 },

  { 70, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(2,2)",
    offsetof(B_ctrl_student_HIL_T, newmem)+4*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 140, 0 },

  { 71, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(3,2)",
    offsetof(B_ctrl_student_HIL_T, newmem)+5*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 142, 0 },

  { 72, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(1,3)",
    offsetof(B_ctrl_student_HIL_T, newmem)+6*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 144, 0 },

  { 73, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(2,3)",
    offsetof(B_ctrl_student_HIL_T, newmem)+7*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 146, 0 },

  { 74, "ctrl_student_hil/Dead reckoning/MATLAB Function", 1, "newmem(3,3)",
    offsetof(B_ctrl_student_HIL_T, newmem)+8*sizeof(real_T), BLOCKIO_SIG, 20, 1,
    2, 148, 0 },

  { 75, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,1)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 150, 0 },

  { 76, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,2)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 152, 0 },

  { 77, "ctrl_student_hil/DP Observer /Observer", 0, "eta_hat_dot(1,3)",
    offsetof(B_ctrl_student_HIL_T, eta_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG,
    17, 1, 2, 154, 0 },

  { 78, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,1)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    156, 0 },

  { 79, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,2)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    158, 0 },

  { 80, "ctrl_student_hil/DP Observer /Observer", 1, "nu_hat_dot(1,3)", offsetof
    (B_ctrl_student_HIL_T, nu_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    160, 0 },

  { 81, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,1)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    162, 0 },

  { 82, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,2)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    164, 0 },

  { 83, "ctrl_student_hil/DP Observer /Observer", 2, "b_hat_dot(1,3)", offsetof
    (B_ctrl_student_HIL_T, b_hat_dot)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    166, 0 },

  { 84, "ctrl_student_hil/DP Observer /Observer", 3, "x_bar", offsetof
    (B_ctrl_student_HIL_T, x_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 168, 0
  },

  { 85, "ctrl_student_hil/DP Observer /Observer", 4, "y_bar", offsetof
    (B_ctrl_student_HIL_T, y_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 170, 0
  },

  { 86, "ctrl_student_hil/DP Observer /Observer", 5, "psi_bar", offsetof
    (B_ctrl_student_HIL_T, psi_bar)+0*sizeof(real_T), BLOCKIO_SIG, 0, 1, 2, 172,
    0 },

  { 87, "ctrl_student_hil/Boundry prevention", 0, "tau_to_m(1,1)", offsetof
    (B_ctrl_student_HIL_T, tau_to_m)+0*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    174, 0 },

  { 88, "ctrl_student_hil/Boundry prevention", 0, "tau_to_m(1,2)", offsetof
    (B_ctrl_student_HIL_T, tau_to_m)+1*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    176, 0 },

  { 89, "ctrl_student_hil/Boundry prevention", 0, "tau_to_m(1,3)", offsetof
    (B_ctrl_student_HIL_T, tau_to_m)+2*sizeof(real_T), BLOCKIO_SIG, 17, 1, 2,
    178, 0 },

  { -1, "", -1, "", 0, 0, 0 }
};

static int NI_SigListSize DataSection(".NIVS.siglistsize") = 90;
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
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, };

static long NI_ExtListSize DataSection(".NIVS.extlistsize") = 45;
static NI_ExternalIO NI_ExtList[] DataSection(".NIVS.extlist") =
{
  { 0, "y_in", 0, EXT_IN, 1, 1, 1 },

  { 1, "x_in", 0, EXT_IN, 1, 1, 1 },

  { 2, "psi_in", 0, EXT_IN, 1, 1, 1 },

  { 3, "u_in", 0, EXT_IN, 1, 1, 1 },

  { 4, "v_in", 0, EXT_IN, 1, 1, 1 },

  { 5, "r_in", 0, EXT_IN, 1, 1, 1 },

  { 6, "Reset", 0, EXT_IN, 1, 1, 1 },

  { 7, "DP Observer /L1_diag", 0, EXT_IN, 3, 3, 1 },

  { 8, "DP Observer /L2_diag ", 0, EXT_IN, 3, 3, 1 },

  { 9, "DP Observer /L3_diag", 0, EXT_IN, 3, 3, 1 },

  { 10, "DP Observer /b", 0, EXT_IN, 1, 1, 1 },

  { 11, "k_0", 0, EXT_IN, 1, 1, 1 },

  { 12, "Dead reckoning/u_dot_imu", 0, EXT_IN, 1, 1, 1 },

  { 13, "joystick/L2_continuous", 1, EXT_IN, 1, 1, 1 },

  { 14, "joystick/PosXRight", 1, EXT_IN, 1, 1, 1 },

  { 15, "joystick/PosYRight", 1, EXT_IN, 1, 1, 1 },

  { 16, "joystick/R2_continuous", 1, EXT_IN, 1, 1, 1 },

  { 17, "joystick/PosXLeft", 1, EXT_IN, 1, 1, 1 },

  { 18, "joystick/PosYLeft", 1, EXT_IN, 1, 1, 1 },

  { 19, "joystick/L1", 1, EXT_IN, 1, 1, 1 },

  { 20, "joystick/R1", 1, EXT_IN, 1, 1, 1 },

  { 21, "joystick/ArrowDown", 1, EXT_IN, 1, 1, 1 },

  { 22, "joystick/ArrowUp", 1, EXT_IN, 1, 1, 1 },

  { 23, "joystick/ArrowLeft", 1, EXT_IN, 1, 1, 1 },

  { 24, "joystick/ArrowRight", 1, EXT_IN, 1, 1, 1 },

  { 0, "psi_d", 0, EXT_OUT, 1, 1, 1 },

  { 1, "x_d", 0, EXT_OUT, 1, 1, 1 },

  { 2, "y_d", 0, EXT_OUT, 1, 1, 1 },

  { 3, "DP Observer /psi_bar", 0, EXT_OUT, 1, 1, 1 },

  { 4, "DP Observer /psi_hat", 0, EXT_OUT, 1, 1, 1 },

  { 5, "DP Observer /r_dot", 0, EXT_OUT, 1, 1, 1 },

  { 6, "DP Observer /u_dot", 0, EXT_OUT, 1, 1, 1 },

  { 7, "DP Observer /v_dot", 0, EXT_OUT, 1, 1, 1 },

  { 8, "DP Observer /x_bar", 0, EXT_OUT, 1, 1, 1 },

  { 9, "DP Observer /x_hat", 0, EXT_OUT, 1, 1, 1 },

  { 10, "DP Observer /y_bar", 0, EXT_OUT, 1, 1, 1 },

  { 11, "DP Observer /y_hat", 0, EXT_OUT, 1, 1, 1 },

  { 12, "SurgeObserver /u_hat", 0, EXT_OUT, 1, 1, 1 },

  { 13, "tau to CSE mocell (only use for HIL testing)/N_d", 0, EXT_OUT, 1, 1, 1
  },

  { 14, "tau to CSE mocell (only use for HIL testing)/X_d", 0, EXT_OUT, 1, 1, 1
  },

  { 15, "tau to CSE mocell (only use for HIL testing)/Y_d", 0, EXT_OUT, 1, 1, 1
  },

  { 16, "tau to CSE mocell (only use for HIL testing)/integrator reset model", 0,
    EXT_OUT, 1, 1, 1 },

  { 17, "tau to CSE mocell (only use for HIL testing)/psi_0 ", 1, EXT_OUT, 1, 1,
    1 },

  { 18, "tau to CSE mocell (only use for HIL testing)/x_0", 1, EXT_OUT, 1, 1, 1
  },

  { 19, "tau to CSE mocell (only use for HIL testing)/y_0", 1, EXT_OUT, 1, 1, 1
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
static char* NI_CompiledModelVersion = "1.332";
static char* NI_CompiledModelDateTime = "Sat Mar 25 19:37:01 2017";
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
      *numContStates = 13;
      *numDiscStates = 915;
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
      (&ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[0], 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "IntegratorSecondOrder_CSTATE");
    contStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[0], 1, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "IntegratorSecondOrder_CSTATE");
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
      (&ctrl_student_HIL_X.Integrator_CSTATE_g, 0, 0, 0);
    strcpy(contStatesNames + (idx++ * 100), "Integrator_CSTATE_g");
  }

  if (discStates && discStatesNames) {
    idx = 0;
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_in_DWORK1");
    for (count = 0; count < 9; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.Memory_PreviousInput, count, 21, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.Memory_PreviousInput");
    }

    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_in_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.psi_d_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.psi_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_d_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_d_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.Reset_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.Reset_DWORK1");
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
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.b_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.b_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.psi_bar_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.psi_bar_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.psi_hat_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.psi_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.r_dot_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.r_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.v_dot_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_bar_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_bar_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_bar_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_bar_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.y_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.y_hat_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.k_0_DWORK1, 0,
      0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.k_0_DWORK1");
    discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.u_hat_DWORK1,
      0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.u_hat_DWORK1");
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
      (&ctrl_student_HIL_DW.u_dot_imu_DWORK1, 0, 0, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.u_dot_imu_DWORK1");
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
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK2, 0, 6, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK2");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.Integrator_IWORK.IcNeedsLoading, 0, 10, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.Integrator_IWORK.IcNeedsLoading");
    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.IntegratorSecondOrder_MODE, 0, 10, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.IntegratorSecondOrder_MODE");
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
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.x_d_DWORK2");
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
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L1_diag_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L1_diag_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L2_diag_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L2_diag_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.L3_diag_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.L3_diag_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.b_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.b_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_bar_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_bar_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.psi_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.psi_hat_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.r_dot_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.r_dot_DWORK2");
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
        (&ctrl_student_HIL_DW.x_bar_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.x_bar_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.x_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.x_hat_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.y_bar_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.y_bar_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.y_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.y_hat_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType(&ctrl_student_HIL_DW.k_0_DWORK2,
        count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100), "&ctrl_student_HIL_DW.k_0_DWORK2");
    }

    for (count = 0; count < 17; count++) {
      discStates[idx] = NIRT_GetValueByDataType
        (&ctrl_student_HIL_DW.u_hat_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.u_hat_DWORK2");
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
        (&ctrl_student_HIL_DW.u_dot_imu_DWORK2, count, 19, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.u_dot_imu_DWORK2");
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
        (&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK3, count, 22, 0);
      strcpy(discStatesNames + (idx++ * 100),
             "&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK3");
    }

    discStates[idx] = NIRT_GetValueByDataType
      (&ctrl_student_HIL_DW.IntegratorSecondOrder_DWORK1, 0, 8, 0);
    strcpy(discStatesNames + (idx++ * 100),
           "&ctrl_student_HIL_DW.IntegratorSecondOrder_DWORK1");
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
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[0],
      0, contStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.IntegratorSecondOrder_CSTATE[0],
      1, contStates[idx++], 0, 0);
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
    NIRT_SetValueByDataType(&ctrl_student_HIL_X.Integrator_CSTATE_g, 0,
      contStates[idx++], 0, 0);
  }

  if (discStates) {
    idx = 0;
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    for (count = 0; count < 9; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Memory_PreviousInput, count,
        discStates[idx++], 21, 0);
    }

    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_in_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_in_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_d_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_d_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Reset_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK1, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK1, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK1, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK1, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK1, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK1, 2,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK1, 0,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK1, 1,
      discStates[idx++], 17, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK1, 2,
      discStates[idx++], 17, 0);
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
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.b_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_bar_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_hat_DWORK1, 0,
      discStates[idx++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_dot_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_dot_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_dot_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_bar_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_bar_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_hat_DWORK1, 0, discStates[idx
      ++], 0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.k_0_DWORK1, 0, discStates[idx++],
      0, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_hat_DWORK1, 0, discStates[idx
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
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_dot_imu_DWORK1, 0,
      discStates[idx++], 0, 0);
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
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.NIVeriStandSignalProbe_DWORK2,
      0, discStates[idx++], 6, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.Integrator_IWORK.IcNeedsLoading,
      0, discStates[idx++], 10, 0);
    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.IntegratorSecondOrder_MODE, 0,
      discStates[idx++], 10, 0);
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
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_in_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.v_in_DWORK2, count,
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
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_d_DWORK2, count,
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
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L1_diag_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L2_diag_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.L3_diag_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.b_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_bar_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.psi_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.r_dot_DWORK2, count,
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
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_bar_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.x_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_bar_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.y_hat_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.k_0_DWORK2, count,
        discStates[idx++], 19, 0);
    }

    for (count = 0; count < 17; count++) {
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_hat_DWORK2, count,
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
      NIRT_SetValueByDataType(&ctrl_student_HIL_DW.u_dot_imu_DWORK2, count,
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
        count, discStates[idx++], 22, 0);
    }

    NIRT_SetValueByDataType(&ctrl_student_HIL_DW.IntegratorSecondOrder_DWORK1, 0,
      discStates[idx++], 8, 0);
  }

  if (clockTicks) {
    S->Timing.clockTick0 = clockTicks[0];
    S->Timing.clockTick1 = clockTicks[0];
  }

  return NI_OK;
}

#endif                                 // of NI_ROOTMODEL_ctrl_student_HIL
