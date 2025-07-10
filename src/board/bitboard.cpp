#include "board/bitboard.h"

#include <iostream>

void print_bitboard(bitboard bb)
{
    for (int row = 7; row >= 0; --row) {
        for (int col = 7; col >= 0; --col) {
            std::cout << (bool)get_bit(bb, row * 8 + col) << " ";
        }

        std::cout << '\n';
    }

    std::cout << bb << '\n';
}

uint8_t count_bits(bitboard bb){
    uint8_t count = 0;

    while (bb != 0) {
        ++count;
        bb &= bb - 1;
    }

    return count;
}
