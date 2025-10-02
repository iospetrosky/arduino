#include "myButton.h"
#include "myLed.h"

myPullupButton greenButton(D0);
myLed led(D5, OUTPUT, LOW);

void setup() {
  Serial.begin(9600);
   
}

void loop() {
  if (greenButton.isPressed()) {
    led.Switch();
  }
  delay(200);

}
