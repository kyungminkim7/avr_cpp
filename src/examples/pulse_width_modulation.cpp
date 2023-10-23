/*
This program is an example of using hardware pulse width modulation.
*/
#include <avr/io.h>
#include <util/delay.h>

#include <avr_cpp/bit.h>
#include <avr_cpp/pulse_width_modulation.h>

using namespace avr_cpp;
using namespace Timer;

int main() {
    uint8_t dutyCycleA = 0;
    uint8_t dutyCycleB = 125;

    setBits(DDRD, PD6, PD5);

    PulseWidthModulation0_8 pwm(Channel::A | 
                                Channel::B);
    pwm.set(dutyCycleA, Channel::A);
    pwm.set(dutyCycleB, Channel::B);

    pwm.start();

    while (true) {
        pwm.set(dutyCycleA++, Channel::A);
        pwm.set(dutyCycleB++, Channel::B);
        _delay_ms(10);
    }

    return 0;
}