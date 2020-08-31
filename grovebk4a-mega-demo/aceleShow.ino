int xa = 50, ya = 13;

void aceleShow() {
  float ax = accelemeter.getAccelerationX();
  float ay = accelemeter.getAccelerationY();
  float az = accelemeter.getAccelerationZ();  
  if (ya >= 15) {
    if (ay > 0.2 && ay < 0.5) {
      ya--;
    } else if (ay >= 0.5 && ay < 0.8) {
      ya -= 2;
    } else if (ay >= 0.8) {
      ya -= 3;
    }
  }
  if (ya < 57) {
    if (ay < -0.2 && ay > -0.5) {
      ya++;
    } else if (ay <= -0.5 && ay > -0.8) {
      ya += 2;
    } else if (ay <= -0.8) {
      ya += 3;
    }
  }
  if (xa <= 108) {
    if (ax > 0.2 && ax < 0.5) {
      xa++;
    } else if (ax >= 0.5 && ax < 0.8) {
      xa += 2;
    } else if (ax >= 0.8) {
      xa += 3;
    }
  }
  if (xa >= 52) {
    if (ax < -0.2 && ax > -0.5) {
      xa--;
    } else if (ax <= -0.5 && ax > -0.8) {
      xa -= 2;
    } else if (ax <= -0.8) {
      xa -= 3;
    }
  }
  Serial.print(ax);
  Serial.print("\t");
  Serial.print(ay);
  Serial.print("\t");
  Serial.println(az);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_12b_mr);
    u8g2.setCursor(0, 16);
    u8g2.print(F("X:"));
    u8g2.print(ax);
    u8g2.setCursor(0, 32);
    u8g2.print(F("Y:"));
    u8g2.print(ay);
    u8g2.setCursor(0, 48);
    u8g2.print(F("Z:"));
    u8g2.print(az);
    u8g2.drawLine(50, 60, 50, 10);
    u8g2.drawLine(110, 10, 50, 10);
    u8g2.drawLine(110, 60, 50, 60);
    u8g2.drawLine(110, 60, 110, 10);
    u8g2.drawDisc(xa, ya, 3, U8G2_DRAW_ALL);
  } while(u8g2.nextPage());
}

