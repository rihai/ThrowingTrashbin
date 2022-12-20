#include<Stepper.h>
#include <Servo.h>

Servo myservo;
const int buttonPin= 2;
int stepsPerRevolution=200;
Stepper myStepper(stepsPerRevolution, 8,9,10,11);
const int servoPin = 5;


void startMotor(){
  myStepper.step(60);
}

void stopMotor(){
  myStepper.step(0);
}



void setPosition(int newPosition){
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(500 + (25*newPosition));
}

void setup() {
  // put your setup code here, to run once:
  myservo.attach(5);
//pinMode(servoPin, OUTPUT);
pinMode(buttonPin,INPUT_PULLUP);
//attachInterrupt(digitalPinToInterrupt(buttonPin),startMotor, RISING);
//myStepper.setSpeed(0);
myStepper.setSpeed(100);
}

void loop() {
  // if button pressed
  if(digitalRead(buttonPin)==LOW){
   startMotor();
   myservo.write(180);    
  //setPosition(10);
    } else {
      //digitalWrite(servoPin,HIGH);
       stopMotor(); 
       myservo.write(0);
    }
    
 
  }
 
