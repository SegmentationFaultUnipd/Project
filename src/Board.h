#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <list>
#include <memory>
#include <assert.h>

#include "Pieces/Pieces.h"
#include "Color.h"

namespace chess {

    class Board {
        public:
            Board();

            bool isEmpty(short file, short rank) const;
            bool isEmpty(Coordinates coords) const;
            Piece& at(short file, short rank);
            Piece& at(Coordinates coords);
           
            bool move(short from_file, short from_rank, short to_file, short to_rank);
            bool move(Coordinates from, Coordinates to);
            std::vector<Coordinates> legalMovesOf(Piece& piece);
            
            std::list<Coordinates>& getPieces(Color color);
			void promote(Coordinates coords, char chosen_piece);

            bool threatenBy(Coordinates coords, Color attackerColor);
            bool isKingInCheck(Color kingColor) const;

        private:
            std::list<Coordinates> white_pieces_;
            std::list<Coordinates> black_pieces_;

            std::unique_ptr<Piece> board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, const Board& board);

} //namespace chess

#endif //BOARD_H