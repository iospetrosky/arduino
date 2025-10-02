// This sketch works for any NodeMCU controller
#define PAUSA 200

int pins[] = {D0, D1, D2, D3, D4, D5, D6, D7, D8};

void setup()
{
    // initialize digital pin LED_BUILTIN as an output.
    for (int k=0; k<9; k++) {
      pinMode(pins[k], OUTPUT);
      digitalWrite(pins[k], LOW);
    }
}

// the loop function runs over and over again forever
void loop()
{
  for (int k=0; k<9; k++) {
    digitalWrite(pins[k], HIGH); // turn the LED on (HIGH is the voltage level)
    delay(PAUSA);           // wait for a second
    digitalWrite(pins[k], LOW); // turn the LED on (HIGH is the voltage level)
    //delay(PAUSA);           // wait for a second
  }
}
