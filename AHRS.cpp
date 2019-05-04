#include "AHRS.h"

namespace AHRS{
	float q0;
	float q1;
	float q2;
	float q3;
	float ax;
	float ay;
	float az;
	float gx;
	float gy;
	float gz;
	int16_t mx;
	int16_t my;
	int16_t mz;
	Madgwick filter;
	
	void init(float _sampleRate){
		
		filter.begin(_sampleRate);

		MPU6000::init();
		HMC5883::init();
	}


	void read(){

		MPU6000::read();
		HMC5883::read();

		ay = convertRawAcceleration(MPU6000::accelX);
		ax = convertRawAcceleration(MPU6000::accelY);
		az = -convertRawAcceleration(MPU6000::accelZ);
		gy = convertRawGyro(MPU6000::gyroX);
		gx = convertRawGyro(MPU6000::gyroY);
		gz = -convertRawGyro(MPU6000::gyroZ);
		mx = HMC5883::mag_x;
		my = HMC5883::mag_y;
		mz = HMC5883::mag_z;
      // update the filter, which computes orientation
		filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

		q0 = filter.q0;
		q1 = filter.q1;
		q2 = filter.q2;
		q3 = filter.q3;
	}

	float convertRawGyro(int gRaw) {
  // since we are using 500 degrees/seconds range
  // -500 maps to a raw value of -32768
  // +500 maps to a raw value of 32767

		float g = (gRaw * 500.0) / 32768.0;
		return g;
	}

	float convertRawAcceleration(int aRaw) {
  // since we are using 4G range
  // -4g maps to a raw value of -32768
  // +4g maps to a raw value of 32767

		float a = (aRaw * 4.0) / 32768.0;
		return a;
	}


}