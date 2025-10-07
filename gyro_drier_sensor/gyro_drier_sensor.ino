#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SSD1306.h>
#include <OLEDDisplayUi.h>
#include "myButton.h"

Adafruit_MPU6050 mpu;
SSD1306Wire display(0x3C, D2, D1);
OLEDDisplayUi ui(&display);

myPullupButton stopButton(D3, LOW);
bool displayActive = true;

unsigned long idlePeriods = 0; 
const unsigned long maxIdlePeriods = 60;

float max_x = 0, max_y = 0, max_z = 0;
const float th_x = 0.06;
const float th_y = 0.01;
const float th_z = 0.01;


void init_display() {
    display.init();
    display.clear();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.display();
    delay(200);
    Serial.println("Display set up");
}

void displayIdle() {
    display.clear();
    display.setFont(ArialMT_Plain_24);
    display.drawString(5, 5, "IDLE");
    display.display();
}

void setup() {
    Serial.begin(115200);
    Serial.println("\nMPU6050 OLED demo");
    pinMode(D6, OUTPUT);
    digitalWrite(D6, LOW); // ensure the transistor is on

    init_display();

    if (!mpu.begin()) {
        Serial.println("Sensor init failed");
        while (1) yield();
    }
    Serial.println("Found a MPU-6050 sensor");
}

void displayData() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    /*
    if (abs(g.gyro.x) > max_x) max_x = abs(g.gyro.x);
    if (abs(g.gyro.y) > max_y) max_y = abs(g.gyro.y);
    if (abs(g.gyro.z) > max_z) max_z = abs(g.gyro.z);
    */

    // Check if the gyroscope readings are below the threshold
    if (abs(g.gyro.y) < th_y &&
        abs(g.gyro.z) < th_z) {
        idlePeriods++;
        Serial.println("Idle: " + String(idlePeriods));
        // If below threshold, check if we are already counting idle time
        if (idlePeriods >= maxIdlePeriods) {
            displayActive = false;
        }
    } else {
        // Reset idle timer if gyro readings exceed the threshold
        idlePeriods = 0;
    }

    // Display current gyro readings
    display.clear();
    //display.drawString(0, 0, "X: " + String(abs(g.gyro.x), 3) + " : " + String(max_x, 3));
    display.drawString(0, 0, "Idle: " + String(idlePeriods));
    display.drawString(0, 26, "Y: " + String(abs(g.gyro.y), 3) );
    display.drawString(0, 51, "Z: " + String(abs(g.gyro.z), 3) );
    display.display();
}

void loop() {
    if (displayActive) {
        displayData();
    } else {
        displayIdle();
    }
    if (stopButton.isPressed()) {
        Serial.println("Stopping the display");
        digitalWrite(D6, HIGH); // turn off the transistor
    }
    delay(100);
}