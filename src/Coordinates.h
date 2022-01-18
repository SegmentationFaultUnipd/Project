#ifndef COORDINATES_H
#define COORDINATES_H

#include <assert.h>
#include <string>
#include <ostream>
#include <sstream>

#define CHESSBOARD_LOWER_BOUND 0
#define CHESSBOARD_UPPER_BOUND 7

namespace chess
{

    /**
     * @brief Contains the coordinates of a square on the chess board
     * file is the column, contains an index 0-7, meaning a-h files
     * rank is the row, contains an index 0-7, meaning 1-8 ranks
     *
     * Occasionaly Coordinates can store values indicating a mathematical vector,
     * example Coordinate delta{-2, 0} indicates a movement of -2 file and same rank
     */
    struct Coordinates
    {
        int file;
        int rank;

        Coordinates(int _file, int _rank)
        {
            file = _file;
            rank = _rank;
        }

        Coordinates(const std::string notation)
        {
            file = tolower(notation[0]) - 'a';
            rank = notation[1] - '1';
        }

        Coordinates() : Coordinates{0, 0} {}

        std::string toNotation() const
        {
            std::ostringstream oss;
            oss << (char)(file + 'a') << (char)(rank + '1');
            return oss.str();
        }

        bool inBounderies() const
        {
            return file >= CHESSBOARD_LOWER_BOUND && file <= CHESSBOARD_UPPER_BOUND
                && rank >= CHESSBOARD_LOWER_BOUND && rank <= CHESSBOARD_UPPER_BOUND;
        }

        bool operator==(const Coordinates &c2) const
        {
            return (file == c2.file && rank == c2.rank);
        }
    };

    inline std::ostream &operator<<(std::ostream &os, const Coordinates &coords)
    {
        os << coords.toNotation();
        return os;
    }

    inline Coordinates &operator+=(Coordinates &coords1, const Coordinates &coords2)
    {
        coords1.file += coords2.file;
        coords1.rank += coords2.rank;
        return coords1;
    }

    inline Coordinates &operator-=(Coordinates &coords1, const Coordinates &coords2)
    {
        coords1.file -= coords2.file;
        coords1.rank -= coords2.rank;
        return coords1;
    }

    inline Coordinates operator+(const Coordinates &coords1, const Coordinates &coords2)
    {
        return Coordinates{coords1.file + coords2.file, coords1.rank + coords2.rank};
    }

    inline Coordinates operator-(const Coordinates &coords1, const Coordinates &coords2)
    {
        return Coordinates{coords1.file - coords2.file, coords1.rank - coords2.rank};
    }

}

#endif // COORDINATES_H