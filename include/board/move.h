#ifndef MOVE_H
#define MOVE_H

struct Move {
    Move(char from, const char to, char promote = 0,
         bool enpassant = false, bool castle = false, bool capture = false)
        : from(from),
          to(to),
          promote(promote),
          enpassant(enpassant),
          castle(castle),
          capture(capture) {};

    char from;
    char to;

    bool enpassant;
    bool castle;
    bool capture;

    char promote;
};

#endif
