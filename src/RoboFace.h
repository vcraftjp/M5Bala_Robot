//
// RoboFace.h
//
#pragma once

#include <M5Stack.h>
#include "Sprite8bpp.h"

class RoboFace : public Sprite8bpp {
public:
	RoboFace(TFT_eSPI *tft, int _marginY) :
		Sprite8bpp(tft),
		isShow(false),
		marginY(_marginY),
		eyeSpan(0.4),
		animMode(NONE),
		eyeDX(0), eyeDY(0), eyeLX(0), eyeRX(0), eyeY(0), driftDX(0),
		paletteHue(-1) { }
	void begin();
	void flush() { Sprite8bpp::flush(palette, marginY); }
	void createPalette(int hue);

	void showEyes(int duration = 500);
	void hideEyes(int duration = 500);
	void moveEyes(int dx = 0, int dy = 0, int speed = 500);
	void setEyeSpan(float n) { eyeSpan = n; }
	void stareEyes(float stare, int speed = 500);
	void driftEyes(int _driftDX = 20) { driftDX = _driftDX; }
	int  getEyeX() { return eyeDX; }
	int  getEyeY() { return eyeDY; }

	void update();
	bool isShow;

private:
	enum AnimMode { NONE, SHOW, HIDE, MOVE };

	int marginY;
	float eyeSpan;
	unsigned long startTick;
	AnimMode animMode;
	int eyeDX;
	int eyeDY;
	int eyeLX;
	int eyeRX;
	int eyeY;
	int eyeLX1;
	int eyeRX1;
	int eyeY1;
	int duration;
	int driftDX;

	uint16_t palette[256];
	int paletteHue;

	bool calcEyesPosition(int dx, int dy, float span = 1.0, bool isMove = false);
	void drawEyes(uint8_t brightness = 255) {
		drawEyes(eyeLX, eyeRX, eyeY, brightness);
	};
	void drawEyes(int lx, int rx, int y, uint8_t brightness = 255);
	void stopMoving();
};