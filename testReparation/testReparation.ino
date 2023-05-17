#include <SoftwareSerial.h>

const int MOTOR_PIN_RIGHT = 3;            // moteur de droite
const int MOTOR_PIN_LEFT = 4;  


void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN_RIGHT, OUTPUT);  // set arduino pin to output mode
  pinMode(MOTOR_PIN_LEFT, OUTPUT);
}

void loop() {
        digitalWrite(MOTOR_PIN_RIGHT, LOW);
      digitalWrite(MOTOR_PIN_LEFT, HIGH);
}