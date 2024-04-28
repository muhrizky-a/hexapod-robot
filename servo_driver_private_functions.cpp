#include "servo_driver_class.h"

// BEGIN PRIVATE FUNCTIONS
// ----------
int XServoDriver::angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);  // Adjust SERVOMIN and SERVOMAX as needed
}

void XServoDriver::_moveServos(Adafruit_PWMServoDriver *pwmPtr, int tripodIndex, int coxaAngle, int femurTibiaAngle) {
    int targetPulseCoxa = angleToPulse(coxaAngle);
    int targetPulseFemurTibia = angleToPulse(femurTibiaAngle);

    // Get the current pulse width
//    int currentPulseCoxa = pwmPtr->getPWM(tripodIndex);
//    int currentPulseFemurTibia = pwmPtr->getPWM(tripodIndex + 1);
//
//    // Calculate the number of steps
//    unsigned long steps = duration / stepInterval;  // Assuming interval ms per step
//    // Calculate the increment value for each step
//    int incrementCoxa = (targetPulseCoxa - currentPulseCoxa) / steps;
//    int incrementFemurTibia = (targetPulseFemurTibia - currentPulseFemurTibia) / steps;
//
//    unsigned long startTime = millis();

    
    // Perform the ramping motion
    //    while (millis() - startTime <= duration) {
    // Check if it's time to move to the next step
    //      if (millis() - previousMillis >= stepInterval) {
    //        // Update the previousMillis for the next step
    //        previousMillis = millis();
    //
    //        // Increment the current pulse width
    //        currentPulseCoxa += incrementCoxa;
    //        currentPulseFemurTibia += incrementFemurTibia;

    //        // Set the new pulse width
    //        Serial.print("coxa: ");
    //        Serial.println(currentPulseCoxa);
    //        pwmPtr->setPWM(tripodIndex, 0, currentPulseCoxa);
    //        pwmPtr->setPWM(tripodIndex + 1, 0, currentPulseFemurTibia);
    //        pwmPtr->setPWM(tripodIndex + 2, 0, currentPulseFemurTibia);
    //      }
    //    }

    // Set the final position
    pwmPtr->setPWM(tripodIndex, 0, targetPulseCoxa);
    pwmPtr->setPWM(tripodIndex + 1, 0, targetPulseFemurTibia);
    pwmPtr->setPWM(tripodIndex + 2, 0, targetPulseFemurTibia);
}

void XServoDriver::_forwardRight(int legStep) {
    if (legStep == 0) {
        _moveServos(&rightDriver, 0, 90, LIFTED_RIGHT_LEG_ANGLE);
        _moveServos(&rightDriver, 4, 110, STAND_ANGLE);
        _moveServos(&rightDriver, 8, 90, LIFTED_RIGHT_LEG_ANGLE);

    } else if (legStep == 1) {
        _moveServos(&rightDriver, 0, 70, STAND_ANGLE);
        _moveServos(&rightDriver, 4, 90, LIFTED_RIGHT_LEG_ANGLE);
        _moveServos(&rightDriver, 8, 70, STAND_ANGLE);

    } else if (legStep == 2) {
        _moveServos(&rightDriver, 0, 110, STAND_ANGLE);
        _moveServos(&rightDriver, 4, 70, STAND_ANGLE);
        _moveServos(&rightDriver, 8, 110, STAND_ANGLE);
    }
}

void XServoDriver::_backwardRight(int legStep) {
    if (legStep == 0) {
        _moveServos(&rightDriver, 0, 90, LIFTED_RIGHT_LEG_ANGLE);
        _moveServos(&rightDriver, 4, 110, STAND_ANGLE);
        _moveServos(&rightDriver, 8, 90, LIFTED_RIGHT_LEG_ANGLE);
    } else if (legStep == 1) {
        _moveServos(&rightDriver, 0, 110, STAND_ANGLE);
        _moveServos(&rightDriver, 4, 70, STAND_ANGLE);
        _moveServos(&rightDriver, 8, 110, STAND_ANGLE);
    } else if (legStep == 2) {
        _moveServos(&rightDriver, 0, 70, STAND_ANGLE);
        _moveServos(&rightDriver, 4, 90, LIFTED_RIGHT_LEG_ANGLE);
        _moveServos(&rightDriver, 8, 70, STAND_ANGLE);
    }
}

void XServoDriver::_forwardLeft(int legStep) {
    if (legStep == 0) {
        _moveServos(&leftDriver, 0, 70, STAND_ANGLE);
        _moveServos(&leftDriver, 4, 90, LIFTED_LEFT_LEG_ANGLE);
        _moveServos(&leftDriver, 8, 70, STAND_ANGLE);
    } else if (legStep == 1) {
        _moveServos(&leftDriver, 0, 90, LIFTED_LEFT_LEG_ANGLE);
        _moveServos(&leftDriver, 4, 110, STAND_ANGLE);
        _moveServos(&leftDriver, 8, 90, LIFTED_LEFT_LEG_ANGLE);
    } else if (legStep == 2) {
        _moveServos(&leftDriver, 0, 110, STAND_ANGLE);
        _moveServos(&leftDriver, 4, 70, STAND_ANGLE);
        _moveServos(&leftDriver, 8, 110, STAND_ANGLE);
    }
}

void XServoDriver::_backwardLeft(int legStep) {
    if (legStep == 0) {
        _moveServos(&leftDriver, 0, 110, STAND_ANGLE);
        _moveServos(&leftDriver, 4, 70, STAND_ANGLE);
        _moveServos(&leftDriver, 8, 110, STAND_ANGLE);
    } else if (legStep == 1) {
        _moveServos(&leftDriver, 0, 90, LIFTED_LEFT_LEG_ANGLE);
        _moveServos(&leftDriver, 4, 110, STAND_ANGLE);
        _moveServos(&leftDriver, 8, 90, LIFTED_LEFT_LEG_ANGLE);
    } else if (legStep == 2) {
        _moveServos(&leftDriver, 0, 70, STAND_ANGLE);
        _moveServos(&leftDriver, 4, 90, LIFTED_LEFT_LEG_ANGLE);
        _moveServos(&leftDriver, 8, 70, STAND_ANGLE);
    }
}

void XServoDriver::_tripodGait(void (XServoDriver::*callGaitFunctionRight)(int), void (XServoDriver::*callGaitFunctionLeft)(int)) {
    unsigned long currentTime = millis();

    if (currentTime - startTime >= duration) {
        Serial.print("step: ");
        Serial.print(_legStep);
        Serial.println(" out of 0 - 2");

        (this->*callGaitFunctionRight)(_legStep);  // For right leg
        (this->*callGaitFunctionLeft)(_legStep);   // For left leg

        _legStep = (_legStep + 1) % 3; // add legStep like 0-1-2-0-1-2
//        if (_legStep > 1) {
//            _legStep = 0;
//        } else {
//            _legStep++;
//        }

        // Toggle state
        state = 1 - state;

        // Reset timer
        startTime = currentTime;
    }
}
// ----------
// END PRIVATE FUNCTIONS
