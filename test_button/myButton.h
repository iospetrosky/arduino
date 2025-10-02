

class myPullupButton {
    private:
        int Pin;
    public:
        myPullupButton(int aPin) {
            Pin = aPin;
            pinMode(Pin, INPUT_PULLUP);
        }

        int getPin() {
            return Pin;
        }

        bool isPressed() {
            if (digitalRead(Pin) == HIGH) {
                return true;
            }
            return false;
        }
};