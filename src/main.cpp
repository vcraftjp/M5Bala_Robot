//
// M5Bala & Tilt Servo Robot Demo
//

#include <M5Stack.h>
#include <M5StackUpdater.h>
#include <M5TreeView.h>
#include <MenuItemNumeric.h>
#include <Preferences.h>
#include <vector>

//#define BLYNK

#ifdef BLYNK
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#define BLYNK_BLE // comment out when using Wifi

#ifndef BLYNK_BLE
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#else
#include <BlynkSimpleEsp32_BLE.h>
#endif // BLYNK_BLE
#endif // BLYNK

#include "M5Bala.h"
#include "util.h"
#include "Servo.hpp"
#include "TOFSensor.h"
#include "RoboFace.h"
#include "Status.h"
#include "Audio.h"
#include "sounds/R2D2.h"
#include "Timeline.h"

#include "unispaceb7pt7b.h"
#define FREE_FONT &unispaceb7pt7b

#define COLOR_OK TFT_GREEN
#define COLOR_NG TFT_YELLOW

#define SPEED_RUN 150
#define SPEED_ROTATE 100
#define SPEED_ROTATE_SLOW 60

// Servo motor (FS0307)
#define SERVO_PIN 17
#define MAX_ANGLE 60.
#define MIN_DUTY  0.9
#define MAX_DUTY  2.1

// PIR Sensor
#define PIR_PIN 36

// Preferences
#define PREFS_NAME "m5bala-cfg"
#define PKEY_IS_BALANCE "isBalance"
#define PKEY_VOLUME "volume"
#define PKEY_MUTE "mute"
#define ROBOT_MODE (isBalance ? "Balance Mode" : "Robot Mode")
Preferences prefs;

M5Bala m5bala(Wire);
RoboFace face(&M5.Lcd, 80);
Status status;
bool isBalance;
TOFSensor tof;
int floorDistance;
Servo servo;
Audio audio;
bool isPIR;

// Tilt Servo

float tiltAngles[] = { -42., -20., 10., 45. };
enum Tilt { TILT_DOWN = 1, TILT_FRONT, TILT_UP, TILT_OVER, TILT_COUNT };
int tilt;

void setTilt(int n) {
	if (n < TILT_DOWN) {
		n = TILT_DOWN;
	} else if (n >= TILT_COUNT) {
		n = TILT_COUNT - 1;
	}
	tilt = n;
	servo.setAngle(tiltAngles[n - TILT_DOWN], MAX_ANGLE, MIN_DUTY, MAX_DUTY);
}

// Timeline

#define PLAY(n) (n + TILT_COUNT)

Timeline timeline;

enum RoboState {
	ROBO_STOP = TILT_COUNT + R2D2_COUNT,
	ROBO_SHOW_EYES,
	ROBO_HIDE_EYES,
	ROBO_STARE_EYES,
	ROBO_RESET_EYES,
	ROBO_DRIFT_EYES,
	ROBO_ROTATE,
	ROBO_ROTATE90,
	ROBO_ROTATE180,
	ROBO_FORWARD,
	ROBO_BACKWARD,
	ROBO_FIND_HUMAN,
	ROBO_FIND_WALL,
	ROBO_FOUND,
	ROBO_NOT_FOUND,
};

// int16_t tl_opening[] = { 1000, ROBO_HIDE_EYES, 1, TILT_DOWN, 3000, ROBO_ROTATE, 500, ROBO_STOP, 500, TILT_UP, 1000, ROBO_SHOW_EYES, 0 };
// int16_t tl_demo[] = { 1000, ROBO_TILT_DOWN, 3000, ROBO_STANDBY, 1000, ROBO_FIND, 5000, ROBO_FIND_END, 500, ROBO_RUN_TURN, 2500, ROBO_FORWARD, 3000, ROBO_STOP, 0 };
// int16_t tl_rotate[] = { 2000, ROBO_ROTATE180, TL_INFINITY, ROBO_STOP, 0 };

int16_t tl_forward[] = { 500, ROBO_FORWARD, 4000, ROBO_STOP, 0 };

int16_t tl_findHuman[] = { 2000, TILT_UP, ROBO_FIND_HUMAN, TL_INFINITY,
	ROBO_NOT_FOUND, TILT_DOWN, PLAY(R2D2_SAD), TL_END,
	ROBO_FOUND, ROBO_STARE_EYES, PLAY(R2D2_PLAYFUL), 2000, ROBO_RESET_EYES, 0 };

int16_t tl_runOnFloor[] = { 2000, TILT_FRONT, ROBO_FIND_WALL, TL_INFINITY,
	ROBO_NOT_FOUND, TILT_DOWN, PLAY(R2D2_SAD), TL_END,
	ROBO_FOUND, PLAY(R2D2_CONCERNED), ROBO_FORWARD, TL_INFINITY,
	TILT_DOWN, PLAY(R2D2_SAD), 2000, ROBO_BACKWARD, 1000, ROBO_ROTATE, 500, TL_LOOP, 0 };

int16_t tl_runOnDesk[] = { 2000, TILT_DOWN, 200, ROBO_FORWARD, TL_INFINITY, PLAY(R2D2_WHISTLE), 1000,
	ROBO_BACKWARD, 200, ROBO_ROTATE90, TL_INFINITY,
	ROBO_FORWARD, TL_INFINITY, PLAY(R2D2_WHISTLE), 0 };

// Voice demo

int playVoice() {
	static int voiceIndex = 0;

	audio.play(voiceIndex);
	int r = voiceIndex;
	if (++voiceIndex >= R2D2_COUNT) {
		voiceIndex = 0;
	}
	return r;
}

// BLYNK

#ifdef BLYNK
const char auth[] = "00000000000000000000000000000000";

#ifndef BLYNK_BLE
const char ssid[] = "xxxxxxxxxx";
const char pass[] = "xxxxxxxxxx";
#endif

BLYNK_CONNECTED() {
	status.print("Blynk connected!", TFT_WHITE);
	audio.play(R2D2_CHEERFUL);
}

BLYNK_DISCONNECTED() {
	status.print("Blynk disconnected", TFT_YELLOW);
	audio.play(R2D2_WHISTLE);
}

BLYNK_WRITE(V0) {
	int16_t jsX = param[0].asInt();
	int16_t jsY = param[1].asInt();
	m5bala.move(jsY);
	m5bala.turn(jsX);
/*
	if (jsX || jsY) {
		char buff[64];
		sprintf(buff, "X=%d y=%d", jsX, jsY);
		status.print(buff, TFT_GREEN);
	} else {
		status.clear();
	}
*/
}

BLYNK_WRITE(V1) {
	if (param.asInt()) {
		m5bala.shutdown();
		status.print("STOP", TFT_RED);
		audio.play(R2D2_LOOK);
		face.hideEyes();
	} else {
		status.clear();
	}
}

BLYNK_WRITE(V2) {
	if (param.asInt()) {
		m5bala.wakeUp();
		status.print("WAKE UP", TFT_CYAN);
		audio.play(R2D2_CONCERNED);
		face.showEyes();
	} else {
		status.clear();
	}
}

BLYNK_WRITE(V3) {
	if (param.asInt()) {
		m5bala.rotate(SPEED_ROTATE);
		status.print("ROTATE", TFT_GREEN);
	} else {
		m5bala.stop();
		status.clear();
	}
}

BLYNK_WRITE(V4) {
	playVoice();
}

BLYNK_WRITE(V5) {
	setTilt(param.asInt());
}
#endif // BLYNK

// Balance mode status
void printM5BalaStatus(bool isError) {
	static unsigned long tick;

	unsigned long t = millis();
	if (t < tick + 500) return;
	tick = t;

	const int y = 32;
	M5.Lcd.fillRect(0, y, M5.Lcd.width(), 80, TFT_BLACK);
	M5.Lcd.setCursor(0, y + 16);
	M5.Lcd.setTextColor(COLOR_OK);
	M5.Lcd.printf("pitch: %4.1f\r\n", m5bala.getAngle());
	if (!isError) {
		M5.Lcd.printf("speed: %d,%d\r\n", m5bala.getSpeed0(), m5bala.getSpeed1());
		M5.Lcd.printf("  pwm: %d,%d\r\n", m5bala.getOut0(), m5bala.getOut1());
	}
}

//
// Setup menu
//
M5TreeView *pMenu = NULL;
typedef std::vector<MenuItem*> vmi;

enum MenuID {
	ID_MODE = 1, ID_M5BALA, ID_ROBOT, ID_SPEAKER, ID_VOLUME, ID_MUTE, ID_VOICE_TEST
};

void cbVolumeLevel(MenuItem* sender) {
	MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
	if (!mi) return;
	audio.stop();
	audio.setMute(false);
	audio.setVolume(mi->value);
	audio.play(R2D2_CONCERNED);
}

void setupMenu() {
	MenuItem::setFreeFont(FREE_FONT);
	MenuItem::clientRect.y = 24;
	MenuItem::fontColor[0] = TFT_GREEN;
	MenuItem::fontColor[1] = TFT_YELLOW;
	MenuItem::backColor[0] = TFT_BLACK;
	MenuItem::backColor[1] = TFT_NAVY;
	MenuItem::frameColor[0] = TFT_BLACK;
	MenuItem::frameColor[1] = TFT_CYAN;

	pMenu = new M5TreeView();
	pMenu->setItems(vmi {
		new MenuItem("Mode", ID_MODE, vmi {
			new MenuItem("M5Bala", ID_M5BALA),
			new MenuItem("Robot", ID_ROBOT)
		}),
  		new MenuItem("Speaker", ID_SPEAKER, vmi {
			new MenuItemNumeric("Volume", MIN_VOLUME, MAX_VOLUME, audio.getVolume(), ID_VOLUME, cbVolumeLevel),			new MenuItem("Mute", ID_MUTE),
		}),
  		new MenuItem("Voice Test", ID_VOICE_TEST)
	});
	M5.Lcd.drawCentreString("Setup", M5.Lcd.width() / 2, 0, 1);
	status.marginBottom = M5ButtonDrawer::height + 4;
	pMenu->begin();
}

bool prefsBegin() {
	if (!prefs.begin(PREFS_NAME)) {
		M5.Lcd.setTextColor(COLOR_NG);
		_println("Failed to begin Preferences");
		M5.Lcd.setTextColor(COLOR_OK);
		return false;
	}
	return true;
}

bool prefsPutBool(const char* key, const bool value) {
	if (prefsBegin()) {
		prefs.putBool(key, value);
		prefs.end();
		return true;
	}
	return false;
}

bool prefsPutUChar(const char* key, const uint8_t value) {
	if (prefsBegin()) {
		prefs.putUChar(key, value);
		prefs.end();
		return true;
	}
	return false;
}

void prefsStatusPrint(const char* msg) {
	String s("Set ");
	status.print((s += msg).c_str(), TFT_WHITE);
}

void doMenu() {
	MenuItem* mi = pMenu->update();
	if (mi == NULL) return;
	Serial.println(mi->tag);
	M5.Lcd.setTextFont(1);
	M5.Lcd.setFreeFont(FREE_FONT);
	switch (mi->tag) {
		case ID_MODE:
			if (!isBalance) {
				pMenu->focusNext();
			}
			break;
		case ID_M5BALA:
		case ID_ROBOT:
			isBalance = (mi->tag == ID_M5BALA);
			if (prefsPutBool(PKEY_IS_BALANCE, isBalance)) {
				prefsStatusPrint(ROBOT_MODE);
			}
			break;
		case ID_VOLUME:
			audio.stop();
			if (prefsPutBool(PKEY_MUTE, false)) {
				int volume = audio.getVolume();
				if (prefsPutUChar(PKEY_VOLUME, volume)) {
					String s("Volume ");
					prefsStatusPrint((s += volume).c_str());
				}
			}
			break;
		case ID_MUTE:
			if (prefsPutBool(PKEY_MUTE, true)) {
				prefsStatusPrint("Mute");
			}
			break;
		case ID_VOICE_TEST: {
			int n = playVoice();
			char buff[16];
			sprintf(buff, "%d/%d", n + 1, R2D2_COUNT);
			prefsStatusPrint(buff);
			break;
		}
		default:
			break;
	}
}

//
// setup()
//
void setup() {
	M5.begin();
	Wire.begin();

	ledcDetachPin(SPEAKER_PIN); // for Servo (TODO)

	if (digitalRead(BUTTON_A_PIN) == 0) {
		Serial.println("Will Load menu binary");
		updateFromFS(SD);
		ESP.restart();
	}

//	M5.Lcd.setTextFont(1);
//	M5.Lcd.setTextSize(2);
	M5.Lcd.setFreeFont(FREE_FONT);
	M5.Lcd.setCursor(0, 16);
	M5.Lcd.setTextColor(COLOR_OK);

	prefsBegin();
	isBalance = prefs.getBool(PKEY_IS_BALANCE, true);
	Serial.println(ROBOT_MODE);

	audio.setVolume(prefs.getUChar(PKEY_VOLUME, MIN_VOLUME + 1));
	audio.setMute(prefs.getBool(PKEY_MUTE, false));
	audio.setSampleRate(SAMPLE_RATE);
	audio.setWaveData(waveDataArray, waveDataSizeArray);

	if (M5.BtnC.isPressed()) { // ButtonC to Setup menu
		prefs.end();
		setupMenu();
		while (M5.BtnC.isPressed()) {
			M5.BtnC.read();
		}
		return;
	}

	m5bala.begin(isBalance);
	if (isBalance) {
		if (M5.BtnB.isPressed()) { // ButtonB to Tune Gyro (Balance Mode)
			M5.Lcd.setTextColor(TFT_WHITE);
			m5bala.autoTuneGyroOffset(prefs);
			M5.Lcd.setTextColor(COLOR_OK);
		} else {
			m5bala.setGyroOffsets(prefs);
		}
	}
	prefs.end();

	if (!isBalance) {
		m5bala.setAutoStraight();

		servo.begin(SERVO_PIN);
		pinMode(PIR_PIN, INPUT_PULLUP);

		if (!tof.begin(0.2)) {
			M5.Lcd.setTextColor(COLOR_NG);
			_println("Failed to boot VL53L0X");
			M5.Lcd.setTextColor(COLOR_OK);
		}
	}

#ifdef BLYNK
#ifndef BLYNK_BLE
	_printf("Blynk connecting to %s ...\r\n", ssid);
	Blynk.begin(auth, ssid, pass);
#else
	_println("Blynk connecting BLE ...");
	Blynk.setDeviceName("Blynk");
	Blynk.begin(auth);
	_println("Blynk started");
#endif
#endif // BLINK
	delay(500);
	M5.Lcd.clear();

	// Robo Face
	if (!isBalance) {
		face.begin();
		face.showEyes();
		face.driftEyes();
	}
	Serial.println("setup done");
}

//
// loop()
//
void loop() {
	static unsigned long tick;
	static int error = -1;

	if (pMenu) {
		doMenu();
		status.update();
		return;
	}

	unsigned long t = millis();
	if (t < tick) return;
	tick = t + (isBalance ? 20 : 50);  // TODO

#ifdef BLYNK
	Blynk.run();
#endif

	if (!isBalance) {
		// TOF Sensor
		if (tof.isReady) {
			int d = tof.getDistance();
#ifdef BLYNK
			Blynk.virtualWrite(V10, d);
#endif
			Serial.println(d);
			status.print(d, COLOR_OK, true);
		}

		// PIR Sensor
		bool b = digitalRead(PIR_PIN) == HIGH;
		if (b != isPIR) {
			isPIR = b;
			face.createPalette(isPIR ? 120 : 0); // Hue
			Serial.print("PIR=");Serial.println(isPIR ? 1 : 0);
		}

		if (timeline.state == 0) {
			if (M5.BtnA.wasPressed()) {
//				timeline.begin(tl_findHuman);
				timeline.begin(tl_forward);
			} else if (M5.BtnB.wasPressed()) {
				timeline.begin(tl_runOnFloor);
			} else if (M5.BtnC.wasPressed()) {
				timeline.begin(tl_runOnDesk);
			}
		} else if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
			m5bala.stop();
			timeline.end();
		}

		for (;;) {
			int event = timeline.update();
			if (event == 0) break;
			if (event < TILT_COUNT) {
				setTilt(event);
			} else if (event < TILT_COUNT + R2D2_COUNT) {
				audio.play(event - TILT_COUNT);
			} else {
				switch (event) {
					case ROBO_STOP:
						m5bala.stop();
						face.moveEyes();
						break;
					case ROBO_SHOW_EYES:
						face.showEyes();
						break;
					case ROBO_HIDE_EYES:
						face.hideEyes();
						break;
					case ROBO_STARE_EYES:
						face.stareEyes(0.5);
						break;
					case ROBO_RESET_EYES:
						face.stareEyes(1.0);
						break;
					case ROBO_DRIFT_EYES:
						face.driftEyes();
						break;
					case ROBO_ROTATE:
					case ROBO_ROTATE90:
					case ROBO_ROTATE180:
						m5bala.startRotate();
					//	face.moveEyes(SPEED_ROTATE / 3);
						break;
					case ROBO_FIND_HUMAN:
					case ROBO_FIND_WALL:
						m5bala.startRotate();
					//	face.moveEyes(SPEED_ROTATE_SLOW / 3);
					//	break;
					case ROBO_FORWARD:
						tof.startEvent();
						break;
					default:
						break;
				}
			}
		}
		switch (timeline.state) {
			case ROBO_ROTATE:
			case ROBO_ROTATE90:
			case ROBO_ROTATE180: {
				m5bala.rotate(-SPEED_ROTATE);
				int angle = m5bala.getRotateAngle();
				if (timeline.state == ROBO_ROTATE90 && angle >= 70 // TODO
				 || timeline.state == ROBO_ROTATE180 && angle >= 180) {
					m5bala.stop();
					face.moveEyes();
					timeline.skipToNext();
				}
				break;
			}
			case ROBO_FORWARD:
				m5bala.move(SPEED_RUN);
				if (tof.isReady) {
					if (tilt == TILT_DOWN) {
						if (tof.isLostFloor()) {
							m5bala.stop();
							timeline.skipToNext();
						}
					} else if (tilt == TILT_FRONT) {
						if (tof.distance > 0 && tof.distance <= 100) { // distance to Wall
							m5bala.stop();
							timeline.skipToNext();
						}
					}
				}
				break;
			case ROBO_BACKWARD:
				m5bala.move(-SPEED_RUN);
				break;
			case ROBO_FIND_HUMAN:
			case ROBO_FIND_WALL: {
				m5bala.rotate(-SPEED_ROTATE_SLOW);
				if (abs(m5bala.getRotateAngle()) >= 360) {
					m5bala.stop();
					face.moveEyes();
					timeline.skipTo(ROBO_NOT_FOUND);
				} else if (timeline.state == ROBO_FIND_WALL) {
					if (tof.isFoundNearest()) {
						m5bala.stop();
						face.moveEyes();
						timeline.skipTo(ROBO_FOUND);
					}
				} else { // ROBO_FIND_HUMAN
					if (isPIR && tof.isFoundNearest(200, 500, 1)) {
						m5bala.stop();
						face.moveEyes();
						timeline.skipTo(ROBO_FOUND);
					}
				}
				break;
			}
			default:
				break;
		}
	}

	if (m5bala.run()) {
#ifdef BLYNK
		Blynk.virtualWrite(V8, m5bala.getSpeed0());
		Blynk.virtualWrite(V9, m5bala.getSpeed1());
#endif
	}

	if (m5bala.isTumbled) {
		m5bala.isTumbled = false;
		audio.play(R2D2_SAD);
	}

	int e = m5bala.getError();
	if (e != error) {
		if (e == 0) {
			if (error == -1) {
				M5.Lcd.clear();
				audio.play(R2D2_PROCESSING);
			}
			status.clearError();
			status.print("Ready");
		} else {
			status.printError("I2C ERROR!");
			audio.play(R2D2_SNAPPY);
		}
		error = e;
	}

	if (isBalance) {
		printM5BalaStatus(error != 0);
	} else {
		face.update();
	}
	status.update();

	M5.update();
}
