#include <Adafruit_PWMServoDriver.h>
#ifndef XSERVODRIVER_H
#define XSERVODRIVER_H

class XServoDriverV2 {
   private:
    // SERVO DRIVERS
    //// Define servo drivers
    Adafruit_PWMServoDriver _rightDriver;
    Adafruit_PWMServoDriver _leftDriver;
    
    //// Define min. and max. pulses supported for the servo drivers
    const int SERVOMIN = 150;  // This is the 'minimum' pulse length count (out of 4096)
    const int SERVOMAX = 600;  // This is the 'maximum' pulse length count (out of 4096)




    // SERVO LEG PINS
    //// Define servo channels (pins in servo driver) for each leg section
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




    // LEG ANGLES
    //// TODO: Modify the servo angle configuration as you need
    const int COXA_LEG_ANGLE_ADDITION = 20;
    const int LEG_ANGLE_ADDITION = 45;
    const int LIFTED_ANGLE = 45;

    //// Define constants for servo angles
    const int STAND_ANGLE = 90;

    const int LIFTED_RIGHT_LEG_ANGLE = STAND_ANGLE - LEG_ANGLE_ADDITION; // 45
    const int LIFTED_LEFT_LEG_ANGLE = STAND_ANGLE + LEG_ANGLE_ADDITION; // 135
    const int LOWERED_RIGHT_LEG_ANGLE = STAND_ANGLE + LEG_ANGLE_ADDITION; // 135
    const int LOWERED_LEFT_LEG_ANGLE = STAND_ANGLE - LEG_ANGLE_ADDITION; // 45

    const int FORWARD_RIGHT_COXA_LEG_ANGLE = STAND_ANGLE - COXA_LEG_ANGLE_ADDITION; // 70
    const int FORWARD_LEFT_COXA_LEG_ANGLE = STAND_ANGLE + COXA_LEG_ANGLE_ADDITION; // 110;
    const int BACKWARD_RIGHT_COXA_LEG_ANGLE = STAND_ANGLE + COXA_LEG_ANGLE_ADDITION; // 110;
    const int BACKWARD_LEFT_COXA_LEG_ANGLE = STAND_ANGLE - COXA_LEG_ANGLE_ADDITION; // 70

    
    // SERVO LEG MOVEMEMTS
    //// TODO: Define leg movement duration
    const int _legStepCycleDuration = 250;  // Adjust duration based on desired walking speed (in miliseconds)
    const int _intervalBetweenLegSteps = 50;  // Interval between steps (in milliseconds)

    //// Pre-filled leg movement config variables
    int _legStepsPerCycle = _legStepCycleDuration / _intervalBetweenLegSteps;  // interval ms per step
    long _legStepPreviousMillis = 0; // Store variables to stores time to fire the _intervalBetweenLegSteps

    

    //// [Auto-filled later] Store currentAngles set in tripod legs
    // The index 0 is coxa angle, the index 1 is femur and tibia angle.
    int _rightFrontCurrentAngles[2];
    int _rightMidCurrentAngles[2];
    int _rightBackCurrentAngles[2];
    int _leftFrontCurrentAngles[2];
    int _leftMidCurrentAngles[2];
    int _leftBackCurrentAngles[2];

    //// [Auto-filled later] Store absolute value targetAngles_X[][] (in-function) - currentAngles_X[0] divided by _legStepsPerCycle
    //// The index 0 is coxa angle, the index 1 is femur and tibia angle.
    int _rightFrontIncrements[2];
    int _rightMidIncrements[2];
    int _rightBackIncrements[2];
    int _leftFrontIncrements[2];
    int _leftMidIncrements[2];
    int _leftBackIncrements[2];

    void _tripodGait(
      int rightFrontBackTargetAngles[][2],
      int rightMidTargetAngles[][2],
      int leftFrontBackTargetAngles[][2],
      int leftMidTargetAngles[][2]
    );
    
    // Functions
    int _angleToPulse(int angle);

//    void _moveServos(Adafruit_PWMServoDriver *pwmPtr, int tripodIndex, int coxaAngle, int femurTibiaAngle);
//    void _forwardRight(int legStep);
//    void _forwardLeft(int legStep);
//    void _backwardLeft(int legStep);
//    void _backwardRight(int legStep);

    //// Set all current servos' angles
    //// The index 0 is coxa angle, the index 1 is femur and tibia angle.
    void _setAllCurrentLegAngles(
      int rightFrontAngles[2],
      int rightMidAngles[2],
      int rightBackAngles[2],
      int leftFrontAngles[2],
      int leftMidAngles[2],
      int leftBackAngles[2]
    );

    // Gait base Functions    
    void _tripodGait(
      int rightFrontTargetAngles[][2],
      int rightMidTargetAngles[][2],
      int rightBackTargetAngles[][2],
      
      int leftFrontTargetAngles[][2],
      int leftMidTargetAngles[][2],
      int leftBackTargetAngles[][2],
      
      int legStepCycleLength
    );

   public:
    void initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left);

    // Static servo legs Movesments
    void afterInit();
    void stand();
    void sit();
    void gripperLift();
    void gripperDown();
    void gripperOpen();
    void gripperClose();
    void leanToFront();
    
    // Operation
    void gripperReady();
    void gripObject();
    
    // Dynamic servo legs Movements
    void forwardTripodGait();
    void forwardClimbTripodGait();
    void backwardTripodGait();
    void turnLeftTripodGait();
    void turnRightTripodGait();
};

#endif
