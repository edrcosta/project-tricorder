# project-tricorder

A modular 8bit handheld computer plataform to study eletronics. 

## Objective 

Build a hand terminal, that can use multiple components and processors

## the computer 

the main porpose of this project is learn... but the computer will be used as the name sugest as a tool for data analisys in hardware... and as a portable gameboy... 

the current version use an atmega as display output, an 8051 as central command unit and an attiny85 to generate audio.

![image](https://user-images.githubusercontent.com/3594012/120138173-59cbdb80-c1ac-11eb-972d-1aee753b2ce7.png)

## Project steps 

#### Hardware to study 

- OK - 2.42' oled display 
- OK - atmegas328p 
- OK - 3v power regulators 
- Kind of ok - 9v recharchable baterry 
- OK - querty keyboard 
- OK - indicator led 
- OK - wi fi module 
- OK - bluetooth module
- TODO - 64 mb flash memory 


#### hardware ports to study 

- OK - code input ports
-- OK - vga port 
- OK - SPI port 
- OK - UART port 
- OK - I2C port 
- OK - PWM port 

#### Tasks

1. DONE - Test and learn how components work 
2. DONE - KEYBOARD 
3. EMULATION 
  - Almost done - Build a brainfuck emulator  (https://github.com/edrcosta/terminal-brainfuck-interpreter)
  - Done - Modify emulator brainfuck into At Brain to be "multicore" 
  - TODO - Build brainfuck emulator to c++
4. TODO - OPERATING SYSTEM 
   - TODO - Port At Brain emulator to C++  
5. TODO - Prototype v1 of computer
6. TODO - Build final version 
