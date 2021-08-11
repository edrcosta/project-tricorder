#include "U8glib.h"

// Setup Diplay
U8GLIB_ST7920_128X64_1X u8g(6, 5, 4 ,7); //Enable, RW, RS, RESET  

void draw(void) {
    u8g.drawStr( 0, 22, "insert a command");
}

void setup(void) {  
  pinMode(8, OUTPUT);
  u8g.setFont(u8g_font_unifont);
}

void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
}