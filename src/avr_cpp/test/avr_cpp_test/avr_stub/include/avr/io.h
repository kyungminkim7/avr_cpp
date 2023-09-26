#pragma once

#include <array>
#include <stdint.h>

#include "sfr_defs.h"

// Digital I/O
extern volatile uint8_t DDRB;
#define DDB7 7
#define DDB6 6
#define DDB5 5
#define DDB4 4
#define DDB3 3
#define DDB2 2
#define DDB1 1
#define DDB0 0

extern volatile uint8_t PINB;
#define PINB7 7
#define PINB6 6
#define PINB5 5
#define PINB4 4
#define PINB3 3
#define PINB2 2
#define PINB1 1
#define PINB0 0

extern volatile uint8_t PORTB;
#define PB7 7
#define PB6 6
#define PB5 5
#define PB4 4
#define PB3 3
#define PB2 2
#define PB1 1
#define PB0 0

// Baud rate
extern volatile uint16_t UBRR0;

// USART
#define USBS0 3

#define TXEN0 3
#define RXEN0 4

#define RXC0 7

#define UDRE0 5

extern volatile uint8_t UDR0;

extern volatile uint8_t UCSR0A;
extern volatile uint8_t UCSR0B;
extern volatile uint8_t UCSR0C;

#define U2X0 1

#define UCSZ00 1
#define UCSZ01 2
#define UCSZ02 2

// Analog Digital Converter
extern volatile uint8_t ADCSRA;
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

extern volatile uint8_t ADMUX;
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

extern volatile uint16_t ADC;
extern volatile uint8_t &ADCH;
extern volatile uint8_t &ADCL;

// External interrupts
extern volatile uint8_t EIMSK;
#define INT1    1
#define INT0    0

extern volatile uint8_t EICRA;
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0
