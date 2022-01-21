#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "../Board.h"
#include <vector>

namespace chess {

    class King : public Piece {
		private:
			bool has_moved;
            bool checkEmptyAndNotInCheck(chess::Board& board, int range, bool isKingSide) const;

        public:
            King(Coordinates pos, Color color) : Piece{pos, color}, has_moved{false} {};

			void move (Coordinates new_position) override;
			bool canCastle(Coordinates to_coords, Board& board) const;
          	bool canMoveAt(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Piece*> takeablePieces(chess::Board& board) const;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            char ascii() const override { return 'R'; }
			bool hasMoved() const {return has_moved;}
    };

} //namespace chess

#endif //KNIGHT_H