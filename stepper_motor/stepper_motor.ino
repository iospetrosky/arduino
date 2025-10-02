
#include <AccelStepper.h>

const int deg90 = 1024; // 90 degrees

const int stepsPerRevolution = deg90 * 4;  // 2048 is half turn

// ULN2003 Motor Driver Pins
#define IN1 D5
#define IN2 D6
#define IN3 D7
#define IN4 D8

// initialize the stepper library
AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);

void setup() {
  // initialize the serial port
  Serial.begin(115200);
  
  // set the speed and acceleration
  stepper.setMaxSpeed(600);
  stepper.setAcceleration(300);
  // set target position
  stepper.moveTo(stepsPerRevolution);
  
}

void loop() {
  //stepper.run();
  if (stepper.distanceToGo() > 1000) {
    stepper.run();
  }
}

/*
void loop() {
  // check current stepper motor position to invert direction
  if (stepper.distanceToGo() == 0){
    stepper.moveTo(-stepper.currentPosition());
    Serial.println("Changing direction");
  }
  // move the stepper motor (one step at a time)
  stepper.run();
}
*/