#include <Servo.h>

Servo myservoHorizontal;
Servo myservoVertical;

const int photoresistorPin0 = A0;
const int photoresistorPin1 = A1;
const int photoresistorPin2 = A2;
const int photoresistorPin3 = A3;

void setup() 
{
  Serial.begin(9600);
  myservoHorizontal.attach(9);
  myservoVertical.attach(10);
  myservoHorizontal.write(90); //TODO: в дальнейшем убрать строку
  myservoVertical.write(90);   //TODO: в дальнейшем убрать строку
  delay(1500);
}

void loop()
{
  //Примеры Debug`a
  // Serial.print("angle");
  // Serial.println(myservo.read());
  int photoresistorValue0 = analogRead(photoresistorPin0);
  int photoresistorValue1 = analogRead(photoresistorPin1);
  int photoresistorValue2 = analogRead(photoresistorPin2);
  int photoresistorValue3 = analogRead(photoresistorPin3);
  
  if(photoresistorValue0 < photoresistorValue2)
  {
    myservoHorizontal.write(myservoHorizontal.read() +10);
    delay(100);
  }
  if(photoresistorValue0 > photoresistorValue2)
  {
    myservoHorizontal.write(myservoHorizontal.read() -10);
    delay(100);
  }
  
  if(photoresistorValue1 < photoresistorValue3)
  {
    myservoVertical.write(myservoVertical.read() +10);
    delay(100);
  }
  if(photoresistorValue1 > photoresistorValue3)
  {
    myservoVertical.write(myservoVertical.read() -10);
    delay(100);
  }
  
  delay(350);
}
