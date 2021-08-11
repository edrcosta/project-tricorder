/**
 * This code will deal with plug and play devices and keyboard input
 * and them communicate with the atmega328p chipset 
 * */
#include <REGX52.h>

// almost 1 second delay
void delay()
{
    int i;
    for(i=0; i<1000; i++) {
        TMOD = 0x01;// Timer0 mode1
        TH0 = 0xFC;//initial value for 1ms
        TL0 = 0x66;
        TR0 = 1;// timer start
        while(TF0==0);  // check overflow condition
        TR0 = 0;// Stop Timer
        TF0 = 0;// Clear flag
    }
}

void main()
{
    // set all ports to 0
	P0=0x00;
	P1=0x00;
	P2=0x00;
	P3=0x00;

    while(1) {
        
        // P3_5 = 0; // clock
        // delay();
        // P2_0 = 1; //WAIT
        // P2_1 = 1; //BUSRQ
        // P2_2 = 1; //RESET

        // P3_7 = 1; // MMI
        // P3_6 = 1; // INT

        // P1_1 = 0; //D0
        // P1_0 = 0; //D1
        // P1_3 = 0; //D2
        // P3_3 = 0; //D3
        // P3_4 = 0; //D4
        // P3_2 = 0; //D5
        // P3_1 = 0; //D6
        // P1_2 = 0; //D7
        // delay();
        // P3_5 = 1; // clock
    }
 }