#pragma once

#ifndef _LINEFOLLOW_H_
#define _LINEFOLLOW_H_

#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"
#include "Ultrasonic.h"

void lineFollow(char direction = 'f', int speed = 150)
{
  // black -> 1, white -> 0
  bool l, m, r;

  if (direction == 'f')
  {
    l = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
    m = analogRead(frontSensors[1]) > BLACK_VALUE ? 0 : 1;
    r = analogRead(frontSensors[2]) > BLACK_VALUE ? 0 : 1;

    if (l == 1 && m == 1 && r == 1)
    {
      forward(speed, speed);
    }
    else if (l == 0 && m == 1 && r == 0)
    {
      forward(speed, speed);
    }
    else if (l == 1 && m == 0 && r == 0)
    {
      leftInverse(speed, speed);
    }
    else if (l == 0 && m == 0 && r == 1)
    {
      rightInverse(speed, speed);
    }
    else
    {
      forward(speed, speed);
    }
  }
  else if (direction == 'b')
  {
    l = analogRead(backSensors[0]) > BLACK_VALUE ? 0 : 1;
    m = analogRead(backSensors[1]) > BLACK_VALUE ? 0 : 1;
    r = analogRead(backSensors[2]) > BLACK_VALUE ? 0 : 1;

    if (l == 1 && m == 1 && r == 1)
    {
      // Serial.println("Back");
      backward(speed, speed);
    }
    else if (l == 0 && m == 1 && r == 0)
    {
      // Serial.println("Back");
      backward(speed, speed);
    }
    else if (l == 1 && m == 0 && r == 0)
    {
      // Serial.println("Left");
      leftInverse(speed, speed);
    }
    else if (l == 0 && m == 0 && r == 1)
    {
      // Serial.println("Right");
      rightInverse(speed, speed);
    }
    else
    {
      // Serial.println("Back");
      backward(speed, speed);
    }
  }
  else if (direction == 'l')
  {
    l = analogRead(leftSensors[0]) > BLACK_VALUE ? 0 : 1;
    m = analogRead(leftSensors[1]) > BLACK_VALUE ? 0 : 1;
    r = analogRead(leftSensors[2]) > BLACK_VALUE ? 0 : 1;

    if (l == 1 && m == 1 && r == 1)
    {
      // Serial.println("Back");
      left(speed, speed);
    }
    else if (l == 0 && m == 1 && r == 0)
    {
      // Serial.println("Back");
      left(speed, speed);
    }
    else if (l == 1 && m == 0 && r == 0)
    {
      // Serial.println("Left");
      leftInverse(speed, speed);
    }
    else if (l == 0 && m == 0 && r == 1)
    {
      // Serial.println("Right");
      rightInverse(speed, speed);
    }
    else
    {
      // Serial.println("Back");
      left(speed, speed);
    }
  }
  else if (direction == 'r')
  {
    l = analogRead(rightSensors[0]) > BLACK_VALUE ? 0 : 1;
    m = analogRead(rightSensors[1]) > BLACK_VALUE ? 0 : 1;
    r = analogRead(rightSensors[2]) > BLACK_VALUE ? 0 : 1;

    if (l == 1 && m == 1 && r == 1)
    {
      // Serial.println("Back");
      right(speed, speed);
    }
    else if (l == 0 && m == 1 && r == 0)
    {
      // Serial.println("Back");
      right(speed, speed);
    }
    else if (l == 1 && m == 0 && r == 0)
    {
      // Serial.println("Left");
      leftInverse(speed, speed);
      // forward(speed, speed);
    }
    else if (l == 0 && m == 0 && r == 1)
    {
      // Serial.println("Right");
      rightInverse(speed, speed);
      // backward(speed, speed);
    }
    else
    {
      // Serial.println("Back");
      right(speed, speed);
    }
  }
}

void lineFollowV1(int speed = 150)
{
  // black -> 1, white -> 0
  bool l, m, r;

  l = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
  m = analogRead(frontSensors[1]) > BLACK_VALUE ? 0 : 1;
  r = analogRead(frontSensors[2]) > BLACK_VALUE ? 0 : 1;

  if (l == 1 && m == 1 && r == 1)
  {
    forward(speed, speed);
  }
  else if (l == 0 && m == 1 && r == 0)
  {
    forward(speed, speed);
  }
  else if (l == 1 && m == 0 && r == 0)
  {
    leftInverse(speed, speed);
  }
  else if (l == 1 && m == 1 && r == 0)
  {
    leftInverse(speed, speed);
  }
  else if (l == 0 && m == 0 && r == 1)
  {
    rightInverse(speed, speed);
  }
  else if (l == 0 && m == 1 && r == 1)
  {
    rightInverse(speed, speed);
  }
  else
  {
    forward(speed, speed);
  }
}

void lineFollowStrips(int stripsToMove, char direction = 'f', int speed = 150)
{
  int stripCount = 0;
  while (true)
  {
    int sensorOnLine = 0;

    if (direction == 'f')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(rightSensors[1]) > BLACK_VALUE ? 0 : 1;
    }
    else if (direction == 'b')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(rightSensors[2]) > BLACK_VALUE ? 0 : 1;
    }
    else if (direction == 'l')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
    }
    else if (direction == 'r')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(backSensors[0]) > BLACK_VALUE ? 0 : 1;
    }

    unsigned long currentMillis = millis();
    if (sensorOnLine && !prevLine)
    {
      stripCount++;
      prevLine = true;
      previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis > intervalMillis)
    {
      prevLine = false;
    }

    if (stripCount < stripsToMove)
    {
      lineFollow(direction, speed);
      // Serial.print("Strip# ");
      // Serial.println(stripCount);
    }
    else
    {
      // Serial.println("Halt!");
      halt();
      return;
    }
  }
}

void lineFollowStripsV1(int stripsToMove, char direction = 'f', int speed = 150)
{
  int stripCount = 0;
  while (true)
  {
    int sensorOnLine = 0;

    if (direction == 'f')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(rightSensors[0]) > BLACK_VALUE ? 0 : 1;
    }
    else if (direction == 'b')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(rightSensors[2]) > BLACK_VALUE ? 0 : 1;
    }
    else if (direction == 'l')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
    }
    else if (direction == 'r')
    {
      // Black -> 1, White -> 0
      sensorOnLine = analogRead(backSensors[0]) > BLACK_VALUE ? 0 : 1;
    }

    unsigned long currentMillis = millis();
    if (sensorOnLine && !prevLine)
    {
      stripCount++;
      prevLine = true;
      previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis > intervalMillis)
    {
      prevLine = false;
    }

    if (stripCount < stripsToMove)
    {
      lineFollow(direction, speed);
      // Serial.print("Strip# ");
      // Serial.println(stripCount);
    }
    else
    {
      // Serial.println("Halt!");
      halt();
      return;
    }
  }
}


void lineFollowUltrasonic(int distanceToStop, int speed = 150)
{
  while (true)
  {
    if (getSonarDistance() > distanceToStop || getSonarDistance() == 0)
    {
      lineFollow('f', speed);
      Serial.print("Distance# ");
      Serial.println(getSonarDistance());
    }
    else
    {
      // Serial.println("Halt!");
      halt();
      return;
    }
  }
}

void lineFollowEncoder(uint32_t ticksToMove, char direction = 'f', int speed = 150)
{
  flEncoder.ticks = 0;
  while (flEncoder.ticks < ticksToMove)
  {
    Serial.println();
    lineFollow(direction, speed);
  }
  halt();
}

#endif //_LINEFOLLOW_H