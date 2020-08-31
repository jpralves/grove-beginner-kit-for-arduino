void tempShow() {
  const int col = 20;
  int humid = dht.readHumidity();
  int temp = dht.readTemperature();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.setCursor(col, 16);
    u8g2.print(F("temp: "));
    u8g2.print(temp);
    u8g2.print(F("C"));
    u8g2.setCursor(col, 48);
    u8g2.print(F("humid: "));
    u8g2.print(humid);
    u8g2.print(F("%"));
//    u8g2.drawLine(10, 0, 10, 64);
  } while(u8g2.nextPage());
}

