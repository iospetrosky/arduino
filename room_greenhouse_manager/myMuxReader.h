const byte Y0 = 0;
const byte Y1 = 1;
const byte Y2 = 2;
const byte Y3 = 3;
const byte Y4 = 4;
const byte Y5 = 5;
const byte Y6 = 6;
const byte Y7 = 7;

class myMuxReader {
private:
  int pins[3] = {0,0,0};
  int analogPin = 0;

  void selectMuxPin(byte channel) {
    if (channel > 7) return;  // Exit if pin is out of scope
    digitalWrite(pins[0], channel & 0x01);
    digitalWrite(pins[1], channel & 0x02);
    digitalWrite(pins[2], channel & 0x04);
  }

public:
  myMuxReader(int S0, int S1, int S2, int AnInp) {
    pins[0] = S0;
    pins[1] = S1;
    pins[2] = S2;
    pinMode(S0, OUTPUT);
    digitalWrite(S0, LOW);
    pinMode(S1, OUTPUT);
    digitalWrite(S1, LOW);
    pinMode(S2, OUTPUT);
    digitalWrite(S2, LOW);
    analogPin = AnInp;
  }

  int readAnalogChannel(byte C) {
    selectMuxPin(C);
    delay(500);
    int att = 0; // two attempts before accepting 1024
    int rd = 1024;
    while ((att < 2) && (rd == 1024)) {
      for (int i = 0; i < 10; i++) {
        analogRead(analogPin);  // dummy read to throw away possible fake reading
        delay(100);
      }
      rd = analogRead(analogPin);
      att++;
    }
    return rd;
  }
};
