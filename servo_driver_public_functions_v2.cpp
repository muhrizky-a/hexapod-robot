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
    
    currentAngles_1[0] = STAND_ANGLE;
    currentAngles_1[1] = STAND_ANGLE;
    currentAngles_2[0] = STAND_ANGLE;
    currentAngles_2[1] = STAND_ANGLE;
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
const int XnumLegs = 6;
//int XstepTime = 1000;  // Time in milliseconds for each step cycle
int XliftedLeg = 0;    // Currently lifted leg index (0-5)

const int Xduration = 250;  // Adjust duration based on desired walking speed
const int XstepInterval = 50;  // Interval between steps (in milliseconds)
long XpreviousMillis = 0;

void XServoDriverV2::forwardTripodGait() {
  Serial.print("STARTO ");
  int steps = Xduration / XstepInterval;  // Assuming interval ms per step
  
    const int targetAngles_1[4][2] = {
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {70,LOWERED_RIGHT_LEG_ANGLE},
      {90,LOWERED_RIGHT_LEG_ANGLE},
      {110,LOWERED_RIGHT_LEG_ANGLE},
    };

    const int targetAngles_2[4][2] = {
      {90,LOWERED_RIGHT_LEG_ANGLE},
      {110,LOWERED_RIGHT_LEG_ANGLE},
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {70,LOWERED_RIGHT_LEG_ANGLE},
    };
    
//    currentAngles[0] = targetAngles[0][0];
//    Serial.println(currentAngles[0]);
//    currentAngles[1] = targetAngles[0][1];  
    
    // Gerak
    for(int i=0; i < 4; i++){
      unsigned long startTime = millis();
      
      
//      Serial.print("current angle begin: ");
//      Serial.println(currentAngles[1]);
//      Serial.print("target angle begin: ");
//      Serial.println(targetAngles[i][1]); 
//
      Serial.print("inc beginz: ");
      Serial.print(" ");
      increments_1[0] = targetAngles_1[i][0] - currentAngles_1[0];
      increments_1[1] = targetAngles_1[i][1] - currentAngles_1[1];
      increments_2[0] = targetAngles_2[i][0] - currentAngles_2[0];
      increments_2[1] = targetAngles_2[i][1] - currentAngles_2[1];
//      Serial.print(increments[0]);
//      Serial.print(" ");
//      Serial.print(steps);
//      Serial.print(" ");
      increments_1[0] = abs(increments_1[0]) / steps;
      increments_1[1] = abs(increments_1[1]) / steps;
      increments_2[0] = abs(increments_2[0]) / steps;
      increments_2[1] = abs(increments_2[1]) / steps;
//      increments[0] = abs(increments[0]);
//      Serial.print(" ");
//      Serial.println(increments_1[0]);
      
      // Count to Xduration (0-1000)
      Serial.print("inc-ed angles: ");
      while (millis() - startTime <= Xduration) {
          // Check if it's time to move to the next step (XstepInterval is 20, so stepping 0,20,40,80,...,1000)
          
          if (millis() - XpreviousMillis >= XstepInterval) {

              // Update the previousMillis for the next step
              XpreviousMillis = millis();
              
              if(targetAngles_1[i][0] < currentAngles_1[0]){
                currentAngles_1[0] -= increments_1[0];
              } else if(targetAngles_1[i][0] > currentAngles_1[0]) {
                currentAngles_1[0] += increments_1[0];
              }
              if(targetAngles_1[i][1] < currentAngles_1[1]){
                currentAngles_1[1] -= increments_1[1];
              } else if(targetAngles_1[i][1] > currentAngles_1[1]) {
                currentAngles_1[1] += increments_1[1];
              }

              if(targetAngles_2[i][0] < currentAngles_2[0]){
                currentAngles_2[0] -= increments_2[0];
              } else if(targetAngles_2[i][0] > currentAngles_2[0]) {
                currentAngles_2[0] += increments_2[0];
              }

              if(targetAngles_2[i][1] < currentAngles_2[1]){
                currentAngles_2[1] -= increments_2[1];
              } else if(targetAngles_2[i][1] > currentAngles_2[1]) {
                currentAngles_2[1] += increments_2[1];
              }

//              Serial.print(currentAngles[1]);
//              Serial.print(" ");
              
  
              // Set the new pulse width
              
              _rightDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _rightDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1]));

              _leftDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _leftDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _leftDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1])); 
          }
      }
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
//      Serial.println(currentAngles_1[0]);
//      delay(1000);
    }

    // Switch lifted leg and repeat
//    XliftedLeg = (XliftedLeg + 1) % XnumLegs;
}

void XServoDriverV2::backwardTripodGait() {
  Serial.print("STARTO ");
  int steps = Xduration / XstepInterval;  // Assuming interval ms per step
  
    const int targetAngles_1[4][2] = {
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {110,STAND_ANGLE},
      {90,STAND_ANGLE},
      {70,STAND_ANGLE},
    };

    const int targetAngles_2[4][2] = {
      {90,STAND_ANGLE},
      {70,STAND_ANGLE},
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {110,STAND_ANGLE},
    };
    
//    currentAngles[0] = targetAngles[0][0];
//    Serial.println(currentAngles[0]);
//    currentAngles[1] = targetAngles[0][1];  
    
    // Gerak
    for(int i=0; i < 4; i++){
      unsigned long startTime = millis();
      
      
//      Serial.print("current angle begin: ");
//      Serial.println(currentAngles[1]);
//      Serial.print("target angle begin: ");
//      Serial.println(targetAngles[i][1]); 
//
      Serial.print("inc beginz: ");
      Serial.print(" ");
      increments_1[0] = targetAngles_1[i][0] - currentAngles_1[0];
      increments_1[1] = targetAngles_1[i][1] - currentAngles_1[1];
      increments_2[0] = targetAngles_2[i][0] - currentAngles_2[0];
      increments_2[1] = targetAngles_2[i][1] - currentAngles_2[1];
//      Serial.print(increments[0]);
//      Serial.print(" ");
//      Serial.print(steps);
//      Serial.print(" ");
      increments_1[0] = abs(increments_1[0]) / steps;
      increments_1[1] = abs(increments_1[1]) / steps;
      increments_2[0] = abs(increments_2[0]) / steps;
      increments_2[1] = abs(increments_2[1]) / steps;
//      increments[0] = abs(increments[0]);
//      Serial.print(" ");
//      Serial.println(increments_1[0]);
      
      // Count to Xduration (0-1000)
      Serial.print("inc-ed angles: ");
      while (millis() - startTime <= Xduration) {
          // Check if it's time to move to the next step (XstepInterval is 20, so stepping 0,20,40,80,...,1000)
          
          if (millis() - XpreviousMillis >= XstepInterval) {

              // Update the previousMillis for the next step
              XpreviousMillis = millis();
              
              if(targetAngles_1[i][0] < currentAngles_1[0]){
                currentAngles_1[0] -= increments_1[0];
              } else if(targetAngles_1[i][0] > currentAngles_1[0]) {
                currentAngles_1[0] += increments_1[0];
              }
              if(targetAngles_1[i][1] < currentAngles_1[1]){
                currentAngles_1[1] -= increments_1[1];
              } else if(targetAngles_1[i][1] > currentAngles_1[1]) {
                currentAngles_1[1] += increments_1[1];
              }

              if(targetAngles_2[i][0] < currentAngles_2[0]){
                currentAngles_2[0] -= increments_2[0];
              } else if(targetAngles_2[i][0] > currentAngles_2[0]) {
                currentAngles_2[0] += increments_2[0];
              }

              if(targetAngles_2[i][1] < currentAngles_2[1]){
                currentAngles_2[1] -= increments_2[1];
              } else if(targetAngles_2[i][1] > currentAngles_2[1]) {
                currentAngles_2[1] += increments_2[1];
              }

//              Serial.print(currentAngles[1]);
//              Serial.print(" ");
              
  
              // Set the new pulse width
              
              _rightDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _rightDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1]));

//              ---
              _leftDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _leftDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _leftDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1])); 
          }
      }
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
//      Serial.println(currentAngles_1[0]);
//      delay(1000);
    }

    // Switch lifted leg and repeat
//    XliftedLeg = (XliftedLeg + 1) % XnumLegs;
}

void XServoDriverV2::turnLeftTripodGait() {
  Serial.print("STARTO ");
  int steps = Xduration / XstepInterval;  // Assuming interval ms per step
  
    const int targetAngles_1[4][2] = {
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {70,STAND_ANGLE},
      {90,STAND_ANGLE},
      {110,STAND_ANGLE},
    };

    const int targetAngles_2[4][2] = {
      {90,STAND_ANGLE},
      {70,STAND_ANGLE},
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {110,STAND_ANGLE},
    };
    
//    currentAngles[0] = targetAngles[0][0];
//    Serial.println(currentAngles[0]);
//    currentAngles[1] = targetAngles[0][1];  
    
    // Gerak
    for(int i=0; i < 4; i++){
      unsigned long startTime = millis();
      
      
//      Serial.print("current angle begin: ");
//      Serial.println(currentAngles[1]);
//      Serial.print("target angle begin: ");
//      Serial.println(targetAngles[i][1]); 
//
      Serial.print("inc beginz: ");
      Serial.print(" ");
      increments_1[0] = targetAngles_1[i][0] - currentAngles_1[0];
      increments_1[1] = targetAngles_1[i][1] - currentAngles_1[1];
      increments_2[0] = targetAngles_2[i][0] - currentAngles_2[0];
      increments_2[1] = targetAngles_2[i][1] - currentAngles_2[1];
//      Serial.print(increments[0]);
//      Serial.print(" ");
//      Serial.print(steps);
//      Serial.print(" ");
      increments_1[0] = abs(increments_1[0]) / steps;
      increments_1[1] = abs(increments_1[1]) / steps;
      increments_2[0] = abs(increments_2[0]) / steps;
      increments_2[1] = abs(increments_2[1]) / steps;
//      increments[0] = abs(increments[0]);
//      Serial.print(" ");
//      Serial.println(increments_1[0]);
      
      // Count to Xduration (0-1000)
      Serial.print("inc-ed angles: ");
      while (millis() - startTime <= Xduration) {
          // Check if it's time to move to the next step (XstepInterval is 20, so stepping 0,20,40,80,...,1000)
          
          if (millis() - XpreviousMillis >= XstepInterval) {

              // Update the previousMillis for the next step
              XpreviousMillis = millis();
              
              if(targetAngles_1[i][0] < currentAngles_1[0]){
                currentAngles_1[0] -= increments_1[0];
              } else if(targetAngles_1[i][0] > currentAngles_1[0]) {
                currentAngles_1[0] += increments_1[0];
              }
              if(targetAngles_1[i][1] < currentAngles_1[1]){
                currentAngles_1[1] -= increments_1[1];
              } else if(targetAngles_1[i][1] > currentAngles_1[1]) {
                currentAngles_1[1] += increments_1[1];
              }

              if(targetAngles_2[i][0] < currentAngles_2[0]){
                currentAngles_2[0] -= increments_2[0];
              } else if(targetAngles_2[i][0] > currentAngles_2[0]) {
                currentAngles_2[0] += increments_2[0];
              }

              if(targetAngles_2[i][1] < currentAngles_2[1]){
                currentAngles_2[1] -= increments_2[1];
              } else if(targetAngles_2[i][1] > currentAngles_2[1]) {
                currentAngles_2[1] += increments_2[1];
              }

//              Serial.print(currentAngles[1]);
//              Serial.print(" ");
              
  
              // Set the new pulse width
              
              _rightDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _rightDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1]));

//              ---
              _leftDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _leftDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _leftDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1])); 
          }
      }
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
//      Serial.println(currentAngles_1[0]);
//      delay(1000);
    }

    // Switch lifted leg and repeat
//    XliftedLeg = (XliftedLeg + 1) % XnumLegs;
}

void XServoDriverV2::turnRightTripodGait() {
  Serial.print("STARTO ");
  int steps = Xduration / XstepInterval;  // Assuming interval ms per step
  
    const int targetAngles_1[4][2] = {
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {110,STAND_ANGLE},
      {90,STAND_ANGLE},
      {70,STAND_ANGLE},
    };

    const int targetAngles_2[4][2] = {
      {90,STAND_ANGLE},
      {110,STAND_ANGLE},
      {90,LIFTED_RIGHT_LEG_ANGLE},
      {70,STAND_ANGLE},
    };
    
//    currentAngles[0] = targetAngles[0][0];
//    Serial.println(currentAngles[0]);
//    currentAngles[1] = targetAngles[0][1];  
    
    // Gerak
    for(int i=0; i < 4; i++){
      unsigned long startTime = millis();
      
      
//      Serial.print("current angle begin: ");
//      Serial.println(currentAngles[1]);
//      Serial.print("target angle begin: ");
//      Serial.println(targetAngles[i][1]); 
//
      Serial.print("inc beginz: ");
      Serial.print(" ");
      increments_1[0] = targetAngles_1[i][0] - currentAngles_1[0];
      increments_1[1] = targetAngles_1[i][1] - currentAngles_1[1];
      increments_2[0] = targetAngles_2[i][0] - currentAngles_2[0];
      increments_2[1] = targetAngles_2[i][1] - currentAngles_2[1];
//      Serial.print(increments[0]);
//      Serial.print(" ");
//      Serial.print(steps);
//      Serial.print(" ");
      increments_1[0] = abs(increments_1[0]) / steps;
      increments_1[1] = abs(increments_1[1]) / steps;
      increments_2[0] = abs(increments_2[0]) / steps;
      increments_2[1] = abs(increments_2[1]) / steps;
//      increments[0] = abs(increments[0]);
//      Serial.print(" ");
//      Serial.println(increments_1[0]);
      
      // Count to Xduration (0-1000)
      Serial.print("inc-ed angles: ");
      while (millis() - startTime <= Xduration) {
          // Check if it's time to move to the next step (XstepInterval is 20, so stepping 0,20,40,80,...,1000)
          
          if (millis() - XpreviousMillis >= XstepInterval) {

              // Update the previousMillis for the next step
              XpreviousMillis = millis();
              
              if(targetAngles_1[i][0] < currentAngles_1[0]){
                currentAngles_1[0] -= increments_1[0];
              } else if(targetAngles_1[i][0] > currentAngles_1[0]) {
                currentAngles_1[0] += increments_1[0];
              }
              if(targetAngles_1[i][1] < currentAngles_1[1]){
                currentAngles_1[1] -= increments_1[1];
              } else if(targetAngles_1[i][1] > currentAngles_1[1]) {
                currentAngles_1[1] += increments_1[1];
              }

              if(targetAngles_2[i][0] < currentAngles_2[0]){
                currentAngles_2[0] -= increments_2[0];
              } else if(targetAngles_2[i][0] > currentAngles_2[0]) {
                currentAngles_2[0] += increments_2[0];
              }

              if(targetAngles_2[i][1] < currentAngles_2[1]){
                currentAngles_2[1] -= increments_2[1];
              } else if(targetAngles_2[i][1] > currentAngles_2[1]) {
                currentAngles_2[1] += increments_2[1];
              }

//              Serial.print(currentAngles[1]);
//              Serial.print(" ");
              
  
              // Set the new pulse width
              
              _rightDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _rightDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _rightDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _rightDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _rightDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _rightDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _rightDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1]));

//              ---
              _leftDriver.setPWM(0, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(1, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(2, 0, _angleToPulse(currentAngles_1[1]));
              
              _leftDriver.setPWM(4, 0, _angleToPulse(currentAngles_2[0]));
              _leftDriver.setPWM(5, 0, _angleToPulse(currentAngles_2[1]));
              _leftDriver.setPWM(6, 0, _angleToPulse(currentAngles_2[1]));

              _leftDriver.setPWM(8, 0, _angleToPulse(currentAngles_1[0]));
              _leftDriver.setPWM(9, 0, _angleToPulse(currentAngles_1[1]));
              _leftDriver.setPWM(10, 0, _angleToPulse(currentAngles_1[1])); 
          }
      }
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
//      Serial.println(currentAngles_1[0]);
//      delay(1000);
    }

    // Switch lifted leg and repeat
//    XliftedLeg = (XliftedLeg + 1) % XnumLegs;
}
