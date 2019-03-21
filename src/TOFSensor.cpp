//
// TOFSensor.cpp
//

#include "TOFSensor.h"

bool TOFSensor::begin(float _filterGain, bool _isDebug) {
	filterGain = _filterGain;
	isDebug = _isDebug;
#ifdef ADAFRUIT
	return isReady = Adafruit_VL53L0X::begin(VL53L0X_I2C_ADDR, isDebug);
#else // Pololu
	isReady = init();
	setTimeout(500);
	return isReady;
#endif
}

int TOFSensor::getDistance() {
	int d = getDistanceRaw();
	if (filterGain == 1.0 || isNotValid(d) || isNotValid(distance)) {
		distance = d;
	} else {
		distance += (d - distance) * filterGain;
	}
	return distance;
}

void TOFSensor::startEvent() {
	distance0 = distance;
	eventCount = 0;
}

bool TOFSensor::isLostFloor(int margin, int elapse) {
	if (!isReady) return false;
	if (distance > distance0 + margin || distance < distance0 - margin || isNotValid(distance)) {
		// Serial.printf("Floor: %d/%d (%d)\r\n", distance, distance0, eventCount);
		if (++eventCount >= elapse) {
			return true;
		}
	} else {
		eventCount = 0;
	}
	return false;
}

bool TOFSensor::isFoundNearest(int minDist, int maxDist, int elapse) {
	if (!isReady) return false;
	if (distance >= minDist && distance < maxDist) {
		if (distance > distance0 || isNotValid(distance0)) {
			// Serial.printf("Nearest: %d->%d (%d)\r\n", distance0, distance, eventCount);
			if (++eventCount >= elapse) {
				return true;
			}
		} else {
			eventCount = 0;
		}
		distance0 = distance;
	}
	return false;
}

int TOFSensor::getDistanceRaw() {
#ifdef ADAFRUIT
	VL53L0X_RangingMeasurementData_t measure;
	getSingleRangingMeasurement(&measure, isDebug);
	if (measure.RangeStatus == 4) {  // phase failures have incorrect data
		return TOF_ERROR;
	}
	return measure.RangeMilliMeter;
#else // Pololu
	int d = readRangeSingleMillimeters();
	if (timeoutOccurred()) {
		return TOF_ERROR;
	}
	return d;
#endif
}
