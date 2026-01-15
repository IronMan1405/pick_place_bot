#include "motor_control.h"
#include "config.h"
#include <Arduino.h>

void setMotorSpeed(int in1, int in2, int enable, int speed) {
    speed = constrain(speed, -MAX_PWM, MAX_PWM);

    if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    }

    analogWrite(enable, speed);
}

void motorInit() {
    pinMode(ENA_1, OUTPUT);
    pinMode(IN1_1, OUTPUT);
    pinMode(IN2_1, OUTPUT);

    pinMode(ENB_1, OUTPUT);
    pinMode(IN3_1, OUTPUT);
    pinMode(IN4_1, OUTPUT);

    pinMode(ENA_2, OUTPUT);
    pinMode(IN1_2, OUTPUT);
    pinMode(IN2_2, OUTPUT);

    pinMode(ENB_2, OUTPUT);
    pinMode(IN3_2, OUTPUT);
    pinMode(IN4_2, OUTPUT);

    stopAllMotors();
}

void drive(float x, float y) {
    int leftSpeed = (x + y) * MAX_PWM;
    int rightSpeed = (x - y) * MAX_PWM;

    setMotorSpeed(IN1_1, IN2_1, ENA_1, leftSpeed);
    setMotorSpeed(IN3_1, IN4_1, ENA_1, leftSpeed);

    setMotorSpeed(IN1_2, IN2_2, ENA_2, rightSpeed);
    setMotorSpeed(IN3_2, IN4_2, ENB_2, rightSpeed);
}

void stopAllMotors() {
    drive(0, 0);
}