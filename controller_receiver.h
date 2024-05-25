#include <WiFi.h>
#include <esp_now.h>

#include "servo_driver_class_v2.h"
XServoDriverV2 servoDriver;

typedef struct joystickStruct {
  int leftX = 0, leftY = 0, rightX = 0, rightY = 0;
  int gripperArmLifted = 0, gripperArmDowned = 0;
  int gripperClosed = 0, gripperOpened = 0;
} joystickStruct;

joystickStruct receivedJoystickData;

// operation remote
unsigned long lastTimeToGrip = 0;
unsigned long lastTime = 0;
unsigned long lastTimeLean = 0;

//// Define COMMANDS
const int FORWARD_COMMAND = 1;
const int BACKWARD_COMMAND = 2;
const int TURN_LEFT_COMMAND = 3;
const int TURN_RIGHT_COMMAND = 4;

const int LEAN_FRONT_COMMAND = 5;
const int LEAN_BACK_COMMAND = 6;
const int MOVE_LEFT_COMMAND = 7;
const int MOVE_RIGHT_COMMAND = 8;

const int GRIPPER_LIFT_COMMAND = 11;
const int GRIPPER_DOWN_COMMAND = 12;
const int GRIPPER_OPEN_COMMAND = 13;
const int GRIPPER_CLOSE_COMMAND = 14;

typedef void (*GeneralMessageFunction) (int);

int getCommand(joystickStruct data){
  if(data.rightX < 100){
    return BACKWARD_COMMAND;
  }
  if(data.rightX > 4000){
    return FORWARD_COMMAND;
    
  }
  if(data.rightY < 100){
    return TURN_LEFT_COMMAND;
  }
  if(data.rightY > 4000){
    return TURN_RIGHT_COMMAND;
  }

  if(data.leftX < 100){
    return LEAN_BACK_COMMAND;
  }
  if(data.leftX > 4000){
    return LEAN_FRONT_COMMAND;
    
  }
  if(data.leftY < 100){
    return MOVE_LEFT_COMMAND;
  }
  if(data.leftY > 4000){
    return MOVE_RIGHT_COMMAND;
  }

  if(data.gripperArmLifted){
    return GRIPPER_LIFT_COMMAND;
  }
  if(data.gripperArmDowned){
    return GRIPPER_DOWN_COMMAND;
  }

  if(data.gripperOpened){
    return GRIPPER_OPEN_COMMAND;
  }
  if(data.gripperClosed){
    return GRIPPER_CLOSE_COMMAND;
  }
  
  return 0;
}

void initWifiReceiver(){
  WiFi.mode(WIFI_STA);
  Serial.print("ESP Board MAC Address:  ");

  // Mac Address ESP32 Fahri: 98:CD:AC:0B:F5:D5
  Serial.println(WiFi.macAddress());
}

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  int slowDuration = 500;
  int fastDuration = 250;

  if ((millis() - lastTime) > 10) {
    memcpy(&receivedJoystickData, incomingData, sizeof(receivedJoystickData));
    Serial.print("leftX: ");
    Serial.print(receivedJoystickData.leftX);
    Serial.print(", leftY: ");
    Serial.print(receivedJoystickData.leftY);
    Serial.print(", rightX: ");
    Serial.print(receivedJoystickData.rightX);
    Serial.print(", rightY: ");
    Serial.print(receivedJoystickData.rightY);
    Serial.println();
    Serial.print("gripperArmLifted: ");
    Serial.print(receivedJoystickData.gripperArmLifted);
    Serial.print(", gripperArmDowned: ");
    Serial.print(receivedJoystickData.gripperArmDowned);
    Serial.println();
  
    int command = getCommand(receivedJoystickData);
  
    if(command == FORWARD_COMMAND){
      servoDriver.setStepDuration(fastDuration);
      servoDriver.setLegCommand(FORWARD_COMMAND);

      servoDriver.forwardTripodGait();
    }
    if(command == BACKWARD_COMMAND){
      servoDriver.setStepDuration(fastDuration);
      servoDriver.setLegCommand(BACKWARD_COMMAND);
      
      servoDriver.backwardTripodGait();
    }
    if(command == TURN_LEFT_COMMAND){
      servoDriver.setStepDuration(fastDuration);
      servoDriver.setLegCommand(TURN_LEFT_COMMAND);

      servoDriver.turnLeftTripodGait(); 
    }
    if (command == TURN_RIGHT_COMMAND){
      servoDriver.setStepDuration(fastDuration);
      servoDriver.setLegCommand(TURN_RIGHT_COMMAND);
      
      servoDriver.turnRightTripodGait();
    }
  
    if (command == LEAN_FRONT_COMMAND){
      servoDriver.setStepDuration(slowDuration);
      servoDriver.setLegCommand(LEAN_FRONT_COMMAND);
      
//      servoDriver.leanToFrontSit();  
//      servoDriver.leanToFront();  
      servoDriver.forwardDongakTripodGait();  
    }
    if (command == MOVE_LEFT_COMMAND){
      servoDriver.setStepDuration(fastDuration);
      servoDriver.setLegCommand(MOVE_LEFT_COMMAND);
      
//      servoDriver.moveLeftTripodGait();
      servoDriver.moveLeftStableTripodGait();
    }
    if (command == MOVE_RIGHT_COMMAND){
      servoDriver.setStepDuration(fastDuration);
      servoDriver.setLegCommand(MOVE_RIGHT_COMMAND);
      
//      servoDriver.moveRightTripodGait();
      servoDriver.moveRightStableTripodGait();
    }
    if (command == LEAN_BACK_COMMAND){
      servoDriver.setStepDuration(slowDuration);
      servoDriver.setLegCommand(LEAN_BACK_COMMAND);
      
      servoDriver.moveLeftClimb90TripodGait();
    }
  
    if (command == GRIPPER_LIFT_COMMAND){
//      servoDriver.gripperClose();
//      lastTimeToGrip++;
//      Serial.print("lastTimeToGrip: ");
//      Serial.println(lastTimeToGrip);
//      
//      if(lastTimeToGrip > 5){
        servoDriver.gripperLift();
//        lastTimeToGrip = 0;
//      }
    }
    if (command == GRIPPER_DOWN_COMMAND){
//      lastTimeToGrip = 0;
      servoDriver.gripperDown();
//      delay(1000);
//      servoDriver.gripperOpen();
    }  
    if (command == GRIPPER_OPEN_COMMAND){
      servoDriver.gripperOpen();
    }
    if (command == GRIPPER_CLOSE_COMMAND){
      servoDriver.gripperClose();
    }  
    
    lastTime = millis();
  }
}

// current mac address receiver: 
void initESPNOW(){
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  Serial.println("Initializing ESP-NOW...");
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("Registering ESP-NOW complete.");
}
