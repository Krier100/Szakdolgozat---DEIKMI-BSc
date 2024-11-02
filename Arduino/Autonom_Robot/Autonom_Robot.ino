#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 8
#define ENA 5
#define ENB 6

int speed = 255; 
long distance1, distance2;
unsigned long previousMillis = 0; 
const long interval = 59;         // Szenzor olvasási intervallum
char command = ' ';
int manual_speed = 120;



void setup() {
  Serial.begin(9600);
  
  pinMode(A4, OUTPUT);         // First sensor trigger pin
  pinMode(A5, INPUT);          // First sensor echo pin
  pinMode(A1, OUTPUT);         // Second sensor trigger pin
  pinMode(A0, INPUT);          // Second sensor echo pin

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    distance2 = checkDistance(A4, A5);  // Measure distance from the first sensor - JOBB SZENZOR
    distance1 = checkDistance(A1, A0);  // Measure distance from the second sensor - BAL SZENZOR

    Serial.print(distance1); // bal
    Serial.print(" ");
    Serial.print(distance2); // jobb
    Serial.print(" ");
    Serial.print(command);
    Serial.println();
  }

  if (Serial.available()) {
    command = Serial.read();
    int value = 0;

    // Appon keresztul kapott command
    if (command == 'S') {
      value = Serial.parseInt();
    }

    // kapott command végrehajtása (EGYSZERRE CSAK EGY)
    switch (command) {
      case 'U':
        moveForward();
        break;
      case 'D':
        moveBackward();
        break;
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case 'S':
        speed = map(value, 0, 10, 0, 255);
        break;
      case 'B':
        stop();
        break;
      case 'F':
        keepDistance();  // "Szabályozó" mozgás függvénye
        break;
      default:
        stop();
        break;
    }
  }
}

void keepDistance() {
  while (command == 'F') {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    distance2 = checkDistance(A4, A5);  // Measure distance from the first sensor - JOBB SZENZOR
    distance1 = checkDistance(A1, A0);  // Measure distance from the second sensor - BAL SZENZOR

    Serial.print(distance1); // bal
    Serial.print(" ");
    Serial.print(distance2); // jobb
    Serial.print(" ");
    Serial.print(command);
    Serial.println();
  }
    if((distance1 - distance2) > 75 || (distance2 - distance1) > 75){
      continue;
    }
    else{
      if (distance1 <= 500 && (distance1 < distance2)) {
        turnRight();
        //delay(1);
        moveForward();
      } else if (distance2 <= 500 && (distance2 < distance1)) {
        turnLeft();
        //delay(1);
        moveForward();
      }else {
        moveForward();
      }
    }
    
    /*
    }else if(distance1 <= 20) {
      turnRight();
      delay(110);
      moveForward();
    } else if (distance2 <= 20) {
      turnLeft();
      delay(110);
      moveForward();
    } else if(distance1 <= 15) {
      turnRight();
      delay(130);
      moveForward();
    } else if (distance2 <= 15) {
      turnLeft();
      delay(130);
      moveForward();
    }else if(distance1 <= 10) {
      turnRight();
      delay(150);
      moveForward();
    } else if (distance2 <= 10) {
      turnLeft();
      delay(150);
      moveForward();*/

    if (Serial.available()) {
      command = Serial.read(); // Ha uj command jon akkor lepjen ki
    }
  }
}

float checkDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  float distance = pulseIn(echoPin, HIGH) / 58.00;
  delay(10);  // Short delay to stabilize the measurement process
  return distance;
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //analogWrite(ENA, speed);
  analogWrite(ENA, manual_speed);
  

  digitalWrite(IN3, HIGH); //CHANGED FROM HIGH TO LOW FOR TEST PURPOSES - PUT HIGH BACK
  digitalWrite(IN4, LOW);
  analogWrite(ENB, manual_speed);
}

void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, manual_speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, manual_speed);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, manual_speed);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, manual_speed);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, manual_speed);

  digitalWrite(IN3, HIGH); //CHANGED FROM HIGH TO LOW FOR TEST PURPOSES - PUT HIGH BACK
  digitalWrite(IN4, LOW);
  analogWrite(ENB, manual_speed); 
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}