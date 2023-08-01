#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB |= _BV(PB4);

    while (1)
    {
        PORTB |= _BV(PB4);
        _delay_ms(2000);
        PORTB &= ~(_BV(PB4));
        _delay_ms(2000);
    }

    return 0;
}