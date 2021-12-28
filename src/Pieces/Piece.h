#ifndef PIECE_H
#define PIECE_H

namespace chess {

class Piece {
    protected:
        short file_, rank_;
        bool is_white_;

    public:
        Piece(short f, short r, bool w) : file_{f}, rank_{r}, is_white_{w} {};

        void inline move(short new_file, short new_rank) {
            file_ = new_file;
            rank_ = new_rank;
        };

        bool canMove(short to_file, short to_rank, const Board& board) { return true; }

        bool isWhite() { return is_white_;}
        short file() { return file_; }
        short rank() { return rank_; }
   
};

} //namespace chess

#endif //PIECE_H