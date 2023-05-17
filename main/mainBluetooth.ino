#include "Ultrasonic.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

Ultrasonic ultrasonic(6, 7); // Trig et Echo

// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(27, 26, 25, 23, 24, 22);

const int MOTOR_PIN_RIGHT = 3; // moteur de droite
const int MOTOR_PIN_LEFT = 4;  // moteur de gauche

#define echoPin 6 // Echo Pin
#define trigPin 7 // Trigger Pin
long duration, distance;

String lcdVar;

SoftwareSerial mySerial(11, 10); // RX, TX

String Information = "";

int time = 0;
int oldDistance = 0;
int vitesse;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    pinMode(MOTOR_PIN_RIGHT, OUTPUT); // set arduino pin to output mode
    pinMode(MOTOR_PIN_LEFT, OUTPUT);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    lcd.begin(16, 2);    // nb horisontal, nb colone
    lcd.setCursor(0, 0); // set le premier caractere en haut a gauche
    lcd.clear();         // clear l'ecran au cas ou il reste des caractere dessus
}

void loop()
{
    distanceCalcul();

    if (mySerial.available())
    {
        Information = char(mySerial.read());
        lcd.setCursor(0, 0);
    }
    else
    {
        if (Information == "s")
        {
            Information = "Stop     ";
            lcd.print(Information);

            digitalWrite(MOTOR_PIN_RIGHT, LOW);
            digitalWrite(MOTOR_PIN_LEFT, LOW);
        }
        if (Information == "t")
        {
            Information = "Forward  ";
            lcd.print(Information);

            digitalWrite(MOTOR_PIN_RIGHT, HIGH);
            digitalWrite(MOTOR_PIN_LEFT, HIGH);
        }
        if (Information == "r")
        {
            Information = "Right    ";
            lcd.print(Information);

            digitalWrite(MOTOR_PIN_RIGHT, LOW);
            digitalWrite(MOTOR_PIN_LEFT, HIGH);
        }
        if (Information == "l")
        {
            Information = "Left     ";
            lcd.print(Information);

            digitalWrite(MOTOR_PIN_RIGHT, HIGH);
            digitalWrite(MOTOR_PIN_LEFT, LOW);
        }
    }
    delay(100);
}

void distanceCalcul()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration, distance;
    duration = pulseIn(echoPin, HIGH);
    // Calculate the distance (in cm) based on the speed of sound.
    distance = duration / 58.2;

    lcd.setCursor(0, 1);
    lcd.print("distance : ");
    mySerial.println(distance);

    if (distance < 10)
    {
        lcd.setCursor(12, 1);
        lcd.print(String(distance) + "   ");
    }
    else if (distance < 100)
    {
        lcd.setCursor(12, 1);
        lcd.print(String(distance) + "  ");
    }
    else if (distance < 1000)
    {
        lcd.setCursor(12, 1);
        lcd.print(String(distance) + " ");
    }
    else
    {
        lcd.setCursor(12, 1);
        lcd.print(distance);
    }

    if (time == 0)
    {
        Serial.println("pouet");
        oldDistance = distance;
    }
    time += 1;
    if (time >= 20)
    {
        Serial.println("time " + String(time));
        Serial.println("old distance " + String(oldDistance));
        Serial.println("distance " + String(distance));

        vitesse = (oldDistance - distance) * 100 / 3;
        time = 0;
        Serial.println(vitesse);

        lcd.setCursor(8, 0);
        if (vitesse >= 0)
        {
            lcd.print(String(vitesse) + " m/s   ");
        }
        else
        {
            vitesse = 0;
            lcd.print(String(vitesse) + " m/s   ");
        }
    }

    if (distance <= 50 & Information == "Forward  ")
    {
        Information = "s";
    }
}