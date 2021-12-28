#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "stdlib.h"

namespace chess {

    class Knight : public Piece {
        public:
            Knight(short file, short rank, Color color) : Piece{file, rank, color} {};
            Knight(char file, short rank, Color color) : Piece{file, rank, color} {};

            bool canMove(short to_file, short to_rank, Piece* board[8][8]) override;
            bool canMove(Piece* board[8][8]) override;
            std::vector<Coordinates> legalMoves(Piece* board[8][8]) override;
            char ascii() override { return 'C'; };
    };

} //namespace chess

#endif //KNIGHT_H