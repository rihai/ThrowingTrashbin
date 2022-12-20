/* Example sketch to control a stepper motor with Arduino Motor Shield Rev3, Arduino UNO and AccelStepper.h library: number of steps or revolutions. More info: https://www.makerguides.com */
#include <Bounce2.h>
// Include the AccelStepper library:
#include <AccelStepper.h>
#include <Servo.h>

#include"pitches.h"

int melody[] = {
NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_AS4, NOTE_A4,                   
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                 

NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_A4,
NOTE_G4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4,      //29               //8
NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS4, NOTE_DS4, NOTE_D4,
NOTE_C4, NOTE_D4,0,                                       

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5,
NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_FS4, NOTE_D5, NOTE_C5,
NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_AS4,             //58

NOTE_D4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_DS5, NOTE_D5,
NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_C5, NOTE_G4,
NOTE_A4, 0, NOTE_AS4, NOTE_A4, 0, NOTE_G4,
NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, 0,

NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, 0,
NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_DS4,
NOTE_C4, NOTE_D4, END

};

// note durations: 8 = quarter note, 4 = 8th note, etc.
int noteDurations[] = {       //duration of the notes
8,4,8,4,
4,4,4,12,
4,4,4,4,4,4,
4,16,4,

8,4,8,4,
4,2,1,1,2,1,1,12,
4,4,4,4,4,4,
4,16,4,

4,4,4,4,4,4,
4,4,4,12,
4,4,4,4,4,4,
4,4,4,12,

4,4,4,4,4,4,
2,1,1,2,1,1,4,8,4,
2,6,4,2,6,4,
2,1,1,16,4,

4,8,4,4,4,
4,16,4,
4,8,4,4,4,
4,20,
};

int speed=90;  //higher value, slower notes


// Button things...
const int buttonPin = 2;
Bounce b = Bounce();

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

  Serial.begin(9600);
for (int thisNote = 0; melody[thisNote]!=-1; thisNote++) {

int noteDuration = speed*noteDurations[thisNote];
tone(3, melody[thisNote],noteDuration*.95);
Serial.println(melody[thisNote]);

delay(noteDuration);

noTone(3);
}

  // Setup button things
  b.attach(buttonPin, INPUT_PULLUP);
  b.interval(50);

  // Setup things for serial ports
  Serial.begin(9600);

  // Initialize the servo pwm pin
  myservo.attach(servoPin);
  myservo.write(0);

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

  if(b.fell())
  {
    // Set the current position to 0:
    //stepper.setCurrentPosition(0);
    Serial.println("Routine started");

    stepper.setSpeed(200);
    while (stepper.currentPosition() != 200) {
      stepper.runSpeed();
    }

    // Run the motor forward at 400 steps/second until the motor reaches 200 steps (1 revolution):
    myservo.write(180); // Dem Servo wird 180 Grad befohlen
  
    delay(2000);
  
    stepper.setSpeed(-200);
    // Run the motor backwards at 200 steps/second until the motor reaches -200 steps (1 revolution):
    while (stepper.currentPosition() != 0) {
      stepper.runSpeed();
    }  

     myservo.write(0); // Dem Servo wird 180 Grad befohlen
     Serial.println("Routine finished");
  }

}
