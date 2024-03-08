#include <TFT.h>  
#include <SPI.h>
#include <Wire.h>

// TFT
#define DISPLAY_RESET_INPUT 8
#define DISPLAY_CS_INPUT 10
#define DISPLAY_DS_INPUT 9
TFT TFTscreen = TFT(DISPLAY_CS_INPUT, DISPLAY_DS_INPUT, DISPLAY_RESET_INPUT);

// KEYBOARD
#define X_Axis_Register_DATAX0 0x32 // Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX1 0x33 // Hexadecima address for the DATAX1 internal register.
#define Power_Register 0x2D // Power Control Register

int KEYBOARD_ADDRESS_I2C = 0x5F; // Address
int X0,X1,X_out; // Keyboard data
 
// Map special keys 
int exeptionCharsInt[17] = { 27, 9, 32, 13, 8, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 183, 180 };
String exeptionChars[17] = { "esq", "tab", "space", "enter", "deletar", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "left", "right" };
// render once each 10 clock cicles
int RENDER_COUNT = 0; 

// indicate what method to run
int EXECUTING = 0;

/*
 * KEYBOARD METHODS ################################################################################  
 */

int checkCharExeption(int input){
  for (size_t i = 0; i < 15; i++) {
    if(input == exeptionCharsInt[i]) return i;
  }
  return -1;
}

void readFromKeyboard(){
  Wire.beginTransmission(KEYBOARD_ADDRESS_I2C);
  Wire.write(X_Axis_Register_DATAX0);
  Wire.write(X_Axis_Register_DATAX1);
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  Wire.requestFrom(KEYBOARD_ADDRESS_I2C,2); // Request the transmitted two bytes from the two registers
  
  if(Wire.available()<=2) {
    X0 = Wire.read(); 
    X1 = Wire.read();   
  }
}

void enableKeyboardReading(){
  Wire.beginTransmission(KEYBOARD_ADDRESS_I2C);
  Wire.write(Power_Register);
  Wire.write(8); // Bit D3 High for measuring enable (0000 1000)
  Wire.endTransmission();
}

/*
 * RENDER METHODS ##################################################################################
 */
bool renderAllowed(){
  RENDER_COUNT++;
  if(RENDER_COUNT == 10){
    RENDER_COUNT = 0;
    return true;
  }
  // delay(10);
  return false;
}

/*
 * APPLICATIONS / contexts ######################################################################
 */

String MENU_TITLES[3] = { "MENU 1", "MENU 2" };

String MENU_1[3] = { "aaaa 1 1", "MENU 1 2", "MENU 1 3" };
String MENU_2[3] = { "MENU 2 1", "MENU 2 2", "MENU 2 3" };

String *MENUS[] = { MENU_1, MENU_2 };
int MENU_POINTER = 0;
int MENU_ACTIVE = 0;

void exec_menu(){
  if(renderAllowed()){
    char title[30];
    
    MENU_TITLES[MENU_POINTER].toCharArray(title, 30);

    TFTscreen.setTextSize(3);
    TFTscreen.stroke(255,  255, 255);
    TFTscreen.text(title, 5, 10);

    for (size_t i = 0; i < sizeof(MENUS[MENU_POINTER]); i++)
    {
      char text[MENUS[MENU_POINTER][i].length() + 1];

      MENUS[MENU_POINTER][i].toCharArray(text, MENUS[MENU_POINTER][i].length() + 1);

      TFTscreen.stroke(47,  86, 214);
      
      if(i == MENU_ACTIVE){
        TFTscreen.setTextSize(1);
        TFTscreen.text(">>", 0, 45 + (20 * i));
      }else{
        TFTscreen.setTextSize(2);
      }

      TFTscreen.setTextSize(2);
      TFTscreen.text(text, 20, 40 + (20 * i));
    }
    
    // text

    char inputedChar = (char) X0;

    int i = checkCharExeption(X0);
    if(exeptionChars[i] == "left"){
      MENU_ACTIVE++;
      if(MENU_ACTIVE > sizeof(MENUS[MENU_POINTER])){
        MENU_ACTIVE = 0;
      }
    }

  }
}

/*
 * FIRMWARE METHODS ##################################################################################
 */
void executionContext(){
  switch (EXECUTING)
  {
    case 0:
      exec_menu();
      break;
  }
}

/*
 * DEFAULT METHODS ##################################################################################
 */
void setup() {
  TFTscreen.begin();
  TFTscreen.setRotation(3);
  Serial.begin(9600);
  Wire.begin();

  TFTscreen.background(0, 0, 0);
  enableKeyboardReading();
  delay(100);
}

void loop() {  
      
  readFromKeyboard();
  executionContext();

  // readFromKeyboard();
  // char inputedChar = (char) X0;

  // int i = checkCharExeption(X0)
  // if(i){
  //   Serial.println(exeptionChars[i])
  // }
  delay(100);
}