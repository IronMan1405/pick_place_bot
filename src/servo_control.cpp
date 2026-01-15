#include "servo_control.h"
#include "config.h"
#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo1;
Servo servo2;

void servoInit() {
    servo1.attach(SERVO_1_PIN, SERVO_MIN_US, SERVO_MAX_US);
    servo2.attach(SERVO_2_PIN, SERVO_MIN_US, SERVO_MAX_US);

    servo1.write(90);
    servo2.write(90);
}

void setServoAngle(uint8_t id, int angle) {
    angle = constrain(angle, 0, 180);

    Serial.println(id);
    Serial.println(angle);

    if (id == 1) servo1.write(angle);
    if (id == 2) servo2.write(angle);
}

void servoStop() {
    servo1.detach();
    servo2.detach();
}