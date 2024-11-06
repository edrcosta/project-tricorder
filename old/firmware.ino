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

int I2C_ADDR_KEYBOARD = 0x5F;   // keyboard i2c address
int LASTPRESS, X0,X1;           // store keyboard values

int NON_ASCCII_CODE[8] = { 27, 9, 13, 8, 182, 181, 180, 183 }; // list of non asscci codes
String NON_ASCCII_KEYS[8] = { "esq", "tab", "enter", "deletar", "down", "up", "left", "right" }; // list of non ascci keys

// rendering control
int RENDER_CLOCK = 0; 
int RENDER_EACH_FRAMES = 50;

bool DEBUG = true;

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

        if(X0 != 0 && DEBUG && X0 > -1){
            LASTPRESS = X0;

            if(isNonAscciKey(X0) > 0){
                Serial.print(X0);
                Serial.print(" - ");
                Serial.print(NON_ASCCII_KEYS[isNonAscciKey(X0)]);
                Serial.print(" - ");
                Serial.print(X1);
                Serial.println("");
            }else {
                Serial.print((char) X0);
                Serial.print(" - ");
                Serial.print(X1);
                Serial.println("");
            }
        }
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

// rendering flags
bool CLEAR_SCREEN = true;       // when true the screen is cleaned
bool FRAME_HAS_CHANGED = true;  // when true the rendering will be allowed

int LIST_CONTROL_ACTIVE = 0;    // control the current active list item
int RENDER_CONTEXT = 0;         // control the current rendering context "swtich applications"

// constants
String MAIN_MENUS[3] = {"Editor", "Execute", "AtBrain Interpreter"};
int MAIN_MENUS_CONTEXT[3] = {1, 2, 3};


/** allow rendering each x frames */
bool renderAllowed(){
    RENDER_CLOCK++;
    if(RENDER_CLOCK == RENDER_EACH_FRAMES && !CLEAR_SCREEN){
        RENDER_CLOCK = 0;
        return true;
    }
    return false;
}

/** draw a second level text */
void drawSecondLevelTitle(char* title){
    TFTscreen.setTextSize(2);
    TFTscreen.stroke(47,  86, 214);
    TFTscreen.text(title, 5, 60);
}

/** draw a window title */
void drawWindowTitle(char* title){
    TFTscreen.setTextSize(2);
    TFTscreen.stroke(47,  86, 214);
    TFTscreen.text(title, 1, 60);
}

/** draw a list and controsl the behavior*/
void drawList(String* list){
    if(LASTPRESS != 0){
        Serial.println(LASTPRESS);
    }

    if(LASTPRESS == 182){
        LIST_CONTROL_ACTIVE++;
        FRAME_HAS_CHANGED = true;
    }

    if(LASTPRESS == 181){
        LIST_CONTROL_ACTIVE--;
        FRAME_HAS_CHANGED = true;
    }

    if(LASTPRESS == 13){
        RENDER_CONTEXT = MAIN_MENUS_CONTEXT[LIST_CONTROL_ACTIVE];
        CLEAR_SCREEN = true;
        FRAME_HAS_CHANGED = true;
    }

    if(!FRAME_HAS_CHANGED) return;

    for(int i = 0; i < sizeof(list); i++){
        TFTscreen.setTextSize(1);

        if(LIST_CONTROL_ACTIVE == i){
            TFTscreen.stroke(255,  255, 255);
        }else{
            TFTscreen.stroke(0,  255, 0);
        }

        Serial.println(list[i]);
        TFTscreen.text(list[i].c_str(), 1, (40 + (10 * i)));
    }
}

/*
* Default apps ##################################################################################
*/
void editorApp(){
    drawWindowTitle("Editor");
}

void executeApp(){
    drawWindowTitle("executer");
}

void atBrainInterpreterApp(){
    drawWindowTitle("interpreter");
}

/*
* MAIN methods ##################################################################################
*/

/** main rendering entrypoint loop method */
void renderLoop(){
    if(CLEAR_SCREEN){
        TFTscreen.background(0, 0, 0);        
        CLEAR_SCREEN = false;
    }

    if(!renderAllowed()) return;

    switch (RENDER_CONTEXT) {
        case 0:
            LIST_CONTROL_ACTIVE = 0;
            drawList(MAIN_MENUS);
            break;
        case 1:
            editorApp();
            break;
        case 2:
            executeApp();
            break;
        case 3:
            atBrainInterpreterApp();
            break;
    }

    FRAME_HAS_CHANGED = false;
    LASTPRESS = -1;
}

/** Run when the device initialize */
void setup() {
    Serial.begin(9600);
    Wire.begin();

    TFTscreen.begin();
    TFTscreen.setRotation(3);
    TFTscreen.background(0, 0, 0);

    initializeKeyboard();
}

/** Main loop */
void loop() {  
    keyboardRead();
    renderLoop();
}
