#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <list>
#include <memory>
#include <assert.h>

#include "Pieces/Piece.h"
#include "Pieces/Knight.h"
#include "Pieces/King.h"
#include "Pieces/Rook.h"

#include "Color.h"

namespace chess {

    class Board {
        public:
            Board();

            bool isEmpty(Coordinates coords) const;

            Piece& at(Coordinates coords);
           
            void move(Coordinates from, Coordinates to);
            void tryMove(Coordinates from, Coordinates to);

            bool isThreatenBy(Coordinates coords, Color pieceColor);
            bool isKingInCheck(Color kingColor) const;

            // DA IMPLEMENTARE
			//void promote(Coordinates coords, char chosen_piece);

            std::vector<Coordinates> legalMovesOf(Piece& piece);
            std::list<Coordinates>& getPieces(Color color);

        private:
            std::unique_ptr<Piece> makePiece(Coordinates coords, char c);

            std::list<Coordinates> white_pieces_;
            std::list<Coordinates> black_pieces_;

            std::unique_ptr<Piece> board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, Board& board);

} //namespace chess

#endif //BOARD_H