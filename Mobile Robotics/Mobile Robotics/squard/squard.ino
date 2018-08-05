#include "motordriver_4wd.h"
#include <seeed_pwm.h>
#include <ChainableLED.h>
#include <math.h>

int right_encoder_count = 0, left_encoder_count = 0;
int right_dirn = 1, left_dirn = 1 ;

const double pi = 3.1415926;

double x = 50.0, y = 50.0 ;
double dx = 0.0, dy = 0.0 ;
double theta = (pi/2), dtheta = 0.0, theta_turn = 0.0;


//const int TicksPerRotation = 72; // in ticks (clavaue ticks)
const double TicksPerRotation = 70.0; // in ticks
const double WheelRadius = 40.0; // in mm
//const double wheelbase_length = 195.0; //End to End
const double wheelbase_length = 175.0; //Middle to Middle
const double ticks_per_cm = TicksPerRotation / (pi *  WheelRadius * 2);


const double boundary = 1500; //in mm



int delay_t = 100;
typedef enum state{ FWD,REV,TRN} STATE;
int state ;

void RightEncoder()
{
  right_encoder_count += right_dirn;
}

void LeftEncoder()
{
  left_encoder_count += left_dirn;
}

void stopMotor(){
  MOTOR.setStop1();
  MOTOR.setStop2();
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

void setup() {
    MOTOR.init();
    Serial.begin(9600);
    attachInterrupt(0, RightEncoder, CHANGE);
    attachInterrupt(1, LeftEncoder, CHANGE);
    right_encoder_count = 0, left_encoder_count = 0;
    setSpeed(10);
    state = FWD;
}

void loop() 
 {
  delay(delay_t);

  if(state == FWD)
  {
    dtheta = pi*(WheelRadius / (wheelbase_length/2.0)) * ((double)(abs(right_encoder_count) - abs(left_encoder_count))/TicksPerRotation);
  } 
  else if(state == TRN)
  {
    if(right_dirn == -1)
     dtheta = pi * (WheelRadius / (wheelbase_length/2.0)) * ((double)(right_encoder_count) / TicksPerRotation);
    else
     dtheta = pi * (WheelRadius / (wheelbase_length/2.0)) * ((double)(left_encoder_count) / TicksPerRotation);
  
  }

  theta = fmod(theta + dtheta, 2*pi);
  theta_turn = theta_turn + dtheta;
  
  dx = pi * WheelRadius * cos(theta) * ((double)(right_encoder_count + left_encoder_count) / TicksPerRotation);
  x = x + dx;
  
  dy = pi * WheelRadius * sin(theta) * ((double)(right_encoder_count + left_encoder_count) / TicksPerRotation);
  y = y + dy;

  //print values
  /*
  Serial.print("right_encoder_count: "); 
  Serial.print(right_encoder_count);
  Serial.print('\t');
  Serial.print("left_encoder_count: "); 
  Serial.println(left_encoder_count);
  
  Serial.print("state: ");
  Serial.println(state);
  //*/
  //*
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("\ty: ");
  Serial.println(y);
  Serial.print("theta: ");
  Serial.println(theta);
  Serial.print("dtheta: ");
  Serial.println(dtheta);
  Serial.print("theta turn: ");
  Serial.println(theta_turn);
  //*/
  Serial.println();
  
  if( (state == FWD) && (x > boundary || x < 0.0 || y > boundary || y < 0.0) )
  {
    Serial.println("reversing");
    stopMotor();
    delay(delay_t);
    left_dirn = -1; right_dirn = -1;
    right_encoder_count = left_encoder_count = 0;
    setSpeed(-10);
    state = REV;
    //leds
  }
  else
  if( (state == REV) && (x < boundary-40 && x > 0.0+40 && y < boundary-40 && y > 0.0+40))
  {
    Serial.println("Turning right");
    stopMotor();
    delay(delay_t);
    //turning 90 
    theta_turn = 0.0;
    left_dirn = 1; right_dirn = -1;
    right_encoder_count = left_encoder_count = 0;
    MOTOR.setSpeedDir1(15,DIRF); 
    MOTOR.setSpeedDir2(15,DIRF);
    state = TRN;
  }
  else
  if( (state == TRN) && (fabs(fabs(theta_turn) - (pi/2)) < 0.3))
  {
    Serial.println("Going forward");
    left_dirn = 1;
    right_dirn = 1;
    right_encoder_count = left_encoder_count = 0;
    setSpeed(10);
    state = FWD;
    //leds
  }
  else
  {
    Serial.println("continue");
    right_encoder_count = left_encoder_count = 0;
  }
 }
