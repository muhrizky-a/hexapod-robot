#include "servo_driver_class_v2.h"

// BEGIN PUBLIC FUNCTIONS
// ----------
void XServoDriverV2::initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left) {
    Serial.println("init servo drivers");
    rightDriver = right;
    leftDriver = left;

    rightDriver.begin();
    rightDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
    leftDriver.begin();
    leftDriver.setPWMFreq(60);  // Set PWM frequency (max: 1600)
}
void XServoDriverV2::afterInit() {
    Serial.println("after init v2");
    for (int i = 0; i <= 8; i += 4) {
        rightDriver.setPWM(i, 0, angleToPulse(70));
    }
}

void XServoDriverV2::stand() {
    Serial.println("stand");
    for (int i = 0; i < 12; i++) {
        rightDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
        leftDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
    }
    
    currentAngles_1[0] = STAND_ANGLE;
    currentAngles_1[1] = STAND_ANGLE;
    currentAngles_2[0] = STAND_ANGLE;
    currentAngles_2[1] = STAND_ANGLE;
}

void XServoDriverV2::sit() {
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

void XServoDriverV2::gripperLift() {
    Serial.println("gripper arm lifted");
    rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(0));
}

void XServoDriverV2::gripperDown() {
    Serial.println("gripper arm down");
    rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(180));
}

void XServoDriverV2::gripperOpen() {
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(135));
}

void XServoDriverV2::gripperClose() {
    rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(0));
}
const int XnumLegs = 6;
//int XstepTime = 1000;  // Time in milliseconds for each step cycle
int XliftedLeg = 0;    // Currently lifted leg index (0-5)

const int Xduration = 200;  // Adjust duration based on desired walking speed
const int XstepInterval = 50;  // Interval between steps (in milliseconds)
long XpreviousMillis = 0;

void XServoDriverV2::forwardTripodGait() {
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
              
              rightDriver.setPWM(0, 0, angleToPulse(currentAngles_1[0]));
              rightDriver.setPWM(1, 0, angleToPulse(currentAngles_1[1]));
              rightDriver.setPWM(2, 0, angleToPulse(currentAngles_1[1]));
              
              rightDriver.setPWM(4, 0, angleToPulse(currentAngles_2[0]));
              rightDriver.setPWM(5, 0, angleToPulse(currentAngles_2[1]));
              rightDriver.setPWM(6, 0, angleToPulse(currentAngles_2[1]));

              rightDriver.setPWM(8, 0, angleToPulse(currentAngles_1[0]));
              rightDriver.setPWM(9, 0, angleToPulse(currentAngles_1[1]));
              rightDriver.setPWM(10, 0, angleToPulse(currentAngles_1[1]));

//              ---
              leftDriver.setPWM(0, 0, angleToPulse(currentAngles_1[0]));
              leftDriver.setPWM(1, 0, angleToPulse(currentAngles_1[1]));
              leftDriver.setPWM(2, 0, angleToPulse(currentAngles_1[1]));
              
              leftDriver.setPWM(4, 0, angleToPulse(currentAngles_2[0]));
              leftDriver.setPWM(5, 0, angleToPulse(currentAngles_2[1]));
              leftDriver.setPWM(6, 0, angleToPulse(currentAngles_2[1]));

              leftDriver.setPWM(8, 0, angleToPulse(currentAngles_1[0]));
              leftDriver.setPWM(9, 0, angleToPulse(currentAngles_1[1]));
              leftDriver.setPWM(10, 0, angleToPulse(currentAngles_1[1]));

              
          }
      }
      // Set the final position;
      Serial.println("");
      Serial.println("=final=");
//      Serial.println(currentAngles_1[0]);
//      delay(1000);
    }
}



void XServoDriverV2::XdoGait() {
  // Calculate the number of steps
    unsigned long steps = Xduration / XstepInterval;  // Assuming interval ms per step
    
    // X6
    int coxaAngle = 90;
    int femurTibiaAngle = 90;
    int targetPulseCoxa = angleToPulse(coxaAngle);
    int targetPulseFemurTibia = angleToPulse(femurTibiaAngle);

    // X6Get the current pulse width
    int currentPulseCoxa = rightDriver.getPWM(XliftedLeg);
    int currentPulseFemurTibia = rightDriver.getPWM(XliftedLeg + 1);

    // X6 Calculate the increment value for each step
    int incrementCoxa = (targetPulseCoxa - currentPulseCoxa) / steps;
    int incrementFemurTibia = (targetPulseFemurTibia - currentPulseFemurTibia) / steps;

    
    unsigned long startTime = millis();
    // Count to Xduration (0-1000)
    while (millis() - startTime <= Xduration) {
        // Check if it's time to move to the next step (XstepInterval is 20, so stepping 0,20,40,80,...,1000)
        if (millis() - XpreviousMillis >= XstepInterval) {
            // Update the previousMillis for the next step
            XpreviousMillis = millis();

            // Increment the current pulse width
            currentPulseCoxa += incrementCoxa;
            currentPulseFemurTibia += incrementFemurTibia;

            // Set the new pulse width
            rightDriver.setPWM(XliftedLeg, 0, currentPulseCoxa);
            rightDriver.setPWM(XliftedLeg + 1, 0, currentPulseFemurTibia);
            rightDriver.setPWM(XliftedLeg + 2, 0, currentPulseFemurTibia);
        }
    }

    // Set the final position
    rightDriver.setPWM(XliftedLeg, 0, targetPulseCoxa);
    rightDriver.setPWM(XliftedLeg + 1, 0, targetPulseFemurTibia);
    rightDriver.setPWM(XliftedLeg + 2, 0, targetPulseFemurTibia);
    
    // Switch lifted leg and repeat
    XliftedLeg = (XliftedLeg + 1) % XnumLegs;
}
