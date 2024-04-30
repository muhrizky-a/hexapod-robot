/*
  Hexapod Robot

  Hexapod Robot that can walks forward, backward, turn left, and turn right

  It uses PCA9685 as the servo driver. Learn  how to use PCA9685 at:
  https://learn.adafruit.com/16-channel-pwm-servo-driver/overview

  Created 19 April 2024
  by Rizki A. Manuel
  
  Modified 28 April 2024
  by Rizki A. Manuel

  Variable naming convention:
  
  1. Creating a class
    a. Use prefix "X" e.g. XClass
  2. Variables Inside Classes
    a.  Public variables and functions are written as is without any prefix.
        Examples: var, var()
    b.  Private variables and functions are written with a single underscore (_) prefix.
        Examples: _var, func()
    c.  Function parameters are written as is without any prefix.
        Examples: func(int params), func(int params)
    d.  In-function variables are written with a double underscore (__) prefix.
        Examples: __var
    e.  Constants are private, CAPITALIZED, and does not need an underscore (_) prefixes.
        Examples: SERVOMIN
*/
 
#include <Wire.h>

//#include "servo_driver_class.h"
#include "servo_driver_class_v2.h"
Adafruit_PWMServoDriver xRightDriver = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver xLeftDriver = Adafruit_PWMServoDriver(0x40);

//XServoDriver servoDriver;
XServoDriverV2 servoDriver;
int xStartTime;

void setup() {
    Serial.begin(9600);
    Serial.println("16 channel PWM test!");

    // Initialize the I2C communication
    Wire.begin();
    servoDriver.initDriver(xRightDriver, xLeftDriver);

    servoDriver.gripperLift();
    servoDriver.stand();
    delay(2000);
//    servoDriver.gripperDown();
//    servoDriver.gripperOpen();
//    delay(1000);
//    servoDriver.gripperClose();
//    delay(1000);
//    servoDriver.afterInit();
//    delay(2000);
  servoDriver.gripperLift();
  xStartTime = millis();
}

void loop() {
    //  stand();
    //  delay(3000);
    //  sit();
    //  delay(3000);
    //
    //  gripperLift();
    //  delay(2000);
    //  gripperDown();
    //  delay(2000);
    Serial.print("Milidetik berjalan sejak awal loop:");
    Serial.println(millis() - xStartTime);
    Serial.println("=====");
    Serial.println("");
      servoDriver.forwardTripodGait();  
    // Jalan 10 detik
//    if(millis() - xStartTime < 5000){
//      servoDriver.forwardTripodGait();  
//    }

//    if(millis() - xStartTime > 5000 && millis() - xStartTime < 10000){
//      servoDriver.backwardTripodGait();  
//    }
//    if(millis() - xStartTime > 10000 && millis() - xStartTime < 15000){
//      servoDriver.turnLeftTripodGait();  
//    }
//    if(millis() - xStartTime > 15000 && millis() - xStartTime < 20000){
//      servoDriver.turnRightTripodGait();  
//    }
//    else {
//      servoDriver.stand();
//    }
    
    //  servoDriver.turnLeftTripodGait();
    //  servoDriver.turnRightTripodGait();
}
