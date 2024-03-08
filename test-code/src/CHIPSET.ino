#include <TFT.h>
#include <SPI.h>
#include <Wire.h>

// TFT
#define DISPLAY_RESET_INPUT 8
#define DISPLAY_CS_INPUT 10
#define DISPLAY_DS_INPUT 9

TFT TFTscreen = TFT(DISPLAY_CS_INPUT, DISPLAY_DS_INPUT, DISPLAY_RESET_INPUT);

// KEYBOARD
// Hexadecima address for the X0 internal register.
#define X_Axis_Register_X0 0x32
// Hexadecima address for the X1 internal register.
#define X_Axis_Register_X1 0x33
// Power Control Register
#define Power_Register 0x2D

int KEYBOARD_ADDRESS_I2C = 0x5F;
int PRESSED_KEY_X0, PRESSED_KEY_X1, X_out;
// Prevent screen to be update every clock cicle
int EDITOR_UPDATE_SCREEN_COUNTER = 0;

// keep track of MENU and current window
int MENU_SELECTED = 0;
int MENU_SELECTED_OPTION = "home_menu";
int MENU_SELECTED_OPTION_PREVIOUS = "";

// Keep track of single line char input buffer
char SINGLE_LINE_BUFFER[40] = "";
int SINGLE_LINE_X = 0;

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
void setCurrentWindow(char selected[]) {
    MENU_SELECTED_OPTION = selected;
    resetDisplay();
}

// ask for data to the i2c keyboard
void    () {
    Wire.beginTransmission(KEYBOARD_ADDRESS_I2C);
    Wire.write(X_Axis_Register_X0);
    Wire.write(X_Axis_Register_X1);
    Wire.endTransmission();
    Wire.requestFrom(KEYBOARD_ADDRESS_I2C, 2);

    if (Wire.available() <= 2) {
        PRESSED_KEY_X0 = Wire.read();
        PRESSED_KEY_X1 = Wire.read();
    }
}

// Read the keyboard registers to check for new inputs
bool readKeyboardEditor() {
    listemKeyboard();

    if(PRESSED_KEY_X0 <= 0){
        return false;
    }

    if (PRESSED_KEY_X0 == 13 && PRESSED_KEY_X1 == 255) {
        EDITOR_LINE_Y++;
        if (EDITOR_LINE_Y >= EDITOR_MAX_ROW_SIZE) {
            EDITOR_LINE_Y = 0;
        }
        EDITOR_LINE_X = 0;
        resetDisplay();
    } else {
        TEXT_OUTPUT[EDITOR_LINE_Y][EDITOR_LINE_X] = (char) PRESSED_KEY_X0;
        EDITOR_LINE_X++;
        if (EDITOR_LINE_X >= EDITOR_MAX_LINE_SIZE) {
            EDITOR_LINE_X = 0;
        }
        resetDisplay();
    }

    return true;
}

// Clear Display
void resetDisplay() {
    TFTscreen.background(0, 0, 0);
}

void setup() {
    Serial.begin(9600);
    TFTscreen.begin();
    TFTscreen.setRotation(3);
    delay(30);    
    // Enable measurement from keyboard
    Wire.begin();    
    Wire.beginTransmission(KEYBOARD_ADDRESS_I2C);
    Wire.write(Power_Register);
    Wire.write(8); // Bit D3 High for measuring enable (0000 1000)
    Wire.endTransmission();
    delay(50);
    resetDisplay();
}

bool isRenderCicle() {
    EDITOR_UPDATE_SCREEN_COUNTER++;
    if (EDITOR_UPDATE_SCREEN_COUNTER == 20) {
        EDITOR_UPDATE_SCREEN_COUNTER = 0;
        return true;
    }
    return false;
}

// Write text to the screen
void editorUpdateScreen() {
    TFTscreen.stroke(255, 255, 255);
    TFTscreen.setTextSize(1);
    for (int i = 0; i < EDITOR_MAX_ROW_SIZE; i++) {
        char LINE[16];
        TEXT_OUTPUT[i].toCharArray(LINE, 16);
        TFTscreen.text(LINE, 5, (i * 10) + 20);
    }
}

void showMenu(char TITLE[], String OPTIONS[], int MAX) {
    char LINE[20];
    OPTIONS[MENU_SELECTED].toCharArray(LINE, 16);

    if (isRenderCicle()) {
        TFTscreen.setTextSize(2);
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text(TITLE, 5, 10);
        TFTscreen.stroke(47, 86, 214);
        TFTscreen.text(LINE, 5, 60);
    }

    listemKeyboard();

    if (PRESSED_KEY_X0 == 0) {
        return;
    }

    int left = 183;
    int right = 180;

    if (PRESSED_KEY_X0 == left) {
        MENU_SELECTED++;
        MENU_SELECTED = MENU_SELECTED == MAX ? 0 : MENU_SELECTED;
        resetDisplay();
    } else if (PRESSED_KEY_X0 == right) {
        MENU_SELECTED--;
        MENU_SELECTED = MENU_SELECTED < 0 ? 0 : MENU_SELECTED;
        resetDisplay();
    }

    bool ENTER_PRESSED = PRESSED_KEY_X0 == 13 && PRESSED_KEY_X1 == 255;

    if (OPTIONS[MENU_SELECTED] == "EDITOR" && ENTER_PRESSED) {
        setCurrentWindow("editor_menu");
    }

    if (OPTIONS[MENU_SELECTED] == "CRIAR" && ENTER_PRESSED) {
        setCurrentWindow("editor_create_dialog");
    }
}

void showEditorCreateDialog() {
    listemKeyboard();

    if (PRESSED_KEY_X0 == 13 && PRESSED_KEY_X1 == 255) {
        setCurrentWindow("editor_new");
    } else if (PRESSED_KEY_X0 > 0) {
        SINGLE_LINE_BUFFER[SINGLE_LINE_X] = (char) PRESSED_KEY_X0;
        SINGLE_LINE_X++;
    }

    if (isRenderCicle()) {
        TFTscreen.setTextSize(2);
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("NOME ARQUIVO:", 5, 10);
        TFTscreen.text(SINGLE_LINE_BUFFER, 5, 50);
    }
}

void loop() {
    // Home screen
    if (MENU_SELECTED_OPTION == "home_menu") {
        showMenu("E OS - 1.0", MENU_OPTIONS, 2);
    }

    // EDITOR first screen
    if (MENU_SELECTED_OPTION == "editor_menu") {
        showMenu("Editor", EDITOR_MENU, 2);
    }

    // EDITOR create file dialog
    if (MENU_SELECTED_OPTION == "editor_create_dialog") {
        showEditorCreateDialog();
    }

    // Editor main screen write a new file
    if (MENU_SELECTED_OPTION == "editor_new") {
        editorUpdateScreen();
        readKeyboardEditor();
    }
    delay(10);
}