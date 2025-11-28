#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"
#include "LineFollow.h"
#include "ServoControl.h"
#include "Encoders.h"
#include "Ultrasonic.h"
#include "StepperControl.h"
#include "ESPComm.h"

void avoidObstacle()
{
  leftTurnEncoder(780);
  delay(300);
  forwardEncoder(1000);
  delay(300);
  rightTurnEncoder(780);
  delay(300);
  forwardEncoder(1800);
  delay(300);
  rightTurnEncoder(780);
  delay(300);
  forwardStrips(1);
  delay(300);
  leftTurnEncoder(780);
}

void manualPhase()
{
  while (true)
  {
    processCommand();

    if (lineFollowFlag == 1)
    {
      lineFollowV1(50);
    }

    if (lineFollowFlag == 0)
    {
      halt();
      lineFollowFlag = 3;
    }

    if (obstacleFlag)
    {
      avoidObstacle();
      obstacleFlag = false;
    }
  }
}

void autonomousPhase()
{
  Serial.println("LF_ON");
  sendCommandToEsp("LF_ON");
  forwardEncoder(500);
  lineFollowStrips(1, 'f');
  delay(500);
  rightTurnEncoder(780);
  delay(500);
  lineFollowEncoder(200);
  lineFollowStripsV1(1, 'f');
  Serial.println("LF_OFF");
  sendCommandToEsp("LF_OFF");
  delay(200);
  Serial.println("QR_SCAN");
  sendCommandToEsp("QR_SCAN");
  String command = waitForResponse();
  Serial.println("Command from ESP: " + command);
  // delay(5000);
  // forwardEncoder(400);
  // delay(300);
  // enableSteppers();
  // plateUp(800);
  // delay(500);
  // disableSteppers();
  // for (int i = 0; i < 2; i++)
  // {
  //     lineFollowEncoder(200);
  //     lineFollowStrips(2, 'f');
  //     delay(500);
  //     rightTurnEncoder(780);
  //     delay(500);
  // }
  // lineFollowEncoder(200);
  // lineFollowStrips(1, 'f');
  // delay(5000);
  // forwardEncoder(400);
  // delay(300);
  // enableSteppers();
  // plateDown(50);
  // delay(500);
  // disableSteppers();
  // delay(1000);
}

void setup()
{
  Serial.begin(9600);
  initESPComm(115200);
  initEncoders();
  initSensors();
  initMotors();
  initServos();
  initSteppers();
  disableSteppers();

  Serial.println("Code Running...");

  delay(5000);

  // Manual Phase
  // manualPhase();

  // Autonomous Phase
  autonomousPhase();

  // lineFollowEncoder(200);
  // lineFollowStrips(2);
  // delay(500);
  // rightTurnEncoder(780);
  // delay(500);
  // lineFollowEncoder(200);
  // lineFollowStrips(1);
  // delay(500);
  // lineFollowUltrasonic(15);

  // enableSteppers();
  // plateUp(800);
  // delay(200);
  // disableSteppers();
  // delay(3000);
  // enableSteppers();
  // plateDown(50);
  // delay(200);
  // disableSteppers();
  // delay(1000);
}

void loop()
{
  // readAllData();
  // printSensorVals(frontSensors);
  // Serial.println(getSonarDistance());
  // printEncoders();
  // readMapSingleSensor(MAP_PINS[0]);
  // checkMap();
  // Serial.println(readMapRed());
  // Serial.println(readMapBlue());
  // delay(50);
  // lineFollowV1(50);
}