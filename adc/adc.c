#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

uint16_t adc_value = 0;


// int main()
// {
//     /* --------------------------------- ADC -------------------------------- */
//     // Enable the global Interrupt
//     sei();

//     // Set Reference to No AVCC
//     ADMUX &= (~(1 << REFS0)) & (~(1 << REFS1));
//     // Select Analog channel as PB4
//     ADMUX |= (1 << MUX1);
//     ADMUX &= (~(1 << MUX0)) | (~(1 << MUX2)) | (~(1 << MUX3));
//     // Adjust the data from lsb
//     ADMUX &= (~(1 << ADLAR));

//     // Enable the ADC & Interrupt
//     ADCSRA |= (1 << ADEN) | (1 << ADATE);

//     // Prescaler for adc
//     ADCSRA &= (~(1 << ADPS2));
//     ADCSRA |= (1 <<ADPS0) & (1 <<ADPS1);

//     // Start Conversion
//     ADCSRA |= (1 << ADSC);

//     /* --------------------------------- PWM -------------------------------- */
//     // Set it to fast PWM mode
//     TCCR0A |= (1 << WGM00) | (1 << WGM01);
//     TCCR0B &= (~(1 << WGM02));

//     // Set PWM Mode
//     TCCR0A |= (1 << COM0A1);
//     TCCR0B &= ~(1 << COM0A0);

//     // Set Prescaler
//     TCCR0B &= ~(1 << CS01);
//     TCCR0B |= (1 << CS00) | (1 << CS02);

//     // Define Pin as Output
//     DDRB |= (1 << PB0);

//     // Set Duty Cycle
//     OCR0A = 128;


//     while (1)
//     {
//         if (adc_value > 128)
//         {
//             OCR0A = 255;
//         }
//         else
//         {
//             OCR0A = 0;
//         }

//         _delay_ms(1000);
        
//     }
    

//     return 0;
// }


// ISR (ADC_vect)
// {
//     adc_value = ADC;
// }



void adc_init(void);
void pwm_init(void);
uint16_t adc_read(void);

int main()
{

    // Inti the ADC
    adc_init();
    pwm_init();

    // PWM Output
    DDRB |= (1 << PB0);

    while (1)
    {
        uint16_t adc_value = adc_read();

        uint8_t pwm_value = adc_value >> 2;

        OCR0A = pwm_value;

        _delay_ms(100);
    }
    

    return 0;
}


void adc_init(void)
{

    // Turn off analog reference and direction of data
    ADMUX &= (~(1 << REFS0)) & (~(1 << REFS1)) & (~(1 << ADLAR));

    
    // Enable the ADC
    ADCSRA |= (1 << ADEN);

    // Prescaler for ADC for 64
    ADCSRA &= (~(1 << ADPS0));
    ADCSRA |= (1 << ADPS1) | (1 << ADPS2);
}

uint16_t adc_read(void)
{
    // Selection for ADC Pin
    ADMUX |= (1 << MUX1);
    ADMUX &= (~(1 << MUX0)) | (~(1 << MUX2)) | (~(1 << MUX3));
    
    // Start Conversion
    ADCSRA |= (1 << ADSC);

    // Wait for Conversion
    while (ADCSRA & (1 << ADSC));

    // Return the 10 bit ADC Value
    return ADC;
}

void pwm_init(void)
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
}