/********************************************************
 * M5Bala balance car Basic Example
 * Reading encoder and writting the motor via I2C
 ********************************************************/
// https://github.com/m5stack/M5Bala/tree/master/examples/Blynk_BLE

#define BLYNK_PRINT Serial

#define BLE // comment out using Wifi

#include <M5Stack.h>
#include "M5StackUpdater.h"

#ifndef BLE
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#else
#include <BlynkSimpleEsp32_BLE.h>
#endif
#include <Wire.h>
#include <Preferences.h>
#include "M5Bala.h"

#include "Audio.h"
#include "sounds/R2D2.h"

Preferences preferences;

M5Bala m5bala(Wire);
Audio audio;

char auth[] = "00000000000000000000000000000000";

#ifndef BLE
char ssid[] = "xxxxxxxxxx";
char pass[] = "xxxxxxxxxx";
#endif

#define MAX_MESSAGE 32
#define MSG_HEIGHT 40

void printStatus(const char *s, uint16_t color) {
	static char prevStr[MAX_MESSAGE] = { 0 };
	if (strcmp(s, prevStr)) {
		strncpy(prevStr, s, MAX_MESSAGE - 1);
		M5.Lcd.fillRect(0, M5.Lcd.height() / 2 - MSG_HEIGHT / 2, M5.Lcd.width(), MSG_HEIGHT, TFT_BLACK);
		if (*s) {
			M5.Lcd.setTextColor(color);
			M5.Lcd.drawCentreString(s, M5.Lcd.width() / 2, M5.Lcd.height() / 2 - MSG_HEIGHT / 2, 4);
			Serial.println(s);
		}
	}
}

void clearStatus() {
	printStatus("", TFT_BLACK);
}

void printError(const char *s) {
	M5.Lcd.fillRect(0, M5.Lcd.height() - MSG_HEIGHT, M5.Lcd.width(), MSG_HEIGHT, TFT_BLACK);
	if (*s) {
		M5.Lcd.setTextColor(TFT_YELLOW);
		M5.Lcd.drawCentreString(s, M5.Lcd.width() / 2, M5.Lcd.height() - MSG_HEIGHT, 4);
		Serial.println(s);
	}
}

void clearError() {
	printError("");
}

BLYNK_CONNECTED() {
	printStatus("Blynk connected!", TFT_WHITE);
	audio.play(R2D2_CHEERFUL);
}

BLYNK_DISCONNECTED() {
	printStatus("Blynk disconnected", TFT_WHITE);
	audio.play(R2D2_WHISTLE);
}


BLYNK_WRITE(V0) {
	int16_t jsX = param[0].asInt();
	int16_t jsY = param[1].asInt();
	m5bala.move(jsY);
	m5bala.turn(jsX);

	if (jsX || jsY) {
		char buff[MAX_MESSAGE];
		sprintf(buff, "X=%d y=%d", jsX, jsY);
		printStatus(buff, TFT_GREEN);
	} else {
		clearStatus();
	}
}

BLYNK_WRITE(V1) {
	if (param.asInt()) {
		m5bala.shutdown();
		printStatus("STOP", TFT_RED);
		audio.play(R2D2_LOOK);
	} else {
		clearStatus();
	}
}

BLYNK_WRITE(V2) {
	if (param.asInt()) {
		m5bala.wakeUp();
		printStatus("WAKE UP", TFT_CYAN);
		audio.play(R2D2_CONCERNED);
	} else {
		clearStatus();
	}
}

BLYNK_WRITE(V3) {
	if (param.asInt()) {
		m5bala.rotate(120);
		printStatus("ROTATE", TFT_GREEN);
	} else {
		m5bala.stop();
		clearStatus();
	}
}

void playVoice() {
	static int voiceIndex = 0;

	audio.play(voiceIndex);
	if (++voiceIndex >= R2D2_COUNT) {
		voiceIndex = 0;
	}
}

BLYNK_WRITE(V4) {
	playVoice();
}

// ================ GYRO offset param ==================
void auto_tune_gyro_offset() {
//	M5.Speaker.tone(500, 200);
	delay(300);
	M5.update();
	M5.Lcd.println("Start IMU calculate gyro offsets");
	M5.Lcd.println("DO NOT MOVE A MPU6050...");
	delay(2000);

	m5bala.imu->calcGyroOffsets(true);
	float gyroXoffset = m5bala.imu->getGyroXoffset();
	float gyroYoffset = m5bala.imu->getGyroYoffset();
	float gyroZoffset = m5bala.imu->getGyroZoffset();
	M5.Lcd.println("Done!!!");
	M5.Lcd.print("X : ");M5.Lcd.println(gyroXoffset);
	M5.Lcd.print("Y : ");M5.Lcd.println(gyroYoffset);
	M5.Lcd.print("Z : ");M5.Lcd.println(gyroZoffset);
	M5.Lcd.println("Program will start after 3 seconds");
	M5.Lcd.println("========================================");

	// Save
	preferences.putFloat("gyroXoffset", gyroXoffset);
	preferences.putFloat("gyroYoffset", gyroYoffset);
	preferences.putFloat("gyroZoffset", gyroZoffset);
	preferences.end();
}

void printM5BalaStatus(int error) {
	static unsigned long tick = 0;

	unsigned long t = millis();
	if (t < tick) return;
	tick = t + 500;

	M5.Lcd.fillRect(0, 0, M5.Lcd.width(), 32, TFT_BLACK);
	M5.Lcd.setCursor(0, 0);
	M5.Lcd.setTextColor(TFT_LIGHTGREY);
	if (error) {
		M5.Lcd.printf("I2C error: %d pitch: %4.1f", error, m5bala.getAngle());
	} else {
		M5.Lcd.printf("speed-in: %d,%d pwm-out: %d,%d pitch: %4.1f", m5bala.getSpeed0(), m5bala.getSpeed1(), m5bala.getOut0(), m5bala.getOut1(), m5bala.getAngle());
	}
}

void setup() {
	// Power ON Stabilizing...
	delay(500);
	M5.begin();

	if (digitalRead(BUTTON_A_PIN) == 0) {
		Serial.println("Will Load menu binary");
		updateFromFS(SD);
		ESP.restart();
	}

	// Init I2C
	Wire.begin();
	Wire.setClock(400000UL);  // Set I2C frequency to 400kHz
	delay(500);

	// Display info
	M5.Lcd.setTextFont(2);
	M5.Lcd.setTextColor(WHITE, BLACK);
	M5.Lcd.println("M5Stack Balance Mode start");

	// Init M5Bala
	m5bala.begin();

	// Loading the IMU parameters
	if (M5.BtnC.isPressed()) {
		preferences.begin("m5bala-cfg", false);
		auto_tune_gyro_offset();

	} else {
		preferences.begin("m5bala-cfg", true);
		m5bala.imu->setGyroOffsets(preferences.getFloat("gyroXoffset"), preferences.getFloat("gyroYoffset"), preferences.getFloat("gyroZoffset"));
	}

	audio.setVolume(MIN_VOLUME + 1);
	audio.setSampleRate(SAMPLE_RATE);
	audio.setWaveData(waveDataArray, waveDataSizeArray);

	if (!M5.BtnB.isPressed()) {
		//Blynk start
		Serial.println("Blynk start...");
	#ifndef BLE
		M5.Lcd.printf("Blynk connecting to %s ...", ssid);
		M5.Lcd.println();
		Blynk.begin(auth, ssid, pass);
	#else
		M5.Lcd.println("Blynk connecting BLE ...");
		Blynk.setDeviceName("Blynk");
		Blynk.begin(auth);
	#endif
		M5.Lcd.clear();
	}

	Serial.println("setup done");
}

void loop() {
	static int error = -1;

	// M5Bala balance run
	if (!m5bala.run()) {
		audio.play(R2D2_SAD);
	}

	// Blynk control
	Blynk.run();

	int err = m5bala.getError();
	if (error == -1) {
		if (err == 0) {
			error = 0;
			M5.Lcd.clear();
			printStatus("Ready", TFT_GREEN);
			audio.play(R2D2_PROCESSING);
		}
	} else if (err != error) {
		if (err > 0) {
			if (error == 0) {
				printError("I2C ERROR!");
				audio.play(R2D2_SNAPPY);
			}
		} else {
			clearError();
		}
		error = err;
	}

	printM5BalaStatus(error);

	if (M5.BtnB.wasPressed()) {
		playVoice();
	}

	// M5 Loop
	M5.update();
}
