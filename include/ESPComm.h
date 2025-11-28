#pragma once

#ifndef _ESP_COMM_H_
#define _ESP_COMM_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Motors.h"
#include "StepperControl.h"

uint8_t lineFollowFlag = 0;
bool obstacleFlag = false;

void initESPComm(unsigned long baudRate = 115200)
{
  Serial2.begin(baudRate);
}

void readAllData()
{
  while (Serial2.available())
  {
    String c = Serial2.readStringUntil('\n');
    Serial.println(c);
  }
}

void sendCommandToEsp(const String &command)
{
  Serial2.println(command);
}

String waitForResponse() {
  while (!Serial2.available()) {
    // Wait for data
  }
  String response = Serial2.readStringUntil('\n');
  Serial.println("Response from ESP: " + response);
  return response;
}

void processCommand()
{
  if (Serial2.available())
  {
    return;
  }

  String command = Serial2.readStringUntil('\n');
  command.trim();

  if (command == "Forward")
  {
    Serial.println("Forward Command Received!");
    forward();
  }
  else if (command == "Backward")
  {
    Serial.println("Backward Command Received!");
    backward();
  }
  else if (command == "Left")
  {
    Serial.println("Left Command Received!");
    leftInverse();
  }
  else if (command == "Right")
  {
    Serial.println("Right Command Received!");
    rightInverse();
  }
  else if (command == "Stop")
  {
    Serial.println("Stop Command Received!");
    halt();
  }
  else if (command == "MC_UP")
  {
    Serial.println("Mechanism Up Command Received!");
    enableSteppers();
    plateUp(800);
    disableSteppers();
  }
  else if (command == "MC_DOWN")
  {
    Serial.println("Mechanism Down Command Received!");
    enableSteppers();
    plateDown(800);
    disableSteppers();
  }
  else if (command == "LN_ON")
  {
    Serial.println("Line follow start Command Received!");
    lineFollowFlag = 1;
  }
  else if (command == "LN_OFF")
  {
    Serial.println("Line follow stop Command Received!");
    lineFollowFlag = 0;
  }
  else if (command == "OBS_AVOID")
  {
    Serial.println("Obstacle avoid Command Received!");
    obstacleFlag = true;
  }
  else
  {
    Serial.println("Unknown command: " + command);
  }
}

#endif //_ESP_COMM_H_