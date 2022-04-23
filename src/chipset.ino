#include <Wire.h>
#include <TFT.h>  
#include <SPI.h>

// TFT 
#define cs   10
#define dc   9
#define rst  8

TFT TFTscreen = TFT(cs, dc, rst);

// i2c keyboard cardkb
int KeyboardI2CAddress = 0x5F;
int X0,X1,X_out;

// address DATAX0 register
#define X_Axis_Register_DATAX0 0x32
// address DATAX1 register
#define X_Axis_Register_DATAX1 0x33
// Power Register
#define Power_Register 0x2D


char keyboardBuffer[] = "";


void enableReadingI2c(){
  Wire.beginTransmission(KeyboardI2CAddress);
  Wire.write(Power_Register);
  // Bit D3 High for measuring enable (0000 1000)
  Wire.write(8);  
  Wire.endTransmission();
}

void resetDisplay() {
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  enableReadingI2c();
  resetDisplay();
}

void readKeyboard(){
  // Init connection
  Wire.beginTransmission(KeyboardI2CAddress);
  // Read data registers
  Wire.write(X_Axis_Register_DATAX0);
  Wire.write(X_Axis_Register_DATAX1);
  Wire.endTransmission();
  // Request
  Wire.requestFrom(KeyboardI2CAddress, 2);
  // Response
  if(Wire.available()<=2) {  
    // Reads registers
    X0 = Wire.read();
    X1 = Wire.read();   
  }

  if(X0 > 0){
    keyboardBuffer = strcat(keyboardBuffer, (char)X0);
    Serial.print("X0= ");
    Serial.print((char)X0);
    Serial.print(keyboardBuffer);
    Serial.print("   X1= ");
    Serial.println(X1);
  }
}

void loop() {
  readKeyboard();
}


