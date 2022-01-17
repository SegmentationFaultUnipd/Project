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
            Rook(Coordinates pos, Color color) : Piece{pos, color} {};

            bool canMoveAt(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
			void move (Coordinates new_position) override;
            char ascii() const override { return 'T'; }
			bool hasMoved() const {return has_moved;}
    };
} //namespace chess
#endif //ROOK_H