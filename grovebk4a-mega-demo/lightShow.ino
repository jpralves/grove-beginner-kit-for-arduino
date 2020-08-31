void lightShow() {
  int l = analogRead(lightPin);
  uint8_t opt;
  if (l >= 50 && l < 100) {
    opt = U8G2_DRAW_UPPER_LEFT;
  }
  if (l >= 100 & l < 200) {
    opt =  U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT;
  }
  if (l >= 200 && l < 350) {
    opt = U8G2_DRAW_LOWER_LEFT | U8G2_DRAW_UPPER_RIGHT | U8G2_DRAW_UPPER_LEFT;
  }
  if (l >= 350) {
    opt = U8G2_DRAW_ALL;
  }

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.drawCircle(8, 8, 8, U8G2_DRAW_ALL);
    if (l >= 50) {
      u8g2.drawDisc(8, 8, 8, opt);
    }
    u8g2.setCursor(26, 32);
    u8g2.print(F("Light: "));
    u8g2.print(l);
    u8g2.drawHLine(0, 48, 128);
  } while(u8g2.nextPage());
}

