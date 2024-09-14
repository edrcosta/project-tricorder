# Tricorder project

this is a simple handheld device, build for learning and fun capable of interfacing with i2c and spi modules.


the main ideia is to run a version of the [atbrain interpreter](https://github.com/edrcosta/terminal-brainfuck-interpreter) and use it to interface with i2c devices


**Uploading the code**

[atmega standalone docs](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoToBreadboard/)

# Hardware 



- 1x Atmega328p [(Datasheet)](https://www.alldatasheet.com/datasheet-pdf/view/241077/ATMEL/ATMEGA328P.html)
- SPI TFT 1.8 display [(ST7735)](https://www.makerhero.com/produto/display-lcd-tft-1-8-128x160/)
- i2c QWERTY keyboard module [(KardKB Docs)](https://github.com/m5stack/m5-docs/blob/master/docs/en/unit/cardkb.md)
