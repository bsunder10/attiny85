#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PORT PORTB
#define LED_PIN PB4

#define INT_BTN PB2

#define GPIO_HIGH(port, pin) port |= (1 << pin)
#define GPIO_LOW(port, pin)  port &= (~(1 << pin))

uint8_t led_state = 0;

int main()
{
    // Configuring the Outputs
    DDRB |= (1 << LED_PIN);

    // Configuring the Interrupt
    sei();                  // Enabling global interrupt
    GIMSK |= (1 << INT0);    // Enabling the Interrupt for INT0
    MCUCR |= (1 << ISC00) & (~(1 << ISC01));    // Any Edge Intr
    // MCUCR |= 0x00000001;

    while (1)
    {
        
    }
    
    return 0;
}

ISR(INT0_vect)
{
    if (led_state)
    {
        GPIO_HIGH(LED_PORT, LED_PIN);
        led_state = 0;
    }
    else
    {
        GPIO_LOW(LED_PORT, LED_PIN);
        led_state = 1;
    }
}