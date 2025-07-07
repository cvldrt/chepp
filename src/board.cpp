#include "board.h"

#include <cassert>
#include <iostream>

#include "bitboard.h"
#include "enums.h"
#include "utils.h"

// default init with the starting posijtion
Board::Board()
    : Board("nbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")
{
}

Board::Board(std::string fen)
{
    bitboards[PLAYER::white].fill(0);
    bitboards[PLAYER::black].fill(0);

    auto tokens = split(fen, ' ');

    std::cout << tokens.size();
    //assert(tokens.size() == 6);

    // parse player to move
    to_move = tokens[1][0] == 'w' ? PLAYER::white : PLAYER::black;

    // parse castling rights
    if (tokens[2] != "-") {
        for (char ch : tokens[2]) switch (ch) {
                case 'K':
                    white_castle_short = true;
                    break;
                case 'k':
                    black_castle_short = true;
                    break;
                case 'Q':
                    white_castle_long = true;
                    break;
                case 'q':
                    black_castle_long = true;
                    break;
            }
    }

    // parse en passant quare
    en_passant = str_to_square(tokens[3]);

    halfmove_clock = atoi(tokens[4].c_str());
    fullmove_number = atoi(tokens[5].c_str());

    // parse board state
    int index = 64;
    for (char ch : tokens[0]) {
        if (std::isdigit(ch)) index -= (ch - 48);
        if (std::isalpha(ch)) --index;

        switch (ch) {
            case '/':
                assert((index) % 8 == 0);
                break;
            case 'P':
                bitboards[PLAYER::white][PIECE::pawn] |= (1ll << index);
                break;
            case 'p':
                bitboards[PLAYER::black][PIECE::pawn] |= (1ll << index);
                break;
            case 'R':
                bitboards[PLAYER::white][PIECE::rook] |= (1ll << index);
                break;
            case 'r':
                bitboards[PLAYER::black][PIECE::rook] |= (1ll << index);
                break;
            case 'N':
                bitboards[PLAYER::white][PIECE::knight] |= (1ll << index);
                break;
            case 'n':
                bitboards[PLAYER::black][PIECE::knight] |= (1ll << index);
                break;
            case 'B':
                bitboards[PLAYER::white][PIECE::bishop] |= (1ll << index);
                break;
            case 'b':
                bitboards[PLAYER::black][PIECE::bishop] |= (1ll << index);
                break;
            case 'Q':
                bitboards[PLAYER::white][PIECE::queen] |= (1ll << index);
                break;
            case 'q':
                bitboards[PLAYER::black][PIECE::queen] |= (1ll << index);
                break;
            case 'K':
                bitboards[PLAYER::white][PIECE::king] |= (1ll << index);
                break;
            case 'k':
                bitboards[PLAYER::black][PIECE::king] |= (1ll << index);
                break;
        }
    }

    std::cout << "Initialized board from fen: " << fen << std::endl;
}

void add_piece(bitboard bb, char ch, char board[8][8])
{
    for (int i = 0; i < 64; ++i) {
        if ((1ll << i) & bb) board[i / 8][i % 8] = ch;
    }
}

void Board::print()
{
    char board[8][8];

    for (char* row : board) {
        for (int i = 0; i < 8; ++i) row[i] = ' ';
    }

    add_piece(bitboards[PLAYER::white][PIECE::pawn], 'P', board);
    add_piece(bitboards[PLAYER::white][PIECE::rook], 'R', board);
    add_piece(bitboards[PLAYER::white][PIECE::knight], 'N', board);
    add_piece(bitboards[PLAYER::white][PIECE::bishop], 'B', board);
    add_piece(bitboards[PLAYER::white][PIECE::queen], 'Q', board);
    add_piece(bitboards[PLAYER::white][PIECE::king], 'K', board);

    add_piece(bitboards[PLAYER::black][PIECE::pawn], 'p', board);
    add_piece(bitboards[PLAYER::black][PIECE::rook], 'r', board);
    add_piece(bitboards[PLAYER::black][PIECE::knight], 'n', board);
    add_piece(bitboards[PLAYER::black][PIECE::bishop], 'b', board);
    add_piece(bitboards[PLAYER::black][PIECE::queen], 'q', board);
    add_piece(bitboards[PLAYER::black][PIECE::king], 'k', board);

    std::cout << "\n   ---------------------------------\n";

    for (int y = 7; y >= 0; --y) {
        std::cout << y + 1 << "  | ";
        for (int x = 7; x >= 0; --x) {
            std::cout << board[y][x] << " | ";
        }

        std::cout << "\n   ---------------------------------\n";
    }

    std::cout << "     a   b   c   d   e   f   g   h\n\n";
    std::cout << "To move: " << (to_move ? "BLACK" : "WHITE") << "\n";


    std::cout << "Castling: ";
    bool possible_castling = white_castle_short || white_castle_long ||
                             black_castle_short || black_castle_long;
    if (possible_castling) {
        std::cout << (white_castle_short ? "K" : "");
        std::cout << (white_castle_long ? "Q" : "");
        std::cout << (black_castle_short ? "k" : "");
        std::cout << (black_castle_long ? "q" : "");
        std::cout << "\n";
    } else {
        std::cout << "-\n";
    }

    std::cout << "En passant: " << square_to_str(en_passant) << "\n";
    std::cout << "Halfmove clock: " << (int) halfmove_clock << "\n";
    std::cout << "Fullmove_number: " << fullmove_number << "\n";
}
