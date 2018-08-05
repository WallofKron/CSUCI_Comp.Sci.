#include "motordriver_4wd.h"
#include <seeed_pwm.h>
#include <ChainableLED.h>
//#include <Servo.h>

//functions
void stopMotor();
int Ping(int pingPin);

const int pingPin = A0;           //ultrasonic sensor

int Ping(int pingPin){
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration= pulseIn(pingPin, HIGH);
  cm = ((duration/29)/2);

  //delay(100);
  return cm;
  }


#define NUM_LEDS 1 //LEDS
float hue = 0.6 ;
ChainableLED leds(11, 12, NUM_LEDS);          

int buttonPin = SCL; // push button             
int buttonState = 0;

//Servo myServo; //servo
const int servoPin = 3;
int pos;                        

void setSpeed(int ispeed)
{
  if(ispeed >= 0)
  {
      MOTOR.setSpeedDir1(ispeed,DIRF);
      MOTOR.setSpeedDir2(ispeed,DIRR);
  }
  else
  {
      MOTOR.setSpeedDir1(-ispeed,DIRR);
      MOTOR.setSpeedDir2(-ispeed,DIRF);
  }
}

void stopMotor()
{
  MOTOR.setStop1();
  MOTOR.setStop2();
}

void backUp()
{
  leds.setColorHSB(0, 0.1, 1.0, 0.1);
  setSpeed(-10);
  delay(1000);
  stopMotor();
}

void standingTurn(int theta){
  
    if(theta > 0){
      
      MOTOR.setSpeedDir1(20,DIRF);
      MOTOR.setSpeedDir2(20,DIRF);

      delay(theta * 22);

      stopMotor();
      
      } else {

      MOTOR.setSpeedDir1(20,DIRR);
      MOTOR.setSpeedDir2(20,DIRR);

      delay(-theta * 22);

      stopMotor();
      }
  }

void setup() {
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
  MOTOR.init();
  leds.init();
  //myServo.attach(servoPin);

  pos = 90;
  //myServo.write(pos);
}

int distanceLimit = 20;
int dist_cm = 0;
void loop() {
  setSpeed(10);
  leds.setColorHSB(0, 0.3, 1.0, 0.1);
  
  dist_cm = Ping(pingPin);
  Serial.println(dist_cm);
  if(dist_cm < distanceLimit)
  {
    stopMotor();
    backUp();
  }
    
}


