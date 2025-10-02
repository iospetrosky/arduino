#include "arduino_secrets.h"

#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
//#include <DHT_U.h>

#include "homepage.h"

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 (the other is 0x3F but not my board) for a 16 chars and 2 line display
const int ctLed = D0;
const int dispButton = D3;

const char *ssid = "lorenzo_work24"; // Write here your router's username
const char *password = "f3d3r1c0";   // Write here your router's passward

const int DHTPIN = D5;     // Digital pin connected to the DHT sensor

ESP8266WebServer server(80);
DHT dht(DHTPIN, DHT22);

void lcdMex(String line1, String line2) {
  lcd.backlight();
  lcd.clear();   
  delay(100); // give time to switch on
  if (line1 !="") {
    lcd.setCursor(0,0);
    lcd.print(line1);
  }
  if (line2 !="") {
    lcd.setCursor(0,1);
    lcd.print(line2);
  }
  delay(500);
  lcd.noBacklight(); 
}

void dispWiFiConfig() {
  lcdMex("Connected IP",WiFi.localIP().toString());
}

// server pages
void handleRoot() {
  digitalWrite(ctLed,HIGH);
  server.send(200, "text/html", home_page);
  digitalWrite(ctLed,LOW);
}

void handleHumidity() {
  digitalWrite(ctLed,HIGH);
  float humidity = dht.readHumidity();
  server.send(200, "text/plain", String(humidity));
  digitalWrite(ctLed,LOW);
}

void handleTemperature() {
  digitalWrite(ctLed,HIGH);
  float temperature = dht.readTemperature();
  server.send(200, "text/plain", String(temperature));
  digitalWrite(ctLed,LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.println("xx");
  Serial.println("xx");
  
  lcd.init();
  lcd.clear();         
  lcd.noBacklight();      // Make sure backlight is off
  
  pinMode(ctLed,OUTPUT);
  digitalWrite(ctLed, LOW);

  pinMode(dispButton, INPUT_PULLUP);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    lcdMex("Attempting to","connect to WiFi");  
  }
  dispWiFiConfig();
  // prepare the web server
  server.on("/", handleRoot);
  server.on("/getHumidity", handleHumidity);
  server.on("/getTemperature", handleTemperature);
  server.begin();
  dht.begin();
  lcdMex("Server started","DHT started");
}

void loop() {
  int x = digitalRead(dispButton);
  //lcdMex("Button is", String(x));
  if ( x == LOW) {
    dispWiFiConfig();
  }
  server.handleClient();
}