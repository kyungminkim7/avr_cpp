#pragma once

namespace avr_cpp {
namespace Usart {

enum class DataSize { FiveBits, SixBits, SevenBits, EightBits, NineBits };
enum class NumStopBits { One, Two };

constexpr auto DEFAULT_SYSTEM_CLOCK_FREQ = F_CPU;
constexpr auto DEFAULT_BAUD_TOLERANCE_PERCENT = 2u;

} // namespace Usart
} // namespace avr_cpp