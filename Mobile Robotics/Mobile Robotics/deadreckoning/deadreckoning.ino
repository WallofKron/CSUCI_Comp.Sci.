#include "motordriver_4wd.h"
#include <seeed_pwm.h>
#include <ChainableLED.h>
#include <math.h>

int right_encoder_count = 0, left_encoder_count = 0;
int right_dirn = 1, left_dirn = 1 ;             //initial values for encoders and direction

const double TPR = 70.0;
const double WheelRad = 40.0;

const double pi = 3.1415926;

const double bounds = 1500;

double x = 100.0, y = 100.0 ;
double dx = 0.0, dy = 0.0 ;
double theta = (PI/2), dtheta = 0.0, theta_turn = 0.0;


//const double wheelbase = 195.0; //End to End
const double wheelbase = 175.0; //Middle to Middle



typedef enum state{FWD,REV,TRN} STATE;
int state;


void RightEncoder()
{
  right_encoder_count += right_dirn;
}


void LeftEncoder()
{
  left_encoder_count += left_dirn;
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
    MOTOR.init();
    Serial.begin(9600);
    attachInterrupt(0, RightEncoder, CHANGE);
    attachInterrupt(1, LeftEncoder, CHANGE);
    setSpeed(15);  
    state = FWD;
}

void loop() {
    delay(150);

   if(state == FWD || state == REV){
    dx = pi*WheelRad*cos(theta) * ((double)((right_encoder_count + left_encoder_count)/TPR));
    x = x+dx;
    dy = pi*WheelRad*sin(theta) * ((double)((right_encoder_count + left_encoder_count)/TPR));
    y = y+dy;
   }

   
if(state == FWD || state == REV){
    dtheta = PI*(WheelRad / (wheelbase/2.0)) * ((double)(abs(right_encoder_count) - abs(left_encoder_count))/TPR);
  
  }else if(state == TRN){
    
    if(right_dirn == -1){
      
     dtheta = PI * (WheelRad / (wheelbase/2.0)) * ((double)(right_encoder_count) / TPR);
    
    }else{
     dtheta = PI * (WheelRad / (wheelbase/2.0)) * ((double)(left_encoder_count) / TPR);
    }
  }

  theta = fmod(theta + dtheta, 2*PI);
  theta_turn = theta_turn + dtheta;
  
    Serial.print("right_encoder_count: "); 
    Serial.print(right_encoder_count);
    Serial.print('\t');
    Serial.print("left_encoder_count: "); 
    Serial.println(left_encoder_count);
    Serial.print("State: ");
    Serial.println(state);
    Serial.print("x: ");
    Serial.print(x);
    Serial.print("\ty: ");
    Serial.println(y);
    Serial.print("theta: ");
    int thetaPrint = (theta * 180) / (pi);
    Serial.println(thetaPrint);
    Serial.print("dtheta: ");
    Serial.println(dtheta);
    Serial.print("theta turn: ");
    Serial.println(theta_turn);
    Serial.println(fabs(fabs(theta_turn) - (PI/2)));
    Serial.println("\n");  

    if((state == FWD) && (x < 0 + 60 || x > bounds - 60 || y < 0 + 60 || y > bounds - 60)){
      state = REV;
      right_encoder_count = 0;
        left_encoder_count = 0;
      theta_turn = 0.0;
      setSpeed(-15);
      left_dirn=-1;
      right_dirn=-1;
      delay(150);
      
      }
     else if(state == REV){
        Serial.println("\tTURNING!!!");
        theta_turn = 0.0;
        state = TRN;
        MOTOR.setSpeedDir1(20,DIRF);
        MOTOR.setSpeedDir2(20,DIRF);
        right_encoder_count = 0;
        left_encoder_count = 0;
        right_dirn = -1;
      }
      
    else if((state == TRN) && (fabs(fabs(theta_turn) - (PI/2)) < 0.3)){
       Serial.println("\tStraight!!!");
       state = FWD;
       right_dirn = 1;
       stopMotor();
       setSpeed(15);
       
       right_encoder_count = left_encoder_count = 0;
    }   
      
    Serial.println("Continue");
    right_encoder_count = 0;
    left_encoder_count = 0;

}
