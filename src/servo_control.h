#pragma once

#include <Arduino.h>

void servoInit();
void setServoAngle(uint8_t id, int angle);
void servoStop();