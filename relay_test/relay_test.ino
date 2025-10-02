#define PIN D7

#RELAY WORKS AT 5v (3v is not enough to trigger the switch)

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN, HIGH);
  delay(1000);
  digitalWrite(PIN, LOW);
  delay(1000);
}
