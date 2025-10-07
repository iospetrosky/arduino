// Basic OLED demo for accelerometer readings from Adafruit MPU6050
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// using this OLED display: I2C OLED Display Module 0.91

#include <Wire.h>
// for the gyro
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
// for the display
#include <SSD1306.h>
#include <OLEDDisplayUi.h>

#include "myButton.h"

Adafruit_MPU6050 mpu;
SSD1306Wire display(0x3C, D2, D1);
OLEDDisplayUi ui ( &display );

myPullupButton stopButton(D3, LOW);
bool displayActive = true;

float x_avg = 0;
float y_avg = 0;
float z_avg = 0;
int readingsCount = 0;
int zeros = 0; // number of times the averages went to 0

void init_display() {
    display.init();
    display.clear();
    display.flipScreenVertically(); // yellow line goes on top
    display.setFont(ArialMT_Plain_16); // fonts are 10/16/24
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.display();
    delay(200);
    Serial.println("Display set up");
}

void displayIdle() {
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.drawString(5,5, "IDLE");
    display.display();
}

void setup() {
    Serial.begin(115200);
    // while (!Serial);
    Serial.println("\nMPU6050 OLED demo");
    pinMode(D6, OUTPUT);
    digitalWrite(D6, LOW); // ensure the transistor is on

    init_display();

    if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
        yield();
    }
    Serial.println("Found a MPU-6050 sensor");
    reset_avgs();
}

void reset_avgs() {
    if ((x_avg < 0.002) && (y_avg < 0.002) && (z_avg < 0.002)) {
        zeros++;
    } else {
        zeros = 0;
    }

    x_avg = 0;
    y_avg = 0;
    z_avg = 0;
    readingsCount = 0;    
}

void displayData() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    readingsCount++;
    x_avg = (x_avg + abs(g.gyro.x)) / readingsCount;
    y_avg = (y_avg + abs(g.gyro.y)) / readingsCount;
    z_avg = (z_avg + abs(g.gyro.z)) / readingsCount;
    display.clear();
    display.drawString(0, 0,  "X: " + String(x_avg, 3) + "   Zr: " + String(zeros));
    display.drawString(0, 26, "Y: " + String(y_avg, 3) + "   Rd: " + String(readingsCount));
    display.drawString(0, 51, "Z: " + String(z_avg, 3));
    display.display();
    if (readingsCount == 70) reset_avgs();
}

void loop() {
    if (displayActive) {
        displayData();
        if (zeros > 10) {
            displayIdle();
            displayActive = false;
        }
    }
    if (stopButton.isPressed()) {
        Serial.println("Stopping the display");
        digitalWrite(D6, HIGH); // turn off the transistor
    }
    delay(100);
}