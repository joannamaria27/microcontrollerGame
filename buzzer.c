#include <msp430x14x.h>

void delay_ms(unsigned int ms )
{
    unsigned int i;
    for (i = 0; i<= ms; i++)
       __delay_cycles(500); 
}
void delay_us(unsigned int us )
{
    unsigned int i;
    for (i = 0; i<= us/2; i++)
       __delay_cycles(1);
}
void beep(unsigned int note, unsigned int duration)
{
    int i;
    long delay = (long)(10000/note); 
    long time = (long)((duration*10)/(delay*2));  
    for (i=0;i<10*time;i++)
    {
	  	P4OUT ^= ~BIT3; 
		delay_us(100*delay);
    }
    delay_ms(20);
}
