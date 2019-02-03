# M5Bala_BlynkRobo
M5Bala control via Blynk (with 'ROBOT' voice)

[Youtube](https://www.youtube.com/watch?v=QmPKu_nfZk0)

![Blynk](http://vcraft.jp/blog/files/cap_blynk_bala_1.jpg)

## About
Control M5Stack Fire+M5Bala via [Blynk](https://www.blynk.cc/) (Wifi/BLE).
- Original Project: https://github.com/m5stack/M5Bala/tree/master/examples/Blynk_BLE
- ROBOT Voice: https://www.soundboard.com/sb/r2d2_r2_d2_sounds
- [iPhoneを使ってM5BALAを操作する（Blynk-BLE編）](https://qiita.com/inasawa/items/6bc2cc0932e5cdd378e5)
- dump_wav.java: 8bit mono .wav files to C Header files

## Dependent library
- [ESP32 BLE Arduino](https://github.com/nkolban/ESP32_BLE_Arduino)
- [Blynk](https://github.com/blynkkk/blynk-library)
- [M5Stack-SD-Updater](https://github.com/tobozo/M5Stack-SD-Updater)

## Attention
 Because the library of BLE is very large, the following error appears.

 ```
 Memory Usage -> http://bit.ly/pio-memory-usageError: The program size (1341988 bytes) is greater than maximum allowed (1310720 bytes)
DATA:    [==        ]  19.0% (used 62252 bytes from 327680 bytes)*** [checkprogsize] Explicit exit, status 1
PROGRAM: [==========]  102.4% (used 1341988 bytes from 1310720 bytes)
 ```
 It is necessary to change ESP32 partition table. For example:
- ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/default.csv
> #Name,   Type, SubType, Offset,  Size, Flags
> nvs,      data, nvs,     0x9000,  0x5000,
> otadata,  data, ota,     0xe000,  0x2000,
> app0,     app,  ota_0,   0x10000, 0x180000,
> app1,     app,  ota_1,   0x190000,0x180000,
> eeprom,   data, 0x99,    0x310000,0x1000,
> spiffs,   data, spiffs,  0x311000,0xEF000,

- ~/.platformio/packages/framework-arduinoespressif32/boards.txt
> esp32.upload.maximum_size=1572864
