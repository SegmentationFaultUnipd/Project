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
            Piece& at(Coordinates coords) const;
            
            const std::vector<Coordinates> legalMovesOf(Piece& piece);
            std::list<Coordinates>& getPieceCoords(Color color);
            Piece& getKing(Color king_color);
           
            bool move(Coordinates from, Coordinates to);
            bool doesMoveCauseSelfCheck(Coordinates from, Coordinates to);

            bool isThreatened(Coordinates piece_coords, Color piece_color);
            bool isKingInCheck(Color king_color);

            bool isReachableBy(Coordinates landing_square, const Piece& piece) const;
            bool isTakingAPiece(Coordinates landing_square, const Piece& piece) const;

            // Special moves ---------------------------------------------
			void promote(Coordinates pawn, char piece);

            bool isCastlingMove(Coordinates from, Coordinates to);
            bool doCastlingMove(Coordinates from, Coordinates to);

            bool isEnPassantMove(Coordinates from, Coordinates to);
            bool doEnPassantMove(Coordinates from, Coordinates to);

            void addAvailableEnPassant(Coordinates from, Coordinates to);
            void clearEnPassants();

        private:
            std::unique_ptr<Piece> makePiece(char c, Coordinates coords, Color color) const;
            std::unique_ptr<Piece> copyPiece(Piece& p) const;

            bool updatePosition(Coordinates from, Coordinates to);

            std::list<Coordinates> white_coords_;
            std::list<Coordinates> black_coords_;

            std::list<std::pair<Coordinates, Coordinates>> available_en_passants_;

            std::unique_ptr<Piece> board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, Board& board);

} //namespace chess

#endif //BOARD_H