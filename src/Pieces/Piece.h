#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>

#include "../Color.h"
#include "../Coordinates.h"

namespace chess {

    class Piece {
        public:
            void move (short file, short rank) {
                position_.file = file;
                position_.rank = rank;
            }

            //Check if the piece can move to a file and rank.
            bool virtual canMove(short to_file, short to_rank, Piece* board[8][8]) = 0;

            //Check if the piece has at least an avaible move
            bool virtual canMove(Piece* board[8][8]) = 0;

            //List all the available moves
            std::vector<Coordinates> virtual legalMoves(Piece* board[8][8]) = 0;

            //returns the ascii character for that piece
            char virtual ascii() = 0;

            bool color() const { return color_;}
            short file() const { return position_.file; }
            short rank() const { return position_.rank; }

        protected:
            Piece(short file, short rank, Color color) : position_{file, rank}, color_{color} {};
            Piece(char file, short rank, Color color) : Piece{(short)(file - 'a'), (short)(rank - 1), color} {};

            Coordinates position_;
            Color color_;
    };

} //namespace chess

#endif //PIECE_H