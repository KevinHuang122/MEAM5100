/* Name: MEAM5100_Lab1_131.c
 * Author: Kevin Huang
 * Copyright: Copyright 2025 Kevin Huang. Academic use permitted.
 * License: For academic use only. No redistribution without permission.
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file


int main(void)
{    
    /* insert your hardware initialization here */
    _clockdivide(0);//set the clock speed to 16Mhz
    set(DDRC,DDC6);//PORT c6 as output
    TCCR3B |= (1<<WGM33)|(1<< WGM32);
    set(TCCR3A,WGM31); //Reset timer3 on mode 14(up to ICR3)
    ICR3 = 867;
    TCCR3B |= (1<<cS32) | (1<<cs30);// turn on counter(prescale=1024)


    for(;;){
        
        /* insert your main loop code here */
        if(TCNT3 == 0)
        {
            toggle(PORTC, PORTC6); //change the voltage status when the number is 0
        }
    }
    return 0;   /* never reached */
}

