#include <avr/io.h>

#include <avr_cpp/digital_port.h>

using namespace avr_cpp;

int main() {
    auto a = new int(8);
    DigitalPort<uint8_t> port(&DDRB, &PORTB);
    port.configurePin(0, PinMode::Output);
    port.writePin(0, true);

    return 0;
}
