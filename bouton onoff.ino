/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor-led
 */

// constants won't change
const int TRIG_PIN = 6; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = 7; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int LED_PIN  = 3; // Arduino pin connected to LED's pin
const int BTN_START = 2; // setup le bouton on/off
const int DISTANCE_THRESHOLD = 200; // centimeters
int interrupteur = LOW;       //valeur de l'interrupeteur
int toggle = 0;             //valeur pour changement d'état du bouton
int buttonState = 0;        //etat fugitif du bouton      

// variables will change:
float duration_us, distance_cm;  

void setup() {
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  pinMode(LED_PIN, OUTPUT);  // set arduino pin to output mode
  pinMode(BTN_START, INPUT);  // set the btn to input

}

void loop() {
  buttonState = digitalRead(BTN_START);

  //On regarde si le bouton est pressé
  if (buttonState == HIGH) {    
    //on regarde si il y a un changement d'état
    if (toggle == 1) {
      // on change l'état du bouton
      interrupteur=!interrupteur;
      // on reinitialise le toggle
      toggle=0;
      // on affiche l'état de l'interupteur virtuel sur la led

      // generate 10-microsecond pulse to TRIG pin
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);

      // measure duration of pulse from ECHO pin
      duration_us = pulseIn(ECHO_PIN, HIGH);
      // calculate the distance
      distance_cm = 0.050 * duration_us;

      if(distance_cm < DISTANCE_THRESHOLD)
        digitalWrite(LED_PIN, LOW); // turn on LED
      else
        digitalWrite(LED_PIN, HIGH);  // turn off LED

      // print the value to Serial Monitor
      Serial.print("distance: ");
      Serial.print(distance_cm);
      Serial.println(" cm");

      delay(500);

    }  
  }
  else {
    //le bouton n'est pas pressé, on active le toggle
    toggle=1;
      
  }
}
