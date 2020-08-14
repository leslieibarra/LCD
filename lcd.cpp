//----------------------------------------------------------------------//
// Programmer: Leslie Ibarra    
// Date: 03/20/2020
// Course: UArizona - ECE 372a
// Assignment: LAB 3
//----------------------------------------------------------------------//

#include "lcd.h"
#include "timer.h"
#include <util/delay.h>


void initLCDPins(){

  //Initializing pins as outputs
  DDRA |= ((1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3));
  //Initializing Enable pin and RS pin
  DDRB |= ((1 << DDB4) | (1 << DDB6));

}

/* 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *      a. data is an unsigned char which has 8 bits. Therefore, you
 *         need assign the bottom 4 bits of "data" to the appropriate bits in
 *         PORTA
 *  2. This is a "command" signal, meaning RS should be Low
 *  3. Assert high on enable pin, delay, and assert low on enable pin
 *  4. delay the provided number in MICROseconds.
 */
void fourBitCommandWithDelay(unsigned char data, unsigned int delay){

  PORTA = data; //Bit mask PORTA with bottom 4 bits of data
  
  PORTB &= ~(1 << PORTB6);  //Setting RS to low
  PORTB |= (1 << PORTB4);   //Setting Enable pin high
  
  delayUs(1);     //Delay 1us
  PORTB &= ~(1 << PORTB4);  //Setting Enable pin low
  delayUs(delay); //Delay specified amount

}

/* Similar to fourBitCommandWithDelay except that now all eight bits of command are
 * sent.
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 *       a. unlike fourBitCommandWithDelay, you need to send the TOP four bits of
 *          "command" first. These should be assigned to appropriate bits in PORTA
 * 2. This is a command signal, meaning RS should be low
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of command to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay the provided number in MICROseconds.
 */
void eightBitCommandWithDelay(unsigned char command, unsigned int delay){
 
  PORTA = (command >> 4); //Bit mask PORTA with top four bits of command
  
  PORTB &= ~(1 << PORTB6);  //Setting RS to low
  PORTB |= (1 << PORTB4);   //Setting Enable pin high
  
  delayUs(1); //Delay 1us
  PORTB &= ~(1 << PORTB4);  //Setting Enable pin low
  delayUs(1); //Delay 1us

  PORTA = (command);  //Bit mask PORTA with bottom four bits of command
  
  PORTB &= ~(1 << PORTB6);  //Setting RS to low
  PORTB |= (1 << PORTB4);   //Setting Enable pin high
  
  delayUs(1); //Delay 1us
  PORTB &= ~(1 << PORTB4);  //Setting Enable pin low
  delayUs(delay); //Delay specified amount

}

/* Similar to eightBitCommandWithDelay except that now RS should be high
 * 1. Assert bits to pins connected to DB[7:4] on the LCD screen
 * 2. This is a "data" signal, meaning RS should be high
 * 3. Assert high on enable pin, delay, and asset low on enable pin
 * 4. Now set the lower four bits of character to appropriate bits in PORTA
 * 5. Assert high on enable pin, delay, and asset low on enable pin
 * 6. delay is always 46 MICROseconds for a character write
 */
void writeCharacter(unsigned char character){
  
  PORTA = (character >> 4);   //Bit mask PORTA with top four bits of character

  PORTB |= (1 << PORTB6);     //Setting RS to high
  PORTB |= (1 << PORTB4);     //Setting Enable pin high

  delayUs(1); //Delay 1us
  PORTB &= ~(1 << PORTB4);  //Setting Enable pin low
  delayUs(1); //Delay 1us
  PORTA = (character);    //Bit mask PORTA with lower four bits of character
  PORTB |= (1 << PORTB4);     //Setting Enable pin high
  delayUs(1); //Delay 1us
  PORTB &= ~(1 << PORTB4);    //Setting Enable pin low
  delayUs(46);

}

/*
 * Writes a provided string such as "Hello!" to the LCD screen. You should
 * remember that a c string always ends with the '\0' character and
 * that this should just call writeCharacter multiple times.
 */
void writeString(const char *string){
  while(*string != '\0') {
    writeCharacter(*string);
    string++;
  }
}

/*
 * This moves the LCD cursor to a specific place on the screen.
 * This can be done using the eightBitCommandWithDelay with correct arguments
 */
void moveCursor(unsigned char x, unsigned char y){

  
  eightBitCommandWithDelay(0x80 | (x << 6) | (y), 53);
  // this line of code: DDRAM = 0x80 | x<<6| y
  // takes 0x80 = 10000000 | with x shifted over (01000000) if on second line | whatever y is (0 - 15)  
  // (see data sheet for more detail)
}
/* This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void initLCDProcedure(){
  
  delayUs(15000);   //Delay 15ms
  
  fourBitCommandWithDelay(0b0011, 4100);  //Write 0b0011 to DB[7:4] and delay 4100us
  fourBitCommandWithDelay(0b0011, 100);   //Write 0b0011 to DB[7:4] and delay 100 ms

  fourBitCommandWithDelay(0b0011, 100);   //Write 0b0011 to DB[7:4] and delay 100us 
  fourBitCommandWithDelay(0b0010, 100);   //Write 0b0010 to DB[7:4] and delay 100us
  eightBitCommandWithDelay(0b00101000, 53);   //Function set in the command table with 53us delay
  eightBitCommandWithDelay(0b00001000, 53);   //Display off in the command table with 53us delay
  eightBitCommandWithDelay(0b00000001, 3000); //Clear display in the command table. Remember the delay is longer!!!
  eightBitCommandWithDelay(0b00000110, 53);   //Entry Mode Set in the command table.
  
  eightBitCommandWithDelay(0b00001100, 53);   //Display ON/OFF Control in the command table.

}

/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void initLCD(){
  initLCDPins();
  initLCDProcedure();
}
