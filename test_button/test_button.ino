#include "myButton.h"
#include "myLed.h"

myPullupButton greenButton(D3);
myLed led(D4, OUTPUT, LOW);

void setup() {
  Serial.begin(9600);
   
}

void loop() {
  
  if (greenButton.isPressed()) {
    led.Switch();
  }
  delay(200);

}
