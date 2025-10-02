#include <Wire.h>
#include <SSD1306.h>

SSD1306Wire display(0x3C, D6, D1); // config for the external OLED SH-S091
#define MAX_Y 40 // 40 for external OLED SH-S091

/*
Wiring
TX - RX
RX - TX as needed, if a system only sends data and the other only receives no need to have both connections

IMPORtant: THE TWO SYSTEMS MUST HAVE A COMMON GROUND!!!
*/


const bool isMaster = true;

void setup() {
  Serial.begin(9600);
 if (isMaster) {
    delay(1000);
    Serial.println("Ciao");
  } else { 
    // it is slave
    display.init();
    display.clear();
    display.setFont(ArialMT_Plain_24); 
    display.drawString(0,0,"Wait serial");
    display.display();
    while (!Serial);
    display.drawString(0,30,"Serial OK");
    display.display();
  }

}
void loop() {
  if (isMaster) {
    Serial.println(String(random(10000)));
    delay(2000);
  } else {
    // it is slave
    if (Serial.available()) {
        String message = Serial.readString(); // Read the incoming message
        display.clear();
        display.drawString(0,10,message);   
        display.display();        
    }
  }
}
