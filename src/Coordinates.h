#ifndef CHESS_COORDINATES_H
#define CHESS_COORDINATES_H

#include <assert.h>
#include <string>
#include <ostream>
#include <sstream>

namespace chess {

    struct Coordinates
    {
        short file; //column index 0-7, means a-h, from queenside to kingside
        short rank; //row index 0-7, means 1-8, from whiteside to blackside

        Coordinates(int _file, int _rank) {
            file = (short)_file;
            rank = (short)_rank;
        }

        Coordinates(const std::string notation) {
            file = tolower(notation[0]) - 'a';
            rank = notation[1] - '1';
        }

        Coordinates() : Coordinates{0,0} {}

        std::string toNotation() const {
            std::ostringstream oss;
            oss << (char)(file + 'a') << (char)(rank + '1');
            return oss.str();
        }

        bool operator==(const Coordinates& c2) const {
            return (file == c2.file && rank == c2.rank);
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Coordinates& coords) {
        os << coords.toNotation();
        return os;
    }

}

#endif //CHESS_COORDINATE_H