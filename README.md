# project-tricorder

A modular handheld computer. 

This project is more drived by "what i wanto study" now the objective is 

- How to do a "operating system like firmaware" 
  - how shared memory allocation space can work (plug and play for processing power)
- Can i use this to drive a z80? 
  - i wanto to create some kind of "plug and play instruction set" if has an device with z80 connected use it.
- Why screens broke so much lol
- 
For this porpose 

## Objective 

Build a hand terminal, that can use multiple components and processors

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

## Updates / Experiments

![image](https://user-images.githubusercontent.com/3594012/118572034-d3e47500-b755-11eb-8b06-7ed4595c64fc.png)

### Keyboard 

push button matrix 
![image](https://user-images.githubusercontent.com/3594012/118571406-553b0800-b754-11eb-9af5-ffc90810b4da.png)
![image](https://user-images.githubusercontent.com/3594012/118571421-5cfaac80-b754-11eb-88ae-4f1f8d5be271.png)

Keyboard Debug interface 

![image](https://user-images.githubusercontent.com/3594012/118571481-89162d80-b754-11eb-8d5a-9121adab3d9a.png)
