class myLed {
    private:
        int Pin;
        int Mode;
        int Status;

    public:
        myLed(int aPin, int aMode, int aStatus = LOW) {
            Pin = aPin;
            Mode = aMode;
            Status = aStatus;
            pinMode(Pin, aMode);
            digitalWrite(Pin, Status);
        }

        int getPin() {
            return Pin;
        }
        int getMode() {
            return Mode;
        }
        void setMode(int aMode) {
            Mode = aMode;
            pinMode(Pin, aMode);
        }

        void switchOn() {
            digitalWrite(Pin, HIGH);
            Status = HIGH;
        }
        void switchOff() {
            digitalWrite(Pin, LOW);
            Status = LOW;
        }
        void Switch() {
            if (Status == HIGH) {
                switchOff();
            } else {
                switchOn();
            }
        }


        int State() {
            return Status;
        }

};