//
// Audio.h
//
#pragma once

#include <M5Stack.h>

#define MIN_VOLUME 0
#define MAX_VOLUME 10

//
// Audio class
//
class Audio {
public:
	static void setVolume(int _volume);
	static int getVolume();
	static void setSampleRate(int _sampleRate);
	static void play(const uint8_t *wave, int length, int duration = 0); // duration(ms), -1=infinite
	static void stop();
	static bool isPlaying();
	static void setMute(bool b);
	static bool isMute();

	static void setWaveData(const uint8_t **waveDataArray, const uint16_t *waveDataSizeArray);
	static void play(int index, int duration = 0);

protected:
	static void init();
};
