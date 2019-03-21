//
// TOFSensor.h
//
#pragma once

#define ADAFRUIT

#include <M5Stack.h>

#ifdef ADAFRUIT
  #include <Adafruit_VL53L0X.h>
  #define VL53L0X_CLASS Adafruit_VL53L0X
#else // Pololu
  #include "VL53L0X.h"
  #define VL53L0X_CLASS VL53L0X
#endif

#define TOF_ERROR (-1)
#define TOF_INFINITY 8190

class TOFSensor : VL53L0X_CLASS {
public:
	TOFSensor() : isReady(false), distance(0) {}

	bool begin(float _filterGain = 1.0, bool _isDebug = false);
	int getDistance();
	void startEvent();
	bool isLostFloor(int margin = 25, int elapse = 3);
	bool isFoundNearest(int minDist = 200, int maxDist = 500, int elapse = 3);
	static bool isNotValid(int d) { return d <= 0 || d >= TOF_INFINITY; }

	bool isReady;
	int distance;
	float filterGain;

private:
	int getDistanceRaw();

	bool isDebug;
	int distance0;
	int eventCount;
};
