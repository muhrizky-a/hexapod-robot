#ifndef XCONTROLLER_RECEIVER_H
#define XCONTROLLER_RECEIVER_H

class XControllerReceiver {
   private:
    
    

    // Received Commands
    int _command = 0;
    unsigned long _lastTime = 0;
    
    // Functions
    

   public:
    // Commands
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
    void receiveSerialData(GeneralMessageFunction);

};

#endif


// BEGIN PRIVATE FUNCTIONS
// ----------
void XControllerReceiver::receiveSerialData(GeneralMessageFunction response){
//  if (Serial1.available()) {
//    _command = Serial1.read();
//    
//    Serial.println("_command1: ");
//    Serial1.println(_command);
////    response(_command);
//  }

  if (Serial.available()) {
    _command = Serial.read();
    
    if ((millis() - _lastTime) > 10) {
      Serial.print("change: ");
      Serial.println(_command);

      response(_command);
     _lastTime = millis();
     
    } 
  }
}
