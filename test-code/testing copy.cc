// DISPLAY ####################################################################
#include <TFT.h>  
#include <SPI.h>

// TFT DISPLAY
#define DISPLAY_RESET_INPUT 8
#define DISPLAY_CS_INPUT 10
#define DISPLAY_DS_INPUT 9
TFT TFTscreen = TFT(DISPLAY_CS_INPUT, DISPLAY_DS_INPUT, DISPLAY_RESET_INPUT);

// Rotary ####################################################################
// Rotary Encoder Inputs
#define ROTARY_ENCODERT_CLK_INPUT 2
#define ROTARY_ENCODERT_DT 3
#define ROTARY_ENCODERT_SW 4

// rotary encoder states
int ROTARY_COUNTER = 0;
int ROTARY_ENCODER_CURRENT_STATE_CLK;
int ROTARY_ENCODER_LAST_STATE_CLK;
int ROTARY_ENCODER_HAS_CHANGED = 0;

String ROTARY_ENCODER_DIRECTION ="";

unsigned long ROTARY_ENCODER_BUTTON_LAST_STATE = 0;

// JOYSTICK ####################################################################
/* Pins */
#define JOYSTICK_INPUT_X A1
#define JOYSTICK_INPUT_Y A0
#define JOYSTICK_INPUT_BUTTON A2

/* Joystick information */
int JOYSTICK_X = 0 ;
int JOYSTICK_Y = 0 ; 
int JOYSTICK_BUTTON = 0 ;
int JOYSTICK_PREVIOUS_X = 0;
int JOYSTICK_PREVIOUS_Y = 0;
int JOYSTICK_DIRECTION_HAS_CHANGED = 1;

/*
  Check rotary encoder current state
*/
void rotary_encoder_get_status(){
  ROTARY_ENCODER_CURRENT_STATE_CLK = digitalRead(ROTARY_ENCODERT_CLK_INPUT);

  // CHECK IF STATE CHANGE 
  if (ROTARY_ENCODER_CURRENT_STATE_CLK != ROTARY_ENCODER_LAST_STATE_CLK  && ROTARY_ENCODER_CURRENT_STATE_CLK == 1){    
    if (digitalRead(ROTARY_ENCODERT_DT) != ROTARY_ENCODER_CURRENT_STATE_CLK) {
      // DECREMENT
      ROTARY_COUNTER --;
      ROTARY_ENCODER_DIRECTION ="DEC";
    } else {
      // INCREMENT
      ROTARY_COUNTER ++;
      ROTARY_ENCODER_DIRECTION ="INC";
    }
    ROTARY_ENCODER_HAS_CHANGED = 1;
  }

  // STORE STATE
  ROTARY_ENCODER_LAST_STATE_CLK = ROTARY_ENCODER_CURRENT_STATE_CLK;

  // ROTARY ENCODER BUTTON CHECK
  if (digitalRead(ROTARY_ENCODERT_SW) == LOW) {
    if (millis() - ROTARY_ENCODER_BUTTON_LAST_STATE > 50) {
      Serial.println("Button pressed!");
    }
    ROTARY_ENCODER_BUTTON_LAST_STATE = millis();
  }
}

void joystick_get_status(){
    JOYSTICK_X = analogRead(JOYSTICK_INPUT_X);  
    JOYSTICK_Y = analogRead(JOYSTICK_INPUT_Y);  
    JOYSTICK_BUTTON = digitalRead(A2);

    if(JOYSTICK_DIRECTION_HAS_CHANGED == 1){
        JOYSTICK_PREVIOUS_X = JOYSTICK_X;
        JOYSTICK_PREVIOUS_Y = JOYSTICK_Y;
        JOYSTICK_DIRECTION_HAS_CHANGED = 0;
    }

    if(JOYSTICK_X > JOYSTICK_PREVIOUS_X){
        if (JOYSTICK_X - JOYSTICK_PREVIOUS_X > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }else{
        if (JOYSTICK_PREVIOUS_X - JOYSTICK_X > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }

    if(JOYSTICK_Y > JOYSTICK_PREVIOUS_Y){
        if (JOYSTICK_Y - JOYSTICK_PREVIOUS_Y > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }else{
        if (JOYSTICK_PREVIOUS_Y - JOYSTICK_Y > 5){
            JOYSTICK_DIRECTION_HAS_CHANGED = 1;
        }
    }
}

void setup() {
  Serial.begin(9600);

  // DISPLAY ########################################
  TFTscreen.begin();
  TFTscreen.setTextSize(1);
  TFTscreen.background(0, 0, 0);

  // ROTARY ########################################
  pinMode(ROTARY_ENCODERT_CLK_INPUT,INPUT);
  pinMode(ROTARY_ENCODERT_DT,INPUT);
  pinMode(ROTARY_ENCODERT_SW, INPUT_PULLUP);
  ROTARY_ENCODER_LAST_STATE_CLK = digitalRead(ROTARY_ENCODERT_CLK_INPUT);

  // JOYSTICK ########################################
  pinMode(JOYSTICK_INPUT_BUTTON, INPUT_PULLUP);
}

int UPDATE_SCREEEN_COUNT = 0;

void update_screen(){
    // TFTscreen.stroke(random(0, 255), random (0, 255), random (0, 255));
    // TFTscreen.text("Hello World", 2, 10);

    // TFTscreen.text("Hello World", 2, 30);

    // TFTscreen.text("Hello World", 2, 50);
}


void loop() {
    // joystick_get_status();
    // rotary_encoder_get_status();

    // // JOYSTICK DEBUG #################
    // if(JOYSTICK_DIRECTION_HAS_CHANGED){
    //     /*Joystick STATUS*/
    //     Serial.print(" X:");
    //     Serial.print(JOYSTICK_X, DEC);
    //     Serial.print(" Y:");
    //     Serial.print(JOYSTICK_Y, DEC);  
       
    //     Serial.print("\n");
    //     JOYSTICK_DIRECTION_HAS_CHANGED = 0;
    // }

    // if(JOYSTICK_BUTTON == 0){
    //     Serial.print(" B:");
    //     Serial.println(JOYSTICK_BUTTON);
    //     Serial.print("\n");
    // }
    
    // // DEBUG ENCODER
    // if(ROTARY_ENCODER_HAS_CHANGED == 1){
    //   Serial.print("Direction: ");
    //   Serial.print(ROTARY_ENCODER_DIRECTION);
    //   Serial.print(" | ROTARY_COUNTER: ");
    //   Serial.println(ROTARY_COUNTER);
    //   ROTARY_ENCODER_HAS_CHANGED = 0;
    // }



    if(UPDATE_SCREEEN_COUNT == 10){
      update_screen();
      UPDATE_SCREEEN_COUNT = 0
    }

    UPDATE_SCREEEN_COUNT++;

    delay(10);
}