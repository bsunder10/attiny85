#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>


#define EEPROM_ADDRESS 0x00

uint8_t read_data(uint8_t address)
{
    return eeprom_read_byte((uint8_t *)address);
}

void write_data(uint8_t address, uint8_t data)
{
    eeprom_write_byte((uint8_t *)address, data);
}


int main(void)
{
    // Set Pin as Output
    DDRB |= (1 << PB0);

    write_data(EEPROM_ADDRESS, 1);
    uint8_t value = read_data(EEPROM_ADDRESS);

    if (value)
    {
        PORTB &= (~(1 << PB0));
    }
    else
    {
        PORTB |= (1 << PB0);
    }



    return 0;
}