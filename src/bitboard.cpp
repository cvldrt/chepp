#include "bitboard.h"

#include <iostream>

void print_bitboard(bitboard b)
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::cout << get_bit(b, row * 8 + col) << " ";
        }

        std::cout << '\n';
    }

    std::cout << b << '\n';
}
