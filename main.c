/*****************************************************
Chip type               : ATmega32
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>
#include <sleep.h>

int i=0;
bit g=0;

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
   PORTB.0=~PORTB.0;   
}

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
    PORTB.0=~PORTB.0;
    i++;
    if(i==5)
    {
        if(!g)
        {
             OCR1A++;
        }
        else
        {
             OCR1A--;
        }
        if(OCR1A==1000)
        {
             g=1;
        }
        if(OCR1A==1)
        {
             g=0;
        }
        i=0;
    }
}

void main(void)
{
PORTB=0x00;
DDRB=0x01;

PORTD=0x00;
DDRD=0x20;

// Timer/Counter 1 initialization
// Clock value: 7.813 kHz
// Mode: Fast PWM top=0x03FF
// Timer1 Overflow Interrupt: On
// Compare A Match Interrupt: On
TCCR1A=0xC3;
TCCR1B=0x09;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x3F;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x14;

// Global enable interrupts
#asm("sei")

sleep_enable();

while (1)
      {
         idle();
      }
}
