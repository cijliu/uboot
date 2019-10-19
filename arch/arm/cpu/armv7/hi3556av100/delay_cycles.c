
void delay_cycles(unsigned int num)
{
    volatile unsigned int i;

    for (i = 0; i < (100 * num); i++) {
        __asm__ __volatile__("nop");
    }
}

