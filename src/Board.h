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
#include "Coordinates.h"

namespace chess {

    class Board {
        public:
            Board();

            bool isEmpty(Coordinates coords) const;
            Piece& at(Coordinates coords);
            
            std::vector<Coordinates> legalMovesOf(Piece& piece);
            std::list<Coordinates>& getPieces(Color color);
           
            bool move(Coordinates from, Coordinates to);
            bool tryMove(Coordinates from, Coordinates to);

            bool isThreatened(Coordinates coords, Color pieceColor);
            bool isKingInCheck(Color kingColor);

            // Special moves
			void promote(Coordinates pawn, char piece);

            bool castle(Coordinates from, Coordinates to);
            bool enPassant(Coordinates from, Coordinates to);

            bool isCastlingMove(Coordinates from, Coordinates to);
            bool isEnPassantMove(Coordinates from, Coordinates to);

            void addToAvailableEnPassants(Coordinates from, Coordinates to);
            void emptyEnPassant();
        private:
            std::unique_ptr<Piece> makePiece(char c, Coordinates coords, Color pieceColor) const;
            std::unique_ptr<Piece> copyPiece(Piece& p) const;

            bool updatePosition(Coordinates from, Coordinates to);

            std::list<Coordinates> white_pieces_;
            std::list<Coordinates> black_pieces_;

            std::list<std::pair<Coordinates, Coordinates>> availableEnPassants_;

            std::unique_ptr<Piece> board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, Board& board);

} //namespace chess

#endif //BOARD_H