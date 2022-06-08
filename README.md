# project-tricorder

A modular 8bit handheld computer plataform to study eletronics. 
a crazy dream that slowly become reallity 

## Objective 

Build a modular handhelt 8 bit retro computer "with a power of an gameboy".

## the computer 

The current version its only a BIOS system to host z80 processors

the core: 1 atmega328p that host and run the BIOS system
display: TFT display
input: cardKb its a qwerty i2c keyboard module

## What i have learned

- Im using a i2c databus 
- i going to need a 8 bit databus if i wanto to be pratical with z80s and running CP/M
- be aware of the clock

## @todo

- I2c communication library to atmega328p
- 8 bit bus communication library to atmega328p (maybe use ports... assembly?)
- AVR DudEeeeeeeeeeeeeeee!!! 
- I2c on an 8051