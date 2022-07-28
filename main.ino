#include "test.h"

stepper led1(3, 4, 5, 6, 1500);
stepper led2(47, 49, 51, 53, 1500);

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
}

void loop() {
 if (Serial.available() != 0){
    delay(30);
    String userInputString = extractUserInput();
    led1.TurnTo(userInputString.toInt());
    led2.TurnTo(userInputString.toInt());
  }
 
}
