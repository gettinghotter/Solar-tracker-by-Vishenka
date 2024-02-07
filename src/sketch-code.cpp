// подключение библиотеки серво
#include <Servo.h>

// введение переменных, считывающих показания пинов, для дальнейших расчетов
const int photoPin0 = A0;
const int photoPin1 = A1;
const int photoPin2 = A2;
const int photoPin3 = A3;

// переменные для двух серво
Servo servoH;
int servohValue = 90;
Servo servoV;
int servovValue = 90;

void setup() 
{
  //подключение пинов к переменным и первичная настройка

  Serial.begin(9600);
  servoH.attach(9);
  servoV.attach(10);
  delay(1500);
}

void loop()
{
  // pin 0 - горизонтальный левый
  // pin 2 - горизонтальный правый
  // pin 1 - вертикальный левый
  // pin 3 - вертикальный правый


  // постоянное чтение значений фоторезисторов

  int photoValue0 = analogRead(photoPin0);
  int photoValue1 = analogRead(photoPin1);
  int photoValue2 = analogRead(photoPin2);
  int photoValue3 = analogRead(photoPin3);

  // введение переменных для двух потенциометров(dtime - для скорости перемещения серво, ...)

  int dtime = analogRead(4)/20;
  int tol = analogRead(5)/4;

  // усреднение значений из всех фоторезисторов

  int avgTop = (photoValue1 + photoValue3) / 2;     // среднее значение сверху
  int avgBottom = (photoValue0 + photoValue2) / 2;  // среднее значение снизу
  int avgLeft = (photoValue1 + photoValue0) / 2;    // среднее значение слева
  int avgRight = (photoValue3 + photoValue2) / 2;   // среднее значение справа

  // разница между усредненными значениями
  
  int diffVert = avgTop - avgBottom;   // разница между верхним и нижним
  int diffHoris = avgLeft - avgRight;  // разница между левым и правым


  // условие для движения вертикального серво
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
    // постоянное присваивание значений в серво
    servoV.write(servovValue);
  }

  // условие для движения горизонтального серво

  if (-1 * tol > diffHoris || diffHoris > tol)
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
    }

    // постоянное присваивание значений в серво
    servoH.write(servohValue);
  }
  delay(dtime);
} 