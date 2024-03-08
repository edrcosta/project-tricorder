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
char TEXT_BUFFER[40] = "";
int TEXT_POINTER = 0;


// ask for data to the i2c keyboard
void listemKeyboard() {
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
}


void loop() {
    listemKeyboard();
    if (PRESSED_KEY_X0 > 0) {
        TEXT_BUFFER[TEXT_POINTER] = (char) PRESSED_KEY_X0;
        TEXT_POINTER++;
    }


    // Serial.println(PRESSED_KEY_X0);
    // Serial.println(PRESSED_KEY_X1);
    // Serial.println(X_out);
    Serial.println( TEXT_BUFFER);
    
    delay(100);
}