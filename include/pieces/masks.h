#pragma once

#include <array>

#include "enums.h"
#include "core/bitboard.h"

inline constexpr std::array<std::array<bitboard, 64>, 2> pawn_attacks = []() {
    std::array<std::array<bitboard, 64>, 2> result{};

    for (int i = 8; i < 56; ++i) {
        result[white][i] = 0;
        result[black][i] = 0;

        if (i % 8 != 0) {
            result[white][i] |= 1ull << (i + 7);
            result[black][i] |= 1ull << (i - 9);
        }

        if (i % 8 != 7) {
            result[white][i] |= 1ull << (i + 9);
            result[black][i] |= 1ull << (i - 7);
        }
    }

    return result;
}();

inline constexpr std::array<bitboard, 64> knight_attacks = []() {
    std::array<bitboard, 64> result{};

    for (int i = 0; i < 64; ++i) {
        result[i] = 0;

        for (int offset : {-17, -15, -10, -6, 6, 10, 15, 17}) {
            int target_i = i + offset;

            if (target_i >= 0 && target_i < 64 &&  // inside board boundaries
                (target_i / 8) - (i / 8) < 3 &&
                (target_i / 8) - (i / 8) > -3 &&  // vertical distance < 3
                (target_i % 8) - (i % 8) < 3 &&
                (target_i % 8) - (i % 8) > -3)  // horizontal distance < 3
            {
                result[i] |= 1ull << (i + offset);
            }
        }
    }

    return result;
}();

inline constexpr std::array<bitboard, 64> bishop_mask_full = []() {
    std::array<bitboard, 64> result{};

    for (int sq = 0; sq < 64; ++sq) {
        // used to avoid "owerflow" between ranks
        int max_left_offset  = sq % 8;
        int max_right_offset = 7 - max_left_offset;

        for (int dist = 1; dist < 8; ++dist) {
            // left
            for (int direction : {-9, 7}) {
                int target_sq = sq + direction * dist;

                if (target_sq >= 0 && target_sq < 64 &&
                    dist <= max_left_offset) {
                    result[sq] |= 1ull << (target_sq);
                }
            }

            // right
            for (int direction : {-7, 9}) {
                int target_sq = sq + direction * dist;

                if (target_sq >= 0 && target_sq < 64 &&
                    dist <= max_right_offset) {
                    result[sq] |= 1ull << (target_sq);
                }
            }
        }
    }

    return result;
}();

inline constexpr std::array<bitboard, 64> bishop_mask = []() {
    std::array<bitboard, 64> result{};

    for (int sq = 0; sq < 64; ++sq) {
        int rank = sq / 8;
        int file = sq % 8;

        for (int r = rank + 1, f = file + 1; r < 7 && f < 7; ++r, ++f)
            set_bit(result[sq], f + r * 8);
        for (int r = rank + 1, f = file - 1; r < 7 && f > 0; ++r, --f)
            set_bit(result[sq], f + r * 8);
        for (int r = rank - 1, f = file + 1; r > 0 && f < 7; --r, ++f)
            set_bit(result[sq], f + r * 8);
        for (int r = rank - 1, f = file - 1; r > 0 && f > 0; --r, --f)
            set_bit(result[sq], f + r * 8);
    }

    return result;
}();

inline constexpr std::array<bitboard, 64> rook_mask_full = []() {
    std::array<bitboard, 64> result{};

    bitboard rank = 0xffull;
    bitboard file = 0x0101010101010101;

    for (int sq = 0; sq < 64; ++sq) {
        result[sq] = rank << (sq / 8) * 8;
        result[sq] ^= file << (sq % 8);
    }

    return result;
}();

inline constexpr std::array<bitboard, 64> rook_mask = []() {
    std::array<bitboard, 64> result{};

    for (int sq = 0; sq < 64; ++sq) {
        int rank = sq / 8;
        int file = sq % 8;

        for (int r = rank + 1; r < 7; ++r) set_bit(result[sq], file + r * 8);
        for (int r = rank - 1; r > 0; --r) set_bit(result[sq], file + r * 8);
        for (int f = file + 1; f < 7; ++f) set_bit(result[sq], f + rank * 8);
        for (int f = file - 1; f > 0; --f) set_bit(result[sq], f + rank * 8);
    }

    return result;
}();

inline constexpr std::array<bitboard, 64> queen_mask_full = []() {
    std::array<bitboard, 64> result{};

    for (int sq = 0; sq < 64; ++sq) {
        result[sq] = bishop_mask_full[sq] | rook_mask_full[sq];
    }

    return result;
}();

inline constexpr std::array<bitboard, 64> king_attacks = []() {
    std::array<bitboard, 64> result{};

    for (int i = 0; i < 64; ++i) {
        for (int offset : {-9, -8, -7, -1, 1, 7, 8, 9}) {
            int target_i = i + offset;

            if (target_i > 0 && target_i < 63 && (target_i % 8) - (i % 8) < 2 &&
                (target_i % 8) - (i % 8) > -2) {
                result[i] |= 1ull << target_i;
            }
        }
    }

    return result;
}();

