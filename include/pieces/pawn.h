#ifndef PAWN_H
#define PAWN_H

#include "bitboard.h"

bitboard pawn_single_pushes(bitboard pawns, bitboard empty, char color);

bitboard pawn_double_pushes(bitboard pawns, bitboard empty, char color);

bitboard pawn_captures_left(bitboard pawns, char color);

bitboard pawn_captures_right(bitboard pawns, char color);

bitboard pawn_captures(bitboard pawns, char color);

#endif
