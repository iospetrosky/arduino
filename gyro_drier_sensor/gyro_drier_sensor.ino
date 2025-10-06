// Basic OLED demo for accelerometer readings from Adafruit MPU6050
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/

// using this OLED display: I2C OLED Display Module 0.91

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include "myButton.h"

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

myPullupButton stopButton(D3, LOW);
bool displayActive = true;


void init_display() {
  Wire.begin();
  Wire.beginTransmission(0x3C); // OLED I2C address
  Wire.write(0x00); // Command mode
  Wire.write(0xAE); // Display OFF
  Wire.endTransmission();
  delay(100); // Give it time to settle
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
}

bool reset_display() {
    display.clearDisplay();
    display.display();
    display.ssd1306_command(SSD1306_DISPLAYOFF);  // Turn off OLED
    return false;
}

void setup() {
  Serial.begin(115200);
  // while (!Serial);
  Serial.println("MPU6050 OLED demo");

  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");
  init_display();
  display.display();
  delay(500); // Pause for 2 seconds
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setRotation(0);
}

void displayData() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Acc:");
  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("");
  display.print("Gyro:");
  display.print(g.gyro.x, 1);
  display.print(", ");
  display.print(g.gyro.y, 1);
  display.print(", ");
  display.print(g.gyro.z, 1);
  display.println("");

  display.display();

}

void loop() {
  if (displayActive) {
    displayData();
  }
  if (stopButton.isPressed() && displayActive) {
    Serial.println("Stopping the display");
    displayActive = reset_display();
  }
  delay(100);
}