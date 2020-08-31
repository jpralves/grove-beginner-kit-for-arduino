void pressureShow() {
  uint32_t pressure = bmp280.getPressure();
  float temp = bmp280.getTemperature();
  Serial.println(pressure);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_16b_mr);
    u8g2.setCursor(30, 16);
    u8g2.print(F("Pressure:")); 
    u8g2.setCursor(25, 34);
    u8g2.print(pressure);
    u8g2.print("Pa");
    u8g2.setCursor(20, 54);
    u8g2.print(F("temp: "));
    u8g2.print(temp);
    u8g2.print(F("C"));
  } while(u8g2.nextPage());
}
