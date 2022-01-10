#ifndef BISHOP_H
#define BISHOP_H

#include <vector>

#include "Piece.h"
#include "../Board.h"
namespace chess {
    class Bishop : public Piece {
        public:
            Bishop(Coordinates coords, Color color) : Piece{coords, color} {};

            bool canMove(Coordinates pos, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;

            char ascii() const override { return 'A'; };
    };

} //namespace chess

#endif //BISHOP_H