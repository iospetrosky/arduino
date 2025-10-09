#include <Wire.h>
#include <EMailSender.h>

#include <Adafruit_MPU6050.h>  // MPU-6050 is the name of the gyroscope
#include <Adafruit_Sensor.h>

#include <SSD1306.h>
#include <OLEDDisplayUi.h>

#include <ESP8266HTTPClient.h>

#include "myButton.h"
#include "my_wifi.h"

Adafruit_MPU6050 mpu;
SSD1306Wire display(0x3C, D2, D1);
OLEDDisplayUi ui(&display);

myPullupButton stopButton(D3, LOW);
bool displayActive = true;

unsigned long idlePeriods = 0; 
const unsigned long maxIdlePeriods = 120;

float max_x = 0, max_y = 0, max_z = 0;
const float th_y = 0.01;
const float th_z = 0.01;

bool sendingMessage = false; // unified semaphore

void init_display() {
    delay(500);
    display.init();
    display.clear();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.display();
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
        display.drawString(5, 5, "Sensor init failed");
        Serial.println("Sensor init failed");
        while (1) yield();
    }
    Serial.println("Found a MPU-6050 sensor");
    display.drawString(2, 2, "Wi-Fi connect");
    display.display();
    connectToWiFi(125);
    display.drawString(2,26,dispWiFiConfig());
    display.display();
    delay(5000);
}

void send_email_notif() {
    Serial.println("Sending email");
    EMailSender::EMailMessage message;
    message.subject = "Gyro is now Idle";
    message.message = "Gyroscope has moved to IDLE!";

    EMailSender emailSend("loruk371@gmail.com", "tiudnygltapfymks");
    EMailSender::Response resp = emailSend.send("lorenzo.pedrotti@gmail.com", message);
    /*Serial.print("Email send status: ");
    Serial.println(resp.status);
    Serial.print("Email send code: ");
    Serial.println(resp.code);*/
    Serial.print("Email send desc: ");
    Serial.println(resp.desc);
}

void send_whatsapp_notif() {
    const char* host = "api.callmebot.com";
    String url = "/whatsapp.php?phone=447999399779&text=The+machine+has+stopped&apikey=2866066";

    WiFiClientSecure client;
    client.setInsecure();
    if (!client.connect(host, 443)) {
        Serial.println("Connect to CallMe Bot failure");
        return;
    }
    Serial.println("Connect to CallMe Bot OK");
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
}


void displayData() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);


    // Check if the gyroscope readings are below the threshold
    if (abs(g.gyro.y) < th_y &&
        abs(g.gyro.z) < th_z) {
        idlePeriods++;
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
    display.setFont(ArialMT_Plain_16);
    display.drawRect(1, 1, 80, 38);
    display.drawString(3,  6, "Y: " + String(abs(g.gyro.y), 3) );
    display.drawRect(0, 39, 80, 61);
    display.drawString(3, 42, "Z: " + String(abs(g.gyro.z), 3) );

    display.drawRect(80, 1, 125, 38);
    display.drawString(83, 3, "Id: " + String(idlePeriods));
    display.display();
}

void loop() {
    if (!sendingMessage) {
        if (displayActive) {
            displayData();
        } else {
            sendingMessage = true; // set semaphore
            displayIdle();
            send_email_notif();
            send_whatsapp_notif();
        }
    }
    if (stopButton.isPressed()) {
        Serial.println("Stopping the display");
        digitalWrite(D6, HIGH); // turn off the transistor
    }
    delay(100);
}