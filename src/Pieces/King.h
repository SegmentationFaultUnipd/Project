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
            King(short file, short rank, Color color) : Piece{file, rank, color} {hasMoved = false;};
            King(char file, short rank, Color color) : Piece{file, rank, color} {hasMoved = false;};

			bool hasMoved() {return hasMoved;}
			void firstMove() {hasMoved = true;}
			bool canCastle(short to_file, short to_rank, Board& board);
          	bool canMove(short to_file, short to_rank, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            char ascii() const override { return 'R'; };
    };

} //namespace chess

#endif //KNIGHT_H