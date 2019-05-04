#ifndef AHRS_H
#define AHRS_H

#include "MPU6000.h"
#include "HMC5883.h"
#include "MadgwickAHRS.h"
#include <Arduino.h>

namespace AHRS{
	extern float q0;
	extern float q1;
	extern float q2;
	extern float q3;
	extern float ax;
	extern float ay;
	extern float az;
	extern float gx;
	extern float gy;
	extern float gz;
	extern int16_t mx;
	extern int16_t my;
	extern int16_t mz; 

	void init(float _sampleRate);
	void read();
	float convertRawAcceleration(int aRaw);
	float convertRawGyro(int gRaw);

}

#endif