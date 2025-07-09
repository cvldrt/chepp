#pragma once

#include <array>

#include "bitboard.h"
#include "enums.h"

inline constexpr std::array<std::array<bitboard, 64>, 2> pawn_attacks = []() {
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
                result[i] |= 1ll << (i + offset);
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
                    result[sq] |= 1ll << (target_sq);
                }
            }

            // right
            for (int direction : {-7, 9}) {
                int target_sq = sq + direction * dist;

                if (target_sq >= 0 && target_sq < 64 &&
                    dist <= max_right_offset) {
                    result[sq] |= 1ll << (target_sq);
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

    bitboard rank = 0xffll;
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
                result[i] |= 1ll << target_i;
            }
        }
    }

    return result;
}();

const uint64_t rook_magics[64] = {
    756607761056301088ull,
    486389076241424385ull,
    1180879918473218ull,
    2269400663066884ull,
    9225910276929357824ull,
    648557928894234658ull,
    2289194500624392ull,
    1134973027356674ull,
    4912301435322105924ull,
    72761831772405760ull,
    37154976165795984ull,
    144678173464860160ull,
    9811373280652165376ull,
    18577421620084740ull,
    18163450257472ull,
    54183935181062208ull,
    18014948270571552ull,
    4625341953385742914ull,
    2310346643737740420ull,
    56295064078389760ull,
    2251872836781568ull,
    18141978616928ull,
    36591837242204224ull,
    648800371090653248ull,
    9232449607001210913ull,
    4503875579027458ull,
    2314885397139750931ull,
    13871654200569563140ull,
    4761430725365334145ull,
    4611704160923158016ull,
    140741783453732ull,
    36284026391113ull,
    90775954909037088ull,
    563090680726592ull,
    1189268069613568640ull,
    2308095084207407120ull,
    20266752516555776ull,
    72409747030020098ull,
    4615081348518904337ull,
    36283887911572ull,
    9799867974604046336ull,
    5066841924042785ull,
    4612847171459352672ull,
    36591782407045152ull,
    4398180761728ull,
    351912574713986ull,
    1159688037693658240ull,
    10233314991256112768ull,
    3531386160012329984ull,
    1127558306202624ull,
    1152956981045167104ull,
    158338335113232ull,
    5779037411607808ull,
    1126467933175824ull,
    693695226136559632ull,
    1161380942840320ull,
    9224115393705181185ull,
    281580207603745ull,
    35270842421516ull,
    108103986615164949ull,
    581245835631658001ull,
    4613093427737788929ull,
    37156930863497348ull,
    2325264783682601473ull,
};

const uint64_t bishop_magics[64] = {
    18164172613386273ull,
    2419717302642016264ull,
    5046285667392421888ull,
    9223935613873422592ull,
    1153495454105731328ull,
    883004628571013184ull,
    167298674458625ull,
    148675971034251328ull,
    246600664421376ull,
    2305878210774171732ull,
    2347267260424ull,
    581531704261607440ull,
    778037109541457920ull,
    38282830249230336ull,
    39479227750416384ull,
    1153240365193609216ull,
    290552615611146257ull,
    2319646313643311104ull,
    288230410521680000ull,
    18031999320072192ull,
    4454350864ull,
    9259400983130144803ull,
    1103943435266ull,
    9804336395296219656ull,
    306288755262701824ull,
    4512464515433476ull,
    18023195144635008ull,
    1225014832783165504ull,
    282574489403392ull,
    612491749423648768ull,
    596727225655755426ull,
    288240284809056800ull,
    10394343141524377728ull,
    2680196039680ull,
    562708611584ull,
    2306058582749348096ull,
    72057740067866642ull,
    72066408386136320ull,
    1302175811641803781ull,
    581250225490919940ull,
    612491783812678664ull,
    9223513393086892064ull,
    450988345344ull,
    4649985856986154048ull,
    2181038368ull,
    18016634157400739ull,
    17680371826976ull,
    36100419910912134ull,
    50582102479360ull,
    4512705092812948ull,
    1441717605269374992ull,
    24911772935260416ull,
    576478346909847552ull,
    72057731546134788ull,
    9331493895823233104ull,
    306262389681039360ull,
    1170938136532947489ull,
    1765696931524390948ull,
    9080041975678976ull,
    1227340850728698370ull,
    2305861700922049544ull,
    2305985948145558023ull,
    9368073453876019488ull,
    576496496371892480ull,
};
