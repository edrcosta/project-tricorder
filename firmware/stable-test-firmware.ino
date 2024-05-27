/**
 * This is a simple firmware that enable test the computer screen and keyboard
 * */
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

int KEYBOARD_ADDRESS_I2C = 0x5F;
int X0,X1,X_out;

// Prevent screen to be update every clock cicle
int EDITOR_UPDATE_SCREEN_COUNTER = 0;

// keep track of MENU and current window
int MENU_SELECTED = 0;
int MENU_SELECTED_OPTION = "home_menu";
int MENU_SELECTED_OPTION_PREVIOUS = "";

// Keep track of single line char input buffer
char SINGLE_LINE_BUFFER[40] = "";
int  SINGLE_LINE_X  = 0;

// Keep track of multiline char input buffer
int EDITOR_LINE_Y = 0;
int EDITOR_LINE_X = 0;
int EDITOR_MAX_ROW_SIZE = 10;
int EDITOR_MAX_LINE_SIZE = 16;

String TEXT_OUTPUT[10] = { 
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

// MENU DIALOGS 
String MENU_OPTIONS[2] = {
  "EDITOR",
  "EXECUTAR"
};

String EDITOR_MENU[2] = {
  "CRIAR",
  "ABRIR"
};

// change current window path
void setCurrentWindow(char selected[]){
  MENU_SELECTED_OPTION = selected;
  resetDisplay(); 
}

// ask for data to the i2c keyboard
void listemKeyboard(){
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

// Read the keyboard registers to check for new inputs
void readKeyboardEditor(){
  listemKeyboard();

  if(X0 > 0){
    if(X0 == 13 && X1 == 255){
      // ENTER PRESSED
      EDITOR_LINE_Y++;
      if(EDITOR_LINE_Y >= EDITOR_MAX_ROW_SIZE){
        EDITOR_LINE_Y = 0;
      }
      EDITOR_LINE_X = 0;
    }else{
      // Add char to buffer
      TEXT_OUTPUT[EDITOR_LINE_Y][EDITOR_LINE_X] = (char) X0;

      EDITOR_LINE_X++;
      if(EDITOR_LINE_X >= EDITOR_MAX_LINE_SIZE){
        EDITOR_LINE_X = 0;
        EDITOR_LINE_Y++;
        if(EDITOR_LINE_Y >= EDITOR_MAX_ROW_SIZE){
          EDITOR_LINE_Y = 0;
        }
      }
    }
  }
}

// enable i2c keyboard
void enableMeasurement(){
  // Enable measurement
  Wire.beginTransmission(KEYBOARD_ADDRESS_I2C);
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
  TFTscreen.setRotation(3);
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  resetDisplay();
  enableMeasurement();
  delay(100);
}

/*
  increment a screen update counter and each 10 iterations allow the rendering of one frame 
  keeping the entire system on 10 frames per second allowing processing in the other 9 clock cicles
  This way i can keep the screen updated without forcing the entire system down to the screen clock and 
  without speed up the screen to operate at the same system speed
*/
bool isRenderCicle(){
  EDITOR_UPDATE_SCREEN_COUNTER++;
  if(EDITOR_UPDATE_SCREEN_COUNTER == 20){
    EDITOR_UPDATE_SCREEN_COUNTER = 0;
    return true;
  }
  return false;
}

// Write text to the screen
void editorUpdateScreen(){
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(1);
    for(int i = 0;i < EDITOR_MAX_ROW_SIZE;i++){
      char LINE[16];
      TEXT_OUTPUT[i].toCharArray(LINE, 16);
      TFTscreen.text(LINE, 5, (i * 10) + 20);
    }
}

// Display a generic title
void showTitle(char TITLE[]){
  TFTscreen.setTextSize(2);
  TFTscreen.stroke(255,  255, 255);
  TFTscreen.text(TITLE, 5, 10);
}

// Display menu Options
void showMenuOptions(char TITLE[], String OPTIONS[], int MAX){
  char LINE[20];
  OPTIONS[MENU_SELECTED].toCharArray(LINE, 16); 

  if(isRenderCicle()){
    TFTscreen.setTextSize(2);
    TFTscreen.stroke(47,  86, 214);
    TFTscreen.text(LINE, 5, 60);
    showTitle(TITLE);
  }
  
  listemKeyboard();

  if(X0 > 0){
    int left = 183;
    int right = 180;

    if(X0 == left){
      MENU_SELECTED++;
      if(MENU_SELECTED == MAX){
        MENU_SELECTED = 0;
      }
      resetDisplay();
    }else if(X0 == right){
      MENU_SELECTED--;
      if(MENU_SELECTED < 0){
        MENU_SELECTED = 0;
      }
      resetDisplay();
    }

    if(X0 == 13 && X1 == 255){
      if(OPTIONS[MENU_SELECTED] == "EDITOR"){
        setCurrentWindow("editor_menu");
      }

      if(OPTIONS[MENU_SELECTED] == "CRIAR"){
        setCurrentWindow("editor_create_dialog");
      }
    }
  }
}

void showEditorCreateDialog(){
  listemKeyboard();  

  if(X0 == 13 && X1 == 255){
    setCurrentWindow("editor_new");
  } else if(X0 > 0){
    SINGLE_LINE_BUFFER[SINGLE_LINE_X] = (char) X0;
    SINGLE_LINE_X++;
  }

  if(isRenderCicle()){
    TFTscreen.setTextSize(2);
    TFTscreen.stroke(255,  255, 255);
    TFTscreen.text("NOME ARQUIVO:", 5, 10);
    TFTscreen.text(SINGLE_LINE_BUFFER, 5, 50);
  }
}

void loop() {
  if(MENU_SELECTED_OPTION == "home_menu"){
    showMenuOptions("E OS - 1.0", MENU_OPTIONS, 2);
  } else if(MENU_SELECTED_OPTION == "editor_menu"){
    showMenuOptions("Editor", EDITOR_MENU, 2);
  } else if(MENU_SELECTED_OPTION == "editor_create_dialog"){
    showEditorCreateDialog();
  } else if(MENU_SELECTED_OPTION == "editor_new"){
    editorUpdateScreen();
    readKeyboardEditor();
  }
  delay(10);
}