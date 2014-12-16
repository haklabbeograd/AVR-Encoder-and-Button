AVR-Encoder-and-Button
======================

AVR code written to read the front buttons and encoder of the [SANGEAN WFR-1 Web Radio](http://www.sangean.com/products/product.asp?mid=23&gal=1). This is a support device for the [InternetOfSoundThings hklbg project](http://wiki.oosm.org/wiki/InternetOfSoundThings)

Arduino is put to sleep between keypresses or encoder movement, so power consumption is low. Upon a key press a string "Button: [button_name]\n" is sent over serial (9600B). uppon encoder CW movement "Encoder: ++\n" is sent, and "Encoder: --\n" for CCW movement.

The library should work with any matrix keyboard and encoder. Encoder is connected to D2 and D3 of Arduino.
By edtiting keypad.h and the char buttons[x][y][z] in keypad.c you can modify the keypad to work with your custom matrix



The code uses the arduino board, but the code is writen in AVR C for avr-gcc.
to compile:
avr-gcc.exe -Wall -mmcu=atmega328p -DF_CPU=16000000UL -Os -I"path_to_avr/include" -I"path_to_projcet_folder" -c keypad.c -o obj\Release\keypad.o
avr-gcc.exe -Wall -mmcu=atmega328p -DF_CPU=16000000UL -Os -I"path_to_avr/include" -I"path_to_projcet_folder" -c main.c -o obj\Release\main.o
avr-gcc.exe -Wall -mmcu=atmega328p -DF_CPU=16000000UL -Os -I"path_to_avr/include" -I"path_to_projcet_folder" -c usart.c -o obj\Release\usart.o
avr-g++.exe -L"path_to_avr/lib" -o bin\Release\EncoderAndButtons.elf obj\Release\keypad.o obj\Release\main.o obj\Release\usart.o  -mmcu=atmega328p

to upload to arduino:
avrdude.exe -C"path_to/avrdude.conf" -v -v -v -v -patmega328p -carduino -P[serial_port] -b57600 -D -Uflash:w:bin\Release\EncoderAndButtons.hex:i

[windows]replace [serial_port] with \\.\COM[x] where x is the COM number arduino is connected to
[linux]replace [serial_port] with  /dev/tty[x] where x is the serial port arduino is connected to
