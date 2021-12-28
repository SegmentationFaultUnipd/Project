#ifndef CHESS_COORDINATE_H
#define CHESS_COORDINATE_H

namespace chess {

struct Coordinates
{
    short file; //column from 'a' to 'h', from queenside to kingside
    short rank; //row from 1 to 8, from white to black

    Coordinates(char _file, short _rank) {
        if (_file >= 'a' && _file <= 'h' && _rank >= 1 && _rank <= 8) {
            file = _file - 'a';
            rank = _rank;
        } else {
            //IllegalArgument Exception
        }
    }

    Coordinates(short _file, short _rank) {
        if (_file >= 0 && _file <= 7 && _rank >= 0 && _rank <= 7) {
            file = _file - 'a';
            rank = _rank;
        } else {
            //IllegalArgument Exception
        }
    }
};

}

#endif //CHESS_COORDINATE_H