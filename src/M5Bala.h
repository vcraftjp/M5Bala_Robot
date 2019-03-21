// The MIT License (MIT)
//
// Copyright (c) 2018 M5Stack
// Author: bin@m5stack.com (0x1abin)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <M5Stack.h>
#include <MPU6050_tockn.h>

#define MOTOR_RPM           150
#define MAX_PWM             255
#define DEAD_ZONE           20

#define M5GO_WHEEL_ADDR     0x56
#define MOTOR_CTRL_ADDR     0x00
#define ENCODER_ADDR        0x04

class Preferences;

class M5Bala {
	public:
		M5Bala();
		M5Bala(TwoWire &w);

		void begin(bool isBalance = true, bool useIMU = true);
		bool run();
		void PIDCompute();
		void setMotor(int16_t pwm0, int16_t pwm1);
		bool readEncder();
		uint8_t i2c_readByte(uint8_t address, uint8_t subAddress);

		void autoTuneGyroOffset(Preferences& prefs);
		void setGyroOffsets(Preferences& prefs);

		void setAngleOffset(float offset) { angle_offset = offset; };
		float getAngle() { return pitch; };
		int16_t getSpeed0() { return speed_input0; };
		int16_t getSpeed1() { return speed_input1; };
		int16_t getOut0() { return pwm_out0; };
		int16_t getOut1() { return pwm_out1; };

		MPU6050 *imu;
		int16_t left_offset, right_offset;
		int16_t forward_offset;

		// control
		void stop();
		void move(int16_t speed, int duration = 0);
		void turn(int16_t speed, int duration = 0);
		void rotate(int16_t speed, int duration = 0);
		void setAutoStraight(float speedWeight = 1.0, float encoderGain = 0.5);
		void startRotate() { sumOfSpeedDiff = 0; }
		int getRotateAngle();

		void wakeUp();
		void shutdown();
		int getError() { return (int)wireError; }

		bool isBalance;
		bool isTumbled;

	private:
		enum State { STOP, RUN, WAKE_UP };

		TwoWire *wire;
		float yaw, pitch, roll;
		int16_t speed_input0, speed_input1;
		int16_t pwm_out0, pwm_out1;
		int8_t angle_offset;
		uint32_t loop_interval;
		float K1, K2, K3, K4, K5;
		uint8_t imu_id;

		uint8_t wireError;
		State state;
		float encoderGain; // encoder filter
		unsigned long startTick;
		int duration;

		bool isMoveStraight;
		float speedWeight;
		int sumOfSpeedDiff;

		void setDuration(int duration);
};
