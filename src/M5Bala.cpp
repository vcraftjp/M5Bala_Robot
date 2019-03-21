#include "M5Bala.h"
#include <Preferences.h>

#define MPU9250_ID   0x71
#define MPU6050_ID   0x68

M5Bala::M5Bala() {
	wire = &Wire;
	wireError = 0;
}

M5Bala::M5Bala(TwoWire &w) {
	wire = &w;
}

void M5Bala::begin(bool _isBalance, bool useIMU) {
	isBalance = _isBalance;
	isTumbled = false;
	encoderGain = isBalance ? 0.1 : 1.0;
	speedWeight = 0.0;

	// I2C
	// wire->begin();
	// wire->setClock(400000UL);  // Set I2C frequency to 400kHz

	if (isBalance || useIMU) {
		// IMU
		imu = new MPU6050(*wire);
		imu->begin();
		imu_id = i2c_readByte(MPU6050_ADDR, MPU6050_WHO_AM_I);
		// imu.calcGyroOffsets(true);
		// imu.setGyroOffsets(-2.40, -0.41, 1.07); // FIRE
		// imu->setGyroOffsets(5.0, 0.50, -2.6); // M5GO

		// PID param
		K1 = 30;
		K2 = 32;
		K3 = 6.5;
		K4 = 5.2;
		K5 = 8;

		for (int i = 0; i < 128; i++) {
			imu->update();
		}
		pitch = imu->getAngleX();
	} else {
		imu = NULL;
	}

	// Motor
	setMotor(0, 0);
	state = RUN;
	duration = 0;

//	loop_interval = 0;
	left_offset = 0;
	right_offset = 0;
	forward_offset = 0;
}

uint8_t M5Bala::i2c_readByte(uint8_t address, uint8_t subAddress)
{
  uint8_t data; // `data` will store the register data
  wire->beginTransmission(address);         // Initialize the Tx buffer
  wire->write(subAddress);                  // Put slave register address in Tx buffer
  wire->endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
  wire->requestFrom(address, (uint8_t) 1);  // Read one byte from slave register address
  data = Wire.read();                      // Fill Rx buffer with result
  return data;                             // Return data read from slave register
}

// ================ GYRO offset param ==================
void M5Bala::autoTuneGyroOffset(Preferences& prefs) {
	delay(300);
	M5.update();
	M5.Lcd.println("Start IMU calculate gyro offsets");
	M5.Lcd.println("DO NOT MOVE A MPU6050...");
	delay(2000);

	imu->calcGyroOffsets(true);
	float gyroXoffset = imu->getGyroXoffset();
	float gyroYoffset = imu->getGyroYoffset();
	float gyroZoffset = imu->getGyroZoffset();
	M5.Lcd.println("Done!!!");
	M5.Lcd.print("X : ");M5.Lcd.println(gyroXoffset);
	M5.Lcd.print("Y : ");M5.Lcd.println(gyroYoffset);
	M5.Lcd.print("Z : ");M5.Lcd.println(gyroZoffset);
	M5.Lcd.println("Program will start after 3 seconds");
//	M5.Lcd.println("========================================");

	// Save
	prefs.putFloat("gyroXoffset", gyroXoffset);
	prefs.putFloat("gyroYoffset", gyroYoffset);
	prefs.putFloat("gyroZoffset", gyroZoffset);
	delay(3000);
	M5.Lcd.clear();
}

void M5Bala::setGyroOffsets(Preferences& prefs) {
	imu->setGyroOffsets(prefs.getFloat("gyroXoffset"), prefs.getFloat("gyroYoffset"), prefs.getFloat("gyroZoffset"));
}

void M5Bala::setMotor(int16_t pwm0, int16_t pwm1) {
	// Value range
	int16_t m0 = constrain(pwm0, -255, 255);
	int16_t m1 = constrain(pwm1, -255, 255);

	// Dead zone
	if (((m0 > 0) && (m0 < DEAD_ZONE)) || ((m0 < 0) && (m0 > -DEAD_ZONE))) m0 = 0;
	if (((m1 > 0) && (m1 < DEAD_ZONE)) || ((m1 < 0) && (m1 > -DEAD_ZONE))) m1 = 0;

	// Same value
	static int16_t pre_m0, pre_m1;
	if ((m0 == pre_m0) && (m1 == pre_m1))
		return;
	pre_m0 = m0;
	pre_m1 = m1;

	// Send I2C
	wire->beginTransmission(M5GO_WHEEL_ADDR);
	wire->write(MOTOR_CTRL_ADDR); // Motor ctrl reg addr
	wire->write(((uint8_t*)&m0)[0]);
	wire->write(((uint8_t*)&m0)[1]);
	wire->write(((uint8_t*)&m1)[0]);
	wire->write(((uint8_t*)&m1)[1]);
	wire->endTransmission();
}

bool M5Bala::readEncder() {
	static float _speed_input0 = 0, _speed_input1 = 0;
	int16_t rx_buf[2];

	//Get Data from Module.
	wire->beginTransmission(M5GO_WHEEL_ADDR);
	wire->write(ENCODER_ADDR); // encoder reg addr
	wire->endTransmission();
	wire->beginTransmission(M5GO_WHEEL_ADDR);
	wire->requestFrom(M5GO_WHEEL_ADDR, 4);

	if (wire->available()) {
		((uint8_t*)rx_buf)[0] = wire->read();
		((uint8_t*)rx_buf)[1] = wire->read();
		((uint8_t*)rx_buf)[2] = wire->read();
		((uint8_t*)rx_buf)[3] = wire->read();

		// filter
		_speed_input0 *= (1.0 - encoderGain);
		_speed_input0 += encoderGain * rx_buf[0];
		_speed_input1 *= (1.0 - encoderGain);
		_speed_input1 += encoderGain * rx_buf[1];

		speed_input0 = constrain((int16_t)(-_speed_input0), -255, 255);
		speed_input1 = constrain((int16_t)(_speed_input1), -255, 255);
		return true;
	}
	return false;
}

void M5Bala::PIDCompute() {
	static float last_angle;
	static int16_t last_wheel;
	float angle, angle_velocity;
	int16_t wheel, wheel_velocity;
	int16_t torque, speed_diff, speed_diff_adjust;

	angle = pitch - angle_offset;
	angle_velocity = angle - last_angle;
	last_angle = angle;

	wheel = (speed_input0 + speed_input1) / 2;  /* wheel = read_encoder()-profiler() */
	wheel_velocity = wheel - last_wheel;
	last_wheel = wheel;

	torque = (angle_velocity * K1) + (angle * K2)
		   + (wheel_velocity * K3) + (wheel * K4);

	speed_diff = (speed_input0 - speed_input1);
	speed_diff_adjust = (K5 * speed_diff);

	pwm_out0 = torque - speed_diff_adjust;
	pwm_out1 = torque;
	pwm_out0 = constrain(pwm_out0, -255, 255);
	pwm_out1 = constrain(pwm_out1, -255, 255);
}

bool M5Bala::run() {
	bool result = false;
//	if (micros() >= loop_interval) {
//		loop_interval = micros() + 10000;

		if (duration > 0 ){
			if (millis() - startTick >= duration) {
				duration = 0;
				stop();
			}
		}

		if (imu) {
			imu->update();
		}
		if (isBalance) {
			// Attitude sample
			pitch = imu->getAngleX() + angle_offset;

			if (imu_id == MPU9250_ID)
				pitch = -pitch;
			// #ifndef MPU6050_IMU
			// pitch = -pitch;
			// #endif

			if (state == STOP) return result;

			float pitchAbs = abs(pitch);

			// Car down
			if (state == RUN) {
				if (pitchAbs > 45.) {
					setMotor(0, 0);
					state = STOP;
					isTumbled = true;
					return result;
				}
			} else if (state == WAKE_UP) {
				if (pitchAbs < 10.) {
					state = RUN;
				}
			}

			// Encoder sample
			if (readEncder()) {
				result = true;
				// PID Compute
				PIDCompute();

				// Motor out
				setMotor(pwm_out0 + forward_offset + left_offset,
						pwm_out1 + forward_offset + right_offset);
			}
		} else { // !isBanalce
			if (state != STOP) {
				if (readEncder()) {
					result = true;
					if (isMoveStraight && speedWeight > 0.0) {
						left_offset = right_offset = 0;
						if (speed_input0 > speed_input1) {
							right_offset = (speed_input0 - speed_input1) * speedWeight;
						} else if (speed_input0 < speed_input1) {
							left_offset = (speed_input1 - speed_input0) * speedWeight;
						}
					}
					sumOfSpeedDiff += speed_input1 - speed_input0;
				}
				setMotor(forward_offset + left_offset, forward_offset + right_offset);
			}
		}
		wireError = wire->lastError();
//	}
	return result;
}

void M5Bala::stop() {
	left_offset = 0;
	right_offset = 0;
	forward_offset = 0;
	isTumbled = false;
	isMoveStraight = false;
}

void M5Bala::shutdown() {
	stop();
	setMotor(0, 0);
	state = STOP;
}

void M5Bala::wakeUp() {
	state = WAKE_UP;
	isTumbled = false;
}

void M5Bala::move(int16_t speed, int _duration) {
	forward_offset = isBalance ? -speed : speed;
	left_offset = right_offset = 0;
	isMoveStraight = true;
	setDuration(_duration);
}

void M5Bala::turn(int16_t speed, int _duration) {
	if (speed > 0) {
		left_offset = speed;
		right_offset = 0;

	} else if (speed < 0) {
		left_offset = 0;
		right_offset = -speed;
	}
	isMoveStraight = false;
	setDuration(_duration);
}

void M5Bala::rotate(int16_t speed, int _duration) {
	left_offset = speed;
	right_offset = -speed;
	forward_offset = 0;
	isMoveStraight = false;
	setDuration(_duration);
}

void M5Bala::setDuration(int _duration) {
	duration = _duration;
	startTick = millis();
}

void M5Bala::setAutoStraight(float _speedWeight, float _encoderGain) {
	speedWeight = _speedWeight;
	encoderGain = _encoderGain;
}

int M5Bala::getRotateAngle() {
	int angle360 = abs(left_offset) * 3 / 2 + 270; // adjust by speed
	return sumOfSpeedDiff * angle360 / 9800; // roughly...
}
