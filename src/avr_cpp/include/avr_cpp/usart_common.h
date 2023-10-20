#pragma once

namespace avr_cpp {
namespace Usart {

enum class DataSize { FiveBits, SixBits, SevenBits, EightBits, NineBits };
enum class NumStopBits { One, Two };

} // namespace Usart
} // namespace avr_cpp