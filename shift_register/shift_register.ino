int latchPin = D7; // L_Clock
int clockPin = D5; // Clock
int dataPin = D6; // Ser_in

/*
Map of the other pins
Reset: VCC - this MUST be connected
OE: ground - not relevant even if not connected
*/

byte leds = 0;
 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  leds = 0;
  updateShiftRegister();
  delay(200);
}

int chooseBitByLetter(String letter) {
  if (letter == "A") return 0;
  if (letter == "B") return 1;
  if (letter == "C") return 2;
  if (letter == "D") return 3;
  // optionally it can be Q0, Q1, etc
  /*
  if (letter[0] == "Q") {
    return std::stoi(letter[1]);
  }*/
  return -1;
}

void loop() 
{
  
  bitSet(leds, chooseBitByLetter("Q0"));
  updateShiftRegister();
  delay(1000);
  bitClear(leds, chooseBitByLetter("A"));
  updateShiftRegister();
  delay(1000);

  bitSet(leds, chooseBitByLetter("B"));
  updateShiftRegister();
  delay(1000);
  bitClear(leds, chooseBitByLetter("B"));
  updateShiftRegister();
  delay(1000);

  bitSet(leds, chooseBitByLetter("C"));
  bitSet(leds, chooseBitByLetter("D"));
  updateShiftRegister();
  delay(1000);
  bitClear(leds, chooseBitByLetter("C"));
  bitClear(leds, chooseBitByLetter("D"));
  updateShiftRegister();
  delay(1000);

/*
  bitSet(leds, 0);
  updateShiftRegister();
  delay(1000);
  bitClear(leds, 0);
  updateShiftRegister();
  delay(1000);
*/

/*  
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    
    delay(200);
  }
  for (int i = 0; i<20 ; i++) {
    leds = random(0,255);
    updateShiftRegister();
    delay(100);
  }
  */
}
 
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}