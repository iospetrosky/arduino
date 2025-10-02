#define LED D4 // built in led on board
#define RED_LED D2
#define WHITE_LED D1


void setup(void)
{ 
  pinMode(LED, OUTPUT);    // LED pin as output.
  pinMode(RED_LED, OUTPUT);    // LED pin as output.
  pinMode(WHITE_LED, OUTPUT);    // LED pin as output.
  //pinMode(D0, WAKEUP_PULLUP);  // doesn't change anything
  
  Serial.begin(74880); // or 9600
  while(!Serial) {}
  Serial.println("xx"); // this starts a new line in the console after all the rubbish during the connection
  digitalWrite(WHITE_LED, HIGH);
  Serial.println("Wating some moments before going to sleep");
  delay(2000);
  digitalWrite(WHITE_LED, LOW);
  go_to_sleep(0.25);
}

void go_to_sleep(float minutes) {
  Serial.print("Now going to sleep for ");
  long msecs = minutes * 60 * 1000 * 1000;
  Serial.print(msecs);
  Serial.println(" microseconds");
  ESP.deepSleep(msecs, WAKE_RF_DEFAULT); // or WAKE_RF_DEFAULT, WAKE_RF_DISABLED, doesn't work either
  delay(2000);
}

void loop() {

  //go_to_sleep(0.25);
}
