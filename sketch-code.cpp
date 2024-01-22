#include <Servo.h>

Servo servoHorizontal;
int servoh = 90;
Servo servoVertical;
int servov = 90;

const int photoresistorPin0 = A0;
const int photoresistorPin1 = A1;
const int photoresistorPin2 = A2;
const int photoresistorPin3 = A3;

void setup() 
{
  Serial.begin(9600);
  servoHorizontal.attach(9);
  servoVertical.attach(10);
  delay(1500);
}

void loop()
{
  // pin 0 - horisontal left
  // pin 2 - horisontal right
  // pin 1 - vertical left
  // pin 3 - vertical right

  int photoresistorValue0 = analogRead(photoresistorPin0);
  int photoresistorValue1 = analogRead(photoresistorPin1);
  int photoresistorValue2 = analogRead(photoresistorPin2);
  int photoresistorValue3 = analogRead(photoresistorPin3);

  int dtime = analogRead(4)/20;
  int tol = analogRead(5)/4;

  int avgTop = (photoresistorValue1 + photoresistorValue3) / 2;     // average value top
  int avgBottom = (photoresistorValue0 + photoresistorValue2) / 2;  // average value bottom
  int avgLeft = (photoresistorValue1 + photoresistorValue0) / 2;    // average value left
  int avgRight = (photoresistorValue3 + photoresistorValue2) / 2;   // average value right
  
  int diffVert = avgTop - avgBottom;   // diffirence of top and bottom
  int diffHoris = avgLeft - avgRight;  // diffirence of left and right

  // check if the diffirence is in the tolerance else change vertical angle
  if (-1 * tol > diffVert || diffVert > tol)
  {
    if (avgTop > avgBottom)
    {
      servov = ++servov;
      if (servov > 180)
      {
        servov = 180;
      }
    }
    else if (avgTop < avgBottom)
    {
      servov= --servov;
      if (servov < 0)
      {
        servov = 0;
      }
    }
    servoVertical.write(servov);
  }

  // check if the diffirence is in the tolerance else change horizontal angle
  if (-1*tol > diffHoris || diffHoris > tol)
  {
    if (avgLeft > avgRight)
    {
      servoh = --servoh;
      if (servoh < 0)
      {
        servoh = 0;
      }
    }
    else if (avgLeft < avgRight)
    {
      servoh = ++servoh;
      if (servoh > 180)
      {
        servoh = 180;
      }
    }
    else if (avgLeft == avgRight)
    {
      // nothing
    }
    servoHorizontal.write(servoh);
  }
  delay(dtime);
} 
