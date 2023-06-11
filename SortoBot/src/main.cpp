//Librarys
#include <Arduino.h>
#include <AccelStepper.h>
#include "RotaryEncoder.h"
#include "CoordinateSys.h"


//MotPins
#define cAxStep 13
#define cAxDir 14
#define xAxStep 27
#define xAxDir 26
#define zAxStep 25
#define zAxDir 33

//LimitPins
#define cLimit 111
#define xLimit 111
#define zLimit 111

//RotatryPins
#define ra1 5
#define rb1 18
#define rs1 19


//StepperCalc
#define stpsPerDeg 133.333333
#define stpsPerMMX 133//4267
#define stpsPerMMZ 160
//Velocety
#define cmaxSpeed 50     // mm/s
#define cmaxAccel 1000   // mm/s^2
#define xmaxSpeed 25     // mm/s
#define xmaxAccel 100   // mm/s^2
#define zmaxSpeed 50     // mm/s
#define zmaxAccel 1000   // mm/s^2


//StepperDeff
AccelStepper cMot(1, cAxStep, cAxDir);
AccelStepper xMot(1, xAxStep, xAxDir);
AccelStepper zMot(1, zAxStep, zAxDir);
//ControllDeff
RotaryEncoder rot1(ra1, rb1, rs1);
//CoordinatDeff
CoordinateSys coord;


//FuncDeff
void runMot();
void reverenz();
void debug();


//Global Variables
int axSelect = 0;

void setup() {
  cMot.setMaxSpeed(cmaxSpeed * stpsPerDeg);
  cMot.setAcceleration(cmaxAccel * stpsPerDeg);
  xMot.setMaxSpeed(xmaxSpeed * stpsPerMMX);
  xMot.setAcceleration(xmaxAccel * stpsPerMMX);
  zMot.setMaxSpeed(zmaxSpeed * stpsPerMMZ);
  zMot.setAcceleration(zmaxAccel * stpsPerMMZ);

  rot1.begin();

  Serial.begin(115200);

}

unsigned long previousMillisSW = 0; 
const long intervalSW = 1000;
void loop() {
  
  unsigned long currentMillisSW = millis();
  if(rot1.getButton() == 1 && (currentMillisSW - previousMillisSW >= intervalSW)){
    previousMillisSW = currentMillisSW;
    axSelect++;
    if(axSelect > 3){
      axSelect = 0;
    }
    Serial.print("Axe Selektion: ");
    Serial.println(axSelect);
  }
  


  switch(axSelect){
    case 0:
      coord.selectAx('n');
    break;
    
    case 1:
      coord.selectAx('x');
      coord.addAxAbs(rot1.getPos());
      xMot.moveTo(coord.getAxAbs('x')*stpsPerMMX);
    break;

    case 2:
      coord.selectAx('c');
      coord.addAxAbs(rot1.getPos());
      cMot.moveTo(coord.getAxAbs('c')*stpsPerDeg);
    break;

    case 3:
      coord.selectAx('z');
      coord.addAxAbs(rot1.getPos());
      zMot.moveTo(coord.getAxAbs('z')*stpsPerMMZ);
    break;
  }  

  
  
  
  
  coord.update(rot1.getPos());
  rot1.run();
  runMot();
  debug();
}

void runMot(){
  cMot.run();
  xMot.run();
  zMot.run();
}

void reverenz(){
  
}













unsigned long previousMillisdebug = 0; 
const long intervaldebug = 1000;
void debug(){

  unsigned long currentMillis = millis(); 
  if (currentMillis - previousMillisdebug >= intervaldebug) { 
    previousMillisdebug = currentMillis; 
    Serial.print("Counter: ");
    Serial.println(rot1.getPos());
    Serial.print("SW state: ");
    Serial.println(rot1.getButton());

    Serial.print("XSoll: ");
    Serial.println(coord.getAxAbs('x'));
    Serial.print("CSoll: ");
    Serial.println(coord.getAxAbs('c'));
    Serial.print("ZSoll: ");
    Serial.println(coord.getAxAbs('z'));






  }
}
