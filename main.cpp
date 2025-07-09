#include "board.h"
#include "piece_masks.h"

int main(int argc, char** argv){

    //std::string fen(argv[1]);
    //Board b(fen);
    //b.print();

    print_bitboard(bishop_mask_full[e4]);
    print_bitboard(bishop_mask[e4]);

    return 0;
}
