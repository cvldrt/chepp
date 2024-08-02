#include <array>
#include <cstdint>
#include <vector>

#include "move.h"

typedef uint64_t bitboard;

class Board {
   public:
    Board();
    bool move(const Move&);
    bool is_legal(const Move&) const;
    bool is_board_state_valid() const;
    std::vector<Move> get_moves() const;
    void print();
    void print(bitboard) const;

   private:
    std::array<bitboard, 6> white_bitboards;
    std::array<bitboard, 6> black_bitboards;

    bool white_castle_short = true;
    bool white_castle_long  = true;
    bool black_castle_short = true;
    bool black_castle_long  = true;
};
