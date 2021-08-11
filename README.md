# project-tricorder

A modular 8bit handheld computer plataform to study eletronics. 
a crazy dream that slowly become reallity 

## Objective 

Build a modular handhelt 8 bit retro computer "with a power of an gameboy".

## the computer 

### Architecture

There will be 4 components at this computer a z80a processor, a atmega328p as chip set capable of SPI video output and bootloading, a atmega328p to be a sound generator IC, and a AT89S51 (8051) as a north bridge to control data flow into and out of the z80a processor... and another 8051 to control a plug and play expansion port 

At firt i will attempt to create an basic BIOS program to load assembly code direct into the z80... that will be stored into the atmega328p (chipset)... and a simple firmware into both of the 8051 to comunicate and receive commands from the chipset... 

### Components 

1. 2x - Atmega328p 
2. 2x - 8051 
3. 1x - z80a

Schematics (in progress): 

![image](https://user-images.githubusercontent.com/3594012/128116066-58a8413d-4160-4418-8acc-8078fc7dd635.png)

Block diagram: 

![image](https://user-images.githubusercontent.com/3594012/128116848-bf59ea1c-448e-4fd6-adf5-2a03c9dc9903.png)

https://en.wikipedia.org/wiki/Southbridge_(computing)
https://en.wikipedia.org/wiki/Northbridge_(computing)
https://en.wikipedia.org/wiki/Chipset
https://en.wikipedia.org/wiki/BIOS

## Related repositories 

atmega328p testing code: https://github.com/edrcosta/projects.arduino 
8051 testing code: https://github.com/edrcosta/8051-mcu-tests
