#ifndef COORDINATES_H
#define COORDINATES_H

#include <assert.h>
#include <string>
#include <ostream>
#include <sstream>

namespace chess
{

    constexpr int BOARD_LOWER_RANK{0};
    constexpr int BOARD_UPPER_RANK{7};
    constexpr int BOARD_LEFT_FILE{0};
    constexpr int BOARD_RIGHT_FILE{7};
    constexpr int BOARD_TARGET_QUEENSIDE_CASTLE_FILE{2};
    constexpr int BOARD_TARGET_KINGSIDE_CASTLE_FILE{6};

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
            return file >= BOARD_LEFT_FILE && file <= BOARD_RIGHT_FILE
                && rank >= BOARD_LOWER_RANK && rank <= BOARD_UPPER_RANK;
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

    inline Coordinates operator*(const Coordinates &coords, const int scalar)
    {
        return Coordinates(coords.file * scalar, coords.rank * scalar);
    }

    inline Coordinates operator*(const int scalar, const Coordinates &coords)
    {
        return Coordinates(coords.file * scalar, coords.rank * scalar);
    }

}

#endif // COORDINATES_H