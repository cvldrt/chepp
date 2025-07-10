#pragma once

#include <cstdint>

typedef uint64_t bitboard;

#define set_bit(bb, bit) (bb |= 1ll << (bit))
#define get_bit(bb, bit) (bb & 1ll << (bit))
#define pop_bit(bb, bit) (bb &= ~(1ll << (bit)))

void print_bitboard(bitboard b);

uint8_t count_bits(bitboard b);
