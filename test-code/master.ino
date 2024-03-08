// i2c/wiring proof of concept code - tie two Arduinos together via
// i2c and do some simple data xfer.
//
// master side code
//
// Jason Winningham (kg4wsv)
// 14 jan 2008

#include <Wire.h> 

void setup() 
{ 
  Wire.begin();        // join i2c bus (address optional for master) 
  Serial.begin(9600);  // start serial for output 
  Serial.print("master sleeping...");
  delay(2000);
  Serial.println("go");
} 
 
void loop() 
{ 
  Wire.requestFrom(2, 1);    // request data from slave device #2 
 
  while(Wire.available())
  { 
    char c = Wire.receive(); // receive a byte as character 
    Serial.print(c);         // print the character 
  } 
 
  delay(100); 
}