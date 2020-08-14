//----------------------------------------------------------------------//
// Programmer: Leslie Ibarra    
// Date: 03/20/2020
// Course: UArizona - ECE 372a
// Assignment: LAB 3
//----------------------------------------------------------------------//

#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

void initLCD();
void initLCDPins();
void initLCDProcedure();
void sendCommand();
void writeString(const char *string);
void writeCharacter(unsigned char character);
void moveCursor(unsigned char x, unsigned char y);
void fourBitCommandWithDelay(unsigned char data, unsigned int delay);
void eightBitCommandWithDelay(unsigned char command, unsigned int delay);

#endif
