#pragma once

#define _BV(bit) (1 << (bit))

#define bit_is_set(value, bit) (value & _BV(bit))

#define bit_is_clear(value, bit) (!(value & _BV(bit)))

#define loop_until_bit_is_set(value, bit) do { } while (bit_is_clear(value, bit))

#define loop_until_bit_is_clear(value, bit) do { } while (bit_is_set(value, bit))