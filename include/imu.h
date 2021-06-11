// IMU Class Header File

#ifndef IMU_H
#define IMU_H

#include <cmath>

class IMU
{
public:
    double Q[4]; // quarternion array
    double dT;   // timestep

    IMU(double *q, double tstep); // constructor

    double *propagate(double *q, double *gyro);
    void normalize(double *ptr);
    void update(double (&q)[4], double (&gyro)[3]);
};

#endif