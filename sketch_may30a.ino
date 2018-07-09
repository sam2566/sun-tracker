/* This code was written by me, Saurabh Mehta, for my final year project,Wireless Power Transmission 
 * with inclusion of sun tracking solar panel. I've been working on dual-axis sun tracker.
 * I have used 4 LDR's (light detecting resisters), each resister is setup at the corners of LDR.
 * The LDR's are connected to 4 different pins namely, ldrtl, ldrtr, ldrbl and ldrbr.
 * The  values obtained from LDR's are stored in various variables.
 * For vertical tracking average of top and bottom ldr values is taken and then compared with current values.
 * The reading is more in whichever direction, the servo moves in that particular direction.
 */
#include <Servo.h>          // initialize servo library

Servo servohori;            //Setting up horizontal servo

int servoh = 0;
int servoLimitHigh = 160;
int servoLimitLow = 20;

Servo servoverti;           //Setting up vertical servo
int servov = 0;
int servovLimitHigh = 160;
int servovLimitLow = 20;

int ldrtl = 2;              //Setting up LDR's
int ldrtr = 1;
int ldrbl = 3;
int ldrbr = 0;

void setup()                //Setup function, to be run only once
{
  servohori.attach(10);     //Horizontal Servo is attached to Pin 10
  servohori.write(0);
  servoverti.attach(9);     //Vertical Servo is attached to Pin 9
  servoverti.write(0);
  delay(500);

}

void loop() 
{
  servoh = servohori.read();              //reads the current position of horizontal Servo
  servov = servoverti.read();             //reads the current position of vertical Servo

  int topl = analogRead(ldrtl);           //Reads value of top-left ldr
  int topr = analogRead(ldrtr);           //Reads value of top-right ldr
  int botl = analogRead(ldrbl);           //Reads value of bottom-left ldr
  int botr = analogRead(ldrbr);           //Reads value of bottom-right ldr

  int avgtop = (topl + topr) / 2;         //average of top ldrs
  int avgbot = (botl + botr) / 2;         //average of bottom ldrs
  int avgleft = (topl + botl) / 2;        //average of left ldrs
  int avgright = (topr + botr) / 2;       //average of right ldrs

  if (avgtop < avgbot)                    //average of top and bottom ldrs is compared
  {
    servoverti.write(servov + 1);         //vertical servo is rotated by 1 degree
    if (servov > servoLimitHigh)          //Servo will be at max position if the value exceeds 160 degrees
    {
      servov = servoLimitHigh;
    }
    delay(10);
  }
  else if (avgbot < avgtop)                //average of top and bottom ldrs is compared
  {
   servoverti.write( servov -1 );          //Servo will be at min position if the value is below 20 degrees
   if (servov < servoLimitLow)
   {
    servov = servoLimitLow;
   }
   delay(10);
  }
  else                                     //if none of the above parameters are true, setup the servo at its current position.
  {
    servoverti.write(servov);
  }
  if (avgleft > avgright)                  // In similar way, we do the same thing with Left and Right LDR's and write the values to horizontal SERVO
  {
    servohori.write(servoh+1);
  
    if (servoh > servoLimitHigh)
    {
      servoh = servoLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh - 1);
    if (servoh < servoLimitLow)
    {
      servoh = servoLimitLow;
    }
    delay(10);
  }
  else
  {
    servohori.write(servoh);
  }
  delay(50);                              // introduce a delay of 50ms
  Serial.println("1=");                   // print the values obtained from ldrs on Serial 
  Serial.println(ldrtl);
  
  Serial.println(ldrtr);
  Serial.println(ldrbl);
  Serial.println(ldrbr);
}
