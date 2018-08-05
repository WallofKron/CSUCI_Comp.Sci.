#include <motordriver_4wd.h>
#include <seeed_pwm.h>
#include <ChainableLED.h>

void markVisited(double x, double y);
void printGrid();
void markBlock(double x, double y);

//-------- PIE constants

const double PIE    = 3.14159265;
const double PIE_O2 = PIE/2.0;
const double PIE2 = PIE*2.0;


//------- Ultrasonic Sensor Crap

const int pingPin = A0;           //ultrasonic sensor
int Ping(int pingPin);
int dist_cm;

//-------- LED crap

#define NUM_LEDS 1
ChainableLED leds(SCL, SDA, NUM_LEDS);

//-------- motor control 

void TurnLeft90();
void TurnRight90();
void Straight( int speed, int dirn );

//-------- bumper
const int buttonPin = 11;
int button_state = 0;

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

enum {FWD, REV} state;

//-------- model of environment crap

double LEFT = 0.0;
double RIGHT = 1500.0;
double BOTTOM = 0.0;
double TOP = 1500.0;

//-------- Path Finding Structure Crap

const int granularity = 5; 
const int rows = granularity;
const int cols = granularity;
int grid[rows][cols];

//======================================================================================
// setup
//======================================================================================
void setup()
{
     for(int x = 0 ; x < granularity ; x++)
      for(int y = 0 ; y < granularity ; y++) 
        grid[x][y] = 0;
  
    leds.init();
    MOTOR.init();

    attachInterrupt(0, LeftEncoder, CHANGE);
    attachInterrupt(1, RightEncoder, CHANGE);
        
    // go straight
    Straight( 10, 1 ); 
    leds.setColorRGB(0, 0, 100, 0);  // green
    state = FWD;    
       
    Serial.begin(9600);
}

//======================================================================================
// Loop
//======================================================================================
void loop()
{
  delay(100);
  dist_cm = Ping(pingPin);
  Serial.println(dist_cm);

  Serial.println("\n\n\n\n\n\n\n\n");
  Serial.print("theta:");
  Serial.println(theta);
  Serial.print("x: ");
  Serial.print((int)(x / 300));
  Serial.print("\ty: ");
  Serial.println((int)(y / 300));
  printGrid();

  
  //---- update robot config (x,y,theta)
  
  dx = PIE * RW * cos(theta) * ((double)(left_encoder_count + right_encoder_count) / TPR);
  x = x + dx;
  
  dy = PIE * RW * sin(theta) * ((double)(left_encoder_count + right_encoder_count) / TPR);
  y = y + dy;
  
  right_encoder_count = left_encoder_count = 0;


  markVisited(x,y);

  
  //---- a simple two-state behavior to stay in the box and detect bumps

  if( digitalRead(buttonPin) == 1) 
  {
    button_state = 1;
    markBlock(x,y);
  }

  // check state

  if ( (state == FWD) && button_state == 1 )
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
    state = REV;   
  } 
  else if ((state == FWD) && (x >= RIGHT || x <= LEFT || y >= TOP || y <= BOTTOM))
  {
    //---- stop
    Straight( 0, 0 );    
    delay(100);

    //---- back up
    leds.setColorRGB(0, 100, 0, 0);  // red
    Straight( 10, -1 );    
    delay(500);

    //---- update state
    state = REV;    
  }
  else
  if ((state == REV) && (x < RIGHT && x > LEFT && y < TOP && y > BOTTOM))
  {
    //---- stop
    Straight( 0, 0 );    

    //---- turn right 90
    leds.setColorRGB(0, 0, 0, 100);
    TurnRight90();
    //---- update robot config (theta)
    theta  = fmod(theta - PIE_O2, PIE2);
    delay(100);

    //---- go straight
    leds.setColorRGB(0, 0, 100, 0);  // green
    Straight( 10, 1 );   

    //---- update state
    state = FWD;    
  }

}


                          //Ultrasonic Sensor Crap
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

/*
void markBlock(double x, double y)
{
  int col = (int)(x / 300);
  int row = (int)(y / 300);

  if(cos(theta) >= 0)
    col++;
  else
    col--;

  if(sin(theta) >= 0)
    row++;
  else
    row--;

  if(row >= 0 && col >= 0)
    grid[row][col] = 2;
}
//*/

void markBlock(double x, double y)
{
  int col = (int)(x / 300);
  int row = (int)(y / 300);

  double thetaConvert = 0;
  if(theta<0){
    thetaConvert = theta + PIE2;
  } else {
    thetaConvert = theta;
    }

  //Serial.print(thetaConvert);
  //*
  if(theta == 0.00){
     col++;
  }
  if(thetaConvert <= 1.7 && thetaConvert >= 1.4){
    row++;
  }
  if(thetaConvert <= 3.3 && thetaConvert >= 3.05){
    col--;
  }
  if(thetaConvert <= 4.85 && thetaConvert >= 4.6){
    row--;
  }  
  //*/
  if(row >= 0 && col >= 0)
    grid[row][col] = 2;
}



void markVisited(double x, double y){
  
  if(grid[(int)(y / 300)][(int)(x / 300)] == 0){
  grid[(int)(y / 300)][(int)(x / 300)] = 1;
  }

}




//======================================================================================
// Print Grid Crap
//======================================================================================

void printGrid()
{
    for(int z = granularity - 1 ; z >= 0 ; z--)
     { for(int w = 0  ; w < granularity ; w++)
        {   
          Serial.print(grid[z][w]);
          Serial.print(" ");
        }
      Serial.println();
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
      MOTOR.setSpeedDir1(0, DIRF); 
      MOTOR.setSpeedDir2(0, DIRR);   
      return;
    }
    else if (dirn == 1)   //-- fwd
    {
      MOTOR.setSpeedDir1(speed, DIRF); 
      MOTOR.setSpeedDir2(speed+(speed*0.05), DIRR); 
    }
    else                  //-- bwd
    {
      MOTOR.setSpeedDir1(speed, DIRR); 
      MOTOR.setSpeedDir2(speed+(speed*0.05), DIRF); 
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
