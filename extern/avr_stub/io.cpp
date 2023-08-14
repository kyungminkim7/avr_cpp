#include <avr/io.h>

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