#include "Ultrasonic.h"
#include <LiquidCrystal.h>

Ultrasonic ultrasonic(6, 7);  // Trig et Echo

// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(27, 26, 25, 23, 24, 22);

int buttonPin = 8;  // le bouton = pin 8
bool buttonState = false;
const int MOTOR_PIN_RIGHT = 3;            // moteur de droite
const int MOTOR_PIN_LEFT = 4;            // moteur de gauche

const int DISTANCE_THRESHOLD = 50;  // centimeters
float duration_us, distance_cm;
int dist;
int test;
int ledOn = 5;
String lcdVar;



void setup() {
  pinMode(buttonPin, INPUT);   // init de mon bouton
  Serial.begin(9600);          // initialize serial port
  pinMode(MOTOR_PIN_RIGHT, OUTPUT);  // set arduino pin to output mode
  pinMode(MOTOR_PIN_LEFT, OUTPUT);
  pinMode(ledOn, OUTPUT);
  lcd.begin(16, 2); // nb horisontal, nb colone
  lcd.setCursor(0, 0);
  lcd.clear();

}

void loop() {

  digitalWrite(ledOn, HIGH);

  // condition 1 : bouton appuyé ET état actuel du bouton éteint
  if (digitalRead(buttonPin) == HIGH && !buttonState) {
    digitalWrite(ledOn, LOW);
    // generate 10-microsecond pulse to TRIG pin
    lcdVar = "distance:" + String(ultrasonic.read()) + " cm";
    lcd.print(lcdVar);

    buttonState = true;

    while (true) {
      test += 1;
      if (test > 100 && digitalRead(buttonPin) == HIGH) {
        test = 0;
        digitalWrite(MOTOR_PIN_RIGHT, LOW);
        digitalWrite(MOTOR_PIN_LEFT, LOW);
        buttonState = !buttonState;
        digitalWrite(ledOn, HIGH);

        break;
      }

      dist = ultrasonic.read();

      switch (dist < DISTANCE_THRESHOLD) {
        case true :
        digitalWrite(MOTOR_PIN_RIGHT, LOW);
        digitalWrite(MOTOR_PIN_LEFT, HIGH);
        delay(700);
        default :
        digitalWrite(MOTOR_PIN_RIGHT, HIGH);
        digitalWrite(MOTOR_PIN_LEFT, HIGH);
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
    digitalWrite(MOTOR_PIN_RIGHT, LOW);
    digitalWrite(MOTOR_PIN_LEFT, LOW);
    buttonState = !buttonState;
    delay(500);
  }
}