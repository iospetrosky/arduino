#include <Wire.h>
#include "SSD1306Wire.h"
// install library ESP8266 for SSD1306

/*
Video with explanation here 
https://www.youtube.com/watch?v=YF6NAjq0044

The one with on-board OLED is 0.96 Inch Display   resolution: 128x64
The external one is OLED SH-S091  resolution: 128x32 (or 64)
*/

//SSD1306Wire display(0x3C, 14, 12); // config for the built-in OLED on the controller
SSD1306Wire display(0x3C, D2, D1); // config for the external OLED SH-S091 (address, SDA, SCL)

const uint8_t activeSymbol[] PROGMEM = {
    B10000001,
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000
};

static const unsigned char PROGMEM cloud_bits[] = {
B00000000, B00000000, 
B00000000, B00000000, 
B00000001, B11000000, 
B00000011, B11100000, 
B00000011, B11111000, 
B00011111, B11111000, 
B00111111, B11111100, 
B01111111, B11111111, 
B01111111, B11111111, 
B01111111, B11111111, 
B00011111, B11111110, 
B00000000, B00000000, 
B00010010, B01001000, 
B00100100, B10010000, 
B01001001, B00100000, 
B00000000, B00000000
};

// the library is here
// https://github.com/ThingPulse/esp8266-oled-ssd1306/blob/master/examples/SSD1306SimpleDemo/SSD1306SimpleDemo.ino

void drawActiveSymbol(int px, int py) {
  display.drawXbm(px, py, 8, 8, activeSymbol);
}

void drawImageDemo(int px, int py) {
  // see https://community.silabs.com/s/article/creating-monochrome-bitmap-files-for-lcd-glib-using-gimp?language=en_US
  // on how to create xbm files with GIMP
  display.drawXbm(px, py, 16,16,cloud_bits);
}

void demo_24() {
  display.clear();
  display.setFont(ArialMT_Plain_24); // fonts are 10/16/24
  display.println("ABCDEFGH");
  display.println("1_2$3%4&5");
  delay(5000);
  display.clear();
  display.println("IJKLMNOP");
  display.println("67890#@=+");
  delay(5000);
}

void demo_16() {
  display.clear();
  display.setFont(ArialMT_Plain_16); // fonts are 10/16/24
  display.println("ABCDEFGHIJKLMNOPQRST");
  display.println("1_2$3%4&567890#@=+");
  display.println("La marianna la va in campagna");
  delay(5000);
}

void demo_24_lib2() {
  /* 
  this uses direct coordinates for the text instead of println
  the vertical resolution should be 32 but it seems to work at 64 
    (maybe this is why I must start at 1)
  the horizontal resolution is 128, confirmed

  */
  display.clear();
  display.setFont(ArialMT_Plain_24); // fonts are 10/16/24

  display.drawString(1,1, "Mode: Dish");
  display.drawString(1,25,"Mode: Dry");
  //display.drawHorizontalLine(0, 55, 128);
  display.fillCircle(60,54,6);
  display.drawRect(0,1,128,63); 
  
  display.display();
  delay(5000);
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  display.init();
  Serial.println(display.getWidth());
  Serial.println(display.getHeight());
  
  display.clear();
  display.flipScreenVertically(); // yellow line goes on top
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  //demo_24_lib2();
  drawImageDemo(50,20);
  display.display();
}


void loop() {

};