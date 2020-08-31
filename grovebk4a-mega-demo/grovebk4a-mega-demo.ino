/*

Created by Joao Alves <jpralves@gmail.com> on 2020-Aug-31.
Copyright 2020 - Under creative commons license 4.0: Attribution-ShareAlike CC BY-SA
This software is provided "as is", without technical support, and with no warranty,
express or implied, as to its usefulness for any purpose.
____ ____ ____ _  _ ____    ___  ____ ____ _ _  _ _  _ ____ ____
| __ |__/ |  | |  | |___    |__] |___ | __ | |\ | |\ | |___ |__/
|__] |  \ |__|  \/  |___    |__] |___ |__] | | \| | \| |___ |  \

_  _ _ ___    ____ ____ ____    ____ ____ ___  _  _ _ _  _ ____
|_/  |  |     |___ |  | |__/    |__| |__/ |  \ |  | | |\ | |  |
| \_ |  |     |    |__| |  \    |  | |  \ |__/ |__| | | \| |__| Mega Demo

Latest versions are available in https://jpralves.net
and https://github.com/jpralves/grove-beginner-kit-for-arduino.

This demo was created to show some of the possibilities to use the
grove modules that come with Grove Beginner Kit for Arduino.
Use the button from the button module to change to the next demo.

It uses several different libraries, all included except u8g2.
The code is divided in multiple files for better organization.

This sketch has 10 different demos:
- logoShow.ino with buzzerShow.ino using OLED display module and buzzer module
- cubeShow.ino - 3D rotating cube using OLED display module
- microShow.ino - three different displays of a audio spectrum analyzer using the grove microphone module
- tempShow.ino - displays temperature and humidity using DHT11 module
- pressureShow.ino - displays pressure and temperature using BMP280 module
- aceleShow.ino - displays x,y,z acceleration using LIS3DHTR module
- lightShow.ino - displays values of light sensor module
- trimShow.ino - uses gauge to display value of the trimmer module

It uses code from others worth mentioning:
- u8g2 library (https://github.com/olikraus/u8g2/wiki)
- DHT from Adafruit Industries (https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor)
- BMP280 from Seeed Studio (https://github.com/Seeed-Studio/Grove_BMP280)
- LIS3DHTR from Seeed Studio (https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR)
- fix_fft from Tom Roberts (https://github.com/kosme/fix_fft)
- 3D cube from Colin Ord (https://colinord.blogspot.com/2015/01/arduino-oled-module-with-3d-demo.html)
- audio spectrum analyser from paul (https://www.dellascolto.com/bitwise/2017/05/25/audio-spectrum-analyzer/)
- code from the official Grove Beginners Kit demo.
- gauge from Giuseppe Bellomo (https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_page_buffer/Gauge/Gauge.ino)

To build, the only requirement is to have u8g2 library installed in Arduino IDE.
Tested with Arduino IDE 1.8.13 and Seeeduino Lotus (Arduino Uno compatible).
*/

#include <U8g2lib.h>
#include <Wire.h>
#include "DHT.h"
#include "Seeed_BMP280.h"
#include "LIS3DHTR.h"
#include "fix_fft.h"
#include "pitches_enhanced.h"

const byte trimPin = A0;
const byte soundPin = A2;
const byte lightPin = A6;
const byte dhtPin = 3;
const byte ledPin = 4;
const byte buzzerPin = 5;
const byte buttonPin = 6;
const byte altledPin = 13;

DHT dht(dhtPin, DHT11);
LIS3DHTR<TwoWire> accelemeter;
BMP280 bmp280;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);

byte stateMode = 0;

void setup() {
  Serial.begin(115200);

  pinMode(soundPin, INPUT);
  pinMode(buttonPin,INPUT);
  pinMode(altledPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  if(!bmp280.init()){
    Serial.println("bmp280 init error!");
  }
  //accelemeter.begin(Wire);
  accelemeter.begin(Wire, LIS3DHTR_ADDRESS_UPDATED); //IIC init
  delay(100);
  accelemeter.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
  if (!accelemeter) {
    Serial.println("LIS3DHTR didn't connect.");
  }

  analogReference(DEFAULT);
  u8g2.begin();
}

// List of demos:
typedef void(*callback_t)(void);
callback_t funcShow[] {
  &logoShow, &cubeShow, &microShow1, &microShow2, &microShow3, &tempShow, &pressureShow, &aceleShow, &lightShow, &trimShow
};

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    while (digitalRead(buttonPin) == HIGH) delay(10);
    stateMode = (stateMode + 1) % (sizeof(funcShow)/sizeof(funcShow[0]));
  }
  funcShow[stateMode]();
}
// Sketch uses 28560 bytes (88%) of program storage space. Maximum is 32256 bytes.
// Global variables use 1178 bytes (57%) of dynamic memory, leaving 870 bytes for local variables. Maximum is 2048 bytes.
