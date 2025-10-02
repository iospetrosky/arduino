#include <Wire.h>
#include <SSD1306Wire.h>
#include <ESP8266HTTPClient.h>

#define DEBUG 1  // comment out to disable debug messages

void dbg(String text) {
#ifdef DEBUG
  Serial.println(text);
#endif
}

#include "my_wifi.h"
#include "myMuxReader.h"

const int relay_lights = D1;
const int relay_sensors = D2;  // this switches on-off all the analog sensors
int run_count = 0;


myMuxReader mux(D5, D6, D7, A0);

void dispWiFiConfig() {
  Serial.println("Wi-Fi IP: " + WiFi.localIP().toString());
}

void go_to_sleep(float minutes) {
  long msecs = minutes * 60 * 1000;
  dbg("Now going to sleep for " + String(msecs) + " milliseconds");
  delay(msecs);
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  pinMode(A0, INPUT);
  pinMode(relay_lights, OUTPUT);
  pinMode(relay_sensors, OUTPUT);
  digitalWrite(relay_lights, LOW);
  digitalWrite(relay_sensors, LOW);

  connectToWiFi(120);
#ifdef DEBUG
  dispWiFiConfig();
#endif
}
//http://mysensors.mygamesonline.org/setval.php?sensor=pippo&rval=23
void cloud2(int field_num, float value) {
  const char* host = "mysensors.mygamesonline.org";
  String url = "/setval.php?sensor=" + String(field_num) + "&rval=" + String(value);
  Serial.println(url.c_str());

  WiFiClient client;

  //client.setInsecure();
  if (!client.connect(host, 80)) {  // 443 is the https port
    Serial.println("Connect to MySensors failure");
    return;
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" + 
                              "User-Agent: ESP8266\r\n" +
                              "Connection: close\r\n\r\n");
  
  // Wait for response
  /*
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read and print response
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);  
  }

  client.stop();
  */

}

void send_to_cloud(String key, int field_num, float value) {
  const char* host = "api.thingspeak.com";
  String url = "/update?api_key=" + (key) + "&field" + String(field_num) + "=" + String(value);
  Serial.println(url.c_str());

  WiFiClientSecure client;

  client.setInsecure();
  if (!client.connect(host, 443)) {  // 443 is the https port
    Serial.println("Connect to ThingSpeak failure");
    return;
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  delay(5000);
  cloud2(field_num, value);
}

void loop() {
  
  // light sensor is tested at every run
  int light = mux.readAnalogChannel(Y0);
  Serial.println("Light: " + String(light));

  send_to_cloud("5XUAVVFH6RJT7IMT", 1, light);

  if (light > 400) {
    digitalWrite(relay_lights, LOW);
  } else {
    digitalWrite(relay_lights, HIGH);
  }

  // execute when run_count goes to ZERO
  if (run_count == 0) {
    digitalWrite(relay_sensors, HIGH);
    delay(5000);  // wait 5 seconds for the sensors to stabilize
    // read the sensors
    int moist1, moist2;
    moist1 = mux.readAnalogChannel(Y1);
    moist2 = mux.readAnalogChannel(Y7);
    dbg("Moisture 1: " + String(moist1));
    dbg("Moisture 2: " + String(moist2));
    // send data to the cloud
    //if (moist1 != 1024) { 
      send_to_cloud("DSS1C6ZEID5ZBE2S", 2, moist1);
      delay(16000);  // delay to allow the API to receive data
    //}
    //if (moist2 != 1024) {
      send_to_cloud("DSS1C6ZEID5ZBE2S", 3, moist2);
    //}
    digitalWrite(relay_sensors, LOW);
    run_count = 5;
  } else {
    run_count--;
    Serial.println("Wait some other executios: " + String(run_count));
  }
  go_to_sleep(5);  // in minutes
}