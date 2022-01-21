#include "Rook.h"

bool chess::Rook::canMoveAt(Coordinates coords, Board& board) const {
    //Rook will only move horizontally or vertically
    //If it's moving vertically it will keep a fixed rank while changing the file and viceversa
    
    //Can't stay stationary
    if(position_ == coords) {
        return false;
    }
    //Can't land on a piece of the same color
    if (!board.isEmpty(coords) && board.at(coords).color() == this->color()) {
        return false;
    }
    //Can't make a move that would cause a self check
    if(board.moveCauseSelfCheck(position_, coords)) {
        return false;
    }

    //VERTICAL MOVEMENT
    if(coords.rank == position_.rank) {
        //Is moving down vertically
        if(coords.file > position_.file) {
            //Checking if the route is free
            for(int i = position_.file + 1; i < coords.file; i++){
                if(!board.isEmpty({i, position_.rank})) {
                    return false;
                }
            }
            return true;
        }
        //Is moving up vertically
        if(coords.file < position_.file) {
            for(int i = position_.file - 1; i > coords.file; i--) {
                if(!board.isEmpty({i, position_.rank})) {
                    return false;
                }
            }
            return true;
        }
    }
    //HORIZONTAL MOVEMENT
    if(coords.file == position_.file) {
        //Is moving right horizontally
        if(coords.rank > position_.rank) {
            for(int i = position_.rank + 1; i < coords.rank; i++) {
                if(!board.isEmpty({position_.file, i})) {
                    return false;
                }
            }
            return true;
        }
        //Is moving left horizontally
        if(coords.rank < position_.rank) {
            for(int i = position_.rank - 1; i > coords.rank; i--) {
                if(!board.isEmpty({position_.file, i})) {
                    return false;
                }
            }
            return true;
        }
    }

    return false;
}

bool chess::Rook::canMove(Board& board) const {
    Coordinates coords;
    const std::vector<Coordinates> directions {
        {0,1}, {-1,0}, {0,-1}, {1,0}
    };

    for(Coordinates dir : directions) {
    coords.file = position_.file + dir.file;
    coords.rank = position_.rank + dir.rank;
    while(coords.inBounderies()) {
            if(canMoveAt(coords, board)) {
                return true;
            }
        }
        coords.file += dir.file;
        coords.rank += dir.rank;
    }
    
    return false;
}

std::vector<chess::Coordinates> chess::Rook::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};
    Coordinates coords = position_;
    const std::vector<Coordinates> directions {
        {0,1}, {-1,0}, {0,-1}, {1,0}
    };

    for(Coordinates dir : directions) {
        coords.file = position_.file + dir.file;
        coords.rank = position_.rank + dir.rank;
        while(coords.inBounderies()) {
            //Can't move past an obstacle
            if(!board.isEmpty(coords)) {
                //Can move to eat a piece of different color
                if(board.at(coords).color() != this->color() && !board.moveCauseSelfCheck(position_, coords)) {
                    moves.push_back(coords);
                }
                break;
            }
            if(!board.moveCauseSelfCheck(position_, coords)) {
                moves.push_back(coords);
            }
            coords.file += dir.file;
            coords.rank += dir.rank;
        }
    }
    
    return moves;
}

void chess::Rook::move(Coordinates new_position) {
	position_ = new_position;
	has_moved = true;
}