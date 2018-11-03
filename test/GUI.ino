#include "U8glib.h"
                     //  D0, D1, CS, DC, RES
U8GLIB_SH1106_128X64 u8g(13, 11, 10,  9,  8); 

int ran[6];
void drawCir(int cir1, int cir2, int cir3, int cir4, int cir5, int cir6){
        u8g.drawCircle(10,10, cir1);
        u8g.drawCircle(10,20, cir2);
        u8g.drawCircle(10,30, cir3);
        u8g.drawCircle(25,10, cir4);
        u8g.drawCircle(25,20, cir5);
        u8g.drawCircle(25,30, cir6);
  }

void setup() {
  // put your setup code here, to run once:
  u8g.setFont(u8g_font_unifont);
}

void loop() {

  ran[0] = random(6);
  ran[1] = random(6);
  ran[2] = random(6);
  ran[3] = random(6);
  ran[4] = random(6);
  ran[5] = random(6);

  u8g.firstPage();
  do{
     u8g.drawStr(35, 20, "Pressure");
    drawCir(ran[0],ran[1],ran[2],ran[3],ran[4],ran[5]);
    }while(u8g.nextPage());
  delay(250);
  
}
