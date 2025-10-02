/*
Due to incompatibility with the latest version, must include 1.8.4 manually the Adafruit library befre the 
EasyNeoPixel. Not that the original library is so complicated to feel the need of an easy version.
*/

#include <Adafruit_NeoPixel.h> 
#include <EasyNeoPixels.h>    

#define PIN D7
#define NUMPIXELS 12

void setup()
{
    setupEasyNeoPixels(PIN, NUMPIXELS);
}

void loop()
{
    for (int x = 0; x < NUMPIXELS; x++)
    {
        writeEasyNeoPixel(x, random(0, 255), random(0, 255), random(0, 255));
    }
    delay(500);
}