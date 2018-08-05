#include <motordriver_4wd.h>
#include <seeed_pwm.h>
#include <ChainableLED.h>

//-------- PIE constants

const double PIE    = 3.14159265;
const double PIE_O2 = PIE/2.0;
const double PIE2 = PIE*2.0;

//-------- LED crap

#define NUM_LEDS  1
ChainableLED leds(SCL, SDA, NUM_LEDS);

//-------- motor control 

void TurnLeft90();
void TurnRight90();
void Straight( int speed, int dirn );
void Wander();

//-------- bumper
const int buttonPin = 11;
int button_state = 0;

//-------- ping crap

int Ping( int );
const int pingPin = A0;

//-------- dead reckoning 

// ticks per rotation
#define TPR 72
 
// robot measurements (mm)
#define RW    42.5  // radius wheel
#define D     158.0

// robot config variables
double x = 100.0, y = 100.0, dx = 0.0, dy = 0.0;
double theta =  PI/2.0;

// encoder variables
volatile long left_encoder_count = 0, right_encoder_count = 0;   
int left_dirn = 1, right_dirn = 1;


//-------- robot state 

enum {WANDER, GOHOME, INCLINE} state;
enum {FWD, REV} wander_state;


//-------- model of environment 

double LEFT = 0.0;
double RIGHT = 1500.0;
double BOTTOM = 0.0;
double TOP = 1500.0;

float ogrid[][5] =  { {0.0,0.0,0.0,0.0,0.0},
                      {0.0,0.0,0.0,0.0,0.0},
                      {0.0,0.0,0.0,0.0,0.0},
                      {0.0,0.0,0.0,0.0,0.0},
                      {0.0,0.0,0.0,0.0,0.0} };

float obj_x, obj_y;
int row, col;

//======================================================================================
// setup
//======================================================================================
void setup()
{
    leds.init();
    MOTOR.init();

    attachInterrupt(0, LeftEncoder, CHANGE);
    attachInterrupt(1, RightEncoder, CHANGE);
        
    // go straight
    Straight( 10, 1 ); 
    leds.setColorRGB(0, 0, 100, 0);  // green
    state = WANDER;
    wander_state = FWD;    
       
    //Serial.begin(9600);
}

//======================================================================================
// Loop
//======================================================================================
void loop()
{

  
  //delay(100);
  //---- read sensors  
  int dist_cm = 51;
  //int dist_cm = Ping(pingPin);  Serial.println(dist_cm);
  if (dist_cm < 50)
  {
    x = x + sin(theta)*dist_cm;  y = y - cos(theta)*dist_cm;
    row = int(x/30);  col = int(y/30);
    if (row >= 0 && row <= 5 && col >= 0 && col <= 5)  
    {
      if (ogrid[row][col] <= 0.0) {ogrid[row][col] = 0.5;}
      ogrid[row][col] += (1.0 - ogrid[row][col])/2.0;
    }
  }
    
  if( digitalRead(buttonPin) == 1) {button_state = 1;}; 
    
  //---- update robot config (x,y,theta)
  dx = PIE * RW * cos(theta) * ((double)(left_encoder_count + right_encoder_count) / TPR);
  x = x + dx;
  
  dy = PIE * RW * sin(theta) * ((double)(left_encoder_count + right_encoder_count) / TPR);
  y = y + dy;
  
  right_encoder_count = left_encoder_count = 0;
  
  //---- simple behavior to wander and go home

  if (state == WANDER)
  {
    //---- try to reach goal cell
    Wander();

    //---- check if we've arrived at goal cell
    if (x > 1400 && y > 1400)
    {
      //---- stop
      Straight( 0, 0 );    
      delay(100);

      //---- update state
      state = GOHOME;         
    }
  }
  else
  if (state == GOHOME)
  {
    //---- use map to go home

    for (int i = 0; i < 10; i++)
    {
      leds.setColorRGB(0, 100, 0, 0);  // red
      delay(1000);
      leds.setColorRGB(0, 0, 100, 0);  // green
      delay(1000);
      leds.setColorRGB(0, 0, 0, 100);  // blue
      delay(1000);
    }

    //---- stop
    Straight( 0, 0 );    
    delay(100);

    //---- update state
    state = INCLINE;
  }
  else
  if (state == INCLINE)
  {
    //--- good luck  
  }

}



//======================================================================================
// Wander()
//======================================================================================
void
Wander()
{
  if (wander_state == FWD)
  {
    if (button_state == 1)
    {
      //---- stop
      Straight( 0, 0 );    
      delay(100);

      //---- back up
      leds.setColorRGB(0, 100, 0, 0);  // red
      Straight( 10, -1 );    
      delay(500);

      button_state = 0;

      //---- update state
      wander_state = REV;
    }   
    else 
    if ((wander_state == FWD) && (x >= RIGHT || x <= LEFT || y >= TOP || y <= BOTTOM))
    {
      //---- stop
      Straight( 0, 0 );    
      delay(100);

      //---- back up
      leds.setColorRGB(0, 100, 0, 0);  // red
      Straight( 10, -1 );    
      delay(500);

      //---- update state
      wander_state = REV;    
    }
  }
  else
  if ((wander_state == REV) && (x < RIGHT && x > LEFT && y < TOP && y > BOTTOM))
  {
    //---- stop
    Straight( 0, 0 );    

    if (theta <= 0.0 && theta >= -PIE_O2)
    {
      //---- turn left 90
      leds.setColorRGB(0, 0, 0, 100);
      TurnLeft90();
      //---- update robot config (theta)
      theta  = fmod(theta + PIE_O2, PIE2);
      delay(100);
    }
    else
    {
      //---- turn right 90
      leds.setColorRGB(0, 0, 0, 100);
      TurnRight90();
      //---- update robot config (theta)
      theta  = fmod(theta - PIE_O2, PIE2);
      delay(100);      
    }

    //---- go straight
    leds.setColorRGB(0, 0, 100, 0);  // green
    Straight( 10, 1 );   

    //---- update state
    wander_state = FWD;    
  }  


}




//======================================================================================
// TurnLeft90
//======================================================================================
void
TurnLeft90()
{
    right_encoder_count = left_encoder_count = 0;
    
    left_dirn = -1; right_dirn = 1;
    MOTOR.setSpeedDir1(40, DIRR); MOTOR.setSpeedDir2(40, DIRR); 
    while (right_encoder_count < 64)
    {
      delayMicroseconds(1);
    }

    MOTOR.setSpeedDir1(0, DIRF); MOTOR.setSpeedDir2(0, DIRR);
}

//======================================================================================
// TurnRight90
// dirn is 1 for right, -1 for left
//======================================================================================
void
TurnRight90()
{
    right_encoder_count = left_encoder_count = 0;
    
    left_dirn = 1; right_dirn = -1;
    MOTOR.setSpeedDir1(40, DIRF); MOTOR.setSpeedDir2(40, DIRF); 
    while (left_encoder_count < 64)
    {
      delayMicroseconds(1);
    }

    MOTOR.setSpeedDir1(0, DIRF); MOTOR.setSpeedDir2(0, DIRR);
}

//======================================================================================
// Straight
// dirn is 1 for fwd, -1 for bwd
//======================================================================================
void
Straight( int speed, int dirn )
{
    //---- setup encoder variables
    left_dirn = dirn; right_dirn = dirn;
    
    if (speed == 0)       //-- stop
    {
      MOTOR.setSpeedDir1(0, DIRF); MOTOR.setSpeedDir2(0, DIRR);   return;
    }
    else if (dirn == 1)   //-- fwd
    {
      MOTOR.setSpeedDir1(speed, DIRF); MOTOR.setSpeedDir2(speed+(speed*0.05), DIRR); 
    }
    else                  //-- bwd
    {
      MOTOR.setSpeedDir1(speed, DIRR); MOTOR.setSpeedDir2(speed+(speed*0.05), DIRF); 
    }
}



//======================================================================================
// Interrupt Service Routines for encoders
//======================================================================================
void LeftEncoder()
{
  left_encoder_count = left_encoder_count + left_dirn;
}

void RightEncoder()
{
  right_encoder_count = right_encoder_count + right_dirn;
}


//======================================================================================
// Ping
//======================================================================================
int
Ping( int pingPin )
{
  long duration, inches, cm; 

  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING: a HIGH
  // pulse duration of which is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = duration / 29 / 2; // 1cm/29us  

  delay(100);

  return cm;
}
