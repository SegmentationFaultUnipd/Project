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
			bool isInCheck(short king_file, short king_rank, Board& board); //return true if the king would be in check in a particular position. Temporarily modifies the board before restoring it in 
          	bool canMove(short to_file, short to_rank, Board& board) override;
            bool canMove(Board& board) override;
            std::vector<Coordinates> legalMoves(Board& board) override;
            char ascii() override { return 'R'; };
    };

} //namespace chess

#endif //KNIGHT_H