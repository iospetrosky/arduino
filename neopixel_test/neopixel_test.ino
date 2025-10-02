#include <Adafruit_NeoPixel.h> // select old 1.8.4 version


#define PIN D7
#define NUMPIXELS 12

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(void)
{
    pixels.begin();
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Black
    }
    pixels.show();
}

void loop()
{
    pixels.clear();
    for (int x = 0; x < NUMPIXELS; x++)
    {
        pixels.setPixelColor(x, pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
    }
    pixels.show();
    delay(500);
}