#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "../Board.h"
#include <vector>

namespace chess {

    class King : public Piece {
		private:
			bool hasMoved;
        public:
            King(Coordinates pos, Color color) : Piece{pos, color} {hasMoved = false;};

			//bool hasMoved() {return hasMoved;}
			void firstMove() {hasMoved = true;}
			bool canCastle(short to_file, short to_rank, Board& board);
          	bool canMove(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            char ascii() const override { return 'R'; };
    };

} //namespace chess

#endif //KNIGHT_H