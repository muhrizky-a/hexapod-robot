//#include "servo_driver_class_v2.h"
//
//// BEGIN PUBLIC FUNCTIONS
//// ----------
//void XServoDriverV2::initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left) {
//    Serial.println("init servo drivers");
//    _rightDriver = right;
//    _leftDriver = left;
//
//    Serial.println("begin init right");
//    _rightDriver.begin();
//    Serial.println("done begin init right");
//    _rightDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
//    Serial.println("begin init left");
//    _leftDriver.begin();
//    Serial.println("done begin init left");
//    _leftDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
//}
//
//void XServoDriverV2::afterInit() {
//    Serial.println("after init v2");
//    for (int i = 0; i <= 8; i += 4) {
//        _rightDriver.setPWM(i, 0, _angleToPulse(70));
//    }
//}
//
//void XServoDriverV2::stand() {
//    Serial.println("stand");
//    for (int i = 0; i < 12; i++) {
//        _rightDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
//        _leftDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
//    }
//
//    int angles[3] = {STAND_ANGLE, STAND_ANGLE, STAND_ANGLE};
//    _setAllCurrentLegAngles(
//      angles,
//      angles,
//      angles,
//      angles,
//      angles,
//      angles
//    );
//}
//
//void XServoDriverV2::sit() {
//    Serial.println("sit");
//
//    // Loop for servo on channel starts in 0, 4, 8
//    for (int i = 0; i <= 8; i += 4) {
//        // This will control servo on channel 0,1,2, then 4,5,6, then 8,9, 10
//        _rightDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
//        _rightDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
//        _rightDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
//
//        _leftDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
//        _leftDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
//        _leftDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
//    }
//}
//
//void XServoDriverV2::gripperLift() {
//    Serial.println("gripper arm lifted");
//    _rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, _angleToPulse(90));
//}
//
//void XServoDriverV2::gripperDown() {
//    Serial.println("gripper arm down");
//    _rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, _angleToPulse(180));
//}
//
//void XServoDriverV2::gripperOpen() {
//    _rightDriver.setPWM(GRIPPER_CHANNEL, 0, _angleToPulse(135));
//}
//
//void XServoDriverV2::gripperClose() {
//    _rightDriver.setPWM(GRIPPER_CHANNEL, 0, _angleToPulse(0));
//}
//
//void XServoDriverV2::leanToFront() {
//  // Loop for servo on channel starts in 0, 4, 8
//  for (int i = 0; i <= 8; i += 4) {
//    // This will control servo on channel 0,1,2, then 4,5,6, then 8,9,10
//    _rightDriver.setPWM(i, 0, _angleToPulse(BACKWARD_RIGHT_COXA_LEG_ANGLE));
//    _rightDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
//    _rightDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));
//    
//    _leftDriver.setPWM(i, 0, _angleToPulse(BACKWARD_LEFT_COXA_LEG_ANGLE));
//    _leftDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
//    _leftDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));
//  }
//}
//
//void XServoDriverV2::forwardTripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontBackTargetAngles[4][3] = {
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
//  };
//
//  int __rightMidTargetAngles[4][3] = {
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//  };
//  
//  int __leftFrontBackTargetAngles[4][3] = {
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//
//  int __leftMidTargetAngles[4][3] = {
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//    
//
//  // Gerak
//  _gait(
//    __rightFrontBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontBackTargetAngles,
//    __leftFrontBackTargetAngles,
//    __leftMidTargetAngles,
//    __leftFrontBackTargetAngles,
//    __legStepCycleLength
//  );
//}
//
//void XServoDriverV2::forwardClimbTripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontTargetAngles[4][3] = {
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {70,STAND_ANGLE, STAND_ANGLE},
//    {90,STAND_ANGLE, STAND_ANGLE},
//    {110,STAND_ANGLE, STAND_ANGLE}
//  };
//
//  int __rightMidTargetAngles[4][3] = {
//    {90,STAND_ANGLE, STAND_ANGLE},
//    {110,STAND_ANGLE, STAND_ANGLE},
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {70,STAND_ANGLE, STAND_ANGLE},
//  };
//
//  int __rightBackTargetAngles[4][3] = {
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
//  };
//  
//  int __leftFrontTargetAngles[4][3] = {
//    {90,STAND_ANGLE, STAND_ANGLE},
//    {70,STAND_ANGLE, STAND_ANGLE},
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {110,STAND_ANGLE, STAND_ANGLE}
//  };
//
//  int __leftMidTargetAngles[4][3] = {
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {110,STAND_ANGLE, STAND_ANGLE},
//    {90,STAND_ANGLE, STAND_ANGLE},
//    {70,STAND_ANGLE, STAND_ANGLE}
//  };
//
//  int __leftBackTargetAngles[4][3] = {
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//    
//
//  // Gerak
//  _gait(
//    __rightBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontTargetAngles,
//    __leftFrontTargetAngles,
//    __leftMidTargetAngles,
//    __leftBackTargetAngles,
//    __legStepCycleLength
//  );
//}
//
//void XServoDriverV2::backwardTripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontBackTargetAngles[4][3] = {
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
//  };
//
//  int __rightMidTargetAngles[4][3] = {
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//  };
//  
//  int __leftFrontBackTargetAngles[4][3] = {
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//
//  int __leftMidTargetAngles[4][3] = {
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//    
//
//  // Gerak
//  _gait(
//    __rightFrontBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontBackTargetAngles,
//    __leftFrontBackTargetAngles,
//    __leftMidTargetAngles,
//    __leftFrontBackTargetAngles,
//    __legStepCycleLength
//  );
//}
//
//void XServoDriverV2::moveLeftTripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontBackTargetAngles[4][3] = {
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, 180}, // swipe end
//  };
//  
//  int __rightMidTargetAngles[4][3] = {
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, 180}, // swipe end
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
//  };
//
//  int __leftFrontBackTargetAngles[4][3] = {
//    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // swipe end
//    {STAND_ANGLE,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, 0}, // step
//  }; 
//
//  int __leftMidTargetAngles[4][3] = {
//    {STAND_ANGLE,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, 0}, // step
//    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // swipe end
//  };
//
//  // Gerak
//  _gait(
//    __rightFrontBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontBackTargetAngles,
//    __leftFrontBackTargetAngles,
//    __leftMidTargetAngles,
//    __leftFrontBackTargetAngles,
//    __legStepCycleLength
//  );
//}
//
//void XServoDriverV2::moveLeftClimbTripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontBackTargetAngles[4][3] = {
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
//  };
//  
//  int __rightMidTargetAngles[4][3] = {
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
//  };
//
//  int __leftFrontBackTargetAngles[4][3] = {
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
//    {STAND_ANGLE,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // swipe end
//    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
//    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
//  }; 
//
//  int __leftMidTargetAngles[4][3] = {
//    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
//    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
//    {STAND_ANGLE,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // swipe end
//  };
//
//  // Gerak
//  _gait(
//    __rightFrontBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontBackTargetAngles,
//    __leftFrontBackTargetAngles,
//    __leftMidTargetAngles,
//    __leftFrontBackTargetAngles,
//    __legStepCycleLength
//  );
//}
//
//void XServoDriverV2::moveLeftClimb1TripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontBackTargetAngles[4][3] = {
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
//  };
//  
//  int __rightMidTargetAngles[4][3] = {
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
//    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
//  };
//
//  int __leftFrontBackTargetAngles[4][3] = {
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swipe end
//    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
//    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
//  }; 
//
//  int __leftMidTargetAngles[4][3] = {
//    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
//    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
//    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swipe end
//  };
//
//  // Gerak
//  _gait(
//    __rightFrontBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontBackTargetAngles,
//    __leftFrontBackTargetAngles,
//    __leftMidTargetAngles,
//    __leftFrontBackTargetAngles,
//    __legStepCycleLength
//  );
//}
//
//void XServoDriverV2::turnLeftTripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontBackTargetAngles[4][3] = {
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
//  };
//
//  int __rightMidTargetAngles[4][3] = {
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//  };
//  
//  int __leftFrontBackTargetAngles[4][3] = {
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//
//  int __leftMidTargetAngles[4][3] = {
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//    
//
//  // Gerak
//  _gait(
//    __rightFrontBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontBackTargetAngles,
//    __leftFrontBackTargetAngles,
//    __leftMidTargetAngles,
//    __leftFrontBackTargetAngles,
//    __legStepCycleLength
//  );
//}
//
//void XServoDriverV2::turnRightTripodGait() {
//  int __legStepCycleLength = 4;
//  
//  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
//  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
//  int __rightFrontBackTargetAngles[4][3] = {
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
//  };
//
//  int __rightMidTargetAngles[4][3] = {
//    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
//    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
//  };
//  
//  int __leftFrontBackTargetAngles[4][3] = {
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//
//  int __leftMidTargetAngles[4][3] = {
//    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
//    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
//    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
//  };
//    
//
//  // Gerak
//  _gait(
//    __rightFrontBackTargetAngles,
//    __rightMidTargetAngles,
//    __rightFrontBackTargetAngles,
//    __leftFrontBackTargetAngles,
//    __leftMidTargetAngles,
//    __leftFrontBackTargetAngles,
//    __legStepCycleLength
//  );
//}
