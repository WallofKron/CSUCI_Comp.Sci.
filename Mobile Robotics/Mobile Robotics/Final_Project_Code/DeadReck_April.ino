#include <motordriver_4wd.h>
#include <seeed_pwm.h>
#include <ChainableLED.h>

//Robert Florence ’Stevenson’
//Stormon ‘Norman’ Force
//Professor Claveau
//CSUCI Spring 2017

void markVisited(double x, double y);
void printGrid();
void markBlock(double x, double y);


//-------- PIE constants

const double PIE    = 3.14159265;
const double PIE_O2 = PIE/2.0;
const double PIE2 = PIE*2.0;

//------- Ultrasonic Sensor Crap

const int pingPin = A0;
int Ping(int pingPin);
int dist_cm;

//-------- LED crap

#define NUM_LEDS 1
ChainableLED leds(SCL, SDA, NUM_LEDS);

//-------- motor control 

void TurnLeft90();
void TurnRight90();
void Straight( int speed, int dirn );
void Wander();

//-------- bumper

const int buttonPin = 11;
int button_state = 0;

//-------- dead reckoning 

// ticks per rotation
#define TPR 71
 
// robot measurements (mm)
#define RW    42.5  // radius wheel
#define D     158.0

// robot config variables
double x = 100.0, y = 100.0, dx = 0.0, dy = 0.0;
double theta =  PI/2.0;

// encoder variables
volatile long left_encoder_count = 0, right_encoder_count = 0;   
int left_dirn = 1, right_dirn = 1;


//-------- robot states

enum {WANDER, GOHOME, INCLINE} state;
enum {FWD, REV} wander_state;

//-------- model of environment crap

double LEFT = 0.0;
double RIGHT = 1500.0;
double BOTTOM = 0.0;
double TOP = 1500.0;

//-------- Mapping Structure Crap

const int granularity = 5; 
const int rows = granularity;
const int cols = granularity;
int grid[rows][cols];

//-------- Stack Go home crap

char Sdir[rows * cols];
int Sxy[rows * cols * 2];
int Sindex = 0 ;

//-------- Light reading crap
enum {LEFT_incline, RIGHT_incline} stateIncline;
int lightPin = A0;
boolean topOfIncline = false;

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
    wander_state = FWD;    

    digitalWrite(lightPin, INPUT_PULLUP);

    Serial.begin(9600);
}


//======================================================================================
// Loop
//======================================================================================
void loop()
{
  Serial.print("theta:");
  Serial.println(theta);
  Serial.print("x: ");
  Serial.print((int)(x / 300));
  Serial.print("\ty: ");
  Serial.println((int)(y / 300));
  //printGrid();

  int dist_cm = 51;
  //int dist_cm = Ping(pingPin);  Serial.println(dist_cm);
  /*
  if (dist_cm < 50)
  {
    x = x + sin(theta)*dist_cm;  
    y = y - cos(theta)*dist_cm;
    row = int(x/30);  
    col = int(y/30);
    if (row >= 0 && row <= 5 && col >= 0 && col <= 5)  
    {
      if (ogrid[row][col] <= 0.0) {ogrid[row][col] = 0.5;}
      ogrid[row][col] += (1.0 - ogrid[row][col])/2.0;
    }
  }
   */
  if( digitalRead(buttonPin) == 1) 
  {
    button_state = 1;
    markBlock(x,y);
  };
    
  //---- update robot config (x,y,theta)
  dx = PIE * RW * cos(theta) * ((double)(left_encoder_count + right_encoder_count) / TPR);
  x = x + dx;
  
  dy = PIE * RW * sin(theta) * ((double)(left_encoder_count + right_encoder_count) / TPR);
  y = y + dy;
  
  right_encoder_count = left_encoder_count = 0;
  
  markVisited(x,y);
  
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


      for (int i = 0; i < 4; i++)
    {
      leds.setColorRGB(0, 100, 0, 0);  // red
      delay(100);
      leds.setColorRGB(0, 0, 100, 0);  // green
      delay(100);
      leds.setColorRGB(0, 0, 0, 100);  // blue
      delay(100);
      leds.setColorRGB(0, 100, 100, 0);  // yellow
      delay(100);
      leds.setColorRGB(0, 100, 0, 100);  // purple
      delay(100);
    }
      

      //---- update state
      state = GOHOME;  
      leds.setColorRGB(0, 100, 0, 100); //purple
      
      TurnLeft90();
      theta  = fmod(theta + PIE_O2, PIE2);
      delay(500);
      TurnLeft90();
      theta  = fmod(theta + PIE_O2, PIE2);
      
      Straight(20,1);

      Sindex--;
    }
  }
  else
  if (state == GOHOME)
  {
    //---- use map to go home

    goHome();
    
    //---- stop
    //Straight( 0, 0 );    
    //delay(100);


    if(x < 300 && y < 200)
      //---- update state
      {
        state = INCLINE;
     
        Straight(0,0);
        delay(200);
        if(theta == (3*PIE)/2)
          TurnRight90();
          
        leds.setColorRGB(0, 100, 100, 0);  // yellow
        delay(2000);
      }
  }
  else
  if (state == INCLINE)
  {
    //if(!topOfIncline)
      inclineLight();    
  }
}


void PushToStack(char direction)
{
      int col = (int)(x / 300);
      int row = (int)(y / 300);
  
      Sdir[Sindex]  = direction ;
      Sxy[2 * Sindex]   = col;
      Sxy[( 2 * Sindex) + 1] = row;

      Sindex++; 
}

//======================================================================================
// Wander()
//======================================================================================
void Wander()
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
      
      PushToStack('r');		//opposite because we'll be facing other direction
      
      //---- turn left 90
      leds.setColorRGB(0, 0, 0, 100);
      TurnLeft90();
      //---- update robot config (theta)
      theta  = fmod(theta + PIE_O2, PIE2);
      delay(100);
    }
    else
    {
      
      PushToStack('l');
      
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

//======================================================================================
// inclineLight() crap
//======================================================================================
void inclineLight()
{
  int val = analogRead(lightPin);
  Serial.println(val);

  /*
  if(val>950){
    delay(1200);
    Straight(0,0);
    topOfIncline = true;
    return;
  }
  */
  
  if (val > 100)
  {
    if (stateIncline == LEFT_incline)
    {
      MOTOR.setSpeedDir1(22, DIRF);
      MOTOR.setSpeedDir2(14, DIRR);
      stateIncline = RIGHT_incline;
      leds.setColorRGB(0, 100, 0, 0);  		// red
      delay(1000);
    }
    else
    if (stateIncline == RIGHT_incline)
    {
      MOTOR.setSpeedDir1(14, DIRF);
      MOTOR.setSpeedDir2(22, DIRR);
      stateIncline = LEFT_incline;
      leds.setColorRGB(0, 100, 100, 100); 	 // white
      delay(1000);      
    }
  }  
}

//======================================================================================
// goHome() crap
//======================================================================================
void goHome()
{
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Y: ");
  Serial.println(y);

  double midX = (int)x % 300;
  double midY = (int)y % 300;
   
  Serial.print("midX: ");
  Serial.println(midX);
  Serial.print("midY: ");
  Serial.println(midY);
  
  int col = (int)(x / 300);
  int row = (int)(y / 300);

  int midLimit1 = 120;
  int midLimit2 = 180;

  if(col == Sxy[2 * Sindex] && row == Sxy[(2 * Sindex) + 1])
  if( (midX > midLimit1 && midX < midLimit2) || (midY > midLimit1 && midY < midLimit2) )
  {
    Straight(0,0);
    delay(100);
    if(Sdir[Sindex] == 'r')
      {
        TurnRight90();
        theta  = fmod(theta - PIE_O2, PIE2);
      }
    else
      {
        TurnLeft90();
        theta  = fmod(theta + PIE_O2, PIE2);
      }

      if(Sindex >= 0)
        Sindex--;

      Straight(20,1);
  }

  
}

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
  if(row >= 0 && col >= 0)
    grid[row][col] = 2;
}

void markVisited(double x, double y)
{
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
    MOTOR.setSpeedDir1(32, DIRR); MOTOR.setSpeedDir2(32, DIRR); 
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
    MOTOR.setSpeedDir1(32, DIRF); MOTOR.setSpeedDir2(31, DIRF); 
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
void Straight( int speed, int dirn )
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
      MOTOR.setSpeedDir2(speed, DIRR); 
    }
    else                  //-- bwd
    {
      MOTOR.setSpeedDir1(speed, DIRR); 
      MOTOR.setSpeedDir2(speed, DIRF); 
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
