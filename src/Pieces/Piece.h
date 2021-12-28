#ifndef PIECE_H
#define PIECE_H

#include "../Color.h"

namespace chess {

    class Piece {
        public:
            Piece(short f, short r, Color c) : file_{f}, rank_{r}, color_{c} {};

            void inline move(short new_file, short new_rank) {
                file_ = new_file;
                rank_ = new_rank;
            };

            bool canMove(short to_file, short to_rank) { return true; }

            bool color() { return color_;}
            short file() { return file_; }
            short rank() { return rank_; }

        protected:
            short file_, rank_;
            Color color_;
    };

} //namespace chess

#endif //PIECE_H