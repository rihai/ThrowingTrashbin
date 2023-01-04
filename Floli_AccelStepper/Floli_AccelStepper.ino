/* Example sketch to control a stepper motor with Arduino Motor Shield Rev3, Arduino UNO and AccelStepper.h library: number of steps or revolutions. More info: https://www.makerguides.com */
#include <Bounce2.h>
// Include the AccelStepper library:
#include <AccelStepper.h>
#include <Servo.h>


// Button things...
const int wrongTrash = 2;
Bounce b = Bounce();

// Button things...
const int goodTrash = 10;
Bounce c = Bounce();

// Servo things...
Servo myservo;
const int servoPin = 6;

// Stepper things...
// Define number of steps per revolution:
const int stepsPerRevolution = 200;

// Give the motor control pins names:
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

// Define the AccelStepper interface type:
#define MotorInterfaceType 2

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(MotorInterfaceType, dirA, dirB);


//--------------------------------------------------------------------------------
int state = 0;

void setup() {

  // Setup button things
  b.attach(wrongTrash, INPUT_PULLUP);
  b.interval(50);

  // Setup button things
  c.attach(goodTrash, INPUT_PULLUP);
  c.interval(50);

  // Setup things for serial ports
  Serial.begin(9600);

  // Initialize the servo pwm pin
  myservo.attach(servoPin);
  myservo.write(150);
  

  // Setup things for the stepper
  // Set the PWM and brake pins so that the direction pins can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);

  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);

  // Set the maximum steps per second:
  stepper.setMaxSpeed(600);
  state = 0;
}


void loop() {
  b.update();
  c.update();
  if(b.fell())
  {
    // Set the current position to 0:
    //stepper.setCurrentPosition(0);
    Serial.println("Routine started");

    myservo.write(180);
    delay(1000);

    stepper.setSpeed(200);
    while (stepper.currentPosition() != 400) {
      stepper.runSpeed();
    }

    myservo.write(80); // Dem Servo wird 180 Grad befohlen
  
    delay(2000);
    myservo.write(150); // Dem Servo wird 180 Grad befohlen
  
    stepper.setSpeed(-200);
    // Run the motor backwards at 200 steps/second until the motor reaches -200 steps (1 revolution):
    while (stepper.currentPosition() != 0) {
      stepper.runSpeed();
    }  

     
     Serial.println("Routine finished");
  }

  if(c.fell())
  {
     myservo.write(80); // Dem Servo wird 180 Grad befohlen

     delay(2000);
     
     stepper.setSpeed(-200);
    while (stepper.currentPosition() != -150) {
      stepper.runSpeed();
    }

    delay(2000);
  
    stepper.setSpeed(200);
    // Run the motor backwards at 200 steps/second until the motor reaches -200 steps (1 revolution):
    while (stepper.currentPosition() != 150) {
      stepper.runSpeed();
    }

    delay(2000);
    myservo.write(150); // Dem Servo wird 180 Grad befohlen
    delay(2000);

    stepper.setSpeed(-200);
    // Run the motor backwards at 200 steps/second until the motor reaches -200 steps (1 revolution):
    while (stepper.currentPosition() != 0) {
      stepper.runSpeed();
    }
     
     Serial.println("Routine finished");
  }

}
