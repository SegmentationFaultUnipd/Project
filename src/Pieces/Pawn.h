#ifndef PAWN_H
#define PAWN_H

#include <vector>

#include "Piece.h"
#include "../Board.h"

namespace chess {
    class Board;
    class Pawn : public Piece {
        public:
            Pawn(Coordinates pos, Color color) : Piece{pos, color}, has_moved{false} {};
            Pawn(const Pawn& obj) : Piece{obj.position_, obj.color_}, has_moved{obj.has_moved} {};
            bool canMoveAt(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            void move(Coordinates new_position) override;
            Pawn& operator=(Pawn& obj) { 
                position_ = obj.position_;
                color_ = obj.color_;
                has_moved = obj.has_moved;
            }
            char ascii() const override { return 'P'; };

        protected:
            bool has_moved;
    };
} //namespace chess

#endif //PAWN_H