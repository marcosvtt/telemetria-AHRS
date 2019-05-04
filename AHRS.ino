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

  AHRS::init(25, 0.2f);
  HMC5883::set_offset(128, -93, -2);

}



void loop(){
  AHRS::read();
  
  Serial.print(AHRS::q0 ,4);
  Serial.print(",");
  Serial.print(AHRS::q1, 4);
  Serial.print(",");
  Serial.print(AHRS::q2, 4);
  Serial.print(",");
  Serial.print(AHRS::q3, 4);
  Serial.print(",");

  Serial.print("\n");
  
}
