#include <Wire.h>
#include <SSD1306Wire.h>
#include <ESP8266HTTPClient.h>

#include "my_analog_pin.h"

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Analogue PIN test");
  Serial.println("");
  //pinMode(analog_pin, INPUT);
}


void loop() {
  int moist = read_analog();
  Serial.println("Analog read: " + String(moist));
  delay(3000);

}