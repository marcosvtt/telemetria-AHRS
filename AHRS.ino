#include "AHRS.h"


#ifndef MS5611_CHIP_SELECT_PIN
  #define MS5611_CHIP_SELECT_PIN 40
#endif

//#define micros_per_reading 40000



void setup(){

  Serial.begin(115200);
  

//********************************************
  pinMode(MS5611_CHIP_SELECT_PIN, OUTPUT);
  digitalWrite(MS5611_CHIP_SELECT_PIN, 1);
//********************************************

  AHRS::init(25);
  HMC5883::set_offset(128, -93, -2);

}



void loop(){
  AHRS::read();
  Serial.print(AHRS::q0 ,10);
  Serial.print(",");
  Serial.print(AHRS::q1, 10);
  Serial.print(",");
  Serial.print(AHRS::q2, 10);
  Serial.print(",");
  Serial.print(AHRS::q3, 10);
  Serial.print("\n\n");
  /*
  Serial.print(AHRS::mx);
  Serial.print(",");
  Serial.print(AHRS::my);
  Serial.print(",");
  Serial.print(AHRS::mz);
  Serial.print("\n\n");
  */

}
/*
x_offset: 101
y_offset: -70
z_offset: 262

x_offset: 128
y_offset: -93
z_offset: -2

x_offset: 141
y_offset: -98
z_offset: -1


*/