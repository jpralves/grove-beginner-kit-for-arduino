// Based on http://www.dellascolto.com/bitwise/2017/05/25/audio-spectrum-analyzer/

char im[64], data[64];                                //variables for the FFT

void microShow(byte displayMode) {
  char basex = 0, ylim = 60;      //variables for drawing the graphics
  int dropMax = 0;
  int curMax;
  int minVal = 1024, maxVal = 0;  //set minumum & maximum ADC values
  for (byte i = 0; i < 64; i++) {
    //take 64 samples
    int val = analogRead(soundPin);      //get audio from Analog 0
    data[i] = val / 4 - 128;           // each element of array is val/4-128
    im[i] = 0;
    if(val > maxVal) maxVal = val;     //capture maximum level
    if(val < minVal) minVal = val;     //capture minimum level
  }
  fix_fft(data, im, 6, 0);

  u8g2.firstPage();
  do {
    if (displayMode == 3) {
      u8g2.drawLine(0, 63, 128, 63);
    }
    int prevx = 0;
    int prevy = ylim - 36;
    for (byte i = 1; i < 64; i++) {
      int dat = sqrt(data[i] * data[i] + im[i] * im[i]);
      dat = (2 - dat / 60) * dat;
      // u8g2.drawLine(0, 63, 128, 63);  // baseline
      switch(displayMode) {
      case 1:
        u8g2.drawPixel(i*4 + basex, ylim - dat + 5);
        break;
      case 2:
        u8g2.drawLine(prevx, prevy, (i*4 + basex), ylim - dat / 2 + 5 - 36);
        prevx = i * 4 + basex;
        prevy = ylim - dat / 2 + 5- 36;
        break;
      case 3:
        u8g2.drawBox(i*4 + basex, ylim - dat + 5, 2, 63 - ylim + dat);
        break;
      }
    }
    curMax = (dropMax + 2 * min((maxVal - minVal) / 4 - 12, 128)) / 3;
    if (curMax > 96)
      Serial.println(curMax);
    digitalWrite(ledPin, (curMax >= 127) ? HIGH : LOW);
    digitalWrite(altledPin, (dropMax == curMax) ? HIGH : LOW);
    u8g2.drawBox(0, 0, curMax, 3);
    if (dropMax > curMax + 4) {
      dropMax = dropMax - 3;
      u8g2.drawBox(dropMax - 4, 0, 3, 3);
    } else {
      dropMax = curMax;
    }
  } while(u8g2.nextPage());
}

void microShow1() {
  microShow(1);
}

void microShow2() {
  microShow(2);
}

void microShow3() {
  microShow(3);
}
