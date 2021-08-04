# project-tricorder

A modular 8bit handheld computer plataform to study eletronics. 
a crazy dream that slowly become reallity 

## Objective 

Build a modular handhelt 8 bit retro computer "with a power of an gameboy".

## the computer 

![image](https://user-images.githubusercontent.com/3594012/128116066-58a8413d-4160-4418-8acc-8078fc7dd635.png)

## Related repositories 

atmega328p testing code: https://github.com/edrcosta/projects.arduino 
8051 testing code: https://github.com/edrcosta/8051-mcu-tests

## Reference 

If you wanto to do this computer you need to understand the following steps:

- LCD to Atmega328p https://circuitdigest.com/microcontroller-projects/graphical-lcd-interfacing-with-arduino
- How to upload code into atmea328p https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoToBreadboard

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
