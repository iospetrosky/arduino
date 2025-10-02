#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

const int RECV_PIN = D6;
const int SEND_PIN = D8;
IRrecv irrecv(RECV_PIN);
IRsend irsend(SEND_PIN);

decode_results results;

uint16_t rawData[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
                        650, 1650, 650, 1650, 650, 1650, 600};

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

int k = 0;

void loop() { // this is the receiver loop
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume();
    k++;
    Serial.println(k);
  }
  delay(100);
}

/*
void loop() { // this is the sender loop
  irsend.sendRaw(rawData, 67, 38); // Send a raw data capture at 38kHz.
  delay(2000);
}
*/