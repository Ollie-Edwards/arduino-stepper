// LED.cpp
#include "test.h"

stepper::stepper(int pin1, int pin2, int pin3, int pin4, int phaseDelay) {
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
  
  float stepsPerRotation = 512;
  float currentPosition = 0;
  int _phaseDelay = 1200;
  int currentPhase = 0; // 
  
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);
  pinMode(_pin4, OUTPUT);
}

void stepper::ClearPosition(){
  float currentPosition = 0;
}

void stepper::turnOFF() {
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
  digitalWrite(_pin3, LOW);
  digitalWrite(_pin4, LOW);
}

void stepper::TurnByDegrees(int Degrees){
  int steps = 0;
  steps = Degrees / degreesPerStep;
//  Serial.println(String(targetMotor)+":"+String(currentPosition);
//  
  Step(steps);
}

void stepper::TurnTo(int Targetposition){
  if (Targetposition >= lowerLimit and Targetposition <= upperLimit){
    Targetposition = Targetposition % 360; // if targetpos is 360 mod it back to 1
    
    if (Targetposition > currentPosition){
      while (Targetposition > currentPosition){
        Step(1);
      }
    }
    else{
      while (Targetposition < currentPosition){
        Step(-1);
      } 
    }
  }else{
    Serial.println("limit broken");
  }
}

void stepper::Step(int num) {
  if (num > 0){
      for (int i=0; i<7; i++){
        digitalWrite(_pin1, pin1sequence[i]);
        digitalWrite(_pin2, pin2sequence[i]);
        digitalWrite(_pin3, pin3sequence[i]);
        digitalWrite(_pin4, pin4sequence[i]);
        delayMicroseconds(1200);
       }
       currentPosition = currentPosition + degreesPerStep;
  }
  else{
    for (int i=7; i>0; i--){
      digitalWrite(_pin4, pin4sequence[i]);
      digitalWrite(_pin3, pin3sequence[i]);
      digitalWrite(_pin2, pin2sequence[i]);   
      digitalWrite(_pin1, pin1sequence[i]);
      delayMicroseconds(1200);
    }
    if (currentPosition < 0){currentPosition=currentPosition+360;}
    currentPosition = currentPosition - degreesPerStep;
  }
  Serial.println(currentPosition);
  turnOFF();
}
