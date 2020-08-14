//----------------------------------------------------------------------//
// Programmer: Leslie Ibarra    
// Date: 03/20/2020
// Course: UArizona - ECE 372a
// Assignment: LAB 3
//----------------------------------------------------------------------//

#include "timer.h"


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){

    //Setting timer 1 into CTC mode
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);

    //Start the clock with prescaler 8 and OCR1A = 2
    TCCR1B &= ~((1 << CS12) | (1 << CS10));
    TCCR1B |= (1 << CS11);
    OCR1A = 2;
  
}

/* This delays the program an amount specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    unsigned int count = 0;

    TIFR1 |= (1 << OCF1A);

    TCNT1 = 0;

    while (count < delay) {
        if(TIFR1 &(1 << OCF1A)) {
            count++;
            TIFR1 |= (1 << OCF1A);
        }
    }
}
