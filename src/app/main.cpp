#include <avr/io.h>

#include <avr_cpp/digital_port.h>

using namespace avr_cpp;

int main() {
    auto a = new int(8);
    DigitalPinBank<uint8_t> port(&DDRB, &PORTB);
    port.configureOutputPins(0);
    port.writePin(0, true);

    return 0;
}
