#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"
#include "LineFollow.h"
#include "ServoControl.h"
#include "Encoders.h"
#include "MapArray.h"
#include "Ultrasonic.h"

void setup()
{
    Serial.begin(9600);
    initEncoders();
    initSensors();
    initMotors();
    initServos();
    initMapArray();

    Serial.println("Code Running...");

    // lineFollowStrips(1, 'f');
    // delay(500);
    // rightTurnEncoder(780);
    // delay(500);
    // lineFollowEncoder(200);
    // lineFollowStrips(1, 'f');
    // delay(5000);
    // for (int i = 0; i < 2; i++)
    // {
    //     lineFollowEncoder(200);

    //     lineFollowStrips(2, 'f');
    //     lineFollowStrips(2, 'f');
    //     delay(500);
    //     rightTurnEncoder(780);
    //     delay(500);
    // }
    // lineFollowEncoder(200);
    // lineFollowStrips(1, 'f');
    // delay(5000);
    // lineFollowEncoder(200);
    // lineFollowStrips(2);
    // delay(500);
    // rightTurnEncoder(780);
    // delay(500);
    // lineFollowEncoder(200);
    // lineFollowStrips(1);
    // delay(500);
    lineFollowUltrasonic(15);
}

void loop()
{
    // printSensorVals(rightSensors);
    // Serial.println(getSonarDistance());
    // printEncoders();
    // readMapSingleSensor(MAP_PINS[0]);
    // checkMap();
    // Serial.println(readMapRed());
    // Serial.println(readMapBlue());
    // delay(50);
}