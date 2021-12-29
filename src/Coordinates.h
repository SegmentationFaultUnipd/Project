#ifndef CHESS_COORDINATE_H
#define CHESS_COORDINATE_H

#include <assert.h>
#include <string>

namespace chess {

    struct Coordinates
    {
        short file; //column from 'a' to 'h', from queenside to kingside
        short rank; //row from 1 to 8, from white to black

        Coordinates(short _file, short _rank) {
            file = _file;
            rank = _rank;
        }

        Coordinates(const std::string notation) {
            file = tolower(notation[0]) - 'a';
            rank = notation[1] - '0' - 1;
        }

        Coordinates() : Coordinates{0,0} {}

        bool operator==(const Coordinates& c2) {
            return file == c2.file && rank == c2.rank;
        }
    };

}

#endif //CHESS_COORDINATE_H