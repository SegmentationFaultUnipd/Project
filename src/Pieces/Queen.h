#ifndef QUEEN_H
#define QUEEN_H

#include <vector>

#include "Piece.h"
#include "../Board.h"
namespace chess {
    class Queen : public Piece {
        public:
            Queen(short file, short rank, Color color) : Piece{file, rank, color} {};
            Queen(char file, short rank, Color color) : Piece{file, rank, color} {};

            bool canMove(short to_file, short to_rank, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;

            char ascii() const override { return 'D'; };
    };

} //namespace chess

#endif //QUEEN_H