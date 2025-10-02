#include <Wire.h>
#include <SSD1306Wire.h>
#include <ESP8266HTTPClient.h>
// install library ESP8266 for SSD1306

#include "my_wifi.h"


void dispWiFiConfig() {
  Serial.println("Wi-Fi IP: " + WiFi.localIP().toString());
}

void send_to_cloud() {
  const char* host = "192.168.1.30:5000";
  String url = "/addrow";
  //Serial.println(url.c_str());

  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  
  Serial.println("[HTTP] begin...");
  http.begin(client, "192.168.1.30", 5000, "/addrow", true); // true for HTTPS // 443 is the https port
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  Serial.println("[HTTP] POST...");
  int retCode = http.POST("defs_id=1&sess_id=jfgnDwQeYbVw&f3_val=32");
  Serial.println("Returned: " + String(retCode));
}



void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");
  
  connectToWiFi();
  dispWiFiConfig();
  send_to_cloud();
}

void loop() {
  
}

