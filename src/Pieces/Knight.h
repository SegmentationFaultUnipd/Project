#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include <memory>

#include "Piece.h"
#include "../Board.h"

namespace chess {
	class Board;
    class Knight : public Piece {
        public:
            Knight(short file, short rank, Color color) : Piece{file, rank, color} {};
            Knight(char file, short rank, Color color) : Piece{file, rank, color} {};

            bool canMove(short to_file, short to_rank, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            //std::vector<Coordinates> takeablePieces(Board& board) const override;
      
            char ascii() const override { return 'C'; };
    };

} //namespace chess

#endif //KNIGHT_H