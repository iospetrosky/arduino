const int light_pin = A0; // the analog pin


#define DEBUG 1 // comment out to disable debug messages

void setup()
{
    Serial.begin(115200);
    
}

void loop()
{
    int analog_value = analogRead(light_pin);
  
    Serial.print("Analog Value = ");
    Serial.println(analog_value); // The raw analog reading

    delay(500);

}

