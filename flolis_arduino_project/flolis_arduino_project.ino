#include <Bounce2.h>
#include <Stepper.h>

const int buttonPin = 2;
Bounce b = Bounce();

// Define number of steps per revolution:
const int stepsPerRevolution = 200;

// Give the motor control pins names:
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13


// Initialize the stepper library on the motor shield:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);

void setup() {
  b.attach(buttonPin, INPUT_PULLUP);
  b.interval(50);
  Serial.begin(9600);

  // Set the PWM and brake pins so that the direction pins can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);

  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);

  // Set the motor speed (RPMs):
  myStepper.setSpeed(120);

  
}

void loop() {
  b.update();

  if(b.fell())
  {
    Serial.println("Button pressed");
    myStepper.step(200);
    delay(1000);
    myStepper.step(-200);
  }
}
