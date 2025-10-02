#include <Wire.h>
#include <SSD1306Wire.h>
#include <ESP8266HTTPClient.h>
// install library ESP8266 for SSD1306

#define DEBUG 1  // comment out to disable debug messages

#include "my_wifi.h"
#include "get_datetime_from_web.h"


void dispWiFiConfig() {
  Serial.println("Wi-Fi IP: " + WiFi.localIP().toString());
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  connectToWiFi(120);
#ifdef DEBUG
  dispWiFiConfig();
#endif
}

void loop() {

  String dt = get_datetime_from_web(); //2024-12-18 16:48:45
  delay(10000);
}