#ifndef LED_h
#define LED_h

#include <Arduino.h>

class stepper {
  private:
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;

    int currentPhase = 0;

    // these arrays store the sequence of pin HIGH and LOW which turns
    // the motor in 8 phases, restulting in a turn of 1 step
//    int pin1sequence[8] = {0,1,1,1,1,1,0,0};
//    int pin2sequence[8] = {1,1,1,1,0,0,0,1};
//    int pin3sequence[8] = {1,1,0,0,0,1,1,1};
//    int pin4sequence[8] = {0,0,0,1,1,1,1,1};

    int pin1sequence[8] = {1,1,0,0,0,0,0,1};
    int pin2sequence[8] = {0,1,1,1,0,0,0,0};
    int pin3sequence[8] = {0,0,0,1,1,1,0,0};
    int pin4sequence[8] = {0,0,0,0,0,1,1,1};   

    // functions

  public:
    stepper(int pin1, int pin2, int pin3, int pin4, int phaseDelay);

    // variables
    int _phaseDelay; // the delay in microseconds between each of the phases of a single step
    float currentPosition;  // stores the current position in degrees of the motor
    int targetposition = 0; // stores the position in degrees the stepper motor must move to
    
    int lowerLimit = 0;
    int upperLimit = 225;
    
    // constants
    const float degreesPerStep = 0.703125; // the number of degrees moved in a single step
                                           
    // functions
    void TurnByDegrees(int Degrees); // relitive turn by a number of degrees  
    void TurnTo(int Targetposition);
    void ClearPosition();
    void Ministep(); // step by a given number of steps
    void Backministep();
    void turnOFF(); // turn all pins connected to the stepper motor to low
};

#endif
