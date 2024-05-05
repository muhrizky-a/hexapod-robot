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

//#include "servo_movement.h"
#include "servo_driver_class_v2.h"

Adafruit_PWMServoDriver xRightDriver = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver xLeftDriver = Adafruit_PWMServoDriver(0x40);

//XServoDriver servoDriver;
//XServoMovement servoMovement();
XServoDriverV2 servoDriver;

// start time before entering loop() sequence, in miliseconds
unsigned long xStartTime;


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
  // Counts the times since the beginning of the loop, in miliseconds
  unsigned long timesElapsed = millis() - xStartTime;
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
    
    Serial.println(timesElapsed);
    Serial.println("=====");
    Serial.println("");

//    servoDriver.forwardTripodGait();  
    servoDriver.forwardClimbTripodGait();  
//    servoDriver.backwardTripodGait();  
//    servoDriver.turnLeftTripodGait(); 
//    servoDriver.turnRightTripodGait();   

    // Jalan test
//    if(timesElapsed < 5000){
//      servoDriver.forwardTripodGait();  
//    }
//    if(timesElapsed > 5000 && timesElapsed < 10000){
//      servoDriver.backwardTripodGait();  
//    }
//    if(timesElapsed > 10000 && timesElapsed < 15000){
//      servoDriver.turnLeftTripodGait();  
//    }
//    if(timesElapsed > 15000 && timesElapsed < 20000){
//      servoDriver.turnRightTripodGait();  
//    }
//    if(timesElapsed > 20000){
//      servoDriver.stand();  
//    }

    // Jalan di Arena
//    if(timesElapsed < 10000){
//      servoDriver.forwardTripodGait();  
//    }
//    if(timesElapsed > 10000 && timesElapsed < 15000){
//      servoDriver.turnLeftTripodGait();  
//    }
//    if(timesElapsed > 15000 && timesElapsed < 20000){
//      servoDriver.forwardTripodGait();  
//    }
//    if(timesElapsed > 15000 && timesElapsed < 16000){
//      servoDriver.gripperReady();
//    }
//    if(timesElapsed > 16000 && timesElapsed < 16500){
//      servoDriver.leanToFront();
//    }
//    if(timesElapsed > 16500 && timesElapsed < 17000){
//      servoDriver.gripperClose();
//    }
//    if(timesElapsed > 17000 && timesElapsed < 17500){
//      servoDriver.stand();
//      servoDriver.gripperLift();
//    }
//    if(timesElapsed > 17500 && timesElapsed < 22500){
//      servoDriver.turnRightTripodGait();
//    }
//    if(timesElapsed > 22500){
//      servoDriver.forwardTripodGait();
//    }
}
