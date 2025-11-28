#pragma once
#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

#include <NewPing.h>

#define TRIG A11
#define ECHO A10

#define MAX_DISTANCE 200

NewPing sonarFront(TRIG, ECHO, MAX_DISTANCE);

int getSonarDistance()
{
  return sonarFront.ping_cm(MAX_DISTANCE);
}

#endif //_ULTRASONIC_H_
