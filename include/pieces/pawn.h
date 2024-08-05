#ifndef PAWN_H
#define PAWN_H

#include "bitboard.h"
#include "enums.h"

bitboard pawn_single_pushes(bitboard pawns, bitboard empty, char color);

bitboard pawn_double_pushes(bitboard pawns, bitboard empty, char color);

bitboard pawn_captures(bitboard pawns, bitboard enemy, SQUARE enpassant);

#endif
