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
            const Piece& at(Coordinates coords) const;
            Piece& at(Coordinates coords);

            const std::vector<Coordinates> legalMovesOf(Piece& piece);
            std::list<Coordinates>& getPiecesCoords(Color color);
            Piece& getKing(Color king_color);
           
            bool move(Coordinates from, Coordinates to);

            bool isThreatened(Coordinates piece_coords, Color piece_color);
            bool isKingInCheck(Color king_color);

            bool isEmptyOrOppositeColor(Coordinates landing_square, Color piece_color) const;
            bool isOppositeColor(Coordinates landing_square, Color piece_color) const;

            // Special moves ---------------------------------------------
            void addAvailableEnPassant(Coordinates from, Coordinates to);
            
			void promote(Coordinates pawn, char piece);

            bool isCastlingMove(Coordinates from, Coordinates to);
            void doCastlingMove(Coordinates from, Coordinates to);

            bool isEnPassantMove(Coordinates from, Coordinates to);
            void doEnPassantMove(Coordinates from, Coordinates to);

        private:
            void addPiece_(char piece_ascii, Coordinates coords, Color color);
            void addPieceToMatrix_(std::unique_ptr<Piece>& attacking_piece_color, Coordinates coords);
            void addPieceCoords_(Coordinates coords);

            void clearEnPassants_(Color attacking_piece_color);

            void removePiece_(Coordinates coords);

            std::unique_ptr<Piece> makePiece_(char c, Coordinates coords, Color color) const;
            std::unique_ptr<Piece> clonePiece_(const Piece& p) const;

            void updatePosition_(Coordinates from, Coordinates to);

            std::list<Coordinates> white_coords_;
            std::list<Coordinates> black_coords_;

            std::list<std::pair<Coordinates, Coordinates>> available_en_passants_;

            std::unique_ptr<Piece> board_[8][8];

            struct State {
                std::unique_ptr<Piece> board[8][8];
                std::list<Coordinates> white_coords;
                std::list<Coordinates> black_coords;
            };
            State getCurrentState_();
            void restoreState_(State& state);
            std::unique_ptr<Piece>** copyPieceMatrix_(std::unique_ptr<Piece> to_copy[8][8]);
    };

    std::ostream& operator<<(std::ostream& os, const Board& board);

} //namespace chess

#endif //BOARD_H