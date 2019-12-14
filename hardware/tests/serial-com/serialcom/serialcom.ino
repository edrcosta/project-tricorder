
#include <SoftwareSerial.h>

#define ADDR "CA"
SoftwareSerial tiny(10, 11); //TBD

void setup() {
  Serial.begin(9600); //debug only
  tiny.begin(9600);
  delay(2000);
  
  tiny.write(ADDR);
}

void loop() {
  //nothing here
  tiny.write("HELLO");

  delay(1000);
}
