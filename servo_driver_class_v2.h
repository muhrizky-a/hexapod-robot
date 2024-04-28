#include <Adafruit_PWMServoDriver.h>
#ifndef XSERVODRIVER_H
#define XSERVODRIVER_H

class XServoDriverV2 {
   private:
    Adafruit_PWMServoDriver _rightDriver;
    Adafruit_PWMServoDriver _leftDriver;

    // Define servo channels (pins in servo driver)
    const int RIGHT_BACK_COXA = 0;
    const int RIGHT_BACK_FEMUR = 1;
    const int RIGHT_BACK_TIBIA = 2;
    const int RIGHT_MID_COXA = 4;
    const int RIGHT_MID_FEMUR = 5;
    const int RIGHT_MID_TIBIA = 6;
    const int RIGHT_FRONT_COXA = 8;
    const int RIGHT_FRONT_FEMUR = 9;
    const int RIGHT_FRONT_TIBIA = 10;

    const int LEFT_FRONT_COXA = 0;
    const int LEFT_FRONT_FEMUR = 1;
    const int LEFT_FRONT_TIBIA = 2;
    const int LEFT_MID_COXA = 4;
    const int LEFT_MID_FEMUR = 5;
    const int LEFT_MID_TIBIA = 6;
    const int LEFT_BACK_COXA = 8;
    const int LEFT_BACK_FEMUR = 9;
    const int LEFT_BACK_TIBIA = 10;

    const int GRIPPER_CHANNEL = 12;
    const int GRIPPER_ARM_CHANNEL = 13;

    const int LEG_SERVO_PINS[6][3] = {
        {RIGHT_BACK_COXA,
         RIGHT_BACK_FEMUR,
         RIGHT_BACK_TIBIA},  // Back right leg (coxa, femur, tibia)
        {RIGHT_MID_COXA,
         RIGHT_MID_FEMUR,
         RIGHT_MID_TIBIA},  // Middle right leg (coxa, femur, tibia)
        {RIGHT_FRONT_COXA,
         RIGHT_FRONT_FEMUR,
         RIGHT_FRONT_TIBIA},  // Front right leg (coxa, femur, tibia)
        {LEFT_BACK_COXA,
         LEFT_BACK_FEMUR,
         LEFT_BACK_TIBIA},  // Back left leg (coxa, femur, tibia)
        {LEFT_MID_COXA,
         LEFT_MID_FEMUR,
         LEFT_MID_TIBIA},  // Middle left leg (coxa, femur, tibia)
        {LEFT_FRONT_COXA,
         LEFT_FRONT_FEMUR,
         LEFT_FRONT_TIBIA},  // Front left leg (coxa, femur, tibia)
    };

    // TODO: Modify the servo angle configuration as you need
    const int COXA_LEG_ANGLE_ADDITION = 20;
    const int LEG_ANGLE_ADDITION = 45;
    const int LIFTED_ANGLE = 45;

    // Define constants for servo angles
    const int STAND_ANGLE = 90;

    const int LIFTED_RIGHT_LEG_ANGLE = STAND_ANGLE - LEG_ANGLE_ADDITION; // 45
    const int LIFTED_LEFT_LEG_ANGLE = STAND_ANGLE + LEG_ANGLE_ADDITION; // 135
    const int LOWERED_RIGHT_LEG_ANGLE = STAND_ANGLE + LEG_ANGLE_ADDITION; // 135
    const int LOWERED_LEFT_LEG_ANGLE = STAND_ANGLE - LEG_ANGLE_ADDITION; // 45

    const int FORWARD_RIGHT_LEG_ANGLE = STAND_ANGLE - LEG_ANGLE_ADDITION; // 45
    const int FORWARD_LEFT_LEG_ANGLE = STAND_ANGLE + LEG_ANGLE_ADDITION; // 135
    const int BACKWARD_RIGHT_LEG_ANGLE = STAND_ANGLE + LEG_ANGLE_ADDITION; // 135
    const int BACKWARD_LEFT_LEG_ANGLE = STAND_ANGLE - LEG_ANGLE_ADDITION; // 45

    const int FORWARD_RIGHT_COXA_LEG_ANGLE = STAND_ANGLE - COXA_LEG_ANGLE_ADDITION; // 70
    const int FORWARD_LEFT_COXA_LEG_ANGLE = STAND_ANGLE + COXA_LEG_ANGLE_ADDITION; // 110;
    const int BACKWARD_RIGHT_COXA_LEG_ANGLE = STAND_ANGLE + COXA_LEG_ANGLE_ADDITION; // 110;
    const int BACKWARD_LEFT_COXA_LEG_ANGLE = STAND_ANGLE - COXA_LEG_ANGLE_ADDITION; // 70


    const int SERVOMIN = 150;  // This is the 'minimum' pulse length count (out of 4096)
    const int SERVOMAX = 600;  // This is the 'maximum' pulse length count (out of 4096)

//    int _currentAngleCoxa;
//    int _currentAngleFemurTibia;

    int currentAngles_1[2];
    int increments_1[2];
    int currentAngles_2[2];
    int increments_2[2];

    // Define variables for timing
    unsigned long _startTime;
    
    // Define variables for state
    int state = 0;  // State variable to track tripod movement
    int legStep = 0;

    // int _legStep = 0;
    int _angleToPulse(int angle);

    void _moveServos(Adafruit_PWMServoDriver *pwmPtr, int tripodIndex, int coxaAngle, int femurTibiaAngle);
    void _forwardRight(int legStep);
    void _forwardLeft(int legStep);
    void _backwardLeft(int legStep);
    void _backwardRight(int legStep);

    void _tripodGait(void (XServoDriverV2::*callGaitFunctionRight)(int), void (XServoDriverV2::*callGaitFunctionLeft)(int));

   public:
    //  Adafruit_PWMServoDriver getRightDriver();
    //  Adafruit_PWMServoDriver getLeftDriver();
    void initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left);

    void afterInit();
    void stand();
    void sit();
    void gripperLift();
    void backwardRight(int legStep);
    void gripperDown();
    void gripperOpen();
    void gripperClose();

    void forwardTripodGait();
    void backwardTripodGait();
    void turnLeftTripodGait();
    void turnRightTripodGait();
};

#endif
