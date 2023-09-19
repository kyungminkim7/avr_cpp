#include <avr/io.h>

#include <etl/endianness.h>

// Digital I/O
volatile uint8_t DDRB = 0;
volatile uint8_t PINB = 0;
volatile uint8_t PORTB = 0;

// Baud rate
volatile uint16_t UBRR0 = 0;

// USART
volatile uint8_t UDR0 = 0;

volatile uint8_t UCSR0A = 0;
volatile uint8_t UCSR0B = 0;
volatile uint8_t UCSR0C = 0;

// Analog Digital Converter
volatile uint8_t ADCSRA = 0;
volatile uint8_t ADMUX = 0;

volatile uint16_t ADC = 0;

volatile uint8_t &ADCH = *(reinterpret_cast<volatile uint8_t *>(&ADC) + 
    (etl::endian::native == etl::endian::little ? 1 : 0));

volatile uint8_t &ADCL = *(reinterpret_cast<volatile uint8_t *>(&ADC) + 
    (etl::endian::native == etl::endian::little ? 0 : 1));
