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
    clear(DDRC, DDC7); //PORT C7(Pin 13) as input
    set(PORTB, PORTB6); //set PORT B6 to 5v
    clear(TCCR3B, ICES3); //store falling edge
    TCCR3B |= (1<<CS32) | (1<<CS30);// turn on counter(prescale=1024)

    int tperiod = 0;
    int oldtime = 0;
    int round = 0;
    int SWITCH_STATUS = 0; //sign of switch is pressed or not
    float ms = 0;

    m_usb_init(); //open PuTTY terminal

    for(;;){
        /* insert your main loop code here */
        if (TCNT3 == 0x0000) //Timer3 overflows
        {
            round = round + 1;
        }


        if (!(bit_is_set(PINC, 7)) && SWITCH_STATUS == 0) // switch is pressed
        {
            set(PORTB, PORTB6); //set PORT B6 to 5v
            // TIFR3 |= (1 << ICF3); // clear flag
            if (ICR3 < oldtime)
            {
                tperiod = 65536 * round + ICR3 - oldtime;
                oldtime = ICR3;
                round = 0; // reset round to 0
            }
            else
            {
                tperiod = ICR3 - oldtime;
                oldtime = ICR3;
                round = 0; // reset round to 0
            }
            
            //mapping the timer number to ms
            ms = tperiod * 4200.0f / 65535.0f;
            SWITCH_STATUS = 1;
            m_usb_tx_string("Tperiod:");
            m_usb_tx_uint(ms);
            m_usb_tx_string("ms");
            m_usb_tx_string("\r\n");
        }
        else if((bit_is_set(PINC,7)) && SWITCH_STATUS == 1) //switch is released
        {
            clear(PORTB, PORTB6); //set PORT B6 to 5v
            SWITCH_STATUS = 0;
            m_usb_tx_string("Switch released");
             m_usb_tx_string("\r\n");
        }
        else if (SWITCH_STATUS == 0) //switch is pressed but not realeased and switch is not pressed
        {
            clear(PORTB, PORTB6); //set PORT B6 to 0v
        }
    }
    return 0;   /* never reached */
}
