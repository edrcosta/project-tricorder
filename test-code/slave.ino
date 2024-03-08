int debug = 0;

// Rotary Encoder Inputs
#define CLK 5
#define DT 3
#define SW 4

// Joystick Inputs
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define BUTTON A2
 

// Rotary encoder values
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

// Joystick Values 
int X_VALUE = 0;
int Y_VALUE = 0;
int buttonCount = 0;
int buttonPressed = 0;

void setup() {
    // Rotary
    pinMode(CLK,INPUT);
    pinMode(DT,INPUT);
    pinMode(SW, INPUT_PULLUP);

    //joystick 
    pinMode(JOYSTICK_Y,INPUT); 
    pinMode(JOYSTICK_X,INPUT); 
    pinMode(BUTTON,INPUT); 

        Serial.begin(9600);
    if(debug == 1){
    }
  
    lastStateCLK = digitalRead(CLK);
}

void detectJoystick(){
  // put your main code here, to run repeatedly:
  X_VALUE = analogRead(JOYSTICK_X);
  Y_VALUE = analogRead(JOYSTICK_Y);

  if(debug == 1){
    Serial.print("X: ");
    Serial.print( map(X_VALUE, 0, 1023, 0, 255));
    Serial.print("Y: ");
    Serial.print( map(Y_VALUE, 0, 1023, 0, 255));
    Serial.print("   button   ");
    Serial.println();
  }

  if(digitalRead(BUTTON) == 0){
    buttonCount++;
  }

if(digitalRead(BUTTON) == 1){
    buttonCount = 0;
    buttonPressed = 0;
  }

  if(buttonCount == 10){
    buttonPressed = 1;
  }

  if(buttonCount > 12){
    buttonPressed = 0;
    buttonCount = 0;
  }
}
void detectRotary(){
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    if (digitalRead(DT) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
    } else {
      counter ++;
      currentDir ="CW";
    }
    if(debug == 1){
        Serial.print("Direction: ");
        Serial.print(currentDir);
        Serial.print(" | Counter: ");
        Serial.println(counter);
    }
    if(counter > 100){
        counter = 0;
    }
  }

  lastStateCLK = currentStateCLK;

  if (digitalRead(SW) == LOW) {
    if (millis() - lastButtonPress > 50) {
        if(debug == 1){
            Serial.println("Button pressed!");
        }
    }
    lastButtonPress = millis();
  }
}

void loop() {
    Serial.print("ROTARY: ");
    Serial.print(counter);
    Serial.print("   X: ");
    Serial.print( map(X_VALUE, 0, 1023, 0, 255));
    Serial.print("Y: ");
    Serial.print( map(Y_VALUE, 0, 1023, 0, 255));
    Serial.print("   button   ");
    Serial.println(buttonPressed);

    detectRotary();
    detectJoystick();
    delay(10);
}