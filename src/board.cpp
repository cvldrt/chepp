#include "board.h"

#include <iostream>

#include "enums.h"

inline void set_bit(bitboard* board, char bit)
{
    *board |= (1ll << bit);
}

inline bool get_bit(bitboard board, char bit)
{
    return board & 1ll << bit;
}

inline void pop_bit(bitboard* board, char bit)
{
    *board &= !(1ll << bit);
}

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
    white_bitboards.fill(0);
    black_bitboards.fill(0);
}

void Board::print()
{
    print_bitboard(white_bitboards[PIECE::pawn]);

    set_bit(&white_bitboards[PIECE::pawn], SQUARE::f4);

    print_bitboard(white_bitboards[PIECE::pawn]);

    pop_bit(&white_bitboards[PIECE::pawn], SQUARE::f4);

    print_bitboard(white_bitboards[PIECE::pawn]);
}

bool Board::is_legal(const Move&) const
{
    return true;
}
