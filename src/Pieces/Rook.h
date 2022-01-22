#ifndef ROOK_H
#define ROOK_H

#include <vector>

#include "Piece.h"
#include "../Board.h"
namespace chess {
    class Rook : public Piece {
		private:
			bool has_moved;
        public:
            Rook(Coordinates pos, Color color) : Piece{pos, color}, has_moved{false} {};
            Rook(const Rook& obj) : Piece{obj}, has_moved{obj.has_moved} {};
            bool canMoveAt(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
			void move (Coordinates new_position, Board& board) override;
            Rook& operator=(const Rook& obj) { 
                position_ = obj.position_;
                color_ = obj.color_;
                has_moved = obj.has_moved;
                return *this;
            }
            char ascii() const override { return 'T'; }
			bool hasMoved() const {return has_moved;}
    };
} //namespace chess
#endif //ROOK_H