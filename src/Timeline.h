//
// Timeline.h
//
#pragma once

#include <M5Stack.h>

#define TL_INFINITY (-1)
#define TL_MAX_STATE 100
#define TL_END (TL_MAX_STATE - 1)
#define TL_LOOP (TL_MAX_STATE - 2)

class Timeline {
public:
	Timeline() : index(-1) {}

	void begin(int16_t* _timeline);  // int16_t timeline[] = { d1, state1, d2, state2, state3, ... , state_n, 0 };
	void end();
	int16_t update();
	bool skipTo(int16_t target);
	void skipToNext() { duration = 0; }

	int16_t state;

private:
	int16_t* timeline;
	int16_t index;
	unsigned long startTick;
	int16_t duration;
};
