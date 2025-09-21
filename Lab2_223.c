/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"

int main(void)
{    
    /* insert your hardware initialization here */
    set(DDRB, DDB6); //PORT B6 as output
    clear(DDRF, DDF0); //PORT F0(Pin A5) as input
    set(PORTB, PORTB6); //set PORT B6 to 5v
    clear(PORTF, PF0); // no pull up resistor


    for(;;){
        /* insert your main loop code here */

        if (!(bit_is_set(PINF,0))) // normal room light
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

