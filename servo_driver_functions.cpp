#include "servo_driver_class.h"

// BEGIN PRIVATE FUNCTIONS
// ----------
void XServoDriver::initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left) {
    Serial.println("init servo drivers");
    rightDriver = right;
    leftDriver = left;

    rightDriver.begin();
    rightDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
    leftDriver.begin();
    leftDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
}

int XServoDriver::angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);  // Adjust SERVOMIN and SERVOMAX as needed
}

unsigned long previousMillis = 0;
const unsigned long interval = 20; // Interval between steps (in milliseconds)
void XServoDriver::moveTripod(Adafruit_PWMServoDriver *pwmPtr, int tripodIndex, int coxaAngle, int femurTibiaAngle) {

    int targetPulseCoxa = angleToPulse(coxaAngle);
    int targetPulseFemurTibia = angleToPulse(femurTibiaAngle);
    
    // Get the current pulse width
    int currentPulseCoxa = pwmPtr->getPWM(tripodIndex);
    int currentPulseFemurTibia = pwmPtr->getPWM(tripodIndex + 1);
    
    // Calculate the number of steps
    unsigned long steps = duration / interval; // Assuming interval ms per step
    
    // Calculate the increment value for each step
    int incrementCoxa = (targetPulseCoxa - currentPulseCoxa) / steps;
    int incrementFemurTibia = (targetPulseFemurTibia - currentPulseFemurTibia) / steps;

    unsigned long startTime = millis();

    // Perform the ramping motion
//    while (millis() - startTime <= duration) {
      // Check if it's time to move to the next step
//      if (millis() - previousMillis >= interval) {
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
    
//    pwmPtr->setPWM(tripodIndex, 0, angleToPulse(coxaAngle));
//    pwmPtr->setPWM(tripodIndex + 1, 0, angleToPulse(femurTibiaAngle));
//    pwmPtr->setPWM(tripodIndex + 2, 0, angleToPulse(femurTibiaAngle));
}

void XServoDriver::tripodGait(void (XServoDriver::*callGaitFunctionRight)(int),void (XServoDriver::*callGaitFunctionLeft)(int)) {
  unsigned long currentTime = millis();
    if (currentTime - startTime >= duration) {
        Serial.print("step: ");
        Serial.print(legStep);
        Serial.println(" out of 3");

        (this->*callGaitFunctionRight)(legStep); // For right leg
        (this->*callGaitFunctionLeft)(legStep);  // For left leg

        if (legStep > 1) {
            legStep = 0;
        } else {
            legStep++;
        }

        //    // Move tripod based on state
        //    if (state == 0) {
        //      moveTripod(0, LIFTED_ANGLE, FORWARD_ANGLE);
        //      moveTripod(2, STAND_ANGLE, BACKWARD_ANGLE);
        //      moveTripod(4, LIFTED_ANGLE, FORWARD_ANGLE);
        //    } else {
        //      moveTripod(1, LIFTED_ANGLE, FORWARD_ANGLE);
        //      moveTripod(3, STAND_ANGLE, BACKWARD_ANGLE);
        //      moveTripod(5, LIFTED_ANGLE, FORWARD_ANGLE);
        //    }
        //
        // Toggle state
        state = 1 - state;

        // Reset timer
        startTime = currentTime;
    }
}

void XServoDriver::forwardRight(int legStep) {
    if (legStep == 0) {
        moveTripod(&rightDriver, 0, 90, LIFTED_RIGHT_LEG_ANGLE);
        moveTripod(&rightDriver, 4, 110, STAND_ANGLE);
        moveTripod(&rightDriver, 8, 90, LIFTED_RIGHT_LEG_ANGLE);

    } else if (legStep == 1) {
        moveTripod(&rightDriver, 0, 70, STAND_ANGLE);
        moveTripod(&rightDriver, 4, 90, LIFTED_RIGHT_LEG_ANGLE);
        moveTripod(&rightDriver, 8, 70, STAND_ANGLE);

    } else if (legStep == 2) {
        moveTripod(&rightDriver, 0, 110, STAND_ANGLE);
        moveTripod(&rightDriver, 4, 70, STAND_ANGLE);
        moveTripod(&rightDriver, 8, 110, STAND_ANGLE);
    }
}

void XServoDriver::backwardRight(int legStep) {
    if (legStep == 0) {
        moveTripod(&rightDriver, 0, 90, LIFTED_RIGHT_LEG_ANGLE);
        moveTripod(&rightDriver, 4, 110, STAND_ANGLE);
        moveTripod(&rightDriver, 8, 90, LIFTED_RIGHT_LEG_ANGLE);
    } else if (legStep == 1) {
        moveTripod(&rightDriver, 0, 110, STAND_ANGLE);
        moveTripod(&rightDriver, 4, 70, STAND_ANGLE);
        moveTripod(&rightDriver, 8, 110, STAND_ANGLE);
    } else if (legStep == 2) {
        moveTripod(&rightDriver, 0, 70, STAND_ANGLE);
        moveTripod(&rightDriver, 4, 90, LIFTED_RIGHT_LEG_ANGLE);
        moveTripod(&rightDriver, 8, 70, STAND_ANGLE);
    }
}

void XServoDriver::forwardLeft(int legStep) {
    if (legStep == 0) {
        moveTripod(&leftDriver, 0, 70, STAND_ANGLE);
        moveTripod(&leftDriver, 4, 90, LIFTED_LEFT_LEG_ANGLE);
        moveTripod(&leftDriver, 8, 70, STAND_ANGLE);
    } else if (legStep == 1) {
        moveTripod(&leftDriver, 0, 90, LIFTED_LEFT_LEG_ANGLE);
        moveTripod(&leftDriver, 4, 110, STAND_ANGLE);
        moveTripod(&leftDriver, 8, 90, LIFTED_LEFT_LEG_ANGLE);
    } else if (legStep == 2) {
        moveTripod(&leftDriver, 0, 110, STAND_ANGLE);
        moveTripod(&leftDriver, 4, 70, STAND_ANGLE);
        moveTripod(&leftDriver, 8, 110, STAND_ANGLE);
    }
}

void XServoDriver::backwardLeft(int legStep) {
    if (legStep == 0) {
        moveTripod(&leftDriver, 0, 110, STAND_ANGLE);
        moveTripod(&leftDriver, 4, 70, STAND_ANGLE);
        moveTripod(&leftDriver, 8, 110, STAND_ANGLE);
    } else if (legStep == 1) {
        moveTripod(&leftDriver, 0, 90, LIFTED_LEFT_LEG_ANGLE);
        moveTripod(&leftDriver, 4, 110, STAND_ANGLE);
        moveTripod(&leftDriver, 8, 90, LIFTED_LEFT_LEG_ANGLE);
    } else if (legStep == 2) {
        moveTripod(&leftDriver, 0, 70, STAND_ANGLE);
        moveTripod(&leftDriver, 4, 90, LIFTED_LEFT_LEG_ANGLE);
        moveTripod(&leftDriver, 8, 70, STAND_ANGLE);
    }
}

// END PRIVATE FUNCTIONS
// ----------
// PUBLIC FUNCTIONS
void XServoDriver::afterInit() {
    Serial.println("after init");
     
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(0));
    delay(1000);
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(45));
    delay(1000);
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(90));
    delay(1000);
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(45));
    delay(1000);
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(0));
    delay(1000);
}

void XServoDriver::stand() {
    Serial.println("stand");
    for (int i = 0; i < 12; i++) {
        rightDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
        leftDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
    }
}

void XServoDriver::sit() {
    Serial.println("sit");
    for (int i = 0; i <= 8; i += 4) {
        rightDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
        leftDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
    }

    // Loop for servo on channel starts in 0, 4, 8
    for (int i = 0; i <= 8; i += 4) {
        // This will control servo on channel 1,2, then 5,6, then 9, 10
        rightDriver.setPWM(i + 1, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        rightDriver.setPWM(i + 2, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
        leftDriver.setPWM(i + 1, 0, angleToPulse(LIFTED_LEFT_LEG_ANGLE));
        leftDriver.setPWM(i + 2, 0, angleToPulse(LIFTED_LEFT_LEG_ANGLE));
    }
}

void XServoDriver::gripperLift() {
    Serial.println("gripper arm lifted");
    rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(0));
}

void XServoDriver::gripperDown() {
    Serial.println("gripper arm down");
    rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(180));
}

void XServoDriver::gripperOpen() {
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(135));   
}

void XServoDriver::gripperClose() {
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(0));
}


void XServoDriver::forwardTripodGait() {
    tripodGait(&XServoDriver::forwardRight, &XServoDriver::forwardLeft);
}


void XServoDriver::turnLeftTripodGait() {
  tripodGait(&XServoDriver::forwardRight, &XServoDriver::backwardLeft);
}

void XServoDriver::turnRightTripodGait() {
  tripodGait(&XServoDriver::backwardRight, &XServoDriver::forwardLeft);
}
