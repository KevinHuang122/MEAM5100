/* Name: MEAM5100_Lab2_214EC.c
 * Author: Kevin Huang
 * Copyright: Copyright 2025 Kevin Huang. Academic use permitted.
 * License: For academic use only. No redistribution without permission.
 */

#define INPUT 1
#define INPUT_PULLUP 2
#define OUTPUT 3

#define pinMode(register, bit, mode)
        if (mode == INPUT)
        {
            clear(DDR##register, bit);
            clear(PORT##register, bit);
        }
        else if (mode == INPUT_PULLUP)
        {
            clear(DDR##register, bit);
            set(PORT##register, bit); // pull up
        }
        else if (mode == OUTPUT)
        {
            set(DDR##register, bit); //output
        }
    

int main(void)
{
    return 0;
} 