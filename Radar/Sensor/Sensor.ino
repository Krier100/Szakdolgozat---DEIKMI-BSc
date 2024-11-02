#include <Servo.h>

Servo myservo;  // szervó objektum létrehozása
long distance;

float checkdistance() {
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  float distance = pulseIn(A0, HIGH) / 58.00;
  delay(10);
  return distance;
}

void setup() {
  Serial.begin (9600); //port

  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  
  //szervó inicializálása
  myservo.attach(A2);  //A2-re vam csatlakoztatva
}

void loop() {
  for(int angle = 0; angle <= 180; angle += 1) { // forgatás 0-tól 180 fokig (jobbról balra)
    myservo.write(angle);              // szervó pozíció beállítása
    delay(15);                         
    distance = checkdistance();        //mérés
    
    //kommunikáció a Processinggel
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    delay(15);                        //szenzor stabilizálása
  }
  for(int angle = 180; angle >= 0; angle -= 1) { //forgatás  visszafele
    myservo.write(angle);              
    delay(15);                         
    distance = checkdistance();        
    
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    
    delay(15);
  }
}
