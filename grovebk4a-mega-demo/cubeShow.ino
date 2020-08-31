// Based on https://colinord.blogspot.com/2015/01/arduino-oled-module-with-3d-demo.html

int wireframe[12][2];
const char front_depth = 20;
const char back_depth = -20;  

//Store cube vertices
const char cube_vertex[8][3] = {
 { -20, -20, front_depth},
 {20, -20, front_depth},
 {20, 20, front_depth},
 { -20, 20, front_depth},
 { -20, -20, back_depth},
 {20, -20, back_depth},
 {20, 20, back_depth},
 { -20, 20, back_depth}
};

void draw_wireframe(void) {
  for(byte i=0; i<4; i++) {
    u8g2.drawLine(wireframe[i][0], wireframe[i][1], wireframe[(i+1)%4][0], wireframe[(i+1)%4][1]);
    u8g2.drawLine(wireframe[4+i][0], wireframe[4+i][1], wireframe[4+(i+1)%4][0], wireframe[4+(i+1)%4][1]);
    u8g2.drawLine(wireframe[i][0], wireframe[i][1], wireframe[4+i][0], wireframe[4+i][1]);
  }
//cross face above
/* u8g2.drawLine(wireframe[1][0], wireframe[1][1], wireframe[3][0], wireframe[3][1]);
 u8g2.drawLine(wireframe[0][0], wireframe[0][1], wireframe[2][0], wireframe[2][1]);
*/
}

void cubeShow() {
  float rot, rotx, roty, rotz, rotxx, rotyy, rotzz, rotxxx, rotyyy, rotzzz;
  const int originx = 64;
  const int originy = 32; 

  float tx, nx, p;
  float ty, ny, py;
  int fl, scale; //focal length
  const double degtorad = .0174532778;
  for (int angle = 0; angle <= 360; angle += 3) {
    for (byte i = 0; i < 8; i++) {
      rot = angle * degtorad; //0.0174532 = one degree
      //rotateY
      rotz = cube_vertex[i][2] * cos(rot) - cube_vertex[i][0] * sin(rot);
      rotx = cube_vertex[i][2] * sin(rot) + cube_vertex[i][0] * cos(rot);
      roty = cube_vertex[i][1];
      //rotateX
      rotyy = roty * cos(rot) - rotz * sin(rot);
      rotzz = roty * sin(rot) + rotz * cos(rot);
      rotxx = rotx;
      //rotateZ
      rotxxx = rotxx * cos(rot) - rotyy * sin(rot);
      rotyyy = rotxx * sin(rot) + rotyy * cos(rot);
      rotzzz = rotzz;
  
      //orthographic projection
      rotxxx += originx;
      rotyyy += originy;
  
      //store new vertices values for wireframe drawing
      wireframe[i][0] = rotxxx;
      wireframe[i][1] = rotyyy;
      wireframe[i][2] = rotzzz;
  
     // u8g2.drawPixel (rotxxx, rotyyy);
      digitalWrite(ledPin, (angle % 2 == 0) ? HIGH : LOW);

      if (digitalRead(buttonPin) == HIGH) {
        break;
      }
    }
    u8g2.firstPage();
    do {
      draw_wireframe();
    } while(u8g2.nextPage());
    if (digitalRead(buttonPin) == HIGH) {
      break;
    }
  }
}
