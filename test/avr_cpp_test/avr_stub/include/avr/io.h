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

#define PC7 7
#define PC6 6
#define PC5 5
#define PC4 4
#define PC3 3
#define PC2 2
#define PC1 1
#define PC0 0

#define PD7 7
#define PD6 6
#define PD5 5
#define PD4 4
#define PD3 3
#define PD2 2
#define PD1 1
#define PD0 0

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

// Pin change interrupts
extern volatile uint8_t PCICR;
#define PCIE2   2
#define PCIE1   1
#define PCIE0   0

extern volatile uint8_t PCMSK0;
extern volatile uint8_t PCMSK1;
extern volatile uint8_t PCMSK2;

// Timers
extern volatile uint8_t OCR0A;
extern volatile uint8_t OCR0B;

extern volatile uint8_t TCCR0A;
#define COM0A1  7
#define COM0A0  6
#define COM0B1  5
#define COM0B0  4
#define WGM01   1
#define WGM00   0

extern volatile uint8_t TCCR0B;
#define FOC0A   7
#define FOC0B   6
#define WGM02   3
#define CS02    2
#define CS01    1
#define CS00    0

extern volatile uint16_t ICR1;
extern volatile uint16_t OCR1A;
extern volatile uint16_t OCR1B;

extern volatile uint8_t TIMSK1;
#define ICIE1   5
#define OCIE1B  2
#define OCIE1A  1
#define TOIE1   0

extern volatile uint16_t TCNT1;

extern volatile uint8_t TCCR1A;
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define WGM11   1
#define WGM10   0

extern volatile uint8_t TCCR1B;
#define ICNC1   7
#define ICES1   6
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

extern volatile uint8_t OCR2A;
extern volatile uint8_t OCR2B;

extern volatile uint8_t TCCR2A;
#define COM2A1  7
#define COM2A0  6
#define COM2B1  5
#define COM2B0  4
#define WGM21   1
#define WGM20   0

extern volatile uint8_t TCCR2B;
#define FOC2A   7
#define FOC2B   6
#define WGM22   3
#define CS22    2
#define CS21    1
#define CS20    0