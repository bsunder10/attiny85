#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main()
{
    // Set it to fast PWM mode
    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    TCCR0B &= (~(1 << WGM02));

    // Set PWM Mode
    TCCR0A |= (1 << COM0A1);
    TCCR0B &= ~(1 << COM0A0);

    // Set Prescaler
    TCCR0B &= (~(1 << CS00)) & (~(1 << CS02));
    TCCR0B |= (1 << CS01);

    // Define Pin as Output
    DDRB |= (1 << PB0);

    // Set Duty Cycle
    OCR0A = 128;
    
    uint8_t i;

    while (1)
    {
        for (i=0; i<252; i++)
        {
            OCR0A = i;
            _delay_ms(10);
        }

        for (i=252; i>0; i--)
        {
            OCR0A = i;
            _delay_ms(10);
        }
    }
    

    return 0;
}