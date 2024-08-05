#ifndef MASK_GENERATOR_H
#define MASK_GENERATOR_H

#include <array>

#include "bitboard.h"
#include "enums.h"

constexpr static std::array<bitboard, 64> rook_mask = []() {
    std::array<bitboard, 64> result{};

    for (int i = 0; i < 64; ++i) {
        result[i] = 1;
    }

    return result;
}();

constexpr static std::array<std::array<bitboard, 64>, 2> pawn_attacks = []() {
    std::array<std::array<bitboard, 64>, 2> result{};

    for (int i = 8; i < 56; ++i) {
        result[white][i] = 0;
        result[black][i] = 0;

        if (i % 8 != 7) {
            result[white][i] |= 1ll << (63 - i + 7);
            result[black][i] |= 1ll << (63 - i - 9);
        }

        if (i % 8 != 0) {
            result[white][i] |= 1ll << (63 - i + 9);
            result[black][i] |= 1ll << (63 - i - 7);
        }
    }

    return result;
}();

#endif
