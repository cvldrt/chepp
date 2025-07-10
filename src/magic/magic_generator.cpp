#include <cstring>
#include <iostream>

#include "bitboard.h"
#include "piece_masks.h"

int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

int bishop_relevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

uint64_t random_uint64()
{
    uint64_t u1, u2, u3, u4;

    u1 = (uint64_t)(random()) & 0xFFFF;
    u2 = (uint64_t)(random()) & 0xFFFF;
    u3 = (uint64_t)(random()) & 0xFFFF;
    u4 = (uint64_t)(random()) & 0xFFFF;

    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

uint64_t random_uint64_fewbits()
{
    return random_uint64() & random_uint64() & random_uint64();
}

bitboard set_occupancy(int index, bitboard mask, int mask_bit_count)
{
    bitboard occupancy = 0;

    for (int count = 0; count < mask_bit_count; ++count) {
        // first non-zero square
        int sq = count_bits((mask & -mask) - 1);
        pop_bit(mask, sq);
        if (index & (1ull << count)) occupancy |= (1ull << sq);
    }

    return occupancy;
}

bitboard rook_attacks(SQUARE sq, bitboard blockers)
{
    bitboard result = 0;

    int rank = sq / 8;
    int file = sq % 8;

    for (int r = rank + 1; r < 7; ++r) {
        set_bit(result, file + r * 8);
        if (result & blockers) break;
    }

    for (int r = rank - 1; r > 0; --r) {
        set_bit(result, file + r * 8);
        if (result & blockers) break;
    }
    for (int f = file + 1; f < 7; ++f) {
        set_bit(result, f + rank * 8);
        if (result & blockers) break;
    }
    for (int f = file - 1; f > 0; --f) {
        set_bit(result, f + rank * 8);
        if (result & blockers) break;
    }

    return result;
}

bitboard bishop_attacks(SQUARE sq, bitboard blockers)
{
    bitboard result = 0;

    int rank = sq / 8;
    int file = sq % 8;

    for (int r = rank + 1, f = file + 1; r < 7 && f < 7; ++r, ++f) {
        set_bit(result, f + r * 8);
        if (result & blockers) break;
    }
    for (int r = rank + 1, f = file - 1; r < 7 && f > 0; ++r, --f) {
        set_bit(result, f + r * 8);
        if (result & blockers) break;
    }
    for (int r = rank - 1, f = file + 1; r > 0 && f < 7; --r, ++f) {
        set_bit(result, f + r * 8);
        if (result & blockers) break;
    }
    for (int r = rank - 1, f = file - 1; r > 0 && f > 0; --r, --f) {
        set_bit(result, f + r * 8);
        if (result & blockers) break;
    }

    return result;
}

uint64_t find_magic(SQUARE sq, int relevant_bit_count, bool bishop)
{
    bitboard occupancies[4096];
    bitboard attacks[4096];
    bitboard used_attacks[4096];

    bitboard mask = bishop ? bishop_mask[sq] : rook_mask[sq];

    int variations = 1 << relevant_bit_count;

    for (int i = 0; i < variations; ++i) {
        occupancies[i] = set_occupancy(i, mask, relevant_bit_count);
        attacks[i]     = bishop ? bishop_attacks(sq, occupancies[i])
                                : rook_attacks(sq, occupancies[i]);
    }

    for (int i = 0; i < 1000000000; ++i) {
        uint64_t magic = random_uint64_fewbits();

        if (count_bits((mask * magic) & 0xff00000000000000ull) < 6) continue;

        memset(used_attacks, 0ull, sizeof(used_attacks));

        bool fail = false;

        for (int count = 0; !fail && count < variations; ++count) {
            int magic_index =
                (occupancies[count] * magic) >> (64 - relevant_bit_count);

            if (used_attacks[magic_index] == 0) {
                used_attacks[magic_index] = attacks[count];
            }

            fail = used_attacks[magic_index] != attacks[count];
        }

        if (!fail) return magic;
    }

    return 0;
}

void print_magic_numbers() {
    std::cout << "const uint64_t rook_magics[64] = {\n";
    for (int sq = 0; sq < 64; ++sq) {
        std::cout << "    "
                  << find_magic((SQUARE)sq, rook_relevant_bits[sq], false)
                  << "ull,\n";
    }
    std::cout << "};\n";

    std::cout << "\n const uint64_t bishop_magics[64] = {\n";
    for (int sq = 0; sq < 64; ++sq) {
        std::cout << "    "
                  << find_magic((SQUARE)sq, bishop_relevant_bits[sq], true)
                  << "ull,\n";
    }
    std::cout << "};\n";
}

int main()
{
}
