#include "servo_driver_class_v2.h"

// BEGIN PRIVATE FUNCTIONS
// ----------
int XServoDriverV2::_angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void XServoDriverV2::_setAllCurrentLegAngles(
  int rightFrontAngles[3],
  int rightMidAngles[3],
  int rightBackAngles[3],
  int leftFrontAngles[3],
  int leftMidAngles[3],
  int leftBackAngles[3]
){
    for (int i = 0; i < 3; i++) {
      _rightFrontCurrentAngles[i] = rightFrontAngles[i];
      _rightMidCurrentAngles[i] = rightMidAngles[i];
      _rightBackCurrentAngles[i] = rightBackAngles[i];

      _leftFrontCurrentAngles[i] = leftFrontAngles[i];
      _leftMidCurrentAngles[i] = leftMidAngles[i];
      _leftBackCurrentAngles[i] = leftBackAngles[i];
    }
}

void XServoDriverV2::_notifyChangedLegCommand(int newLegCommand){
  if (_legCommand != newLegCommand) {
    _currentAngleSequence = -1;
  }
}

void XServoDriverV2::_gait(
  int rightFrontTargetAngles[][3],
  int rightMidTargetAngles[][3],
  int rightBackTargetAngles[][3],
  int leftFrontTargetAngles[][3],
  int leftMidTargetAngles[][3],
  int leftBackTargetAngles[][3],
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
    int servoCountPerLeg = 3;
    for(int i = 0; i < legStepCycleLength; i++){
      for (int j = 0; j < servoCountPerLeg; j++) {
        _rightFrontAngleIncrements[j] = rightFrontTargetAngles[i][j] - _rightFrontCurrentAngles[j];
        _rightMidAngleIncrements[j] = rightMidTargetAngles[i][j] - _rightMidCurrentAngles[j];
        _rightBackAngleIncrements[j] = rightBackTargetAngles[i][j] - _rightBackCurrentAngles[j];
        _leftFrontAngleIncrements[j] = leftFrontTargetAngles[i][j] - _leftFrontCurrentAngles[j];
        _leftMidAngleIncrements[j] = leftMidTargetAngles[i][j] - _leftMidCurrentAngles[j];
        _leftBackAngleIncrements[j] = leftBackTargetAngles[i][j] - _leftBackCurrentAngles[j];
        
        _rightFrontAngleIncrements[j] = abs(_rightFrontAngleIncrements[j]) / _legStepsPerCycle;
        _rightMidAngleIncrements[j] = abs(_rightMidAngleIncrements[j]) / _legStepsPerCycle;
        _rightBackAngleIncrements[j] = abs(_rightBackAngleIncrements[j]) / _legStepsPerCycle;
        _leftFrontAngleIncrements[j] = abs(_leftFrontAngleIncrements[j]) / _legStepsPerCycle;
        _leftMidAngleIncrements[j] = abs(_leftMidAngleIncrements[j]) / _legStepsPerCycle;  
        _leftBackAngleIncrements[j] = abs(_leftBackAngleIncrements[j]) / _legStepsPerCycle;
      }
      
      unsigned long __startTime = millis();
      while (millis() - __startTime <= _LEG_STEP_CYCLE_DURATION) {
        
          // Check if it's time to move to the next step
          if (millis() - _legStepPreviousMillis >= _INTERVAL_BETWEEN_LEG_STEPS) {

              // Update the previousMillis for the next step
              _legStepPreviousMillis = millis();

              // Adjust angle Increments
              for (int j = 0; j < servoCountPerLeg; j++) {
                __adjustAngle (
                  rightFrontTargetAngles[i][j],
                  _rightFrontCurrentAngles[j],
                  _rightFrontAngleIncrements[j]
                );
                __adjustAngle (
                  rightMidTargetAngles[i][j],
                  _rightMidCurrentAngles[j],
                  _rightMidAngleIncrements[j]
                );
                __adjustAngle (
                  rightBackTargetAngles[i][j],
                  _rightBackCurrentAngles[j],
                  _rightBackAngleIncrements[j]
                );
                
                __adjustAngle (
                  leftFrontTargetAngles[i][j],
                  _leftFrontCurrentAngles[j],
                  _leftFrontAngleIncrements[j]
                ); 
                __adjustAngle (
                  leftMidTargetAngles[i][j],
                  _leftMidCurrentAngles[j],
                  _leftMidAngleIncrements[j]
                );
                __adjustAngle (
                  leftBackTargetAngles[i][j],
                  _leftBackCurrentAngles[j],
                  _leftBackAngleIncrements[j]
                ); 
              }

              // Set the new pulse width              
              _rightDriver.setPWM(0, 0, _angleToPulse(_rightFrontCurrentAngles[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(_rightFrontCurrentAngles[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(_rightFrontCurrentAngles[2]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(_rightMidCurrentAngles[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(_rightMidCurrentAngles[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(_rightMidCurrentAngles[2]));

              _rightDriver.setPWM(8, 0, _angleToPulse(_rightBackCurrentAngles[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(_rightBackCurrentAngles[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(_rightBackCurrentAngles[2]));

              _leftDriver.setPWM(0, 0, _angleToPulse(_leftFrontCurrentAngles[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(_leftFrontCurrentAngles[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(_leftFrontCurrentAngles[2]));

              _leftDriver.setPWM(4, 0, _angleToPulse(_leftMidCurrentAngles[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(_leftMidCurrentAngles[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(_leftMidCurrentAngles[2]));

              _leftDriver.setPWM(8, 0, _angleToPulse(_leftBackCurrentAngles[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(_leftBackCurrentAngles[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(_leftBackCurrentAngles[2])); 
          }
      }
      
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
//      delay(1000);
    }
}


void XServoDriverV2::_gaitSingle(
  int rightFrontTargetAngles[3],
  int rightMidTargetAngles[3],
  int rightBackTargetAngles[3],
  int leftFrontTargetAngles[3],
  int leftMidTargetAngles[3],
  int leftBackTargetAngles[3]
){
    auto __adjustAngle = [&](int& targetAngle, int& currentAngle, int& increment) -> void {
      if (targetAngle < currentAngle) {
        currentAngle -= increment;
        
      } else if (targetAngle > currentAngle) {
        currentAngle += increment;
      }
    };
    
    // Gerak
    int servoCountPerLeg = 3;
    for (int j = 0; j < servoCountPerLeg; j++) {
      _rightFrontAngleIncrements[j] = rightFrontTargetAngles[j] - _rightFrontCurrentAngles[j];
      _rightMidAngleIncrements[j] = rightMidTargetAngles[j] - _rightMidCurrentAngles[j];
      _rightBackAngleIncrements[j] = rightBackTargetAngles[j] - _rightBackCurrentAngles[j];
      _leftFrontAngleIncrements[j] = leftFrontTargetAngles[j] - _leftFrontCurrentAngles[j];
      _leftMidAngleIncrements[j] = leftMidTargetAngles[j] - _leftMidCurrentAngles[j];
      _leftBackAngleIncrements[j] = leftBackTargetAngles[j] - _leftBackCurrentAngles[j];
      
      _rightFrontAngleIncrements[j] = abs(_rightFrontAngleIncrements[j]) / _legStepsPerCycle;
      _rightMidAngleIncrements[j] = abs(_rightMidAngleIncrements[j]) / _legStepsPerCycle;
      _rightBackAngleIncrements[j] = abs(_rightBackAngleIncrements[j]) / _legStepsPerCycle;
      _leftFrontAngleIncrements[j] = abs(_leftFrontAngleIncrements[j]) / _legStepsPerCycle;
      _leftMidAngleIncrements[j] = abs(_leftMidAngleIncrements[j]) / _legStepsPerCycle;  
      _leftBackAngleIncrements[j] = abs(_leftBackAngleIncrements[j]) / _legStepsPerCycle;
    }
    
    unsigned long __startTime = millis();
    while (millis() - __startTime <= _LEG_STEP_CYCLE_DURATION) {
      
        // Check if it's time to move to the next step
        if (millis() - _legStepPreviousMillis >= _INTERVAL_BETWEEN_LEG_STEPS) {

            // Update the previousMillis for the next step
            _legStepPreviousMillis = millis();

            // Adjust angle Increments
            for (int j = 0; j < servoCountPerLeg; j++) {
              __adjustAngle (
                rightFrontTargetAngles[j],
                _rightFrontCurrentAngles[j],
                _rightFrontAngleIncrements[j]
              );
              __adjustAngle (
                rightMidTargetAngles[j],
                _rightMidCurrentAngles[j],
                _rightMidAngleIncrements[j]
              );
              __adjustAngle (
                rightBackTargetAngles[j],
                _rightBackCurrentAngles[j],
                _rightBackAngleIncrements[j]
              );
              
              __adjustAngle (
                leftFrontTargetAngles[j],
                _leftFrontCurrentAngles[j],
                _leftFrontAngleIncrements[j]
              ); 
              __adjustAngle (
                leftMidTargetAngles[j],
                _leftMidCurrentAngles[j],
                _leftMidAngleIncrements[j]
              );
              __adjustAngle (
                leftBackTargetAngles[j],
                _leftBackCurrentAngles[j],
                _leftBackAngleIncrements[j]
              ); 
            }

            // Set the new pulse width              
            _rightDriver.setPWM(0, 0, _angleToPulse(_rightFrontCurrentAngles[0]));
            _rightDriver.setPWM(1, 0, _angleToPulse(_rightFrontCurrentAngles[1]));
            _rightDriver.setPWM(2, 0, _angleToPulse(_rightFrontCurrentAngles[2]));
            
            _rightDriver.setPWM(4, 0, _angleToPulse(_rightMidCurrentAngles[0]));
            _rightDriver.setPWM(5, 0, _angleToPulse(_rightMidCurrentAngles[1]));
            _rightDriver.setPWM(6, 0, _angleToPulse(_rightMidCurrentAngles[2]));

            _rightDriver.setPWM(8, 0, _angleToPulse(_rightBackCurrentAngles[0]));
            _rightDriver.setPWM(9, 0, _angleToPulse(_rightBackCurrentAngles[1]));
            _rightDriver.setPWM(10, 0, _angleToPulse(_rightBackCurrentAngles[2]));

            _leftDriver.setPWM(0, 0, _angleToPulse(_leftFrontCurrentAngles[0]));
            _leftDriver.setPWM(1, 0, _angleToPulse(_leftFrontCurrentAngles[1]));
            _leftDriver.setPWM(2, 0, _angleToPulse(_leftFrontCurrentAngles[2]));

            _leftDriver.setPWM(4, 0, _angleToPulse(_leftMidCurrentAngles[0]));
            _leftDriver.setPWM(5, 0, _angleToPulse(_leftMidCurrentAngles[1]));
            _leftDriver.setPWM(6, 0, _angleToPulse(_leftMidCurrentAngles[2]));

            _leftDriver.setPWM(8, 0, _angleToPulse(_leftBackCurrentAngles[0]));
            _leftDriver.setPWM(9, 0, _angleToPulse(_leftBackCurrentAngles[1]));
            _leftDriver.setPWM(10, 0, _angleToPulse(_leftBackCurrentAngles[2])); 
        }
    }
    
    // Set the final position;
    Serial.println("");
    Serial.println("=final single=");
}
// ----------
// END PRIVATE FUNCTIONS
