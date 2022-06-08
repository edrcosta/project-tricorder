# project-tricorder

A modular 8bit handheld computer plataform to study eletronics. 
a crazy dream that slowly become reallity 

## Objective 

Build a modular handhelt 8 bit retro computer "with a power of an gameboy".

## the computer 


At this stage, im focusing on BIOS (basic input output), im currently writing a firmware for the atmega328p connected to the TFT display that will be capable of:

- Write text files into SD card with any extension.
- Read Text files from sd card.
- Browser sd card files 
- Execute simple instructions as a Terminal like "load file.txt" "edit file.txt"

After i have this i will implement a small IO program to input/output data using the second atmega328p... 

## Components 

- 2 Atmega 328p MCUs 
- TFT display ISP 
- KardB i2c qwerty keyboard


