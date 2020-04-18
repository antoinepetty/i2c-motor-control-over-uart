#include <RMCS-220X.h>

/* Configure connected motors */
#define NUMBER_OF_MOTORS 2

int[NUMBER_OF_MOTORS] motorAddress = {0x15,0x16};


/* Array of all connected motors */
RMCS220X motor[NUMBER_OF_MOTORS];

// Incoming command
String inputString = ""; // a String to hold incoming data
int messagePart = 0; // Which part of the message is currently being read
// Incoming command parts
int motorNum = 0;
String command = "";
long commandValue = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUMBER_OF_MOTORS; i++) {
    motor[i].begin(motorAddress(i));
  }
}

void loop() {
  // Nothing in main loop, all controlled from SerialEvent
}

void writeToMotor(int motorIndex, String command, long value) {
  /*Serial.print("Writing\nMotor: ");
  Serial.println(motorIndex);
  Serial.print("Command: ");
  Serial.println(command);
  Serial.print("Value: ");
  Serial.println(value);*/
  if(command == "S"){
    motor[motorIndex].writeSpeed(value);
  }
  else if(command == "M"){
    motor[motorIndex].writeMaxSpeed(value);
  }
  else if(command == "D"){
    motor[motorIndex].writeSpeedDamping(value);
  }
  else if(command == "P"){
    motor[motorIndex].calibrateEncoderPositionInSteps(value);
  }
  else if(command == "G"){
    motor[motorIndex].goToPositionInSteps(value);
  }
  else if(command == "R"){
    motor[motorIndex].goToRelativePositionInSteps(value);
  }
  else if(command == "A"){
    motor[motorIndex].writeSpeedFeedbackGainTerm(value);
  }
  else if(command == "B"){
    motor[motorIndex].writePGainTerm(value);
  }
  else if(command == "C"){
    motor[motorIndex].writeIGainTerm(value);
  }
}

void readFromMotor(int motorIndex, String command) {
  /*Serial.print("Reading\nMotor: ");
  Serial.println(motorIndex);
  Serial.print("Command: ");
  Serial.println(command);*/
  long response = 0;
  if(command == "S"){
    response = motor[motorIndex].readSpeed();
  }
  else if(command == "M"){
    response = motor[motorIndex].readMaxSpeed();
  }
  else if(command == "D"){
    response = motor[motorIndex].readSpeedDamping();
  }
  else if(command == "P"){
    response = motor[motorIndex].readEncoderPositionInSteps();
  }
  else if(command == "G"){
    response = motor[motorIndex].readGoToPositionInSteps();
  }
  else if(command == "A"){
    response = motor[motorIndex].readSpeedFeedbackGainTerm();
  }
  else if(command == "B"){
    response = motor[motorIndex].readPGainTerm();
  }
  else if(command == "C"){
    response = motor[motorIndex].readIGainTerm();
  }
  Serial.println(String(response));
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar == ',' || inChar == '\n') {
      if (messagePart == 0) {
        // Motor number
        motorNum = inputString.toInt();
      }
      else if (messagePart == 1) {
        // Command
        command = inputString;
      }
      else if (messagePart == 2) {
        // Value
        commandValue = inputString.toInt(); // the toInt function actually returns a Long
      }
      if (inChar == '\n') {
        if(messagePart == 1){ 
          //If no value received to be written, this must be a read
          readFromMotor(motorNum, command);
        }
        else{
          writeToMotor(motorNum, command, commandValue);
        }
        messagePart = 0;
        motorNum = 0;
        command = "";
        commandValue = 0;
        inputString = "";
        break;
      }

      messagePart++;
      inputString = "";
    }
    else {
      inputString += inChar;
    }
  }
}
