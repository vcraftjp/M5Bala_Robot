//
// Status.cpp
//

#include "Status.h"

#define MAX_MESSAGE 64

void Status::print(const char *s, uint16_t color, bool upper) {
	static char prevStr[MAX_MESSAGE];
	if (strcmp(s, prevStr)) {
		*prevStr = '\0';
		strncpy(prevStr, s, MAX_MESSAGE - 1);
		clear(upper);
		if (*s) {
			int y = upper ? 0 : M5.Lcd.height() - lineHeight - marginBottom;
			M5.Lcd.setTextSize(fontSize);
			M5.Lcd.setTextColor(color);
			M5.Lcd.drawCentreString(s, M5.Lcd.width() / 2, y, font);
			//Serial.println(s);
			if (!upper && duration != 0) {
				endTick = millis() + duration;
			}
		}
	}
}

void Status::printError(const char *s) {
	print(s, TFT_YELLOW, true);
}

void Status::print(int n, uint16_t color, bool upper) {
	char buff[16];
	sprintf(buff, "%d", n);
	print(buff, color, upper);
}

void Status::clear(bool upper) {
	int y = upper ? 0 : M5.Lcd.height() - lineHeight - marginBottom;
	M5.Lcd.fillRect(0, y, M5.Lcd.width(), lineHeight, TFT_BLACK);
}
void Status::update() {
	if (endTick == 0) return;
	if (millis() >= endTick) {
		endTick = 0;
		clear();
	}
}
