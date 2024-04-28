 #include <Wire.h>

//#include "servo_driver_class.h"
#include "servo_driver_class_v2.h"
Adafruit_PWMServoDriver xRightDriver = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver xLeftDriver = Adafruit_PWMServoDriver(0x42);

//XServoDriver servoDriver;
XServoDriverV2 servoDriver;

void setup() {
    Serial.begin(9600);
    Serial.println("16 channel PWM test!");

    // Initialize the I2C communication
    Wire.begin();
    servoDriver.initDriver(xRightDriver, xLeftDriver);

//    servoDriver.gripperLift();
    servoDriver.stand();
    delay(2000);
//    servoDriver.gripperOpen();
//    delay(2000);
//    servoDriver.gripperClose();
//    delay(2000);
//    servoDriver.afterInit();
//    delay(2000);
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
    servoDriver.forwardTripodGait();
    //  servoDriver.turnLeftTripodGait();
    //  servoDriver.turnRightTripodGait();
}
