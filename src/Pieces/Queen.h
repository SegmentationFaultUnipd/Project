#ifndef QUEEN_H
#define QUEEN_H

#include <vector>

#include "Piece.h"
#include "../Board.h"
namespace chess {
    class Queen : public Piece {
        public:
            Queen(Coordinates coords, Color color) : Piece{coords, color} {};
            Queen(const Queen& obj) : Piece{obj.position_, obj.color_} {};
            bool canMoveAt(Coordinates pos, Board& board) const override;
            bool canMove(Board& board) const override;
            std::vector<Coordinates> legalMoves(Board& board) const override;
            Queen& operator=(const Queen& obj) { 
                position_ = obj.position_;
                color_ = obj.color_;
                return *this;
            }
            char ascii() const override { return 'D'; };
    };

} //namespace chess

#endif //QUEEN_H