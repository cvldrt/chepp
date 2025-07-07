#include <array>
#include <string>
#include <vector>

#include "bitboard.h"
#include "move.h"
#include "enums.h"

class Board {
   public:
    Board();
    Board(std::string fen);

    bool move(const Move&);

    bool is_square_attacked() const;
    bool is_board_state_valid() const;

    std::vector<Move> get_moves() const;

    void print();
    void print(bitboard) const;

   private:
    std::array<std::array<bitboard, 6>, 2> bitboards;

    bool to_move = PLAYER::white;

    bool white_castle_short = false;
    bool white_castle_long  = false;
    bool black_castle_short = false;
    bool black_castle_long  = false;

    SQUARE en_passant = SQUARE::none;

    uint8_t halfmove_clock = 0;
    uint16_t fullmove_number = 1;

};
