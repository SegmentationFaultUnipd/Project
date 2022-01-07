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

            bool isEmpty(short file, short rank);
            bool isEmpty(Coordinates coords);
            Piece& at(short file, short rank);
            Piece& at(Coordinates coords);
           
            void move(short from_file, short from_rank, short to_file, short to_rank);
            std::vector<Coordinates> legalMovesOf(Piece& piece);
            
            std::list<Coordinates>& getPieces(Color color);

            bool isInCheck(Coordinates coord, Color color);
            bool isKingInCheck(Color color);

        private:
            std::list<Coordinates> white_pieces_;
            std::list<Coordinates> black_pieces_;

            std::unique_ptr<Piece> board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, Board& board);

} //namespace chess

#endif //BOARD_H