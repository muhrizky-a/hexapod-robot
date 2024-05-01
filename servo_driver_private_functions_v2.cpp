#include "servo_driver_class_v2.h"

// BEGIN PRIVATE FUNCTIONS
// ----------
int XServoDriverV2::_angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void XServoDriverV2::_setAllCurrentLegAngles(int coxaAngle, int femurTibiaAngle){
    _rightFrontBackCurrentAngles[0] = coxaAngle;
    _rightFrontBackCurrentAngles[1] = femurTibiaAngle;
    _rightMidCurrentAngles[0] = coxaAngle;
    _rightMidCurrentAngles[1] = femurTibiaAngle;
    _leftFrontBackCurrentAngles[0] = coxaAngle;
    _leftFrontBackCurrentAngles[1] = femurTibiaAngle;
    _leftMidCurrentAngles[0] = coxaAngle;
    _leftMidCurrentAngles[1] = femurTibiaAngle;
}


void XServoDriverV2::_tripodGait(
  int rightFrontBackTargetAngles[][2],
  int rightMidTargetAngles[][2],
  int leftFrontBackTargetAngles[][2],
  int leftMidTargetAngles[][2],
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
        _rightFrontBackIncrements[j] = rightFrontBackTargetAngles[i][j] - _rightFrontBackCurrentAngles[j];
        _rightMidIncrements[j] = rightMidTargetAngles[i][j] - _rightMidCurrentAngles[j];
        _leftFrontBackIncrements[j] = leftFrontBackTargetAngles[i][j] - _leftFrontBackCurrentAngles[j];
        _leftMidIncrements[j] = leftMidTargetAngles[i][j] - _leftMidCurrentAngles[j];
        
        _rightFrontBackIncrements[j] = abs(_rightFrontBackIncrements[j]) / _legStepsPerCycle;
        _rightMidIncrements[j] = abs(_rightMidIncrements[j]) / _legStepsPerCycle;
        _leftFrontBackIncrements[j] = abs(_leftFrontBackIncrements[j]) / _legStepsPerCycle;
        _leftMidIncrements[j] = abs(_leftMidIncrements[j]) / _legStepsPerCycle;  
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
                  rightFrontBackTargetAngles[i][j],
                  _rightFrontBackCurrentAngles[j],
                  _rightFrontBackIncrements[j]
                );
                __adjustAngle (
                  rightMidTargetAngles[i][j],
                  _rightMidCurrentAngles[j],
                  _rightMidIncrements[j]
                );
                __adjustAngle (
                  leftFrontBackTargetAngles[i][j],
                  _leftFrontBackCurrentAngles[j],
                  _leftFrontBackIncrements[j]
                ); 
                __adjustAngle (
                  leftMidTargetAngles[i][j],
                  _leftMidCurrentAngles[j],
                  _leftMidIncrements[j]
                );
              }

              // Set the new pulse width              
              _rightDriver.setPWM(0, 0, _angleToPulse(_rightFrontBackCurrentAngles[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(_rightFrontBackCurrentAngles[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(_rightFrontBackCurrentAngles[1]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(_rightMidCurrentAngles[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(_rightMidCurrentAngles[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(_rightMidCurrentAngles[1]));

              _rightDriver.setPWM(8, 0, _angleToPulse(_rightFrontBackCurrentAngles[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(_rightFrontBackCurrentAngles[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(_rightFrontBackCurrentAngles[1]));

              _leftDriver.setPWM(0, 0, _angleToPulse(_leftFrontBackCurrentAngles[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(_leftFrontBackCurrentAngles[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(_leftFrontBackCurrentAngles[1]));

              _leftDriver.setPWM(4, 0, _angleToPulse(_leftMidCurrentAngles[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(_leftMidCurrentAngles[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(_leftMidCurrentAngles[1]));

              _leftDriver.setPWM(8, 0, _angleToPulse(_leftFrontBackCurrentAngles[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(_leftFrontBackCurrentAngles[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(_leftFrontBackCurrentAngles[1])); 
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
