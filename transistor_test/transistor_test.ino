/*
Connect voltage to the side pins of the transistor.
Connect control pin of the transistor to D6.

The code below works if the LED is connected to 3V and the GND passes through the transistor.
If you invert the wiring with 3V passing through the transistor, then invert LOW and HIGH

*/



const int transistorPin = D5;  // GPIO12 on ESP8266
bool ledState = false; // false = OFF

void setup() {
  Serial.begin(9600);               // Start serial communication
  pinMode(transistorPin, OUTPUT);     // Set D6 as output
  digitalWrite(transistorPin, LOW);   // Ensure LED is off initially
  Serial.println("Setup complete. Starting LED toggle every 10 seconds...");
}

void loop() {
  
  ledState = !ledState;  // Toggle state
  digitalWrite(transistorPin, ledState ? LOW : HIGH);

  // Debug message
  if (ledState) {
    Serial.println("LED ON - Transistor activated");
  } else {
    Serial.println("LED OFF - Transistor deactivated");
  }

  delay(5000);  // Wait for 10 seconds
  
}