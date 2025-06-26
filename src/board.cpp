#include "board.h"

#include <iostream>

#include "bitboard.h"
#include "enums.h"
#include "piece_masks.h"
#include "pieces/pawn.h"

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
    //print_bitboard(knight_attacks[e1]);
    //print_bitboard(rook_mask[e4]);
    //print_bitboard(pawn_attacks[white][e1]);
    //print_bitboard(bishop_mask[e4]);
    //print_bitboard(qween_mask[a1]);
    print_bitboard(king_attacks[a1]);
    print_bitboard(king_attacks[e4]);
    print_bitboard(king_attacks[d8]);
}
