//
// Timeline.cpp
//

#include "Timeline.h"

void Timeline::begin(int16_t* _timeline) {
	timeline = _timeline;
	index = 0;
	state = 0;
	startTick = millis();
	duration = 0;
}

void Timeline::end() {
	index = -1;
	state = 0;
}

int16_t Timeline::update() {
	if (index == -1) return 0;
	unsigned long tick = millis();
	if (duration != 0) {
		if (tick - startTick < duration || duration == TL_INFINITY) return 0;
		duration = 0;
	}
	int n = timeline[index++];
	if (n >= 0 && n < TL_MAX_STATE) {
		state = n;
		if (n == 0 || n == TL_END) {
			index = -1;
			if (n != 0) {
				state = 0;
			}
		} else if (n == TL_LOOP) {
			index = 1; // skip first duration (TODO)
			state = 0;
		}
		// Serial.print("Timeline: ");Serial.println(state);
		return state;
	}
	duration = n;
	startTick = tick;
	return 0;
}

bool Timeline::skipTo(int16_t target) {
	index = 0;
	for(;;) {
		int16_t n = timeline[index++];
		if (n == target) {
			index--;
			duration = 0;
			return true;
		}
		if (n == 0) {
			end();
			return false;
		}
	}
}
