# project-tricorder

A 8 bit computer based on atmega328p

## Objective 

Build a "multi core" computer based on atmega328p... i know the concept of a computer in a microcontroller is "crazy" because all problens in harward archteture about limited code memory and no external RAM... 

but i want this restrictions of hardware to improve my development skill set and have a lower eletronics skill requirement... 

the computer will have 1 or N atmegas internconecteds sharing a memmory map to work as a single computer... 

for this we will have a "esoteric language" based on brainfuck to allow the user a interface with the device. the language i callet At Brain will be a single char instruction language (without count parameters of course rs)... 


## the computer 

the main porpose of this project is learn... but the computer will be used as the name sugest as a tool for data analisys in hardware... and as a portable gameboy... 

## Hardware 

- 2.42' oled display 
- 4 atmegas328p 
- 5v & 3v power regulators 
- 9v recharchable baterry 
- querty keyboard 
- indicator led 
- wi fi module 
- bluetooth module
- 64 mb flash memory 

## hardware ports 

- code input port 
- vga port 
- SPI port 
- UART port 
- IC2 port 
- PWM port 
- audio p2 

## Project steps 

DONE - Test and learn how components work 
DOING - Build a brainfuck emulator 
TODO - Port brainfuck emulator to c++
TODO - Modify emulator brainfuck into At Brain to be "multicore" 
TODO - Port At Brain emulator to C++
TODO - Prototype v1 of computer
TODO - Build final version 
