# M5Bala_Robot
M5Bala Tilt Servo Robot with PIR and TOF Sensor<br>
[Movie](https://www.youtube.com/watch?v=co43yuhac1o),
[Short Demo](https://www.youtube.com/watch?v=akfxEFwsyFQ)

![M5Bala Robot](https://user-images.githubusercontent.com/46808493/54679760-7a6b6600-4b4b-11e9-81b8-4aed014e21ad.jpg)

## Description

- M5Bala Balance mode and self-controled Robot mode.<br>
(Open the setup menu by pressing the C button on reset.)
- Perform the following 3 actions:
  - BtnA : Look around and search for human.
  - BtnB : Find the nearest wall and advance to it.
  - BtnC : Advance to the edge of the desk.
- Servo motor(FS0307) controls tilt angle.
- PIR sensor detects human, TOF sensor measures distance.
- 'ROBOT' Voice: https://www.soundboard.com/sb/r2d2_r2_d2_sounds
- java/dump_wav.java: 8bit mono .wav files to C Header files
- Manual control via [Blynk](https://www.blynk.cc/) (Wifi/BLE).
- Unispace free font: https://www.1001freefonts.com/fixed-width-fonts.php
 (use [fontconvert](https://github.com/adafruit/Adafruit-GFX-Library/tree/master/fontconvert))

![git_cap_setup_blynk](https://user-images.githubusercontent.com/46808493/54685019-18196200-4b59-11e9-96cd-d31163627989.jpg)

## Dependent libraries
- [M5Stack-SD-Updater](https://github.com/tobozo/M5Stack-SD-Updater)
- [ESP32 BLE Arduino](https://github.com/nkolban/ESP32_BLE_Arduino)
- [Blynk](https://github.com/blynkkk/blynk-library)
- [MPU6050_tockn](https://github.com/tockn/MPU6050_tockn)
- [Adafruit_VL53L0X](https://github.com/adafruit/Adafruit_VL53L0X)
- [M5Stack_TreeView](https://github.com/lovyan03/M5Stack_TreeView)
- [M5OnScreenKeyboard](https://github.com/lovyan03/M5Stack_OnScreenKeyboard)

## References

- M5Bala example: https://github.com/m5stack/M5Bala/tree/master/examples/Blynk_BLE
- [iPhoneを使ってM5BALAを操作する（Blynk-BLE編）](https://qiita.com/inasawa/items/6bc2cc0932e5cdd378e5)

## Attention

### TOF Sensor(VL53L0X) issue
M5Stack TOF Unit I purchased was very unstable, not working at all on Fire-PortA, and barely working on the M5Bala's power supply.<br>
The alternative [Seeed Studio Grove TOF Sensor](https://www.switch-science.com/catalog/3988/) worked perfectly!

### Partition issue
 Because the library of BLE is very large, the following error appears.

 ```
 Memory Usage -> http://bit.ly/pio-memory-usageError: The program size (1341988 bytes) is greater than maximum allowed (1310720 bytes)
DATA:    [==        ]  19.0% (used 62252 bytes from 327680 bytes)*** [checkprogsize] Explicit exit, status 1
PROGRAM: [==========]  102.4% (used 1341988 bytes from 1310720 bytes)
 ```
 It is necessary to change ESP32 partition table. For example:
- ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/default.csv
> #Name,   Type, SubType, Offset,  Size, Flags<br>
> nvs,      data, nvs,     0x9000,  0x5000,<br>
> otadata,  data, ota,     0xe000,  0x2000,<br>
> app0,     app,  ota_0,   0x10000, 0x180000,<br>
> app1,     app,  ota_1,   0x190000,0x180000,<br>
> eeprom,   data, 0x99,    0x310000,0x1000,<br>
> spiffs,   data, spiffs,  0x311000,0xEF000,<br>

- ~/.platformio/packages/framework-arduinoespressif32/boards.txt
> esp32.upload.maximum_size=1572864
