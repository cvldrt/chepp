#include "pieces/nonsliding.h"

bitboard push(bitboard pawns, char color)
{
    return (pawns << 8) >> (color >> 4);
}

bitboard pawn_single_pushes(bitboard pawns, bitboard empty, char color)
{
    return push(pawns, color) & empty;
}

bitboard pawn_double_pushes(bitboard pawns, bitboard empty, char color)
{
    bitboard pushed          = push(pawns, color) & empty;
    bitboard double_push_row = 0x00000000ff000000 << (color * 8);

    return push(pushed, color) & empty & double_push_row;
}

bitboard pawn_captures_left(bitboard pawns, char color)
{
    return ((pawns & 0x7f7f7f7f7f7f7f7f) << 9) >> (16 * color);
}

bitboard pawn_captures_right(bitboard pawns, char color)
{
    return ((pawns & 0xfefefefefefefefe) << 7) >> (16 * color);
}

bitboard pawn_captures(bitboard pawns, char color)
{
    return pawn_captures_left(pawns, color) |
           pawn_captures_right(pawns, color);
}
