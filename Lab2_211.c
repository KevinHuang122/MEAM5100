/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

int main(void)
{    
    /* insert your hardware initialization here */
    set(DDRB, DDB6); //PORT B6 as output
    clear(DDRF, DDF0); //PORT F0(Pin A5) as input
    set(PORTB, PORTB6); //set PORT B6 to 5v
    set(PORTF, PORTF0); // Pull up

    for(;;){
        /* insert your main loop code here */

        if (bit_is_set(PINF,0)) // switch is not pressed
        {
            clear(PORTB, PORTB6); //set PORT B6 to 0v
        }
        
        else
        {
            set(PORTB, PORTB6); //set PORT B6 to 5v
        }
    }
    return 0;   /* never reached */
}