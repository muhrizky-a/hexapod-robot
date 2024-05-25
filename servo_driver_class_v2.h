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

    const int GRIPPER_CHANNEL = 15;
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
    int _LEG_STEP_CYCLE_DURATION = 250;  // Adjust duration based on desired walking speed (in miliseconds)
    const int _INTERVAL_BETWEEN_LEG_STEPS = 50;  // Interval between steps (in milliseconds)

    //// Pre-filled leg movement config variables
    int _legStepsPerCycle = _LEG_STEP_CYCLE_DURATION / _INTERVAL_BETWEEN_LEG_STEPS;  // interval ms per step
    long _legStepPreviousMillis = 0; // Store variables to stores time to fire the _intervalBetweenLegSteps

    

    //// [Auto-filled later] Store currentAngles set in tripod legs
    //// The index 0 is coxa angle, the index 1 is femur angle, and the index 2 is tibia angle.
    int _rightFrontCurrentAngles[3];
    int _rightMidCurrentAngles[3];
    int _rightBackCurrentAngles[3];
    int _leftFrontCurrentAngles[3];
    int _leftMidCurrentAngles[3];
    int _leftBackCurrentAngles[3];

    //// [Auto-filled later] Store absolute value targetAngles_X[][] (in-function) - currentAngles_X[0] divided by _legStepsPerCycle
    //// The index 0 is coxa angle, the index 1 is femur angle, and the index 2 is tibia angle.
    int _rightFrontAngleIncrements[3];
    int _rightMidAngleIncrements[3];
    int _rightBackAngleIncrements[3];
    int _leftFrontAngleIncrements[3]; 
    int _leftMidAngleIncrements[3];
    int _leftBackAngleIncrements[3];

    // "Supporting operation" variables
    int _currentAngleSequence = -1;

    //// Leg Command uses the COMMAND
    int _legCommand = 0;
    
    // Functions
    int _angleToPulse(int angle);

    //// Set all current servos' angles
    //// The index 0 is coxa angle, the index 1 is femur angle, and the index 2 is tibia angle.
    void _setAllCurrentLegAngles(
      int rightFrontAngles[3],
      int rightMidAngles[3],
      int rightBackAngles[3],
      int leftFrontAngles[3],
      int leftMidAngles[3],
      int leftBackAngles[3]
    );

    // Servo legs supporting Functions
    void _notifyChangedLegCommand(int newLegCommand);

    // Gait base Functions    
    void _gait(
      int rightFrontTargetAngles[][3],
      int rightMidTargetAngles[][3],
      int rightBackTargetAngles[][3],
      
      int leftFrontTargetAngles[][3],
      int leftMidTargetAngles[][3],
      int leftBackTargetAngles[][3],
      
      int legStepCycleLength
    );

    void _gaitSingle(
      int rightFrontTargetAngles[3],
      int rightMidTargetAngles[3],
      int rightBackTargetAngles[3],
      int leftFrontTargetAngles[3],
      int leftMidTargetAngles[3],
      int leftBackTargetAngles[3]
    );

   public:
    void initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left);
    // Servo legs supporting Functions in public
    void setStepDuration(int newDuration);
    void setLegCommand(int newLegCommand);
    void changeGaitAngleSequence(int angleSequence);


    // Single-use static servo legs Movements
    void afterInit();
    void stand();
    void stand90();
    void sit();
    void gripperLift();
    void gripperDown();
    void gripperOpen();
    void gripperClose();
    void leanToFront();
    void leanToFrontSit();
   
    
    // Dynamic servo legs Movements
    void forwardTripodGait();
    void forwardDongakTripodGait();
    void forwardClimbTripodGait();
    
    void moveLeftTripodGait();
    void moveLeftStableTripodGait();
    void moveLeftClimbTripodGait();
    void moveLeftClimbTripodGaitPertamina();
    void moveLeftClimb90TripodGait();
    void moveRightTripodGait();
    void moveRightStableTripodGait();
    
    void backwardTripodGait();
    void turnLeftTripodGait();
    void turnRightTripodGait();
};

#endif
