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
#include <Arduino.h>
#include <Wire.h>

//#include "x_robot_arena.h"
//XRobotArena robotArena;

//#include "x_servo_drivers.h"
//#include "x_servo_movement.h"

#include "controller_receiver.h"

//#include "servo_driver_class_v2.h"
//XServoDriverV2 servoDriver;

Adafruit_PWMServoDriver xRightDriver = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver xLeftDriver = Adafruit_PWMServoDriver(0x40);

// Unused yet
//XServoMovement servoMovement(XServoDrivers(xRightDriver,xLeftDriver));

//XServoDriverV2 servoDriver;
//XControllerReceiver controllerReceiver;

// start time before entering loop() sequence, in miliseconds
unsigned long xStartTime;

void setup() {
    Serial.begin(9600);
    Serial.println("16 channel PWM test!");

    // Initialize the I2C communication
    Wire.begin();

    initWifiReceiver();
    initESPNOW();
    servoDriver.initDriver(xRightDriver, xLeftDriver);
    delay(1000);
    servoDriver.gripperLift();
    servoDriver.gripperClose();
    servoDriver.stand();
    delay(2000);
    
    servoDriver.setLegCommand(1);
    xStartTime = millis();
}

void loop() {
  // Counts the times since the beginning of the loop, in miliseconds
  unsigned long timesElapsed = millis() - xStartTime;
//    Serial.print("Milidetik berjalan sejak awal loop:");
//    Serial.println(timesElapsed);
//    Serial.println("=====");
//    Serial.println("");
    
//    receiveSerialData([](int v) {
//        // Your code here
//        //// MOVEMENTS
//        if(v == FORWARD_COMMAND){
//            servoDriver.setStepDuration(250);
//            servoDriver.forwardTripodGait();
//          }
//          if(v == BACKWARD_COMMAND){
//            servoDriver.setStepDuration(250);
//            servoDriver.backwardTripodGait();
//          }
//          if(v == TURN_LEFT_COMMAND){
//            servoDriver.setStepDuration(250);
//            servoDriver.turnLeftTripodGait(); 
//          }
//          if (v == TURN_RIGHT_COMMAND){
//            servoDriver.setStepDuration(250);
//            servoDriver.turnRightTripodGait();
//          }
//
//          if (v == LEAN_FRONT_COMMAND){
//            servoDriver.setStepDuration(250);
//            servoDriver.leanToFront();
//          }
//          if (v == MOVE_LEFT_COMMAND){
//            servoDriver.setStepDuration(250);
//            servoDriver.moveLeftTripodGait();
//          }
//          if (v == MOVE_RIGHT_COMMAND){
//            servoDriver.setStepDuration(250);
//            servoDriver.moveRightTripodGait();
//          }
//          if (v == LEAN_BACK_COMMAND){
//            servoDriver.setStepDuration(500);
//            servoDriver.moveLeftClimbTripodGait();
//          }
//
//          if (v == GRIPPER_LIFT_COMMAND){
//            servoDriver.gripperClose();
//            lastTimeToGrip++;
//            Serial.print("lastTimeToGrip: ");
//            Serial.println(lastTimeToGrip);
//            
//            if(lastTimeToGrip > 5){
//              servoDriver.gripperLift();
//              lastTimeToGrip = 0;
//            }
//          }
//
//          if (v == GRIPPER_DOWN_COMMAND){
//            lastTimeToGrip = 0;
//            servoDriver.gripperDown();
//            servoDriver.gripperOpen();
//          }
//      }
//    );

//    servoDriver.leanToFront();
//    servoDriver.forwardTripodGait();  
//    servoDriver.forwardClimbTripodGait();  
//    servoDriver.moveLeftTripodGait();
//    servoDriver.moveLeftClimbTripodGait();
//    servoDriver.moveLeftClimb1TripodGait();
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
