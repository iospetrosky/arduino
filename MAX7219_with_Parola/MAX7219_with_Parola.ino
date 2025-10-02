#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

/*
Tutorial here
https://lastminuteengineers.com/max7219-dot-matrix-arduino-tutorial/

This is useful if more matrixes are connected to form a bigger display

MD_MAX72 library documentation here
https://majicdesigns.github.io/MD_MAX72XX/
https://github.com/mongoose-os-libs/md-max72xx/blob/master/examples/MD_MAX72xx_Test/MD_MAX72xx_Test.ino
*/

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 1
#define CS_PIN D1

// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
	// Intialize the object
	myDisplay.begin();

	// Set the intensity (brightness) of the display (0-15)
	myDisplay.setIntensity(0);

	// Clear the display
	myDisplay.displayClear();
}


void loop() {
	myDisplay.setTextAlignment(PA_LEFT);
	myDisplay.print("33");
	delay(2000);
	myDisplay.print("12");
	delay(2000);
	myDisplay.print("8");
	delay(2000);
	myDisplay.print("90");
	delay(2000);
}
