#include <LiquidCrystal_I2C.h>
/*
Nice tutorial here
https://lastminuteengineers.com/esp8266-i2c-lcd-tutorial/
*/
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 (the other is 0x3F but not my board) for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.noBacklight();      // Make sure backlight is off
}

void loop() {
  char text[20];
  for(int x=0; x< 5; x++) {
    lcd.backlight();
    lcd.setCursor(2,0);
    sprintf(text, "Loop %d", x);
    lcd.print(text);
    delay(1000);
    lcd.noBacklight();
    delay(1000);
  }
}