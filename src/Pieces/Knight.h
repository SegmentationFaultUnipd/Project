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
            Knight(Coordinates pos, Color color) : Piece{pos, color} {};

            bool canMoveAt(Coordinates coords, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            std::vector<Piece*> takeablePieces(Board& board) const override;

            char ascii() const override { return 'C'; };
        private:
            const std::vector<Coordinates> candidateMoves_() const;
    };

} //namespace chess

#endif //KNIGHT_H