                                                                                                                                                           o//**************************************************************//
//  Name    : shiftIn Example 2.2                               //
//  Author  : Carlyn Maw                                        //
//  Date    : 25 Jan, 2007                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a CD4021B Shift Register       //
//          :                                                   //
//****************************************************************
#include "U8glib.h"


U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

//define where your pins are
int latchPin = 8;
int dataPin = 9;
int clockPin = 7;

//Define variables to hold the data 
//for each shift register.
//starting with non-zero numbers can help
//troubleshoot
byte switchVar1 = 72;  //01001000
byte switchVar2 = 159; //10011111

//define an array that corresponds to values for each 
//of the first shift register's pins
char note2sing[] = {
  'C', 'd', 'e', 'f', 'g', 'a', 'b', 'c'}; 

//define an array that has a place for the values of
//pins 1-7 (not 0) of the second shift register's
//pins. Not 0 because that will be used as a flag value
byte settingVal[] = {
  0, 0, 0, 0, 0, 0, 0};   

//a flag varible used to track whether the program
//is in a setting update mode or not
byte settingSwitch = 0;  

void setup() {

      // flip screen, if required
    // u8g.setRot180();
    
    // set SPI backup if required
    //u8g.setHardwareBackup(u8g_backup_avr_spi);

    // assign default color value
    if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
        u8g.setColorIndex(255);     // white
    }
    else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
        u8g.setColorIndex(3);         // max intensity
    }
    else if ( u8g.getMode() == U8G_MODE_BW ) {
        u8g.setColorIndex(1);         // pixel on
    }
    else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
        u8g.setHiColorByRGB(255,255,255);
    }
    
    pinMode(8, OUTPUT);
    
  //start serial
  Serial.begin(9600);

  //define pin modes
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, INPUT);

}

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 22, "Te amo Isabella <3");
}

void loop() {

  //Pulse the latch pin:
  //set it to 1 to collect parallel data
  digitalWrite(latchPin,1);
  //set it to 1 to collect parallel data, wait
  delayMicroseconds(20);
  //set it to 0 to transmit data serially  
  digitalWrite(latchPin,0);

  //while the shift register is in serial mode
  //collect each shift register into a byte
  //the register attached to the chip comes in first 
  switchVar1 = shiftIn(dataPin, clockPin);
  switchVar2 = shiftIn(dataPin, clockPin);

  //Print out the results.
  //leading 0's at the top of the byte 
  //(7, 6, 5, etc) will be dropped before 
  //the first pin that has a high input
  //reading  
  Serial.println(switchVar1, BIN);
  Serial.println(switchVar2, BIN);


  //This for-loop steps through the byte
  //bit by bit which holds the shift register data 
  //and if it was high (1) then it prints
  //the corresponding location in the array
  for (int n=0; n<=7; n++)
  {
    //so, when n is 3, it compares the bits
    //in switchVar1 and the binary number 00001000
    //which will only return true if there is a 
    //1 in that bit (ie that pin) from the shift
    //register.
    if (switchVar1 & (1 << n) ){
      //print the value of the array location
      Serial.println(note2sing[n]);
    }
  }

//This is a away to examine the whole
//byte at once and create combinations
//of settings.

//By passing the switchVar1 variable to
//a "switch" statement and comparing it against
//a set nemerical value (written in binary)
//you can create special cases

  switch (switchVar1) {
  case B00101010:
    Serial.println("D minor");
    break;
  case B00010101:
    Serial.println("C major");
    break;
  case B01010100:
    Serial.println("E minor");
    break;
  case B00101001:
    Serial.println("F major");
    break;    
  case B01010010:
    Serial.println("G major");
    break;        
  case B00100101:
    Serial.println("A minor");
    break;     
  case B01001010:
    Serial.println("B diminished");
    break;     
  default: 
    // if nothing else matches, do the default
    Serial.println("Play It, Joe"); 
  }


//--- SHIFT REGISTER 2
// This is a more complicated behavior


//If the switch attached to pin 7 is High
  if (switchVar2 & (1 << 7) ){
    //print"Check, Check" to let us know the settings are being updated"
    Serial.println("Check, Check");
    //set a flag variable to let the progam know the settings are being updated
    settingSwitch = 1;

    //While the switch attached to seven is high,
    //take the bottom 7 bits and load them into
    //an array for easy access later. 
    for (int v=6; v>=0; v--)
    {
      if (switchVar2 & (1 << v) ){
        settingVal[v] = 1;
      } 
      else {
        settingVal[v] = 0;
      }
    }
  }
  //if the switch is low
  else {
    //and if it was high the very last time it came through
    //this if statement (indicated by the settingSwitch variable still 
    //set to "1")
    if (settingSwitch) {
      //turn off the settingSwitch variable
      settingSwitch=0;

      //Print out the current settings
      Serial.println("___SETTINGS___");

      for (int s=0; s<=6; s++)
      {

      //Print out the setting names
      //this is being done as a case statement because
      //there weren't built in string arrays yet
      //in Arduino as of Feb. 2007
        switch (s) {
        case 0:
          Serial.print("Mute");
          break;
        case 1:
          Serial.print("Octave Shift");
          break;
        case 2:
          Serial.print("Delay");
          break;
        case 3:
          Serial.print("Reverb");
          break;    
        case 4:
          Serial.print("Vibrato");
          break;        
        case 5:
          Serial.print("Funkify");
          break;     
        case 6:
          Serial.print("Dampen");
          break;     
        default: 
          // if nothing else matches, do the default
          Serial.println("Not Defined"); 
        }

        //Print Status
        if (settingVal[s]) {
          Serial.print(" On");
          } 
        else {
          Serial.print(" Off") ;       
         }

         //white space
         Serial.println();

      }
    }
  }


//white space
Serial.println("-------------------");
//delay so all these print satements can keep up. 
delay(500);

}

//------------------------------------------------end main loop

////// ----------------------------------------shiftIn function
///// just needs the location of the data pin and the clock pin
///// it returns a byte with each bit in the byte corresponding
///// to a pin on the shift register. leftBit 7 = Pin 7 / Bit 0= Pin 0
byte shiftIn(int myDataPin, int myClockPin) { 
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);
//we will be holding the clock pin high 8 times (0,..,7) at the
//end of each time through the for loop

//at the begining of each loop when we set the clock low, it will
//be doing the necessary low to high drop to cause the shift
//register's DataPin to change state based on the value
//of the next bit in its serial information flow.
//The register transmits the information about the pins from pin 7 to pin 0
//so that is why our function counts down
  for (i=7; i>=0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(2);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;
      //set the bit to 0 no matter what
      myDataIn = myDataIn | (1 << i);
    }
    else {
      //turn it off -- only necessary for debuging
     //print statement since myDataIn starts as 0
      pinState = 0;
    }

    //Debuging print statements
    //Serial.print(pinState);
    //Serial.print("     ");
    //Serial.println (dataIn, BIN);

    digitalWrite(myClockPin, 1);

  }

   // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  //delay(50);

  //debuging print statements whitespace
  //Serial.println();
  //Serial.println(myDataIn, BIN);
  return myDataIn;
}
