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

// External interrupts
volatile uint8_t EIMSK = 0;
volatile uint8_t EICRA = 0;

// Pin change interrupts
volatile uint8_t PCICR = 0;
volatile uint8_t PCMSK0 = 0;
volatile uint8_t PCMSK1 = 0;
volatile uint8_t PCMSK2 = 0;

// Timers
volatile uint8_t OCR0A = 0;
volatile uint8_t OCR0B = 0;
volatile uint8_t TCCR0A = 0;
volatile uint8_t TCCR0B = 0;

volatile uint16_t ICR1 = 0;
volatile uint16_t OCR1A = 0;
volatile uint16_t OCR1B = 0;
volatile uint8_t TIMSK1 = 0;
volatile uint16_t TCNT1 = 0;
volatile uint8_t TCCR1A = 0;
volatile uint8_t TCCR1B = 0;

volatile uint8_t OCR2A = 0;
volatile uint8_t OCR2B = 0;
volatile uint8_t TCCR2A = 0;
volatile uint8_t TCCR2B = 0;