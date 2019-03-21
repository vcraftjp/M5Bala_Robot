//
// RoboFace.cpp
//

#include "RoboFace.h"
#include "util.h"
#include "bitmap_data.h"

#define EYE_RADIUS 24

void RoboFace::begin() {
	setColorDepth(8);
	createSprite(M5.Lcd.width(), M5.Lcd.height() - marginY * 2);
	createPalette(0);
}

void RoboFace::createPalette(int hue) {
	if (hue == paletteHue) return;
	paletteHue = hue;
	const int th = 144;
	const int min_sat = MAX_SV / 2;
	for (int i = 0; i < 256; i++) {
		int s = (i < th) ? MAX_SV : MAX_SV + ((i - th) * min_sat + (th - i) * MAX_SV) / (256 - th);
		int v = (i < th) ? i * MAX_SV / th : MAX_SV;
		palette[i] = color32To16(hsvToRGB(hue, s, v));
		// Serial.printf("%d: 0x%04X (s=%d)\r\n", i, palette[i], s);
	}
	if (isShow) {
//		Serial.print("createPalette:");Serial.println(hue);
		flush();
	}
}

void RoboFace::showEyes(int _duration) {
	if (isShow) return;
	clear();
	calcEyesPosition(0, 0);
	if (_duration == 0) {
		drawEyes();
	} else {
		duration = _duration;
		startTick = millis();
		animMode = SHOW;
	}
	isShow = true;
}

void RoboFace::hideEyes(int _duration) {
	if (!isShow) return;
	if (_duration == 0) {
		clear();
		flush();
	} else {
		duration = _duration;
		startTick = millis();
		animMode = HIDE;
	}
	isShow = false;
}

void RoboFace::moveEyes(int dx, int dy, int speed) {
	if (speed == 0) {
		if (calcEyesPosition(dx, dy)) {
			clear();
			drawEyes();
		}
	} else {
		stopMoving();
		calcEyesPosition(dx, dy, 1.0, true);
		duration = (int)sqrt((eyeLX1 - eyeLX) * (eyeLX1 - eyeLX) + (eyeY1 - eyeY) * (eyeY1 - eyeY)) * 1000. / speed;
		if (duration > 0) {
			startTick = millis();
			animMode = MOVE;
		}
	}
}

void RoboFace::stareEyes(float stare, int speed) {
	if (speed == 0) {
		if (calcEyesPosition(eyeDX, eyeDY, stare)) {
			clear();
			drawEyes();
		}
	} else {
		stopMoving();
		calcEyesPosition(eyeDX, eyeDY, stare, true);
		duration = abs((eyeRX1 - eyeLX1) - (eyeRX - eyeLX));
		if (duration > 0) {
			startTick = millis();
			animMode = MOVE;
		}
	}
}

void RoboFace::stopMoving() {
	if (animMode == MOVE) {
		int t = (int)(millis() - startTick);
		if (t >= duration) {
			t = duration;
		}
		eyeLX += (eyeLX1 - eyeLX) * t / duration;
		eyeRX += (eyeRX1 - eyeRX) * t / duration;
		eyeY += (eyeY1 - eyeY) * t / duration;
		animMode = NONE;
	}
}

bool RoboFace::calcEyesPosition(int dx, int dy, float stare, bool isMove) {
	eyeDX = dx;
	eyeDY = dy;
	int cx = M5.Lcd.width() / 2;
	int cy = M5.Lcd.height() / 2 - marginY;
	int dist = (int)(M5.Lcd.width() * eyeSpan * stare);
	int lx = cx - dist / 2 + dx;
	int rx = cx + dist / 2 + dx;
	int y = cy + dy;
	bool r = false;
	if (isMove) {
		eyeLX1 = lx;
		eyeRX1 = rx;
		eyeY1 = y;
	} else if (lx != eyeLX || rx != eyeRX || y != eyeY) {
		r = true;
		eyeLX = lx;
		eyeRX = rx;
		eyeY = y;
	}
	return r;
}

void RoboFace::drawEyes(int lx, int rx, int y, uint8_t brightness) {
	drawBitmap(lx - EYE_RADIUS, y - EYE_RADIUS, EYE_RADIUS * 2, EYE_RADIUS * 2,  bitmap_data, brightness);
	drawBitmap(rx - EYE_RADIUS, y - EYE_RADIUS, EYE_RADIUS * 2, EYE_RADIUS * 2,  bitmap_data, brightness);
	flush();
}

void RoboFace::update() {
	if (animMode == NONE) return;
	int brightness = 255;
	int t = (int)(millis() - startTick);
	switch (animMode) {
		case SHOW:
			brightness = t * 255 / duration;
			if (brightness >= 255) {
				brightness = 255;
				if (driftDX) {
					moveEyes(driftDX);
				} else {
					animMode = NONE;
				}
			}
			drawEyes((uint8_t)brightness);
			break;
		case HIDE:
			brightness = 255 - t * 255 / duration;
			if (brightness <= 0) {
				brightness = 0;
				animMode = NONE;
			}
			drawEyes((uint8_t)brightness);
			break;
		case MOVE: {
			if (t >= duration) {
				t = duration;
			}
			int lx = eyeLX + (eyeLX1 - eyeLX) * t / duration;
			int rx = eyeRX + (eyeRX1 - eyeRX) * t / duration;
			int y = eyeY + (eyeY1 - eyeY) * t / duration;
			clear();
			drawEyes(lx, rx, y, (uint8_t)brightness);
			if (t == duration) {
				eyeLX = eyeLX1;
				eyeRX = eyeRX1;
				eyeY = eyeY1;
				if (driftDX) {
					if (eyeDX > 0) {
						moveEyes(-driftDX);
					} else {
						moveEyes(0);
						driftDX = 0;
					}
				} else {
					animMode = NONE;
				}
			}
			break;
		}
		default:
			break;
	}
}
