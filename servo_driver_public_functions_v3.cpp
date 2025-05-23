#include "servo_driver_class_v2.h"

// BEGIN PUBLIC FUNCTIONS
// ----------
void XServoDriverV2::initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left) {
    Serial.println("init servo drivers");
    _rightDriver = right;
    _leftDriver = left;

    Serial.println("begin init right");
    _rightDriver.begin();
    Serial.println("done begin init right");
    _rightDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
    Serial.println("begin init left");
    _leftDriver.begin();
    Serial.println("done begin init left");
    _leftDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
}

void XServoDriverV2::afterInit() {
    Serial.println("after init v2");
    for (int i = 0; i <= 8; i += 4) {
        _rightDriver.setPWM(i, 0, _angleToPulse(70));
    }
}

void XServoDriverV2::stand() {
//    Serial.println("stand");
    for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 0,1,2, then 4,5,6, then 8,9, 10
        _rightDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
        _rightDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));

        _leftDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
        _leftDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));
    }

    _rightDriver.setPWM(0, 0, _angleToPulse(110));
    _rightDriver.setPWM(4, 0, _angleToPulse(STAND_ANGLE));
    _rightDriver.setPWM(8, 0, _angleToPulse(70));
    _leftDriver.setPWM(0, 0, _angleToPulse(110));
    _leftDriver.setPWM(4, 0, _angleToPulse(STAND_ANGLE));
    _leftDriver.setPWM(8, 0, _angleToPulse(70));

    int angles1[3] = {110, STAND_ANGLE, STAND_ANGLE};
    int anglesMid[3] = {STAND_ANGLE, STAND_ANGLE, STAND_ANGLE};
    int angles3[3] = {70, STAND_ANGLE, STAND_ANGLE};
    _setAllCurrentLegAngles(
      angles1,
      anglesMid,
      angles3,
      angles1,
      anglesMid,
      angles3
    );
}

void XServoDriverV2::stand90() {
//    Serial.println("stand");
    for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 0,1,2, then 4,5,6, then 8,9, 10
        _rightDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
        _rightDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
        _rightDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));

        _leftDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
        _leftDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
        _leftDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));
    }

    int angles[3] = {STAND_ANGLE, STAND_ANGLE, STAND_ANGLE};
    _setAllCurrentLegAngles(
      angles,
      angles,
      angles,
      angles,
      angles,
      angles
    );
}

void XServoDriverV2::gripperLift() {
//    Serial.println("gripper arm lifted");
    _rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, _angleToPulse(180));
}

void XServoDriverV2::gripperDown() {
//    Serial.println("gripper arm down");
    _rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, _angleToPulse(80));
}

void XServoDriverV2::gripperOpen() {
    _rightDriver.setPWM(GRIPPER_CHANNEL, 0, _angleToPulse(60)); 
}

void XServoDriverV2::gripperClose() {
    _rightDriver.setPWM(GRIPPER_CHANNEL, 0, _angleToPulse(0));
}

void XServoDriverV2::sit() {
  // Loop for servo on channel starts in 0, 4, 8
  for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 0,1,2, then 4,5,6, then 8,9, 10
        _rightDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        _rightDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));

        _leftDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
        _leftDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
    }

    _rightDriver.setPWM(0, 0, _angleToPulse(110));
    _rightDriver.setPWM(4, 0, _angleToPulse(STAND_ANGLE));
    _rightDriver.setPWM(8, 0, _angleToPulse(70));
    _leftDriver.setPWM(0, 0, _angleToPulse(110));
    _leftDriver.setPWM(4, 0, _angleToPulse(STAND_ANGLE));
    _leftDriver.setPWM(8, 0, _angleToPulse(70));

    int angles1[3] = {110, LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE};
    int angles2[3] = {STAND_ANGLE, LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE};
    int angles3[3] = {70, LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE};
    int angles4[3] = {110, LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE};
    int angles5[3] = {STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE};
    int angles6[3] = {70, LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE};
    _setAllCurrentLegAngles(
      angles1,
      angles2,
      angles3,
      angles4,
      angles5,
      angles6
    );
}

void XServoDriverV2::leanToFront() {
  // Loop for servo on channel starts in 0, 4, 8
  for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 0,1,2, then 4,5,6, then 8,9, 10
        _rightDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
        _rightDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));

        _leftDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
        _leftDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));
    }

    _rightDriver.setPWM(0, 0, _angleToPulse(130));
    _rightDriver.setPWM(4, 0, _angleToPulse(110));
    _rightDriver.setPWM(8, 0, _angleToPulse(STAND_ANGLE));
    _leftDriver.setPWM(0, 0, _angleToPulse(STAND_ANGLE));
    _leftDriver.setPWM(4, 0, _angleToPulse(70));
    _leftDriver.setPWM(8, 0, _angleToPulse(50));

    int angles1[3] = {130, STAND_ANGLE, STAND_ANGLE};
    int angles2[3] = {110, STAND_ANGLE, STAND_ANGLE};
    int angles3[3] = {STAND_ANGLE, STAND_ANGLE, STAND_ANGLE};
    int angles4[3] = {STAND_ANGLE, STAND_ANGLE, STAND_ANGLE};
    int angles5[3] = {70, STAND_ANGLE, STAND_ANGLE};
    int angles6[3] = {50, STAND_ANGLE, STAND_ANGLE};
    _setAllCurrentLegAngles(
      angles1,
      angles2,
      angles3,
      angles4,
      angles5,
      angles6
    );
}

void XServoDriverV2::leanToFrontSit() {
  // Loop for servo on channel starts in 0, 4, 8
  for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 0,1,2, then 4,5,6, then 8,9, 10
        _rightDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        _rightDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));

        _leftDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
        _leftDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
    }

    _rightDriver.setPWM(0, 0, _angleToPulse(130));
    _rightDriver.setPWM(4, 0, _angleToPulse(110));
    _rightDriver.setPWM(8, 0, _angleToPulse(STAND_ANGLE));
    _leftDriver.setPWM(0, 0, _angleToPulse(STAND_ANGLE));
    _leftDriver.setPWM(4, 0, _angleToPulse(70));
    _leftDriver.setPWM(8, 0, _angleToPulse(50));

    int angles1[3] = {130, LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE};
    int angles2[3] = {110, LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE};
    int angles3[3] = {STAND_ANGLE, LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE};
    int angles4[3] = {STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE};
    int angles5[3] = {70, LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE};
    int angles6[3] = {50, LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE};
    _setAllCurrentLegAngles(
      angles1,
      angles2,
      angles3,
      angles4,
      angles5,
      angles6
    );
}

//// Supporting functions: setStepDuration
void XServoDriverV2::setStepDuration(int newDuration){
  _LEG_STEP_CYCLE_DURATION = newDuration;
}

//// Supporting functions: setLegCommand
void XServoDriverV2::setLegCommand(int newLegCommand){
  _notifyChangedLegCommand(newLegCommand);

  _legCommand = newLegCommand;
}

void XServoDriverV2::changeGaitAngleSequence(int maxAngleSequence){
  if(_currentAngleSequence >= maxAngleSequence - 1){
    _currentAngleSequence = 0;  
  } else {
    _currentAngleSequence++;
  }
}

void XServoDriverV2::forwardTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {130,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {50,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };
  
  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {130,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {50,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::forwardDongakTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {90,STAND_ANGLE, STAND_ANGLE},
    {110,STAND_ANGLE, STAND_ANGLE},
    {130,STAND_ANGLE, STAND_ANGLE}
  };

  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {90,115, 110},
    {110,115, 110},
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {70,115, 110},
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {50,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };
  
  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {130,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {90,65, 70},
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,65, 70},
    {70,65, 70}
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,STAND_ANGLE, STAND_ANGLE},
    {50,STAND_ANGLE, STAND_ANGLE},
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {90,STAND_ANGLE, STAND_ANGLE}
  };

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::forwardClimbTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {90,STAND_ANGLE, STAND_ANGLE},
    {110,STAND_ANGLE, STAND_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {70,STAND_ANGLE, STAND_ANGLE},
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {70,STAND_ANGLE, STAND_ANGLE},
    {90,STAND_ANGLE, STAND_ANGLE},
    {110,STAND_ANGLE, STAND_ANGLE}
  };
  
  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {90,STAND_ANGLE, STAND_ANGLE},
    {70,STAND_ANGLE, STAND_ANGLE},
    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {110,STAND_ANGLE, STAND_ANGLE}
  };

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {110,STAND_ANGLE, STAND_ANGLE},
    {90,STAND_ANGLE, STAND_ANGLE},
    {70,STAND_ANGLE, STAND_ANGLE}
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::backwardTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {130,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {50,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };
  
  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {130,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {50,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::moveLeftTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {110,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {110,LOWERED_RIGHT_LEG_ANGLE, 180}, // swipe end
  };
  
  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, 180}, // swipe end
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {70,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {70,LOWERED_RIGHT_LEG_ANGLE, 180}, // swipe end
  };

  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
    {110,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // swipe end
    {110,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {110,LOWERED_LEFT_LEG_ANGLE, 0}, // step
  }; 

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, 0}, // step
    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // swipe end
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
    {70,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // swipe end
    {70,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {70,LOWERED_LEFT_LEG_ANGLE, 0}, // step
  }; 

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::moveLeftStableTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {110,STAND_ANGLE, 65}, // step
    {110,70, STAND_ANGLE}, // swiping
    {110,STAND_ANGLE, 115}, // swipe end
  };
  
  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,70, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, 115}, // swipe end
    {STAND_ANGLE,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, 65}, //;  step
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {70,STAND_ANGLE, 65}, // step
    {70,70, STAND_ANGLE}, // swiping
    {70,STAND_ANGLE, 115}, // swipe end
  };

  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,110, STAND_ANGLE}, // swiping
    {110,STAND_ANGLE, 115}, // swipe end
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {110,STAND_ANGLE, 65}, // step
  }; 

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, 65}, // step
    {STAND_ANGLE, 110, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, 115}, // swipe end
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,110, STAND_ANGLE}, // swiping
    {70,STAND_ANGLE, 115}, // swipe end
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {70,STAND_ANGLE, 65}, // step
  };

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::moveLeftClimbTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    // v1 gait angles
    {110,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {130,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
  };
  
  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    // v1 gait angles
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    // v1 gait angles
    {70,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {50,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
  };

  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    // v1 gait angles
    {110,STAND_ANGLE, STAND_ANGLE}, // swiping
    {130,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // swipe end
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
  }; 

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    // v1 gait angles
    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // swipe end
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    // v1 gait angles
    {70,STAND_ANGLE, STAND_ANGLE}, // swiping
    {50,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // swipe end
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
  }; 

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::moveLeftClimbTripodGaitPertamina() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    // v2 gait angles
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {130,STAND_ANGLE, STAND_ANGLE}, // middle of lifted / stepped
    {130,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // step/swiping
    {110,LOWERED_RIGHT_LEG_ANGLE, 158}, // swipe end
  };
  
  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    // v2 gait angles
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // step/swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, 158}, // swipe end
    {STAND_ANGLE,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // middle of lifted / stepped
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    // v2 gait angles
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {50,STAND_ANGLE, STAND_ANGLE}, // middle of lifted / stepped
    {50,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // step/swiping
    {70,LOWERED_RIGHT_LEG_ANGLE, 158}, // swipe end
  };

  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    // v2 gait angles
    {130,STAND_ANGLE, 68}, // step/swiping
    {130,STAND_ANGLE, STAND_ANGLE}, // swipe end
    {110,LIFTED_LEFT_LEG_ANGLE, STAND_ANGLE}, // lift post swipe
    {110,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // middle of lifted / stepped
  }; 

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    // v2 gait angles
    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, STAND_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // middle of lifted / stepped
    {STAND_ANGLE,STAND_ANGLE, 68}, // step/swiping
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swipe end
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    // v2 gait angles
    {50,STAND_ANGLE, 68}, // step/swiping
    {50,STAND_ANGLE, STAND_ANGLE}, // swipe end
    {70,LIFTED_LEFT_LEG_ANGLE, STAND_ANGLE}, // lift post swipe
    {70,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // middle of lifted / stepped
  }; 

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::moveLeftClimb90TripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
  };
  
  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // step
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swipe end
  };

  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, 125}, // swipe end
    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
  }; 

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, 125}, // swipe end
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, 125}, // swipe end
    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // step
  }; 

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::moveRightTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {110,LOWERED_RIGHT_LEG_ANGLE, 180}, // step
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {110,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // swipe end
  };
  
  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // swipe end
    {STAND_ANGLE,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_RIGHT_LEG_ANGLE, 180}, // step
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,STAND_ANGLE, STAND_ANGLE}, // lift post swipe
    {70,LOWERED_RIGHT_LEG_ANGLE, 180}, // step
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}, // swiping
    {70,LOWERED_RIGHT_LEG_ANGLE, STAND_ANGLE}, // swipe end
  };

  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
    {110,LOWERED_LEFT_LEG_ANGLE, 0}, // swipe end
    {110,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {110,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // step
  }; 

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // step
    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
    {STAND_ANGLE,LOWERED_LEFT_LEG_ANGLE, 0}, // swipe end
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}, // swiping
    {70,LOWERED_LEFT_LEG_ANGLE, 0}, // swipe end
    {70,STAND_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {70,LOWERED_LEFT_LEG_ANGLE, STAND_ANGLE}, // step
  }; 

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::moveRightStableTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {110,STAND_ANGLE, 115}, // step
    {110,70, STAND_ANGLE}, // swiping
    {110,STAND_ANGLE, 65}, // swipe end
  };
  
  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,70, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, 65}, // swipe end
    {STAND_ANGLE,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, 115}, // step
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE}, // lift post swipe
    {70,STAND_ANGLE, 115}, // step
    {70,70, STAND_ANGLE}, // swiping
    {70,STAND_ANGLE, 65}, // swipe end
  };

  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,110, STAND_ANGLE}, // swiping
    {110,STAND_ANGLE, 65}, // swipe end
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {110,STAND_ANGLE, 115}, // step
  }; 

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {STAND_ANGLE,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {STAND_ANGLE,STAND_ANGLE, 115}, // step
    {STAND_ANGLE,110, STAND_ANGLE}, // swiping
    {STAND_ANGLE,STAND_ANGLE, 65}, // swipe end
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,110, STAND_ANGLE}, // swiping
    {70,STAND_ANGLE, 65}, // swipe end
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE}, // lift post swipe
    {70,STAND_ANGLE, 115}, // step
  }; 

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}


void XServoDriverV2::turnLeftTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {130,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[__legStepCycleLength][3] = {
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
  };

  int __rightBackTargetAngles[__legStepCycleLength][3] = {
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {50,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };
  
  int __leftFrontTargetAngles[__legStepCycleLength][3] = {
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {130,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[__legStepCycleLength][3] = {
    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftBackTargetAngles[__legStepCycleLength][3] = {
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {50,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}

void XServoDriverV2::turnRightTripodGait() {
  int __legStepCycleLength = 4;
  changeGaitAngleSequence(__legStepCycleLength);
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontTargetAngles[4][3] = {
    {110,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {130,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[4][3] = {
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
  };

  int __rightBackTargetAngles[4][3] = {
    {70,LIFTED_RIGHT_LEG_ANGLE, LIFTED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE},
    {50,LOWERED_RIGHT_LEG_ANGLE, LOWERED_RIGHT_LEG_ANGLE}
  };
  
  int __leftFrontTargetAngles[4][3] = {
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {110,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {130,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[4][3] = {
    {90,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftBackTargetAngles[4][3] = {
    {70,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {50,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE},
    {70,LIFTED_LEFT_LEG_ANGLE, LIFTED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE, LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _gaitSingle(
    __rightFrontTargetAngles[_currentAngleSequence],
    __rightMidTargetAngles[_currentAngleSequence],
    __rightBackTargetAngles[_currentAngleSequence],
    __leftFrontTargetAngles[_currentAngleSequence],
    __leftMidTargetAngles[_currentAngleSequence],
    __leftBackTargetAngles[_currentAngleSequence]
  );
}
