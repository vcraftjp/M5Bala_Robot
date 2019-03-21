//
// Servo.hpp
//
#pragma once

#include <M5Stack.h>

#define SERVO_CHANNEL 0
#define PULSE_MS 20
#define RESO_BITS 10

//
// Servo class
//
class Servo {
public:
	void begin(uint8_t _pin) {
		pin = _pin;
		pinMode(pin, OUTPUT);
		ledcSetup(SERVO_CHANNEL, 1000 / PULSE_MS, RESO_BITS);
		ledcAttachPin(pin, SERVO_CHANNEL);
	}
	void end() {
		ledcDetachPin(pin);
	}
	void setAngle(float angle, float maxAngle, float minDuty, float maxDuty) {
		float duty = (angle + maxAngle) / (maxAngle * 2) * (maxDuty - minDuty) + minDuty;
		int n = round(duty  * (1 << RESO_BITS) / PULSE_MS);
		ledcWrite(SERVO_CHANNEL, n);
	}

private:
	uint8_t pin;
};
