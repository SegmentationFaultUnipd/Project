#include "Queen.h"

bool chess::Queen::canMove(short to_file, short to_rank, Board& board) const {
    //Queen can move as much as she wants both horizontally, vertically or diagonally
    //It mixes the movement of a Bishop with the move of a Rook

    //Can't land on a piece of the same color
    if(board.at(to_file, position_.rank).color() == this->color()) {
        return false;
    }
    //Can' stay stationary
    if(position_.file == to_file && position_.rank == to_rank) {
        return false;
    }

    
}