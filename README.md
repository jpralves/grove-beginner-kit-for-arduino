# grove-beginner-kit-for-arduino

Created by Joao Alves <jpralves@gmail.com> on 2020-Aug-31.
Copyright 2020 - Under creative commons license 4.0: Attribution-ShareAlike CC BY-SA
This software is provided "as is", without technical support, and with no warranty,
express or implied, as to its usefulness for any purpose.
```
____ ____ ____ _  _ ____    ___  ____ ____ _ _  _ _  _ ____ ____
| __ |__/ |  | |  | |___    |__] |___ | __ | |\ | |\ | |___ |__/
|__] |  \ |__|  \/  |___    |__] |___ |__] | | \| | \| |___ |  \

_  _ _ ___    ____ ____ ____    ____ ____ ___  _  _ _ _  _ ____
|_/  |  |     |___ |  | |__/    |__| |__/ |  \ |  | | |\ | |  |
| \_ |  |     |    |__| |  \    |  | |  \ |__/ |__| | | \| |__| Mega Demo
```
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
