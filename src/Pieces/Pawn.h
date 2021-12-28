#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"

namespace chess {

class Pawn : public Piece{
    private:
        bool has_moved_;
    public:
        Pawn(short f, short r, bool w) : file_{f}, rank_{r}, is_white_{w} has_moved_{false} {};
        bool canMove(short to_file, short to_rank, const Board& board);
};
}

#endif