#include "RotaryEncoder.h"

void RotaryEncoder::begin(){
  counter = 0;
  aState = 0;
  aLastState = 0;
  buttonState = 0;
  lastButtonState = 0;


  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(outputSW, INPUT_PULLUP);
  aLastState = digitalRead(outputA);
}

void RotaryEncoder::run(){
  
  //Rot
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
   } 
  aLastState = aState; // Updates the previous state of the outputA with the current state

  
  
  
  //SW
  bool reading = !digitalRead(outputSW);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        buttonState = reading;
      }
    }
  }
  lastButtonState = reading;
}






int RotaryEncoder::getPos(){
  return(counter);
}

bool RotaryEncoder::getButton(){
  return (buttonState);
}
