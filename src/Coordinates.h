//AUTORE: Filippo Mazzarotto
#ifndef COORDINATES_H
#define COORDINATES_H

#include <assert.h>
#include <string>
#include <ostream>
#include <sstream>

namespace chess
{

    constexpr int LOWER_RANK{0};
    constexpr int UPPER_RANK{7};
    constexpr int LEFT_FILE{0};
    constexpr int RIGHT_FILE{7};
    constexpr int TARGET_QUEENSIDE_CASTLE_FILE{2};
    constexpr int TARGET_KINGSIDE_CASTLE_FILE{6};

    /**
     * @brief Contiene le coordinate di una casa nella scacchiera
     * file è la colonna, contiene un indice da 0 a 7 per le file da a a h
     * rank è la riga, contiene un indice da 0 a 7 per le righe da 1 a 8
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

        /**
         * @brief Ritorna una stringa con la coordinata in notazione
         * alfanumerica
         * 
         * @return std::string con le coordinata alfanumerica ex:
         * 00 diventa a1
         */
        std::string toNotation() const
        {
            std::ostringstream oss;
            oss << (char)(file + 'a') << (char)(rank + '1');
            return oss.str();
        }

        /**
         * @brief Verifica se si trova all'interno della scacchiera 8x8
         * 
         * @return true se si trova all'interno della scacchiera
         * @return false altrimenti
         */
        bool inBounderies() const
        {
            return file >= LEFT_FILE && file <= RIGHT_FILE
                && rank >= LOWER_RANK && rank <= UPPER_RANK;
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