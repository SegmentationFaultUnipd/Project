#ifndef CHESS_COORDINATE_H
#define CHESS_COORDINATE_H

#include <assert.h>
#include <string>

namespace chess {

    struct Coordinates
    {
        short file; //column index 0-7, means a-h, from queenside to kingside
        short rank; //row index 0-7, means 1-8, from whiteside to blackside

        Coordinates(short _file, short _rank) {
            file = _file;
            rank = _rank;
        }

        Coordinates(const std::string notation) {
            file = tolower(notation[0]) - 'a';
            rank = notation[1] - '1';
        }

        Coordinates() : Coordinates{0,0} {}

        std::string toNotation() {
            return "" + (char)(file + 'a') + (char)(rank + '1');
        }

        bool operator==(const Coordinates& c2) const {
            return file == c2.file && rank == c2.rank;
        }
    };

}

#endif //CHESS_COORDINATE_H