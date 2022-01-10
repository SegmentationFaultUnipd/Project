#include "Queen.h"

bool chess::Queen::canMove(Coordinates coords, Board& board) const {
    //Queen can move as much as she wants both horizontally, vertically or diagonally
    //It mixes the movement of a Bishop with the move of a Rook

    //Can't land on a piece of the same color
    if(!board.isEmpty({coords.file, position_.rank}) && board.at({coords.file, position_.rank}).color() == this->color()) {
        return false;
    }
    //Can' stay stationary
    if(position_.file == coords.file && position_.rank == coords.rank) {
        return false;
    }


}