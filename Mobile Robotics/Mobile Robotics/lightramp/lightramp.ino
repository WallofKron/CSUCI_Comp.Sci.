#include "motordriver_4wd.h"
#include "seeed_pwm.h"
#include <ChainableLED.h>


#define NUM_LEDS 1
ChainableLED leds(SCL, SDA, NUM_LEDS);


enum {LEFT, RIGHT} state;
int lightPin = A0;
void setup()
{
  digitalWrite(lightPin, INPUT_PULLUP);
  MOTOR.init();
  MOTOR.setSpeedDir1(20, DIRF);
  MOTOR.setSpeedDir2(12, DIRR);
  state = RIGHT;
  delay(100);
  
  Serial.begin(9600);
}

void loop()
{
  int val = analogRead(lightPin);
  Serial.println(val);
  
  if(val>950){
    delay(1200);
    MOTOR.setSpeedDir1(0, DIRF);
    MOTOR.setSpeedDir2(0, DIRR); 

 for (int i = 0; i < 10; i++)
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

    
  } else if (val > 100)
  {
    if (state == LEFT)
    {
      MOTOR.setSpeedDir1(20, DIRF);
      MOTOR.setSpeedDir2(12, DIRR);
      state = RIGHT;
      delay(400);
    }
    else
    if (state == RIGHT)
    {
      MOTOR.setSpeedDir1(12, DIRF);
      MOTOR.setSpeedDir2(20, DIRR);
      state = LEFT;
      delay(400);      
    }
  }

}
