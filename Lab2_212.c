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
    set(PORTF, PORTF0); // Pull up
    TCCR3B |= (1<<CS32) | (1<<CS30);// turn on counter(prescale=1024)

    m_usb_init(); //open PuTTY terminal
    int SWITCH_STATUS = 0; //sign of switch is pressed or not

    for(;;){
        /* insert your main loop code here */

        if (!(bit_is_set(PINF,0)) && SWITCH_STATUS == 0) // switch is pressed
        {
            set(PORTB, PORTB6); //set PORT B6 to 5v
            SWITCH_STATUS = 1;
            m_usb_tx_string("Switch pressed");
            m_usb_tx_uint(TCNT3);
            m_usb_tx_string("\r\n");
        }
        
        else if((bit_is_set(PINF,0)) && SWITCH_STATUS == 1) //switch is released
        {
            clear(PORTB, PORTB6); //set PORT B6 to 0v
            SWITCH_STATUS = 0;
            m_usb_tx_string("Switch released");
            m_usb_tx_uint(TCNT3);
             m_usb_tx_string("\r\n");
        }

        else
        {
            clear(PORTB, PORTB6); //set PORT B6 to 0v
        }
    }
    return 0;   /* never reached */
}
