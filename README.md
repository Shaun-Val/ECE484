# ECE484 - Chip Interfacing

This file explains the Blue.c and Blue.h files. Blue.c is the file that will turn on an LED when a 1 is transmitted via bluethooth. 

### Pre-reqs:
* AVR ATmega microcontroller/ Arduino Uno
* HC-05 Module
* Android Phone with Bluetooth Terminal
* LED

### Functions: 
 * led - Sets up the LED as an output 
 * receiver - Reads in characters from bluetooth termianl  
 * transmit - Send characters back to the bluetooth terminal

### Compile Command:
The 3 commands below are to be ran in the terminal within the same directory of your compile files. When on PC replace /dev/cu.usbmodem1101 with the COM port number. 
(Note in the the command Blue should be replaced with your .c file name)
* /dev/cu.usbmodem1101: is only used for mac 
* COM4: is only used for PC

## 

avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -B 9600 -Os -o Blue.o Blue.c    
avr-objcopy -O ihex -R .eeprom Blue.o Blue.hex
avrdude -F -V -c arduino -p ATMEGA328P -P  /dev/cu.usbmodem1101 -b 115200 -U flash:w:Blue.hex
