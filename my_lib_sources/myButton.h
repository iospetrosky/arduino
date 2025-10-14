

class myPullupButton {
    private:
        int Pin;
        int hl_press; // what to check
    public:
        myPullupButton(int aPin, int aDir) {
            Pin = aPin;
            hl_press = aDir;
            pinMode(Pin, INPUT_PULLUP);
        }

        int getPin() {
            return Pin;
        }

        bool isPressed() {
            if (digitalRead(Pin) == hl_press) {
                return true;
            }
            return false;
        }
};