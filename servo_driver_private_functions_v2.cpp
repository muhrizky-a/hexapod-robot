#include "servo_driver_class_v2.h"

// BEGIN PRIVATE FUNCTIONS
// ----------
int XServoDriverV2::_angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void XServoDriverV2::_setCurrentLegAngles(int coxaAngle1, int femurTibiaAngle1, int coxaAngle2, int femurTibiaAngle2){
    _currentAngles_1[0] = coxaAngle1;
    _currentAngles_1[1] = femurTibiaAngle1;
    _currentAngles_2[0] = coxaAngle2;
    _currentAngles_2[1] = femurTibiaAngle2;
}

void XServoDriverV2::_tripodGait(int targetAngles_1[][2], int targetAngles_2[][2]){
    // Gerak
    for(int i=0; i < 4; i++){
      
      
      _increments_1[0] = targetAngles_1[i][0] - _currentAngles_1[0];
      _increments_1[1] = targetAngles_1[i][1] - _currentAngles_1[1];
      _increments_2[0] = targetAngles_2[i][0] - _currentAngles_2[0];
      _increments_2[1] = targetAngles_2[i][1] - _currentAngles_2[1];

      _increments_1[0] = abs(_increments_1[0]) / _legStepsPerCycle;
      _increments_1[1] = abs(_increments_1[1]) / _legStepsPerCycle;
      _increments_2[0] = abs(_increments_2[0]) / _legStepsPerCycle;
      _increments_2[1] = abs(_increments_2[1]) / _legStepsPerCycle;


      unsigned long __startTime = millis();
      while (millis() - __startTime <= _legStepCycleDuration) {
        
          // Check if it's time to move to the next step
          if (millis() - _legStepPreviousMillis >= _intervalBetweenLegSteps) {

              // Update the previousMillis for the next step
              _legStepPreviousMillis = millis();
              
              if(targetAngles_1[i][0] < _currentAngles_1[0]){
                _currentAngles_1[0] -= _increments_1[0];
              } else if(targetAngles_1[i][0] > _currentAngles_1[0]) {
                _currentAngles_1[0] += _increments_1[0];
              }
              if(targetAngles_1[i][1] < _currentAngles_1[1]){
                _currentAngles_1[1] -= _increments_1[1];
              } else if(targetAngles_1[i][1] > _currentAngles_1[1]) {
                _currentAngles_1[1] += _increments_1[1];
              }

              if(targetAngles_2[i][0] < _currentAngles_2[0]){
                _currentAngles_2[0] -= _increments_2[0];
              } else if(targetAngles_2[i][0] > _currentAngles_2[0]) {
                _currentAngles_2[0] += _increments_2[0];
              }

              if(targetAngles_2[i][1] < _currentAngles_2[1]){
                _currentAngles_2[1] -= _increments_2[1];
              } else if(targetAngles_2[i][1] > _currentAngles_2[1]) {
                _currentAngles_2[1] += _increments_2[1];
              }

              // Set the new pulse width              
              _rightDriver.setPWM(0, 0, _angleToPulse(_currentAngles_1[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(_currentAngles_1[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(_currentAngles_1[1]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(_currentAngles_2[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(_currentAngles_2[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(_currentAngles_2[1]));

              _rightDriver.setPWM(8, 0, _angleToPulse(_currentAngles_1[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(_currentAngles_1[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(_currentAngles_1[1]));

              _leftDriver.setPWM(0, 0, _angleToPulse(_currentAngles_1[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(_currentAngles_1[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(_currentAngles_1[1]));
              
              _leftDriver.setPWM(4, 0, _angleToPulse(_currentAngles_2[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(_currentAngles_2[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(_currentAngles_2[1]));

              _leftDriver.setPWM(8, 0, _angleToPulse(_currentAngles_1[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(_currentAngles_1[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(_currentAngles_1[1])); 
          }
      }
      
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
      // delay(1000);
    }

    // Switch lifted leg and repeat
    // XliftedLeg = (XliftedLeg + 1) % XnumLegs;
}
// ----------
// END PRIVATE FUNCTIONS
