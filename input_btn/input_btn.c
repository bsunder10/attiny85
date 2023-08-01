#define F_CPU 8000000UL     // 8MHz Internal Oscillator

#include <avr/io.h>
#include <util/delay.h>

#define IO_PORT PORTB

#define LED_PIN PB4
#define BTN_PIN PB3

#define GPIO_HIGH(port, pin)    port |= (1 << pin)
#define GPIO_LOW(port, pin)     port &= (~(1 << pin))

#define GPIO_READ(port, pin)    port & (1 << pin)


int main()
{
    // Configure Inputs
    DDRB &= (~(1 << DDB3));
    // PORTB |= (1 << BTN_PIN);

    // Configure Outputs
    DDRB |= (1 << LED_PIN);

    GPIO_HIGH(IO_PORT, LED_PIN);
    _delay_ms(1000);
    GPIO_LOW(IO_PORT, LED_PIN);
    _delay_ms(1000);

    while (1)
    {
        if (PINB & (1 << BTN_PIN))
        {
            GPIO_LOW(IO_PORT, LED_PIN);
        }
        else
        {
            GPIO_HIGH(IO_PORT, LED_PIN);
        }

        _delay_ms(100);
    }
    
}