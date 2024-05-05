#include "servo_driver_class_v2.h"

// BEGIN PRIVATE FUNCTIONS
// ----------
int XServoDriverV2::_angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void XServoDriverV2::_setAllCurrentLegAngles(
  int rightFrontAngles[2],
  int rightMidAngles[2],
  int rightBackAngles[2],
  int leftFrontAngles[2],
  int leftMidAngles[2],
  int leftBackAngles[2]
){
    for (int i = 0; i < 2; i++) {
      _rightFrontCurrentAngles[i] = rightFrontAngles[i];
      _rightMidCurrentAngles[i] = rightMidAngles[i];
      _rightBackCurrentAngles[i] = rightBackAngles[i];

      _leftFrontCurrentAngles[i] = leftFrontAngles[i];
      _leftMidCurrentAngles[i] = leftMidAngles[i];
      _leftBackCurrentAngles[i] = leftBackAngles[i];
    }
}

void XServoDriverV2::_tripodGait(
  int rightFrontTargetAngles[][2],
  int rightMidTargetAngles[][2],
  int rightBackTargetAngles[][2],
  int leftFrontTargetAngles[][2],
  int leftMidTargetAngles[][2],
  int leftBackTargetAngles[][2],
  int legStepCycleLength
){
    auto __adjustAngle = [&](int& targetAngle, int& currentAngle, int& increment) -> void {
      if (targetAngle < currentAngle) {
        currentAngle -= increment;
        
      } else if (targetAngle > currentAngle) {
        currentAngle += increment;
      }
    };
    
    // Gerak
    for(int i = 0; i < legStepCycleLength; i++){
      for (int j = 0; j < 2; j++) {
        _rightFrontIncrements[j] = rightFrontTargetAngles[i][j] - _rightFrontCurrentAngles[j];
        _rightMidIncrements[j] = rightMidTargetAngles[i][j] - _rightMidCurrentAngles[j];
        _rightBackIncrements[j] = rightBackTargetAngles[i][j] - _rightBackCurrentAngles[j];
        _leftFrontIncrements[j] = leftFrontTargetAngles[i][j] - _leftFrontCurrentAngles[j];
        _leftMidIncrements[j] = leftMidTargetAngles[i][j] - _leftMidCurrentAngles[j];
        _leftBackIncrements[j] = leftBackTargetAngles[i][j] - _leftBackCurrentAngles[j];
        
        _rightFrontIncrements[j] = abs(_rightFrontIncrements[j]) / _legStepsPerCycle;
        _rightMidIncrements[j] = abs(_rightMidIncrements[j]) / _legStepsPerCycle;
        _rightBackIncrements[j] = abs(_rightBackIncrements[j]) / _legStepsPerCycle;
        _leftFrontIncrements[j] = abs(_leftFrontIncrements[j]) / _legStepsPerCycle;
        _leftMidIncrements[j] = abs(_leftMidIncrements[j]) / _legStepsPerCycle;  
        _leftBackIncrements[j] = abs(_leftBackIncrements[j]) / _legStepsPerCycle;
      }
      
      unsigned long __startTime = millis();
      while (millis() - __startTime <= _legStepCycleDuration) {
        
          // Check if it's time to move to the next step
          if (millis() - _legStepPreviousMillis >= _intervalBetweenLegSteps) {

              // Update the previousMillis for the next step
              _legStepPreviousMillis = millis();

              // Adjust angle Increments
              for (int j = 0; j < 2; j++) {
                __adjustAngle (
                  rightFrontTargetAngles[i][j],
                  _rightFrontCurrentAngles[j],
                  _rightFrontIncrements[j]
                );
                __adjustAngle (
                  rightMidTargetAngles[i][j],
                  _rightMidCurrentAngles[j],
                  _rightMidIncrements[j]
                );
                __adjustAngle (
                  rightBackTargetAngles[i][j],
                  _rightBackCurrentAngles[j],
                  _rightBackIncrements[j]
                );
                
                __adjustAngle (
                  leftFrontTargetAngles[i][j],
                  _leftFrontCurrentAngles[j],
                  _leftFrontIncrements[j]
                ); 
                __adjustAngle (
                  leftMidTargetAngles[i][j],
                  _leftMidCurrentAngles[j],
                  _leftMidIncrements[j]
                );
                __adjustAngle (
                  leftBackTargetAngles[i][j],
                  _leftBackCurrentAngles[j],
                  _leftBackIncrements[j]
                ); 
              }

              // Set the new pulse width              
              _rightDriver.setPWM(0, 0, _angleToPulse(_rightFrontCurrentAngles[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(_rightFrontCurrentAngles[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(_rightFrontCurrentAngles[1]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(_rightMidCurrentAngles[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(_rightMidCurrentAngles[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(_rightMidCurrentAngles[1]));

              _rightDriver.setPWM(8, 0, _angleToPulse(_rightBackCurrentAngles[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(_rightBackCurrentAngles[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(_rightBackCurrentAngles[1]));

              _leftDriver.setPWM(0, 0, _angleToPulse(_leftFrontCurrentAngles[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(_leftFrontCurrentAngles[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(_leftFrontCurrentAngles[1]));

              _leftDriver.setPWM(4, 0, _angleToPulse(_leftMidCurrentAngles[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(_leftMidCurrentAngles[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(_leftMidCurrentAngles[1]));

              _leftDriver.setPWM(8, 0, _angleToPulse(_leftBackCurrentAngles[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(_leftBackCurrentAngles[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(_leftBackCurrentAngles[1])); 
          }
      }
      
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
//      delay(1000);
    }
}

// ----------
// END PRIVATE FUNCTIONS
