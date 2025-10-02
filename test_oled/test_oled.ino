#include <Wire.h>
#include <SSD1306.h>
// install library ESP8266 for SSD1306
#include <OLEDDisplayUi.h>
#include <ESP8266WiFi.h>



/*
Video with explanation here 
https://www.youtube.com/watch?v=YF6NAjq0044

The one with on-board OLED is 0.96 Inch Display   resolution: 128x64
Port 0x3c - just guessing since i2cdetect does not detect
For some reason it works with numeric values of the ports but not with the symbols
*/

SSD1306Wire display(0x3c, 14, 12); // config for the built-in OLED on the controller

// Pins for ESP8266: SDA = D2, SCL = D1
//SSD1306Wire display(0x3C, D6, D1); // config for the external OLED SH-S091 (address, SDA, SCL)

OLEDDisplayUi ui ( &display );


#define MAX_Y 40 // 40 for external OLED SH-S091

const uint8_t activeSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000
};

static unsigned char cloud_bits[] = {
   0x00, 0x00, 0x00, 0x88, 0x10, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x08, 0x40, 0x00, 0x08, 0x44, 0x00, 0x48, 0x44, 0x00, 0x48, 0x44, 0x00,
   0x88, 0xf4, 0x00, 0x48, 0x04, 0x00, 0x08, 0x04, 0x00, 0x08, 0x04, 0x00,
   0x08, 0x04, 0x02, 0xf8, 0x9f, 0x03, 0x48, 0x84, 0x00, 0x40, 0x84, 0x00,
   0x40, 0xfc, 0x00, 0x40, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00 };

// the library is here
// https://github.com/ThingPulse/esp8266-oled-ssd1306/blob/master/examples/SSD1306SimpleDemo/SSD1306SimpleDemo.ino

void drawRectDemo() {
  // Draw a pixel at given position
  for (int i = 0; i < 10; i++) {
    display.setPixel(i, i);
    display.setPixel(10 - i, i);
  }
  display.drawRect(12, 12, 20, 20);

  // Fill the rectangle
  display.fillRect(21, 21, 20, 20);

  // Draw a line horizontally
  display.drawHorizontalLine(0, 40, 20);

  // Draw a line horizontally
  display.drawVerticalLine(40, 0, 20);
}
void drawCircleDemo() {
  for (int i = 1; i < 8; i++) {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i * 3);
    if (i % 2 == 0) {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i * 3);
  }
}

void drawImageDemo(int px, int py) {
  // see https://community.silabs.com/s/article/creating-monochrome-bitmap-files-for-lcd-glib-using-gimp?language=en_US
  // on how to create xbm files with GIMP
  display.drawXbm(px, py, 20,20,cloud_bits);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  display.init();
  display.clear();
  //display.flipScreenVertically(); // yellow line goes on top
  display.setFont(ArialMT_Plain_24); // fonts are 10/16/24
  display.setTextAlignment(TEXT_ALIGN_LEFT);


  //drawRectDemo();
  //drawCircleDemo();
  
  display.display();
  connectToWiFi();
}

const char *ssid = "sabrina_lorenzo"; 
const char *password = "f3d3r1c0";  

// example of assigning a static IP 
IPAddress subnet(255, 255, 255, 0);			           
IPAddress gateway(192, 168, 1, 254);			            
IPAddress local_IP(192, 168, 1, 120);	

void connectToWiFi() {
  /*
  if (WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Static IP Configured");
  }
  else {
    Serial.println("Static IP Configuration Failed");
  }
  */
  WiFi.begin(ssid, password);
  // Initialising the UI will init the display too.
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect to WiFi");  
    delay(500);
  }
  dispWiFiConfig();
}

void dispWiFiConfig() {
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, WiFi.localIP().toString());
  display.display();
  delay(5000);
}

void loop() {
  // clear the display
  
  for (int row = 0; row <= MAX_Y; row++) {
    display.clear();
    display.drawString(0, row, "Cippa!  " + String(row));
    
    display.display();
    delay(300);
  }
  
  for (int x = 3; x< 100; x++) {
    display.clear();
    drawImageDemo(x, 10);
    display.display();
    delay(200);
  }
  
}