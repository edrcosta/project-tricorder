const int clockPin = 7;    //74HC595 Pin 11
const int latchPin = 8;    //74HC595 Pin 12
const int dataPin = 12;    //74HC595 Pin 14
const int digitPins[4] = {5,4,3,2};

void setup(){               
  for(int i=0;i<4;i++)
  {
    pinMode(digitPins[i],OUTPUT);
    digitalWrite(digitPins[i], HIGH);
  }
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 
}


void loop() {
  for(int i=0;i<4;i++)
  {
    //select the digit by enabling the common cathode (sink)
    digitalWrite(digitPins[i], LOW);

    // write '0'
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 64);
    digitalWrite(latchPin, HIGH);
    delay(1000);
  }
}
