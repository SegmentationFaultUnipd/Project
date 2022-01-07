#ifndef ROOK_H
#define ROOK_H

#include <vector>

#include "Piece.h"
#include "../Board.h"
namespace chess {
    class Rook : public Piece {
        public:
            Rook(short file, short rank, Color color) : Piece{file, rank, color} {};
            Rook(char file, short rank, Color color) : Piece{file, rank, color} {};

            bool canMove(short to_file, short to_rank, Board& board) override;
            bool canMove(Board& board) override;
            std::vector<Coordinates> legalMoves(Board& board) override;
      
            char ascii() override { return 'T'; };
    };
} //namespace chess
#endif //ROOK_H