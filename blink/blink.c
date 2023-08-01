#define F_CPU 8000000UL     // 8MHz Internal Oscillator

#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTB
#define LED_PIN1 PB4
#define LED_PIN2 PB3

#define GPIO_HIGH(port, pin)    port |= (1 << pin)
#define GPIO_LOW(port, pin)     port &= (~(1 << pin))


int main()
{
    // Define the pin
    DDRB |= (1 << LED_PIN1) | (1 << LED_PIN2);

    while (1)
    {
        GPIO_HIGH(LED_PORT, LED_PIN1);
        GPIO_HIGH(LED_PORT, LED_PIN2);
        _delay_ms(500);
        GPIO_LOW(LED_PORT, LED_PIN1);
        GPIO_LOW(LED_PORT, LED_PIN2);
        _delay_ms(500);
    }
    
}