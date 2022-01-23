//AUTORE: Tommaso Leoni
#include "Bishop.h"

bool chess::Bishop::canMoveAt(Coordinates coords, Board& board) const {
    //Bishop can only move diagonally
    //To move diagonally it should move the same amount vertically and horizontally

    //Can't land on a piece of the same color
    if(!board.isEmpty(coords) && board.at(coords).color() == this->color()) {
        return false;
    }
    //Can' stay stationary
    if(position_ == coords) {
        return false;
    }
    
    //Getting the movement in each direction
    short delta_file = coords.file - position_.file;
    short delta_rank = coords.rank - position_.rank;
    //Verify if the route is free
    if(abs(delta_file) == abs(delta_rank)) {
        Coordinates curr_pos = position_;
        Coordinates dir {delta_file/abs(delta_file), delta_rank/abs(delta_rank)};
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

bool chess::Bishop::canMove(Board& board) const {
    Coordinates coords;
    const std::vector<Coordinates> directions {
        {1,1}, {-1,1}, {-1,-1}, {1,-1}
    };

    for(Coordinates dir : directions) {
        coords.file = position_.file + dir.file;
        coords.rank = position_.rank + dir.rank;
        while(coords.inBounderies()) {
            if(canMoveAt(coords, board)
                && !board.isKingInCheckAfterMove(position_, coords)) {
                return true;
            }
            coords.file += dir.file;
            coords.rank += dir.rank;
        }
    }
    
    return false;
}

std::vector<chess::Coordinates> chess::Bishop::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    Coordinates coords;
    const std::vector<Coordinates> directions {
        {1,1}, {-1,1}, {-1,-1}, {1,-1}
    };

    for(Coordinates dir : directions) {
        coords.file = position_.file + dir.file;
        coords.rank = position_.rank + dir.rank;
        while(coords.inBounderies()) {
            //Can't move past an obstacle
            if(!board.isEmpty(coords)) {
                //Can move to eat a piece of different color
                if(board.isOppositeColor(coords, this->color())) {
                    moves.push_back(coords);
                }
                break;
            }
            moves.push_back(coords);
            coords.file += dir.file;
            coords.rank += dir.rank;
        }
    }
    
    return moves;
}