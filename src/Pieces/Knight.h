#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include "Piece.h"
#include "../Board.h"
namespace chess {
	class Board;
    class Knight : public Piece {
        public:
            Knight(short file, short rank, Color color) : Piece{file, rank, color} {};
            Knight(char file, short rank, Color color) : Piece{file, rank, color} {};

            bool canMove(short to_file, short to_rank, Board& board) override;
            bool canMove(Board& board) override;
            std::vector<Coordinates> legalMoves(Board& board) override;
            char ascii() override { return 'C'; };
    };

} //namespace chess

#endif //KNIGHT_H