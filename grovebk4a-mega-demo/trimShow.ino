// Based on https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_page_buffer/Gauge/Gauge.ino

void drawGauge(int x, byte y, byte r, byte p, int v, int minVal, int maxVal, byte t) {
  float gs_rad, ge_rad, i;
  int xp, yp;
  int n = (r / 100.00) * p; // calculate needle percent lenght

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    switch (t & 0x0f){
      case 0: //left quarter
        gs_rad = -1.572; //-90 degrees in radiant
        ge_rad = 0;
        i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        xp = x + (sin(i) * n);
        yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT);
        u8g2.drawLine(x, y, xp, yp);
        if ((t & 0x10) != 0) {
          u8g2.setCursor(60, 20);
          u8g2.print(v);
        }
        break;
      case 1: //right quarter, needle anticlockwise
        gs_rad = 0;
        ge_rad = 1.572; //90 degrees in radiant
        i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        xp = x + (cos(i) * n);
        yp = y - (sin(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_RIGHT);
        u8g2.drawLine(x, y, xp, yp);
        if ((t & 0x10) != 0) {
          u8g2.setCursor(10, 20);
          u8g2.print(v);
        }
        break;
      case 2: //upper half
        gs_rad = -1.572;
        ge_rad = 1.572;
        i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        xp = x + (sin(i) * n);
        yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT);
        u8g2.drawLine(x, y, xp, yp);
        if ((t & 0x10) != 0) {
          u8g2.setCursor(40, 40);
          u8g2.print(v);
        }
        break;
      case 3: //three quarter starting at -180
        gs_rad = -3.142;
        ge_rad = 1.572;
        i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        xp = x + (sin(i) * n);
        yp = y - (cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_LEFT);
        u8g2.drawLine(x,y,xp,yp);
        if ((t & 0x10) != 0) {
          u8g2.setCursor(60, 38);
          u8g2.print(v);
        }
        break;
      case 4: //three quarter starting at -90
        gs_rad = -1.572;
        ge_rad = 3.141;
        i = ((v - minVal) * (ge_rad - gs_rad) / (maxVal - minVal) + gs_rad);
        xp = x+(sin(i) * n);
        yp = y-(cos(i) * n);
        u8g2.drawCircle(x, y, r, U8G2_DRAW_UPPER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_LOWER_RIGHT);
        u8g2.drawLine(x, y, xp, yp);
        if ((t & 0x10) != 0) {
          u8g2.setCursor(12, 38);
          u8g2.print(v);
        }
        break;
    }
  } while(u8g2.nextPage());
}

void trimShow() {
  int v = 1023 - analogRead(trimPin);
  drawGauge(50, 20, 20, 80, v, 0, 1023, 0 | 0x10);
}
