#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <vector>

namespace chess {

    class King : public Piece {
        public:
            King(short file, short rank, Color color) : Piece{file, rank, color} {};
            King(char file, short rank, Color color) : Piece{file, rank, color} {};

            bool canMove(short to_file, short to_rank, Piece* board[8][8]) override;
            bool canMove(Piece* board[8][8]) override;
            std::vector<Coordinates> legalMoves(Piece* board[8][8]) override;
            char ascii() override { return 'R'; };
    };

} //namespace chess

#endif //KNIGHT_H