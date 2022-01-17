#ifndef PAWN_H
#define PAWN_H

#include <vector>

#include "Piece.h"
#include "../Board.h"

namespace chess {
    class Board;
    class Pawn : public Piece {
        public:
            Pawn(Coordinates pos, Color color) : Piece{pos, color}, hasMoved{false} {};

            bool canMoveAt(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            void move(Coordinates new_position) override;
            char ascii() const override { return 'P'; };

        protected:
            bool hasMoved;
    };
} //namespace chess

#endif //PAWN_H