#include <TFT.h>  
#include <SPI.h>
#include <Wire.h>

// TFT
#define DISPLAY_RESET_INPUT 8
#define DISPLAY_CS_INPUT 10
#define DISPLAY_DS_INPUT 9
TFT TFTscreen = TFT(DISPLAY_CS_INPUT, DISPLAY_DS_INPUT, DISPLAY_RESET_INPUT);

// KEYBOARD
// Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX0 0x32
// Hexadecima address for the DATAX1 internal register.
#define X_Axis_Register_DATAX1 0x33
// Power Control Register
#define Power_Register 0x2D

// Keyboard data variables
int keyboardi2cAddress = 0x5F;
int X0,X1,X_out;

// Screen data variables
int UPDATE_SCREEN_COUNTER = 0;
int LINE_Y = 0;
int LINE_X = 0;
int MAX_ROW_SIZE = 10;
int MAX_LINE_SIZE = 16;

// Screen buffer
String TEXT_OUTPUT[6] = { 
  "                ", 
  "                ", 
  "                ", 
  "                ", 
  "                ", 
  "                ", 
  "                ", 
  "                ", 
  "                ", 
  "                ", 
};

// Jump to the line bellow if its at the last line back to the top
void pressEnter(){
  LINE_Y++;
  if(LINE_Y >= MAX_ROW_SIZE){
    LINE_Y = 0;
  }
  LINE_X = 0;
}

// create a new char on TEXT_OUTPUT at the current cursor position
void addCharacterToTextBuffer(){
  TEXT_OUTPUT[LINE_Y][LINE_X] = (char) X0;

  LINE_X++;
  if(LINE_X >= MAX_LINE_SIZE){
    LINE_X = 0;
  }
}

// Read the keyboard registers to check for new inputs
void readKeyboard(){
  Wire.beginTransmission(keyboardi2cAddress);
  Wire.write(X_Axis_Register_DATAX0);
  Wire.write(X_Axis_Register_DATAX1);
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  Wire.requestFrom(keyboardi2cAddress,2); // Request the transmitted two bytes from the two registers
  
  if(Wire.available()<=2) {
    X0 = Wire.read(); 
    X1 = Wire.read();   
  }

  if(X0 > 0){
    if(X0 == 13 && X1 == 255){
      pressEnter();
    }else{
      addCharacterToTextBuffer();
    }
  }
}

// enable i2c keyboard
void enableMeasurement(){
  // Enable measurement
  Wire.beginTransmission(keyboardi2cAddress);
  Wire.write(Power_Register);
  // Bit D3 High for measuring enable (0000 1000)
  Wire.write(8);  
  Wire.endTransmission();
}

// Clear Display
void resetDisplay(){
  TFTscreen.background(0, 0, 0);
}

void setup() {
  TFTscreen.begin();
  resetDisplay();
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  enableMeasurement();
  delay(100);
}

// Write text to the screen
void updateScreen(){
    // TFTscreen.setTextSize();
    TFTscreen.stroke(random(0, 255), random (0, 255), random (0, 255));
    for(int i = 0;i < MAX_ROW_SIZE;i++){
      char LINE[16];
      TEXT_OUTPUT[i].toCharArray(LINE, 16);
      TFTscreen.text(LINE, 5, i * 10);
    }
}

void loop() {
  if(UPDATE_SCREEN_COUNTER == 10){
    updateScreen();
    readKeyboard();
    UPDATE_SCREEN_COUNTER = 0;
  }

  UPDATE_SCREEN_COUNTER++;
  delay(10);
}