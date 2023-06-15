#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "Arduino.h"

class RotaryEncoder{
  private:
    int outputA;
    int outputB;
    int outputSW;
    int counter;
    int aState;
    int aLastState;
    
    bool buttonState;
    bool lastButtonState;
    unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


  public:
    RotaryEncoder(int outputAin, int outputBin, int outputSWin){
      outputA = outputAin;
      outputB = outputBin;
      outputSW = outputSWin;
    }

    void begin();
    void run();
    int getPos();
    bool getButton();
};


#endif
