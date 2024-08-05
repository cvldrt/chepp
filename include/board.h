#include <array>
#include <string>
#include <vector>

#include "bitboard.h"
#include "move.h"

class Board {
   public:
    Board();
    Board(std::string& fen);

    bool move(const Move&);

    bool is_square_attacked() const;
    bool is_board_state_valid() const;

    std::vector<Move> get_moves() const;

    void print();
    void print(bitboard) const;

   private:
    std::array<std::array<bitboard, 6>, 2> bitboards;

    bool white_castle_short = true;
    bool white_castle_long  = true;
    bool black_castle_short = true;
    bool black_castle_long  = true;
};
