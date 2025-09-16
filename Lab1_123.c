/* Name: MEAM5100_Lab1_123.c
 * Author: Kevin Huang
 * Copyright: Copyright 2025 Kevin Huang. Academic use permitted.
 * License: For academic use only. No redistribution without permission.
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file


int main(void)
{    
    /* insert your hardware initialization here */
    set(DDRB,DDB6); //PORTB6 as output
    set(PORTB,PORTB6); //set PORT B6 to 5v


    for(;;){
        
        /* insert your main loop code here */
        toggle(PORTB,PORTB6); //Reverse the PORT B6 voltage
        _delay_ms(1000);      // wait
    }
    return 0;   /* never reached */
}

