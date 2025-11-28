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
  forwardEncoder(1200);
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
  delay(300);
  lineFollowStripsV1(1, 'f');
  delay(300);
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
  lineFollowStripsV1(2, 'f');
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
  String a_qr = waitForResponse();
  a_qr.replace("QR1", "");
  a_qr.replace("+", "");
  Serial.println("Command from ESP: " + a_qr);
  // delay(5000);
  forwardEncoder(500);
  delay(300);
  Serial.println("MC_ON");
  sendCommandToEsp("MC_ON");
  delay(50);
  Serial.println("LF_UP_STARTED");
  sendCommandToEsp("LF_UP_STARTED");
  enableSteppers();
  plateUp(800);
  delay(500);
  disableSteppers();
  Serial.println("LF_UP_COMPLETED");
  sendCommandToEsp("LF_UP_COMPLETED");
  delay(50);
  Serial.println("MC_OFF");
  sendCommandToEsp("MC_OFF");
  delay(50);
  Serial.println("TR C");
  sendCommandToEsp("TR C");
  delay(50);
  Serial.println("LF_ON");
  sendCommandToEsp("LF_ON");
  lineFollowStripsSonar(2, 'f');
  if (getSonarDistance() <= 16 && getSonarDistance() > 0)
  {
    delay(5000);
    if (getSonarDistance() <= 16 && getSonarDistance() > 0)
    {
      Serial.println("OBS_STARTED");
      sendCommandToEsp("OBS_STARTED");
      avoidObstacle();
      Serial.println("OBS_COMPLETED");
      sendCommandToEsp("OBS_COMPLETED");
    }
    else
    {
      lineFollowStripsV1(1, 'f');
      delay(500);
    }
  }
  else
  {
    Serial.println("NO_OBS");
    sendCommandToEsp("NO_OBS");
  }
  rightTurnEncoder(780);
  delay(500);
  lineFollowEncoder(200);
  lineFollowStripsV1(3, 'f');
  delay(500);
  rightTurnEncoder(780);
  delay(500);
  lineFollowEncoder(200);
  lineFollowStripsV1(1, 'f');
  Serial.println("LF_OFF");
  sendCommandToEsp("LF_OFF");
  delay(500);
  Serial.println("QR_SCAN");
  sendCommandToEsp("QR_SCAN");
  String c_qr = waitForResponse();
  c_qr.replace("QR1", "");
  c_qr.replace("+", "");
  Serial.println("Command from ESP: " + c_qr);
  if (a_qr == "LP-1" && c_qr == "UP-1")
  {
    forwardEncoder(500);
    delay(500);
    Serial.println("LF_DOWN_STARTED");
    sendCommandToEsp("LF_DOWN_STARTED");
    enableSteppers();
    plateDown(800);
    delay(500);
    disableSteppers();
    Serial.println("LF_DOWN_COMPLETED");
    sendCommandToEsp("LF_DOWN_COMPLETED");
    delay(50);
    Serial.println("TR B");
    sendCommandToEsp("TR B");
    delay(50);
    Serial.println("LF_ON");
    sendCommandToEsp("LF_ON");
    lineFollowStripsV1(2, 'f');
    delay(300);
    rightTurnEncoder(780);
    delay(300);
    lineFollowEncoder(200);
    lineFollowStripsV1(1, 'f');
    delay(300);
    rightTurnEncoder(780);
    delay(300);
    lineFollowEncoder(200);
    lineFollowStripsV1(1, 'f');
    delay(50);
    Serial.println("LF_OFF");
    sendCommandToEsp("LF_OFF");
    delay(300);

    Serial.println("QR_SCAN");
    sendCommandToEsp("QR_SCAN");
    String b_qr = waitForResponse();
    b_qr.replace("QR1", "");
    b_qr.replace("+", "");
    Serial.println("Command from ESP: " + b_qr);

    forwardEncoder(600);
    delay(300);
    Serial.println("LF_UP_STARTED");
    sendCommandToEsp("LF_UP_STARTED");
    enableSteppers();
    plateUp(800);
    delay(500);
    disableSteppers();
    Serial.println("LF_UP_COMPLETED");
    sendCommandToEsp("LF_UP_COMPLETED");
    delay(50);
    Serial.println("TR D");
    sendCommandToEsp("TR D");
    delay(50);
    Serial.println("LF_ON");
    sendCommandToEsp("LF_ON");
    lineFollowStripsSonar(2, 'f');
    delay(500);
    rightTurnEncoder(780);
    delay(500);
    lineFollowEncoder(200);
    lineFollowStripsV1(3, 'f');
    delay(500);
    rightTurnEncoder(780);
    delay(500);

    lineFollowEncoder(200);
    lineFollowStripsSonar(1, 'f');
    if (getSonarDistance() <= 16 && getSonarDistance() > 0)
    {
      delay(5000);
      if (getSonarDistance() <= 16 && getSonarDistance() > 0)
      {
        Serial.println("OBS_STARTED");
        sendCommandToEsp("OBS_STARTED");
        avoidObstacle();
        Serial.println("OBS_COMPLETED");
        sendCommandToEsp("OBS_COMPLETED");
      }
      else
      {
        lineFollowStripsV1(1, 'f');
      }
    }
    else
    {
      Serial.println("NO_OBS");
      sendCommandToEsp("NO_OBS");
    }

    Serial.println("LF_OFF");
    sendCommandToEsp("LF_OFF");
    delay(500);
    Serial.println("QR_SCAN");
    sendCommandToEsp("QR_SCAN");
    String d_qr = waitForResponse();
    d_qr.replace("QR1", "");
    d_qr.replace("+", "");
    Serial.println("Command from ESP: " + d_qr);

    forwardEncoder(500);
    delay(300);
    Serial.println("MC_ON");
    sendCommandToEsp("MC_ON");
    delay(50);
    Serial.println("LF_DOWN_STARTED");
    sendCommandToEsp("LF_DOWN_STARTED");
    enableSteppers();
    plateDown(800);
    delay(500);
    disableSteppers();
    Serial.println("LF_DOWN_COMPLETED");
    sendCommandToEsp("LF_DOWN_COMPLETED");
    delay(50);
    Serial.println("MC_OFF");
    sendCommandToEsp("MC_OFF");
    delay(50);

    Serial.println("TR START");
    sendCommandToEsp("TR START");
    delay(50);
    lineFollowStripsV1(2, 'f');
    delay(500);
    rightTurnEncoder(780);
    delay(500);
    lineFollowEncoder(2700);
  }
  else if (a_qr == "LP-1" && c_qr == "UP-2")
  {
    // TODO
  }
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
}

void loop()
{
  // readAllData();
  printSensorVals(rightSensors);
  // Serial.println(getSonarDistance());
  // printEncoders();
  // readMapSingleSensor(MAP_PINS[0]);
  // checkMap();
  // Serial.println(readMapRed());
  // Serial.println(readMapBlue());
  delay(50);
  // lineFollowV1(50);
}