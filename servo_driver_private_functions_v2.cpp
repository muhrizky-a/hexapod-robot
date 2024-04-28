#include "servo_driver_class_v2.h"

// BEGIN PRIVATE FUNCTIONS
// ----------
int XServoDriverV2::_angleToPulse(int angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);  // Adjust SERVOMIN and SERVOMAX as needed
}
// ----------
// END PRIVATE FUNCTIONS
