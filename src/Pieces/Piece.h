#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <iostream>

#include "../Color.h"
#include "../Coordinates.h"

namespace chess {
	class Board;

    class Piece {
        public:
            void move (Coordinates new_position) {
                position_ = new_position;
            }

            //Check if the piece can move to a file and rank.
            bool virtual canMove(Coordinates pos, chess::Board& board) const = 0;

            //Check if the piece has at least an avaible move
            bool virtual canMove(chess::Board& board) const = 0;

            //List all the avaible moves
            std::vector<Coordinates> virtual legalMoves(chess::Board& board) const = 0;

            //List all the moves that capture an enemy piece
            // std::vector<Coordinates> virtual takeablePieces(chess::Board& board) const;

            // returns the ascii character for that piece
            char virtual ascii() const = 0;

            Color color() const { return color_;}
            short file() const { return position_.file; }
            short rank() const { return position_.rank; }

        protected:
            Piece(Coordinates pos, Color color) {
                position_ = pos;
                color_ = color;
            };

            Coordinates position_;
            Color color_;
    };

} //namespace chess

#endif //PIECE_H