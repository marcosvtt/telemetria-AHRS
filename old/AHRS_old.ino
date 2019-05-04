#include "MPU6000.h"
#include "HMC5883.h"
#include "MadgwickAHRS.h"


#ifndef MS5611_CHIP_SELECT_PIN
  #define MS5611_CHIP_SELECT_PIN 40
#endif

#define micros_per_reading 40000

uint32_t timer = 0;

Madgwick filter;

/**********************************************************************************/
float convertRawAcceleration(int aRaw) {
  // since we are using 4G range
  // -4g maps to a raw value of -32768
  // +4g maps to a raw value of 32767
  
  float a = (aRaw * 4.0) / 32768.0;
  return a;
}
/**********************************************************************************/
float convertRawGyro(int gRaw) {
  // since we are using 500 degrees/seconds range
  // -500 maps to a raw value of -32768
  // +500 maps to a raw value of 32767
  
  float g = (gRaw * 500.0) / 32768.0;
  return g;
}
/**********************************************************************************/
void setup(){

  Serial.begin(115200);
  filter.begin(25);

//********************************************
  pinMode(MS5611_CHIP_SELECT_PIN, OUTPUT);
  digitalWrite(MS5611_CHIP_SELECT_PIN, 1);
//********************************************

  MPU6000::init();
  HMC5883::init();

  timer = micros();
}



void loop(){
  if ( MPU6000::newdata ) {
    float ax, ay, az;
    float gx, gy, gz;
    float roll, pitch, heading;
    uint32_t time_now;

    // check if it's time to read data and update the filter
    //timer = micros();
    if (micros() - timer >= micros_per_reading) {

      MPU6000::read();
      HMC5883::read();

    
      ay = convertRawAcceleration(MPU6000::accelX);
      ax = convertRawAcceleration(MPU6000::accelY);
      az = -convertRawAcceleration(MPU6000::accelZ);
      gy = convertRawGyro(MPU6000::gyroX);
      gx = convertRawGyro(MPU6000::gyroY);
      gz = -convertRawGyro(MPU6000::gyroZ);

      // update the filter, which computes orientation
      filter.update(gx, gy, gz, ax, ay, az, HMC5883::mag_x, HMC5883::mag_y, HMC5883::mag_z);

      // print the heading, pitch and roll
     
      //Serial.print("Orientation: ");
      //Serial.print(heading);
      //Serial.print(" ");
      //Serial.print(pitch);
      //Serial.print(" ");
      //Serial.println(roll);
      Serial.print(filter.q0 ,10);
      Serial.print(",");
      Serial.print(filter.q1, 10);
      Serial.print(",");
      Serial.print(filter.q2, 10);
      Serial.print(",");
      Serial.print(filter.q3, 10);
      Serial.print("\n\n");

    
     // increment previous time, so we keep proper pace
      timer += micros_per_reading;
    }
  }
}