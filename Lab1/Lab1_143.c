/* Name: MEAM5100_Lab1_143.c
 * Author: Kevin Huang
 * Copyright: Copyright 2025 Kevin Huang. Academic use permitted.
 * License: For academic use only. No redistribution without permission.
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define FADE_IN_TIME 100 //unit:ms
#define FADE_OUT_TIME 400 //unit:ms
#define DELAY_TIME 10 //unit: ms
#define LOW_INTENSITY 50 //50%

int main(void)
{    
    /* insert your hardware initialization here */
    float brightness = 0.0;
    int dir = 1; // fade in/out sign
    int count = 1; //intensity sign
    int cir = 1; //circulation sign
    int counter = 0; // weak sign
    int FADE_IN_STEP = FADE_IN_TIME / DELAY_TIME;
    int FADE_OUT_STEP = FADE_OUT_TIME / DELAY_TIME;
    float  WEAKEN_STEP = 255.0f / 20.0f;
    float FADE_IN_BRIGHTNESS = 255.0f / FADE_IN_STEP;// numbers of step
    float LOW_FADE_IN_BRIGHTNESS = (LOW_INTENSITY / 100.0f) * 255 / FADE_IN_STEP;
    float LOW_FADE_OUT_BRIGHTNESS = (LOW_INTENSITY / 100.0f) * 255 / FADE_OUT_STEP;
    float FADE_OUT_BRIGHTNESS = 255.0f / FADE_OUT_STEP; //brightness of each step

    set(DDRC, DDC6); //PORT C6 as output
    set(TCCR3B, WGM32);
    set(TCCR3A, WGM30); //Reset timer3 on 0x00FF(255)
    set(TCCR3A, COM3A1); //output compare (clear motion)
    TCCR3B |= (1 << CS31); // turn on counter (prescale=8)

    for(;;){
        /* insert your main loop code here */


        OCR3A = (int)brightness;

        if (dir && count) //large intensity fade in 
        {
            if (brightness + FADE_IN_BRIGHTNESS > (255 - counter * WEAKEN_STEP))//exceed the maximum of timer
            {
                brightness = 255 - counter * WEAKEN_STEP;
                dir = 0;
                cir = 0;
                counter += 1;
            }
            else
            {
                brightness += FADE_IN_BRIGHTNESS;//increase the duty cycle
                _delay_ms(DELAY_TIME);		// wait
            }
        }      
        else if (!dir && !cir)// fade out
        {
            if (brightness - FADE_OUT_BRIGHTNESS < 0)//exceed the minimum of timer
            {
                brightness = 0;
                dir = 1;
                count = !count; //inverse
            }
            else
            {
                brightness -= FADE_OUT_BRIGHTNESS;//decrease the duty cycle
                _delay_ms(DELAY_TIME);		// wait
            }
        }
        else if (dir && !count)// low intensity fade in
        {
            if (brightness + LOW_FADE_IN_BRIGHTNESS > (LOW_INTENSITY/100.0f)*(255 - counter * WEAKEN_STEP))
            {
                brightness = (LOW_INTENSITY/100.0f)*(255 - counter * WEAKEN_STEP);
                dir = 0;
                cir = 1;
            }
            else
            {
                brightness += LOW_FADE_IN_BRIGHTNESS;
                _delay_ms(DELAY_TIME);		// wait
            }
        }
        else //low intensity fade out and wait more 2s
        {
            if (brightness - LOW_FADE_OUT_BRIGHTNESS < 0)//exceed the minimum of timer
            {
                brightness = 0;
                dir = 1;
                count = !count; //inverse
                FADE_IN_BRIGHTNESS = (255.0f - counter * WEAKEN_STEP)  / FADE_IN_STEP;
                LOW_FADE_IN_BRIGHTNESS = (LOW_INTENSITY / 100.0f) *(255 - counter * WEAKEN_STEP) / FADE_IN_STEP;
                LOW_FADE_OUT_BRIGHTNESS = (LOW_INTENSITY / 100.0f) *(255 - counter * WEAKEN_STEP) / FADE_OUT_STEP;
                FADE_OUT_BRIGHTNESS = (255.0f - counter * WEAKEN_STEP) / FADE_OUT_STEP; //upgrade
                _delay_ms(2000);		// wait
            }
            else
            {
                brightness -= LOW_FADE_OUT_BRIGHTNESS;//decrease the duty cycle
                _delay_ms(DELAY_TIME);		// wait
            }
        }
    }
    return 0;   /* never reached */
}

