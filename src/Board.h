#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <memory>

#include "Pieces/Piece.h"
#include "Pieces/Knight.h"
#include "Color.h"

namespace chess {

    class Board {
        public:
            Board();
            ~Board();

            Piece* at(short file, short rank);
            
            void move(short from_file, short from_rank, short to_file, short to_rank);
            
        private:
            //at(char file, short rank)
            std::vector<Piece*> white_pieces_;
            std::vector<Piece*> black_pieces_;
            Piece* board_[8][8];
    };

    std::ostream& operator<<(std::ostream& os, Board& board);

} //namespace chess

#endif //BOARD_H