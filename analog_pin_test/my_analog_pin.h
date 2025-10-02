const int analog_pin = A0; // the analog pin

int read_analog()  {
    for (int i=0; i<10; i++) {
      analogRead(analog_pin); // dummy read to throw away fake reading
      delay(100);
    }
    return  analogRead(analog_pin);
}