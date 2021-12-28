#ifndef PIECE_H
#define PIECE_H

#include "../Color.h"
#include "../Coordinates.h"

namespace chess {

    class Piece {
        public:
            Piece(short file, short rank, Color color) : position_{file, rank}, color_{color} {};
            Piece(char file, short rank, Color color) : Piece{(short)(file - 'a'), rank + 1, color} {};

            void move (short file, short rank) {
                position_.file = file;
                position_.rank = rank;
            }

            bool canMove(short to_file, short to_rank) { return true; }

            bool color() { return color_;}
            short file() { return position_.file; }
            short rank() { return position_.rank; }

        protected:
            Coordinates position_;
            Color color_;
    };

} //namespace chess

#endif //PIECE_H