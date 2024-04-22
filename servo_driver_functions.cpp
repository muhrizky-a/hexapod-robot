#include "servo_driver_class.h"

void XServoDriver::initDriver(Adafruit_PWMServoDriver right, Adafruit_PWMServoDriver left)
{
  Serial.println("init servo drivers");
  rightDriver = right;
  leftDriver = left;

  rightDriver.begin();
  rightDriver.setPWMFreq(60); // Set PWM frequency (max: 1600)
  leftDriver.begin();
  leftDriver.setPWMFreq(60); // Set PWM frequency (max: 1600)
}

//Adafruit_PWMServoDriver XServoDriver::getRightDriver(){
//  return rightDriver;
//}
//
//Adafruit_PWMServoDriver XServoDriver::getLeftDriver(){
//  return leftDriver;
//}
//  
int XServoDriver::angleToPulse(int angle)
{
  return map(angle, 0, 180, SERVOMIN, SERVOMAX); // Adjust SERVOMIN and SERVOMAX as needed
}

// ----------
// PUBLIC FUNCTIONS
void XServoDriver::afterInit()
{
  rightDriver.setPWM(4, 0, angleToPulse(45));
  rightDriver.setPWM(5, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
  rightDriver.setPWM(6, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
}

void XServoDriver::stand()
{
  Serial.println("stand");
  for (int i = 0; i < 12; i++)
  {
    rightDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
    leftDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
  }
}

void XServoDriver::sit()
{
  Serial.println("sit");
  for (int i = 0; i <= 8; i += 4)
  {
    rightDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
    leftDriver.setPWM(i, 0, angleToPulse(STAND_ANGLE));
  }

  // Loop for servo on channel starts in 0, 4, 8
  for (int i = 0; i <= 8; i += 4)
  {
    // This will control servo on channel 1,2, then 5,6, then 9, 10
    rightDriver.setPWM(i + 1, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
    rightDriver.setPWM(i + 2, 0, angleToPulse(LIFTED_RIGHT_LEG_ANGLE));
    leftDriver.setPWM(i + 1, 0, angleToPulse(LIFTED_LEFT_LEG_ANGLE));
    leftDriver.setPWM(i + 2, 0, angleToPulse(LIFTED_LEFT_LEG_ANGLE));
  }
}

void XServoDriver::gripperLift()
{
  Serial.println("gripper arm lifted");
  rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(0));
}

void XServoDriver::gripperDown()
{
  Serial.println("gripper arm down");
  rightDriver.setPWM(GRIPPER_ARM_CHANNEL, 0, angleToPulse(180));
}

void XServoDriver::gripperOpen()
{
  rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(0));
}

void XServoDriver::gripperClose()
{
  rightDriver.setPWM(GRIPPER_CHANNEL, 0, angleToPulse(90));
}

void XServoDriver::moveTripod(Adafruit_PWMServoDriver *pwmPtr, int tripodIndex, int coxaAngle, int femurTibiaAngle) {
    pwmPtr->setPWM(tripodIndex, 0, angleToPulse(coxaAngle));
    pwmPtr->setPWM(tripodIndex + 1, 0, angleToPulse(femurTibiaAngle));
    pwmPtr->setPWM(tripodIndex + 2, 0, angleToPulse(femurTibiaAngle));
}

void XServoDriver::tripodGait()
{
  unsigned long currentTime = millis();
  if (currentTime - startTime >= duration)
  {
    Serial.print("step: ");
    Serial.print(legStep);
    Serial.println(" out of 3");
//    int offset = 1, inc = 4;

    if (legStep == 0) {
      moveTripod(&rightDriver, 0, 90, LIFTED_RIGHT_LEG_ANGLE);
      moveTripod(&leftDriver, 4, 90, LIFTED_LEFT_LEG_ANGLE);
      moveTripod(&rightDriver, 8, 90, LIFTED_RIGHT_LEG_ANGLE);

      moveTripod(&leftDriver, 0, 70, 90);
      moveTripod(&rightDriver, 4, 110, 90);
      moveTripod(&leftDriver, 8, 70, 90);
    } else if (legStep == 1)     {
      moveTripod(&rightDriver, 0, 70, 90);
      moveTripod(&leftDriver, 4, 110, 90);
      moveTripod(&rightDriver, 8, 70, 90);

      moveTripod(&leftDriver, 0, 90, LIFTED_LEFT_LEG_ANGLE);
      moveTripod(&rightDriver, 4, 90, LIFTED_RIGHT_LEG_ANGLE);
      moveTripod(&leftDriver, 8, 90, LIFTED_LEFT_LEG_ANGLE);
    } else if (legStep == 2) {
      moveTripod(&rightDriver, 0, 110, 90);
      moveTripod(&leftDriver, 4, 70, 90);
      moveTripod(&rightDriver, 8, 110, 90);

      moveTripod(&leftDriver, 0, 110, 90);
      moveTripod(&rightDriver, 4, 70, 90);
      moveTripod(&leftDriver, 8, 110, 90);
    }

    if (legStep > 1)
    {
      legStep = 0;
    }
    else
    {
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
