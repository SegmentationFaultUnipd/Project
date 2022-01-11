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
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"

#include "Color.h"

namespace chess {

    class Board {
        public:
            Board();

            bool isEmpty(Coordinates coords) const;

            Piece& at(Coordinates coords);
           
            bool move(Coordinates from, Coordinates to);
            bool tryMove(Coordinates from, Coordinates to);

            bool isThreaten(Coordinates coords, Color pieceColor);
            bool isKingInCheck(Color kingColor);

            // DA IMPLEMENTARE
			//void promote(Coordinates coords, char chosen_piece);
            bool castle(Coordinates from, Coordinates to);

            std::vector<Coordinates> legalMovesOf(Piece& piece);
            std::list<Coordinates>& getPieces(Color color);

        private:
            std::unique_ptr<Piece> makePiece(char c, Coordinates coords, Color pieceColor);
            std::unique_ptr<Piece> copyPiece(Piece& p);

            bool updatePosition(Coordinates from, Coordinates to);

            std::list<Coordinates> white_pieces_;
            std::list<Coordinates> black_pieces_;

            std::unique_ptr<Piece> board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, Board& board);

} //namespace chess

#endif //BOARD_H