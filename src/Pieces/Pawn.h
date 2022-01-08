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
            
            void move (short file, short rank) {
                if(!hasMoved) hasMoved = true;
                position_.file = file;
                position_.rank = rank;
            }
            bool canMove(short to_file, short to_rank, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;

            char ascii() const override { return 'P'; };

        protected:
            bool hasMoved;
    };
} //namespace chess

#endif //PAWN_H