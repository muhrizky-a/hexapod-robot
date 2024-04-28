#include "servo_driver_class.h"

// BEGIN PUBLIC FUNCTIONS
// ----------
void XServoDriver::initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left) {
    Serial.println("init servo drivers");
    rightDriver = right;
    leftDriver = left;

    rightDriver.begin();
    rightDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
    leftDriver.begin();
    leftDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
}
void XServoDriver::afterInit() {
    Serial.println("after init");
    
}

void XServoDriver::stand() {
    Serial.println("stand");
    for (int i = 0; i < 12; i++) {
        rightDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
        leftDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
    }
}

void XServoDriver::sit() {
    Serial.println("sit");
    for (int i = 0; i <= 8; i += 4) {
        rightDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
        leftDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
    }

    // Loop for servo on channel starts in 0, 4, 8
    for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 1,2, then 5,6, then 9, 10
        rightDriver.setPWM(i + 1, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        rightDriver.setPWM(i + 2, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        leftDriver.setPWM(i + 1, 0, angleToPulse(LIFTED_LEFT_LEG_ANGLE));
        leftDriver.setPWM(i + 2, 0, angleToPulse(LIFTED_LEFT_LEG_ANGLE));
    }
}

void XServoDriver::gripperLift() {
    Serial.println("gripper arm lifted");
    rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(0));
}

void XServoDriver::gripperDown() {
    Serial.println("gripper arm down");
    rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(180));
}

void XServoDriver::gripperOpen() {
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(135));
}

void XServoDriver::gripperClose() {
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(0));
}

void XServoDriver::forwardTripodGait() {
    _tripodGait(&XServoDriver::_forwardRight, &XServoDriver::_forwardLeft);
}

void XServoDriver::backwardTripodGait() {
    _tripodGait(&XServoDriver::_backwardRight, &XServoDriver::_backwardLeft);
}

void XServoDriver::turnLeftTripodGait() {
    _tripodGait(&XServoDriver::_forwardRight, &XServoDriver::_backwardLeft);
}

void XServoDriver::turnRightTripodGait() {
    _tripodGait(&XServoDriver::_backwardRight, &XServoDriver::_forwardLeft);
}
