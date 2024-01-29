#include <Servo.h>

const int photoPin0 = A0;
const int photoPin1 = A1;
const int photoPin2 = A2;
const int photoPin3 = A3;

Servo servoH;
int servohValue = 90;
Servo servoV;
int servovValue = 90;

void setup() 
{
  Serial.begin(9600);
  servoH.attach(9);
  servoV.attach(10);
  delay(1500);
}

void loop()
{
  // pin 0 - horisontal left
  // pin 2 - horisontal right
  // pin 1 - vertical left
  // pin 3 - vertical right

  int photoValue0 = analogRead(photoPin0);
  int photoValue1 = analogRead(photoPin1);
  int photoValue2 = analogRead(photoPin2);
  int photoValue3 = analogRead(photoPin3);

  int dtime = analogRead(4)/20;
  int tol = analogRead(5)/4;

  int avgTop = (photoValue1 + photoValue3) / 2;     // average value top
  int avgBottom = (photoValue0 + photoValue2) / 2;  // average value bottom
  int avgLeft = (photoValue1 + photoValue0) / 2;    // average value left
  int avgRight = (photoValue3 + photoValue2) / 2;   // average value right
  
  int diffVert = avgTop - avgBottom;   // diffirence of top and bottom
  int diffHoris = avgLeft - avgRight;  // diffirence of left and right

  if (-1 * tol > diffVert || diffVert > tol)
  {
    if (avgTop > avgBottom)
    {
      servovValue = ++servovValue;
      if (servovValue > 180)
      {
        servovValue = 180;
      }
    }
    else if (avgTop < avgBottom)
    {
      servovValue= --servovValue;
      if (servovValue < 0)
      {
        servovValue = 0;
      }
    }
    servoV.write(servovValue);
  }

  if (-1*tol > diffHoris || diffHoris > tol)
  {
    if (avgLeft > avgRight)
    {
      servohValue = --servohValue;
      if (servohValue < 0)
      {
        servohValue = 0;
      }
    }
    else if (avgLeft < avgRight)
    {
      servohValue = ++servohValue;
      if (servohValue > 180)
      {
        servohValue = 180;
      }
    }
    else if (avgLeft == avgRight)
    {
      // nothing
    }
    servoH.write(servohValue);
  }
  delay(dtime);
} 
