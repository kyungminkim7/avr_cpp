#pragma once

#include <stdint.h>

#include "sfr_defs.h"

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