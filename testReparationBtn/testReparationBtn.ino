#include "Ultrasonic.h"
Ultrasonic ultrasonic(6, 7);  // Trig et Echo

int buttonPin = 8;  // le bouton = pin 8
bool buttonState = false;
const int MOTOR_PIN = 3;            // moteur
const int DISTANCE_THRESHOLD = 50;  // centimeters
float duration_us, distance_cm;
int dist;
int test;


void setup() {
  pinMode(buttonPin, INPUT);   // init de mon bouton
  Serial.begin(9600);          // initialize serial port
  pinMode(MOTOR_PIN, OUTPUT);  // set arduino pin to output mode
}

void loop() {

  // condition 1 : bouton appuyé ET état actuel du bouton éteint
  if (digitalRead(buttonPin) == HIGH && !buttonState) {

    Serial.println("bouton on");
    // generate 10-microsecond pulse to TRIG pin

    buttonState = true;

    while (true) {
      test += 1;
      if (test > 100 && digitalRead(buttonPin) == HIGH) {
        test = 0;
        digitalWrite(MOTOR_PIN, LOW);
        buttonState = !buttonState;
        break;
      }

      dist = ultrasonic.read();

      if (dist < DISTANCE_THRESHOLD) {
        digitalWrite(MOTOR_PIN, LOW);  // turn on LED
      } else {
        digitalWrite(MOTOR_PIN, HIGH);  // turn off LED
      }
    }
    // print the value to Serial Monitor
    Serial.print("distance: ");
    Serial.print(ultrasonic.read());
    Serial.println(" cm");

    delay(500);
  }

  // condition 2 : bouton appuyé ET état actuel du bouton allumé
  if (digitalRead(buttonPin) == HIGH && buttonState) {
    Serial.println("bouton off");
    digitalWrite(MOTOR_PIN, LOW);
    buttonState = !buttonState;
    delay(500);
  }
}