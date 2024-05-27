#include <TFT.h>  
#include <SPI.h>
#include <Wire.h>

// TFT
#define DISPLAY_RESET_INPUT 8
#define DISPLAY_CS_INPUT 10
#define DISPLAY_DS_INPUT 9
TFT TFTscreen = TFT(DISPLAY_CS_INPUT, DISPLAY_DS_INPUT, DISPLAY_RESET_INPUT);

// KEYBOARD
#define REG_ADDR_DATAX0 0x32
#define REG_ADDR_DATAX1 0x33
#define REG_POWER_CTRL 0x2D

int I2C_ADDR_KEYBOARD = 0x5F;
int X0,X1;// store keyboard values

int NON_ASCCII_CODE[17] = { 27, 9, 32, 13, 8, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 183, 180 };
String NON_ASCCII_KEYS[17] = { "esq", "tab", "space", "enter", "deletar", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "f10", "left", "right" };

// SYSTEM
int RENDER_CLOCK = 0; 
int EXECUTION_INDEX = 0;

/*
 * KEYBOARD METHODS ################################################################################  
 */

int isNonAscciKey(int input){
  for (size_t i = 0; i < 15; i++) {
    if(input == NON_ASCCII_CODE[i]) return i;
  }
  return -1;
}

void keyboardRead(){
  Wire.beginTransmission(I2C_ADDR_KEYBOARD);
  Wire.write(REG_ADDR_DATAX0);
  Wire.write(REG_ADDR_DATAX1);
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  Wire.requestFrom(I2C_ADDR_KEYBOARD,2); // Request the transmitted two bytes from the two registers
  
  if(Wire.available()<=2) {
    X0 = Wire.read(); 
    X1 = Wire.read();   
  }
}

void initializeKeyboard(){
  Wire.beginTransmission(I2C_ADDR_KEYBOARD);
  Wire.write(REG_POWER_CTRL);
  Wire.write(8); // Bit D3 High for measuring enable (0000 1000)
  Wire.endTransmission();
}

/*
 * RENDER METHODS ##################################################################################
 */
bool renderAllowed(){
  RENDER_CLOCK++;
  if(RENDER_CLOCK == 10){
    RENDER_CLOCK = 0;
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

int MENU_I = 0;
int MENU_ACTIVE = 0;

void exec_menu(){
  if(renderAllowed()){
    char title[30];
    
    MENU_TITLES[MENU_I].toCharArray(title, 30);

    TFTscreen.setTextSize(3);
    TFTscreen.stroke(255,  255, 255);
    TFTscreen.text(title, 5, 10);

    for (size_t i = 0; i < sizeof(MENUS[MENU_I]); i++)
    {
      char text[MENUS[MENU_I][i].length() + 1];

      MENUS[MENU_I][i].toCharArray(text, MENUS[MENU_I][i].length() + 1);

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

    char inputedChar = (char) X0;

    int i = isNonAscciKey(X0);
    if(NON_ASCCII_KEYS[i] == "left"){
      MENU_ACTIVE++;
      if(MENU_ACTIVE > sizeof(MENUS[MENU_I])){
        MENU_ACTIVE = 0;
      }
    }
  }
}

/*
 * DEFAULT METHODS ##################################################################################
 */
void setup() {
  Serial.begin(9600);
  Wire.begin();

  TFTscreen.begin();
  TFTscreen.setRotation(3);
  TFTscreen.background(0, 0, 0);
  initializeKeyboard();
}

void loop() {  
  keyboardRead();
  executionContext();
  delay(100);
}