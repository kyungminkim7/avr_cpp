#pragma once

#define ISR(vect) void isr##vect()

void sei();
void cli();