//----------------------------------------------------------------------//
// Programmer: Leslie Ibarra    
// Date: 03/20/2020
// Course: UArizona - ECE 372a
// Assignment: LAB 3
//----------------------------------------------------------------------//

#include <avr/io.h>
#include "lcd.h"
#include "timer.h"


int main(){

/*
  // Initialze timer, LCD, and write Hello!
  initTimer1();
  initLCD();
  moveCursor(0, 4);
  writeString("Hello!\0");
*/

//------------------------------//
  // EXTRA CREDIT: 
  // Display on the 1st line "My name is:" followed by
  // Display on the 2nd line your firstname and initial
  initTimer1();
  initLCD();
  moveCursor(0,0);
  writeString("Hello world!\0");
  moveCursor(1,0);
  writeString("-Les\0");
//-------------------------------//
 
  while(1){
    //If we wanted to display some sort of data that is being read in by a sensor (i.e. temperature/humidity..)
    //it would go here.
  }

  return 0;
}
