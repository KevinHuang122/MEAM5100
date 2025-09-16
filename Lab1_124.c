/* Name: MEAM5100_Lab1_124.c
 * Author: Kevin Huang
 * Copyright: Copyright 2025 Kevin Huang. Academic use permitted.
 * License: For academic use only. No redistribution without permission.
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define DUTYCYCLE 80
#define PERIOD_MS 10

int main(void)
{    
    /* insert your hardware initialization here */
    set(DDRB,DDB6); //PORT B6 as output
    float high = PERIOD_MS * DUTYCYCLE / 100.0f; //high voltage time
    float low = PERIOD_MS - high; // low voltage time

    for(;;){
        
        /* insert your main loop code here */
        set(PORTB,PORTB6); // set PORT B6 to 5v
        _delay_ms(high);      // wait
        clear(PORTB,PORTB6); //set PORT B6 to 0v
        _delay_ms(low); //wait
    }
    return 0;   /* never reached */
}

