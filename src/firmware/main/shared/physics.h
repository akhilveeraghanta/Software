#pragma once

#include "math/tbots_math.h"

// This file contains all the physical constants of the robot
// Dimensions and the like as well as

#define CONTROL_LOOP_HZ 200U
#define QUARTERDEGREE_TO_MS (0.0000554f * CONTROL_LOOP_HZ)
#define QUARTERDEGREE_TO_RPM                                                             \
    (CONTROL_LOOP_HZ / 240.0f)       // encoder quarter of degree to motor RPM
#define RPM_TO_VOLT (1.0f / 374.0f)  // motor RPM to back EMF

#define HALL_PHASE_TO_MS (0.00171 * CONTROL_LOOP_HZ)

#define QUARTERDEGREE_TO_VOLT (QUARTERDEGREE_TO_RPM * RPM_TO_VOLT)

#define ROBOT_RADIUS 0.085f
#define TICK_TIME (1.0f / (float)CONTROL_LOOP_HZ)
#define ROBOT_POINT_MASS 2.48f
#define WHEEL_SLIP_VOLTAGE_LIMIT 4.25f  // Voltage where wheel slips (acceleration cap)

// Maximum safe jerk for the robot
#define JERK_LIMIT 40.0f  //(m/s^3)

// all the interial components of the robot
// This one is a little strange as it is the effective rotational mass
// The rotational mass * (ROBOT_RADIUS)^2 will give the conventional interia
#define INERTIAL_FACTOR 0.37f

// factor for steel motor mounts
#define STEEL_INTERTIAL_FACTOR 0.3858f

#define ROT_MASS (INERTIAL_FACTOR * ROBOT_POINT_MASS)
#define INERTIA (ROT_MASS * ROBOT_RADIUS * ROBOT_RADIUS)

#define CURRENT_PER_TORQUE 39.21f  // from motor data sheet (1/25.5 mNm)
#define GEAR_RATIO 0.5143f         // define as speed multiplication from motor to wheel
#define WHEEL_RADIUS 0.0254f

// constants for radial bangbang controller
#define MAX_R_V 2.0f
#define MAX_R_A 3.0f


#define MAX_X_V 2.0f  // maximal linear velocity in the X direction
#define MAX_Y_V 1.0f  // maximum linear velocity in the Y direction
#define MAX_T_V 0.1f  // max robot rotation rate in radians per second

extern const float MAX_VEL[3];

// WRONG NUMBERS, POKE JON TO GET ACTUAL NUMBERS
#define MAX_X_A 3.0f
#define MAX_Y_A 3.0f
#define MAX_T_A 30.0f

//#define SLOW_MAX_X_A 1.2f
//#define SLOW_MAX_Y_A 1.2f
//#define SLOW_MAX_T_A 10.0f

extern const float MAX_ACC[3];

// gyro running at 2000/second and in integers such that 32767 is 2000
// 61.0 millidegrees/second / LSB
#define DEGREES_PER_GYRO (61.0f / 1000.0f)
#define MS_PER_DEGREE (2.0f * (float)P_PI * ROBOT_RADIUS / 360.0f)
#define MS_PER_GYRO (MS_PER_DEGREE * DEGREES_PER_GYRO)

// Accelerometer is running at +/- 2G's, 32767 is 2G's
// ~61.0 uG per accelerometer LSB
#define GRAVITY 9.807f
#define ACCEL_RANGE 2.0f
#define NUM_DIVISIONS 32767
#define G_PER_ACCEL (ACCEL_RANGE / NUM_DIVISIONS)
#define M_S_2_PER_ACCEL (GRAVITY * G_PER_ACCEL)

extern const float ROBOT_MASS[3];
extern const float MAX_VEL[3];


// transformation matricies to convert speeds in the
// two different domains commonly used by the robot
// speed4 which is the listing of wheel speeds
// and speed3 which is a speed in x,y,rotation in
// robot relative coordinates
void speed4_to_speed3(const float speed4[4], float speed3[3]);
void speed3_to_speed4(const float speed3[3], float speed4[4]);

// transformation matricies to convert forces in the
// two different domains commonly used by the robot
// force4 which is the listing of wheel forces
// and force3 which is a force in x,y,rotation in
// robot relative coordinates
void force4_to_force3(const float force4[4], float force3[3]);
void force3_to_force4(float force3[3], float force4[4]);

float min_angle_delta(float, float);

float norm2(float a1, float a2);

// rotate a velocity vector through angle
void rotate(float speed3[2], float angle);

// Vector addition
void vectorSub(float* a, const float* b, int len);
// Vector addition
void vectorAdd(float* a, const float* b, int len);
// Vector copy
void vectorCopy(float* a, const float* b, int len);

// polar cartesian transforms
void Cart2Pol(float vec[2]);
void Pol2Cart(float vec[2]);
void CartVel2Pol(float const loc[2], float vel[2]);
void PolVel2Cart(float const loc[2], float vel[2]);
void PolAcc2Cart(float const loc[2], float const vel[2], float const Pacc[2],
                 float Cacc[2]);

// C++ does not allow variable length arguments, but we would still like to
// enforce them when possible, so we compile this differently depending
// on what language this header is being used in
#ifndef __cplusplus
void matrix_mult(float* lhs, int lhs_len, const float* rhs, int rhs_len,
                 const float matrix[lhs_len][rhs_len]);
void matrix_mult_t(float* lhs, int lhs_len, const float* rhs, int rhs_len,
                   const float matrix[lhs_len][rhs_len]);

void mm_mult(int lm_rows, int rm_rows, int rm_cols, const float lmatrix[lm_rows][rm_rows],
             const float rmatrix[rm_rows][rm_cols], float matrix_out[lm_rows][rm_cols]);

void mm_mult_t(int lm_rows, int rm_rows, int rm_cols,
               const float lmatrix[lm_rows][rm_rows],
               const float rmatrix[rm_rows][rm_cols], float matrix_out[lm_rows][rm_cols]);

void mm_copy(int nrows, int ncols, float A[nrows][ncols], float B[nrows][ncols]);

void mm_add(int nrows, int ncols, float a[nrows][ncols], const float b[nrows][ncols]);

void mm_sub(int nrows, int ncols, const float a[nrows][ncols],
            const float b[nrows][ncols], float c[nrows][ncols]);

void mm_inv(int n, float a[n][n]);
#else
void matrix_mult(float *lhs, int lhs_len, const float *rhs, int rhs_len,
                 const float **matrix);
void matrix_mult_t(float *lhs, int lhs_len, const float *rhs, int rhs_len,
                   const float **matrix);

void mm_mult(int lm_rows, int rm_rows, int rm_cols, const float **lmatrix,
             const float **rmatrix, float **matrix_out);

void mm_mult_t(int lm_rows, int rm_rows, int rm_cols, const float **lmatrix,
               const float **rmatrix, float **matrix_out);

void mm_copy(int nrows, int ncols, float **A, float **B);

void mm_add(int nrows, int ncols, float **a, const float **b);

void mm_sub(int nrows, int ncols, const float **a, const float **b, float **c);

void mm_inv(int n, float **a);
#endif

void decompose_radial(const float speed, float* vf, const float* init_pos,
                      const float* final_pos);

float dot_product(const float vec1[], const float vec2[], const int size);

float dot2D(float vec1[2], float vec2[2]);

float dot3D(float vec1[3], float vec2[3]);