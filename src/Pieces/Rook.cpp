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

    //Getting the movement in each direction
    short delta_file = coords.file - position_.file;
    short delta_rank = coords.rank - position_.rank;
    //Verify if the route is free
    if(delta_file == 0) {
        Coordinates curr_pos = position_;
        Coordinates dir {0, delta_rank/abs(delta_rank)};
        for(short i = 0; i < abs(delta_rank) - 1; i++) {
            curr_pos += dir;
            if(!board.isEmpty(curr_pos)) {
                return false;
            }
        }
        return true;
    }
    else if (delta_rank == 0){
        Coordinates curr_pos = position_;
        Coordinates dir {delta_file/abs(delta_file), 0};
        for(short i = 0; i < abs(delta_file) - 1; i++) {
            curr_pos += dir;
            if(!board.isEmpty(curr_pos)) {
                return false;
            }
        }
        return true;
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
            coords.file += dir.file;
            coords.rank += dir.rank;
        }
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