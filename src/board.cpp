#include "board.h"

#include <iostream>

#include "bitboard.h"
#include "enums.h"
#include "piece_masks.h"

void print_bitboard(bitboard b)
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::cout << get_bit(b, row * 8 + col) << " ";
        }

        std::cout << '\n';
    }

    std::cout << '\n';
}

Board::Board()
{
    bitboards[PLAYER::white].fill(0);
    bitboards[PLAYER::black].fill(0);
}

void Board::print()
{
    print_bitboard(pawn_attacks[black][a2]);
    print_bitboard(pawn_attacks[white][e4]);

}
