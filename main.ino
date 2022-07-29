#include "test.h"

stepper stepper1(3, 4, 5, 6, 1500);
stepper stepper2(47, 49, 51, 53, 1500);

const int numOfSteppers = 2;

stepper arr1[numOfSteppers] = {stepper1, stepper2};
int arr2[numOfSteppers] = {0, 0};

String extractUserInput(){
  String userInputString = "";
  if (Serial.available() != 0) {
    int bufferLength = Serial.available();
    for (bufferLength; bufferLength>0; bufferLength--){
      int newValue = Serial.read();
        if (newValue != 10){
          userInputString = userInputString + (String(char(newValue)));
        }
    }
  }
  return userInputString;
}

void setup() {
  Serial.begin(9600);
  pinMode(52, INPUT);
  pinMode(50, INPUT);
  pinMode(48, INPUT);
}

void loop() {
 if (Serial.available() != 0){
    delay(30);
    String userInputString = extractUserInput();
    int endindex = userInputString.indexOf(":");
    int targetMotor = (userInputString.substring(0, endindex)).toInt();
    int MotorInstruction = (userInputString.substring(endindex+1, userInputString.length() )).toInt();
    
    arr2[targetMotor] = MotorInstruction;
  }

  if (digitalRead(52) == HIGH){
    arr2[0] = arr2[0] + 1;
    delay(2);
  }
  if (digitalRead(50) == HIGH){
    arr2[0] = arr2[0] - 1;
    delay(2);
  }
  if (digitalRead(48) == HIGH){
    arr2[1] = arr2[1] + 1;
    delay(2);
  }

  for (int i=0; i<8; i++){
    for (int j=0; j<numOfSteppers; j++){
      if (arr2[j] > 0){
        arr1[j].Ministep();
        if (i == 7){arr2[j] = arr2[j] - 1;}
      }
      else if (arr2[j] < 0){
        arr1[j].Backministep();
        if (i == 7){arr2[j] = arr2[j] + 1;}
      }
      else{
        arr1[j].turnOFF();
      }
    }
    delayMicroseconds(2000); 
  }
}
