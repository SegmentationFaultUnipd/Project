#ifndef PAWN_H
#define PWAN_H

#include <vector>

#include "Piece.h"
#include "../Board.h"

namespace chess {
    class Board;
    class Pawn : public Piece {
        public:
            Pawn(short file, short rank, Color color) : Piece{file, rank, color}, hasMoved{false} {};
            Pawn(char file, short rank, Color color) : Piece{file, rank, color}, hasMoved{false} {};

            bool canMove(short to_file, short to_rank, Board& board) override;
            bool canMove(Board& board) override;
            std::vector<Coordinates> legalMoves(Board& board) override;

            char ascii() override { return 'P'; };

        protected:
            bool hasMoved;
    };
} //namespace chess

#endif //PAWN_H