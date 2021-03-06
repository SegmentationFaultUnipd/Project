/**
 * @file Knight.h
 * @author Filippo Mazzarotto
 * @date 2022-01-23
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include <memory>

#include "Piece.h"
#include "../Board.h"

namespace chess {
	class Board;
    /**
     * @brief Rappresenta un pezzo di tipo cavallo
     * 
     */
    class Knight : public Piece {
        public:
            Knight(Coordinates pos, Color color) : Piece{pos, color} {};
            Knight(const Knight &obj) : Piece{obj.position_, obj.color_} {};
            
            Knight& operator=(const Knight& obj) {
                position_ = obj.position_;
                return *this;
            }
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