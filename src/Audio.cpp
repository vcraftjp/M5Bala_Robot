//
// Audio.cpp
//

#include "Audio.h"

static int volume = MIN_VOLUME;
static int sampleRate = 8000;
static const uint8_t *wave;
static int waveIndex = -1;
static int waveLength;
static int writeBytes;
static int totalBytes;
static bool _isMute; // = false;
static const uint8_t **waveDataArray; // = NULL;
static const uint16_t *waveDataSizeArray; // = NULL;

static volatile SemaphoreHandle_t timerSemaphore;
static hw_timer_t *timer; // = NULL;

void IRAM_ATTR onTimer() {
	if (waveIndex >= 0) {
		M5.Speaker.write(pgm_read_byte(wave + waveIndex) / (MAX_VOLUME + 1 - volume));
		waveIndex++;
		writeBytes++;
		if (waveIndex >= waveLength) {
			if (totalBytes) {
				if (totalBytes == -1) { // infinite loop
					waveIndex = 0;
				} else if (writeBytes < totalBytes) {
					waveIndex = 0;
				} else {
					Audio::stop();
				}
			} else {
				Audio::stop();
			}
		}
	}
	xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

void Audio::setVolume(int _volume) {
	volume = min(_volume, MAX_VOLUME);
}

int Audio::getVolume() {
	return volume;
}

void Audio::setSampleRate(int _sampleRate) {
	if (_sampleRate != sampleRate) {
		sampleRate = _sampleRate;
		if (timer) {
			timerAlarmWrite(timer, 1000000 / sampleRate, true);
		}
	}
}

void Audio::init() {
	timerSemaphore = xSemaphoreCreateBinary();

	timer = timerBegin(0, 80, true);
	timerAttachInterrupt(timer, &onTimer, true);
	timerAlarmWrite(timer, 1000000 / sampleRate, true);
	timerAlarmEnable(timer);
}

void Audio::play(const uint8_t *_wave, int _length, int _duration) {
	if (_isMute) return;
	wave = _wave;
	waveLength = _length;
	waveIndex = 0;
	writeBytes = 0;
	totalBytes = _duration;
	if (_duration > 0) {
		totalBytes = _duration * (sampleRate / 1000);
	}
	if (!timer) {
		init();
	}
}

void Audio::stop() {
	waveIndex = -1;
	M5.Speaker.write(0);
}

bool Audio::isPlaying() {
	return waveIndex != -1;
}

void Audio::setMute(bool b) {
	_isMute = b;
	if (isPlaying()) {
		stop();
	}
}

bool Audio::isMute() {
	return _isMute;
}

void Audio::setWaveData(const uint8_t **_waveDataArray, const uint16_t *_waveDataSizeArray) {
	waveDataArray = _waveDataArray;
	waveDataSizeArray = _waveDataSizeArray;
}

void Audio::play(int index, int _duration) {
	play(waveDataArray[index], waveDataSizeArray[index], _duration);
}