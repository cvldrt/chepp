#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>

typedef uint64_t bitboard;

void print_bitboard(bitboard b);

inline void set_bit(bitboard* board, char bit)
{
    *board |= 1ll << (63 - bit);
}

inline bool get_bit(bitboard board, char bit)
{
    return board & 1ll << (63 - bit);
}

inline void pop_bit(bitboard* board, char bit)
{
    *board &= ~(1ll << (63 - bit));
}

void fun();

#endif
