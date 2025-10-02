#include <LiquidCrystal_I2C.h>
/*
Tutorial for the LCD
https://lastminuteengineers.com/esp8266-i2c-lcd-tutorial/

Tutorial for the distance
https://randomnerdtutorials.com/esp8266-nodemcu-hc-sr04-ultrasonic-arduino/
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 (the other is 0x3F but not my board) for a 16 chars and 2 line display

#define trigPin D6
#define echoPin D7
#define SOUND_VELOCITY 0.034

long duration = 0;
float distanceCm = 0;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.noBacklight();         // Make sure backlight is off
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
}

void loop() {
  char text[20];
  lcd.backlight();
  digitalWrite(trigPin, LOW);  // clears the pin
  delay(5);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY / 2;

  lcd.setCursor(2, 0);
  sprintf(text, "Distance %f", distanceCm);
  lcd.print(text);
  delay(1000);
  lcd.noBacklight();
  delay(1000);
}