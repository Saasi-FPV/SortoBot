// Pin-Definitionen
#define motorIn1 8
#define motorIn2 9
#define motorPWM 10
#define sensorPin 7
int i = 0;
// Anfahrzeit in Millisekunden
const int rampTime = 3000;
float rampTime2 = 1;

void setup() 
{
  // Initialisierung der Pins
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorPWM, OUTPUT);
  pinMode(sensorPin, INPUT);
  
  // Motorantrieb aus
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);

  Serial.begin(115200);

  
}

bool flag;

void loop() {
  // Motorantrieb ein
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);

  // Ramp-up: Motor-Geschwindigkeit langsam erhöhen
 
  {
    analogWrite(motorPWM, 153);
    
  }
  
  // Warten, bis ein Objekt erkannt wird
  while (digitalRead(sensorPin) == LOW){
    analogWrite(motorPWM, 0);
    delay(100);
    i= 0;


    if(Serial.available()){
      String inputString = Serial.readString();
      inputString.trim();
      if(flag == 0 && inputString == "request"){
        Serial.println("1");
        flag = 1;
      
    }
    }
    

  } 

  flag = 0;
}
  
  // Ramp-down: Motor-Geschwindigkeit langsam verringern
 
  
  // Motorantrieb aus
  //digitalWrite(motorIn1, LOW);
  //digitalWrite(motorIn2, LOW);
