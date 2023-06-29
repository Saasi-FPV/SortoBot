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

//MagnetPin
#define magnet 32



//StepperCalc
#define stpsPerDeg 134
#define stpsPerMMX 133//4267
#define stpsPerMMZ 160
//Velocety
#define cmaxSpeed 20     // mm/s
#define cmaxAccel 100   // mm/s^2
#define xmaxSpeed 15     // mm/s
#define xmaxAccel 50   // mm/s^2
#define zmaxSpeed 20     // mm/s
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
void serialCordIn();
void runOnPos();
void onPos();
void manuelControll();
void debug();



//Global Variables
int axSelect = 0;
int inX = 0;
int inC = 0;
int inZ = 0;
int inM = 0;
bool flagOnPos = 0;

void setup() {
  cMot.setMaxSpeed(cmaxSpeed * stpsPerDeg);
  cMot.setAcceleration(cmaxAccel * stpsPerDeg);
  xMot.setMaxSpeed(xmaxSpeed * stpsPerMMX);
  xMot.setAcceleration(xmaxAccel * stpsPerMMX);
  zMot.setMaxSpeed(zmaxSpeed * stpsPerMMZ);
  zMot.setAcceleration(zmaxAccel * stpsPerMMZ);

  pinMode(magnet, OUTPUT);

  rot1.begin();

  Serial.begin(115200);

}

void loop() {
  
  serialCordIn();

  if(inM == 2){
    digitalWrite(magnet, 1);
    runOnPos();
    onPos();
  }
  if(inM == 1){
    digitalWrite(magnet, 0);
    runOnPos();
    onPos();
  }
  if(inM >= 3){
    manuelControll();
  }





  
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

void serialCordIn(){
  
  if (Serial.available()) {

    flagOnPos = 0;


    String input = Serial.readStringUntil('\n');  // Eingabe bis zur Zeilenumbruch-Zeichen ('\n') lesen
    input.trim();  // Führende und nachfolgende Leerzeichen entfernen

    // Variablen für die Werte initialisieren
    int x = 0;
    int c = 0;
    int z = 0;
    int m = 0;

    // Eingabe aufteilen und Werte extrahieren
    int xPos = input.indexOf('x');
    int cPos = input.indexOf('c');
    int zPos = input.indexOf('z');
    int mPos = input.indexOf('m');

    if (xPos != -1 && cPos != -1 && zPos != -1 && mPos != -1) {
      // Extrahieren der Werte als Teilstrings
      String xValue = input.substring(xPos + 1, cPos);
      String cValue = input.substring(cPos + 1, zPos);
      String zValue = input.substring(zPos + 1, mPos);
      String mValue = input.substring(mPos + 1);

      // Konvertieren der Teilstrings in Ganzzahlen
      x = xValue.toInt();
      c = cValue.toInt();
      z = zValue.toInt();
      m = mValue.toInt();
    }

    // Überprüfen, ob die Werte erfolgreich extrahiert wurden
    if (x != 0 && c != 0 && z != 0 && m != 0) {
      // Hier kannst du den Code ausführen, der die Werte verwendet
      // Zum Beispiel: Serial.print(x);, Serial.print(y); usw.
      inX = x;
      inC = c;
      inZ = z;
      inM = m;
      /*
      Serial.print("inX "); Serial.println(inX);
      Serial.print("inC "); Serial.println(inC);
      Serial.print("inZ "); Serial.println(inZ);
      Serial.print("inM "); Serial.println(inM);
      */
    }
  }
}

void runOnPos(){

  coord.selectAx('x');
  coord.setAxAbs(inX);
  xMot.moveTo(coord.getAxAbs('x')*-stpsPerMMX);
  coord.selectAx('c');
  coord.setAxAbs(inC);
  cMot.moveTo(coord.getAxAbs('c')*-stpsPerDeg);
  coord.selectAx('z');
  coord.setAxAbs(inZ);
  zMot.moveTo(coord.getAxAbs('z')*-stpsPerMMZ);

}


void onPos(){

  int flagcounteronPos = 0;

  if(coord.getAxAbs('x')*-stpsPerMMX == xMot.currentPosition()){
    flagcounteronPos++;
  }

  if(coord.getAxAbs('c')*-stpsPerDeg == cMot.currentPosition()){
    flagcounteronPos++;
  }

  if(coord.getAxAbs('z')*-stpsPerMMZ == zMot.currentPosition()){
    flagcounteronPos++;
  }

  if(flagcounteronPos == 3 && flagOnPos == 0){
    Serial.println("onPosition");
    flagOnPos = 1;
  }


}



unsigned long previousMillisSW = 0; 
const long intervalSW = 1000;
void manuelControll(){

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
      xMot.moveTo(coord.getAxAbs('x')*-stpsPerMMX);
    break;

    case 2:
      coord.selectAx('c');
      coord.addAxAbs(rot1.getPos());
      cMot.moveTo(coord.getAxAbs('c')*-stpsPerDeg);
    break;

    case 3:
      coord.selectAx('z');
      coord.addAxAbs(rot1.getPos());
      zMot.moveTo(coord.getAxAbs('z')*-stpsPerMMZ);
    break;
  }  
  coord.update(rot1.getPos());
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

    Serial.print("XAxSoll: ");
    Serial.println(coord.getAxAbs('x'));
    Serial.print("CAxSoll: ");
    Serial.println(coord.getAxAbs('c'));
    Serial.print("ZAxSoll: ");
    Serial.println(coord.getAxAbs('z'));
    Serial.print("M: ");
    Serial.println(inM);


  }
}
