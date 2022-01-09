#ifndef ROOK_H
#define ROOK_H

#include <vector>

#include "Piece.h"
#include "../Board.h"
namespace chess {
    class Rook : public Piece {
        public:
            Rook(Coordinates pos, Color color) : Piece{pos, color} {};

            bool canMove(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
      
            char ascii() const override { return 'T'; };
    };
} //namespace chess
#endif //ROOK_H