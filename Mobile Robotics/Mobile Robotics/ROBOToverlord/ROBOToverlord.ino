#include "motordriver_4wd.h"
#include <seeed_pwm.h>
#include <ChainableLED.h>
#include <Servo.h>

//NOTES and COMMENTS

//setSpeedDir1 (DIRR) = Left side and reverse
//setSpeedDir1 (DIRF) = Left side and forward

//setSpeedDir2 (DIRR) = Right side and forward
//setSpeedDir2 (DIRF) = Right side and reverse


//Servo motor notes
//pos = 0 -> facing robots left
//pos = 90 -> facing forward
//pos = 180 -> facing robots right

//functions
void stopMotor();
int Ping(int pingPin);



#define NUM_LEDS 1 //LEDS
float hue = 0.5 ;
ChainableLED leds(11,12, NUM_LEDS);          


int buttonPin = SCL; // push button             
int buttonState = 0;


Servo myServo; //servo
//const int servoPin = 3;
int pos;                        


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



void stopMotor(){
  MOTOR.setStop1();
  MOTOR.setStop2();
}



void setup() {
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
  MOTOR.init();
  leds.init();
  //leds.setColorHSB(0, 0.9, 1.0, 0.1);
  //myServo.attach(servoPin);
  pos = 0;
}


void loop() {

//myServo.write(pos);
  
buttonState = digitalRead(buttonPin);
if(buttonState == 1)
  {
    Serial.print("afsdsfadsdgfkhjde");
    hue = 0;
    //leds.setColorHSB(0, 0.1, 1.0, 0.5);
  }

  leds.setColorHSB(0, hue, 1.0, 0.5);

hue += 0.01;
Serial.print(hue);
Serial.println("---");
int dist_cm = Ping(pingPin);
Serial.println(dist_cm);


//leds.setColorHSB(0, (dist_cm/100), 1.0, 0.5);


}
