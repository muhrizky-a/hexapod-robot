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
    Serial.println("stand");
    for (int i = 0; i < 12; i++) {
        _rightDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
        _leftDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
    }

    _setAllCurrentLegAngles(
      STAND_ANGLE,
      STAND_ANGLE
    );
}

void XServoDriverV2::sit() {
    Serial.println("sit");
    for (int i = 0; i <= 8; i += 4) {
        _rightDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
        _leftDriver.setPWM(i, 0, _angleToPulse(STAND_ANGLE));
    }

    // Loop for servo on channel starts in 0, 4, 8
    for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 1,2, then 5,6, then 9, 10
        _rightDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        _rightDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        _leftDriver.setPWM(i + 1, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
        _leftDriver.setPWM(i + 2, 0, _angleToPulse(LIFTED_LEFT_LEG_ANGLE));
    }
}

void XServoDriverV2::gripperLift() {
    Serial.println("gripper arm lifted");
    _rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, _angleToPulse(90));
}

void XServoDriverV2::gripperDown() {
    Serial.println("gripper arm down");
    _rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, _angleToPulse(180));
}

void XServoDriverV2::gripperOpen() {
    _rightDriver.setPWM(GRIPPER_CHANNEL, 0, _angleToPulse(135));
}

void XServoDriverV2::gripperClose() {
    _rightDriver.setPWM(GRIPPER_CHANNEL, 0, _angleToPulse(0));
}

void XServoDriverV2::leanFront() {
  // Loop for servo on channel starts in 0, 4, 8
  for (int i = 0; i <= 8; i += 4) {
    // This will control servo on channel 0,1,2, then 4,5,6, then 8,9,10
    _rightDriver.setPWM(i, 0, _angleToPulse(BACKWARD_RIGHT_COXA_LEG_ANGLE));
    _rightDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
    _rightDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));
    
    _leftDriver.setPWM(i, 0, _angleToPulse(BACKWARD_LEFT_COXA_LEG_ANGLE));
    _leftDriver.setPWM(i + 1, 0, _angleToPulse(STAND_ANGLE));
    _leftDriver.setPWM(i + 2, 0, _angleToPulse(STAND_ANGLE));
  }
}


void XServoDriverV2::forwardTripodGait() {
  int __legStepCycleLength = 4;
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontBackTargetAngles[4][2] = {
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[4][2] = {
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE},
  };
  
  int __leftFrontBackTargetAngles[4][2] = {
    {90,LOWERED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE},
    {90,LIFTED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[4][2] = {
    {90,LIFTED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _tripodGait(
    __rightFrontBackTargetAngles,
    __rightMidTargetAngles,
    __leftFrontBackTargetAngles,
    __leftMidTargetAngles,
    __legStepCycleLength
  );
}

void XServoDriverV2::backwardTripodGait() {
  int __legStepCycleLength = 4;
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontBackTargetAngles[4][2] = {
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[4][2] = {
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE},
  };
  
  int __leftFrontBackTargetAngles[4][2] = {
    {90,LOWERED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE},
    {90,LIFTED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[4][2] = {
    {90,LIFTED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _tripodGait(
    __rightFrontBackTargetAngles,
    __rightMidTargetAngles,
    __leftFrontBackTargetAngles,
    __leftMidTargetAngles,
    __legStepCycleLength
  );
}

void XServoDriverV2::turnLeftTripodGait() {
  int __legStepCycleLength = 4;
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontBackTargetAngles[4][2] = {
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[4][2] = {
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE},
  };
  
  int __leftFrontBackTargetAngles[4][2] = {
    {90,LOWERED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE},
    {90,LIFTED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[4][2] = {
    {90,LIFTED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _tripodGait(
    __rightFrontBackTargetAngles,
    __rightMidTargetAngles,
    __leftFrontBackTargetAngles,
    __leftMidTargetAngles,
    __legStepCycleLength
  );
}

void XServoDriverV2::turnRightTripodGait() {
  int __legStepCycleLength = 4;
  
  // Leg Target Angles for one cycle (each cycle below consists of 4 angles).
  // The index 0 is coxa angle, the index 1 is femur and tibia angle.
  int __rightFrontBackTargetAngles[4][2] = {
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE},
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE}
  };

  int __rightMidTargetAngles[4][2] = {
    {90,LOWERED_RIGHT_LEG_ANGLE},
    {70,LOWERED_RIGHT_LEG_ANGLE},
    {90,LIFTED_RIGHT_LEG_ANGLE},
    {110,LOWERED_RIGHT_LEG_ANGLE},
  };
  
  int __leftFrontBackTargetAngles[4][2] = {
    {90,LOWERED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE},
    {90,LIFTED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE}
  };

  int __leftMidTargetAngles[4][2] = {
    {90,LIFTED_LEFT_LEG_ANGLE},
    {110,LOWERED_LEFT_LEG_ANGLE},
    {90,LOWERED_LEFT_LEG_ANGLE},
    {70,LOWERED_LEFT_LEG_ANGLE}
  };
    

  // Gerak
  _tripodGait(
    __rightFrontBackTargetAngles,
    __rightMidTargetAngles,
    __leftFrontBackTargetAngles,
    __leftMidTargetAngles,
    __legStepCycleLength
  );
}
