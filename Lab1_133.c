/* Name: MEAM5100_Lab1_133.c
 * Author: Kevin Huang
 * Copyright: Copyright 2025 Kevin Huang. Academic use permitted.
 * License: For academic use only. No redistribution without permission.
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

int main(void)
{    
    /* insert your hardware initialization here */
    set(DDRC, DDC6); //PORT C6 as output
    set(TCCR3B, WGM32);
    set(TCCR3A, WGM30); //Reset timer3 on 0x00FF(255)
    set(TCCR3A, COM3A1); //output compare (clear motion)
    TCCR3B |= (1 << CS31); // turn on counter (prescale=8)

    int brightness = 0;
    int dir = 1;

    for(;;){
        
        /* insert your main loop code here */
        OCR3A = brightness;
        brightness += dir;

        if (brightness == 0 || brightness == 255)
        {
            dir = -dir;
        }

        _delay_ms(15);		// wait
        // set_led(TOGGLE);	// switch the led state
        // _delay_ms(1000);		// wait
    }
    return 0;   /* never reached */
}
