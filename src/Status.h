//
// Status.h
//
#pragma once

#include <M5Stack.h>

class Status {
public:
	Status(int _font = 1, int _fontSize = 1, int _lineHeight = 20) :
		font(_font), fontSize(_fontSize), lineHeight(_lineHeight), marginBottom(0), duration(2000)
		, endTick(0) {}

	void print(const char *s, uint16_t color = TFT_GREEN, bool upper = false);
	void print(int n, uint16_t color = TFT_GREEN, bool upper = false);
	void printError(const char *s);
	void clear(bool upper = false);
	void clearError() { clear(true); }
	void update();

	int font;
	int fontSize;
	int lineHeight;
	int marginBottom;
	int duration;

private:
	unsigned long endTick;
};