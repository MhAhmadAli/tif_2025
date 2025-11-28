#pragma once

#ifndef _STEPPERCONTROL_H_
#define _STEPPERCONTROL_H_

#include <Arduino.h>
#include <AccelStepper.h>

#define EN_PIN 34

#define X_STEP 36
#define X_DIR 38
#define Y_STEP 40
#define Y_DIR 42

AccelStepper stepperX(AccelStepper::DRIVER, X_STEP, X_DIR);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP, Y_DIR);

void initSteppers()
{
  pinMode(EN_PIN, OUTPUT);

  stepperX.setMaxSpeed(200);
  stepperX.setAcceleration(100);
  stepperY.setMaxSpeed(200);
  stepperY.setAcceleration(100);
}

void enableSteppers()
{
  digitalWrite(EN_PIN, LOW); // Enable the stepper drivers
}

void disableSteppers()
{
  digitalWrite(EN_PIN, HIGH); // Disable the stepper drivers
}

void plateUp(int position)
{
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);

  stepperX.moveTo(position);
  stepperY.moveTo(-position);

  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
  {
    stepperX.run();
    stepperY.run();
  }
}

void plateDown(int position)
{
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);

  stepperX.moveTo(-position);
  stepperY.moveTo(position);

  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
  {
    // Serial.println("X Distance to go: " + String(stepperX.distanceToGo()));
    // Serial.println("Y Distance to go: " + String(stepperY.distanceToGo()));
    stepperX.run();
    stepperY.run();
  }
}

void stepperMoveToPosition(int position)
{
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);

  stepperX.moveTo(position);
  stepperY.moveTo(-position);

  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0)
  {
    stepperX.run();
    stepperY.run();
  }
}

#endif //_STEPPERCONTROL_H_