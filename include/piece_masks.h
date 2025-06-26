#ifndef MASK_GENERATOR_H
#define MASK_GENERATOR_H

#include <array>

#include "bitboard.h"
#include "enums.h"

constexpr static std::array<bitboard, 64> rook_mask = []() {
    std::array<bitboard, 64> result{};

    bitboard row = 0xff;
    bitboard col = 0x0101010101010101;

    for (int i = 0; i < 64; ++i) {
        result[i] = row << (i / 8) * 8;
        result[i] ^= col << (i % 8);
    }

    return result;
}();

constexpr static std::array<bitboard, 64> bishop_mask = []() {
    std::array<bitboard, 64> result{};

    for (int i = 0; i < 64; ++i) {
        // used to avoid "owerflow" between ranks
        int max_left_offset  = i % 8;
        int max_right_offset = 7 - max_left_offset;

        for (int dist = 1; dist < 8; ++dist) {
            // left
            for (int direction : {-9, 7}) {
                int target_i = i + direction * dist;

                if (target_i >= 0 && target_i < 64 && dist <= max_left_offset) {
                    result[i] |= 1ll << (target_i);
                }
            }

            // right
            for (int direction : {-7, 9}) {
                int target_i = i + direction * dist;

                if (target_i >= 0 && target_i < 64 &&
                    dist <= max_right_offset) {
                    result[i] |= 1ll << (target_i);
                }
            }
        }
    }

    return result;
}();

constexpr static std::array<bitboard, 64> qween_mask = []() {
    std::array<bitboard, 64> result{};

    for (int i = 0; i < 64; ++i) {
        result[i] = bishop_mask[i] | rook_mask[i];
    }

    return result;
}();


constexpr static std::array<bitboard, 64> king_attacks = []() {
    std::array<bitboard, 64> result{};

    for (int i = 0; i < 64; ++i){

        for (int offset : {-9, -8, -7, -1, 1, 7, 8, 9}){

            int target_i = i + offset;

            if (target_i > 0 && target_i < 63 &&
                (target_i % 8) - (i % 8) < 2 && (target_i % 8) - (i % 8) > -2){
                result[i] |= 1ll << target_i; 
            }
        }
    }

    return result;
}();

constexpr static std::array<bitboard, 64> knight_attacks = []() {
    std::array<bitboard, 64> result{};

    for (int i = 0; i < 64; ++i) {
        result[i] = 0;

        for (int offset : {-17, -15, -10, -6, 6, 10, 15, 17}) {
            int target_i = i + offset;

            if (target_i >= 0 && target_i < 64 && // inside board boundaries
                (target_i / 8) - (i / 8) < 3 && (target_i / 8) - (i / 8) > -3 && // vertical distance < 3
                (target_i % 8) - (i % 8) < 3 && (target_i % 8) - (i % 8) > -3) // horizontal distance < 3
            {
                result[i] |= 1ll << (i + offset);
            }
        }
    }

    return result;
}();

constexpr static std::array<std::array<bitboard, 64>, 2> pawn_attacks = []() {
    std::array<std::array<bitboard, 64>, 2> result{};

    for (int i = 8; i < 56; ++i) {
        result[white][i] = 0;
        result[black][i] = 0;

        if (i % 8 != 0) {
            result[white][i] |= 1ll << (i + 7);
            result[black][i] |= 1ll << (i - 9);
        }

        if (i % 8 != 7) {
            result[white][i] |= 1ll << (i + 9);
            result[black][i] |= 1ll << (i - 7);
        }
    }

    return result;
}();

#endif
