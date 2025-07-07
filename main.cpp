#include "board.h"

int main(int argc, char** argv){
    
    std::string fen(argv[1]);

    Board b(fen);

    b.print();

    return 0;
}
