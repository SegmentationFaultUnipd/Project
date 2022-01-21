#include "Queen.h"

bool chess::Queen::canMoveAt(Coordinates coords, Board& board) const {
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
    //Can't make a move that would cause a self check
    if(board.moveCauseSelfCheck(position_, coords)) {
        return false;
    }

    //MOVING LIKE A BISHOP
    short delta_file = coords.file - position_.file;
    short delta_rank = coords.rank - position_.rank;
    //Verify if the route is free
    if(abs(delta_file) == abs(delta_rank)) {
        Coordinates curr_pos = position_;
        Coordinates dir {delta_file/abs(delta_file), delta_rank/abs(delta_rank)};
        for(short i = 0; i < abs(delta_file); i++) {
            curr_pos += dir;
            if(!board.isEmpty(curr_pos)) {
                return false;
            }
        }
        return true;
    }

    //MOVING LIKE A ROOK
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

bool chess::Queen::canMove(Board& board) const {
    Coordinates coords;
    const std::vector<Coordinates> directions {
        {1,1}, {-1,1}, {-1,-1}, {1,-1},
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

std::vector<chess::Coordinates> chess::Queen::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    Coordinates coords;
    const std::vector<Coordinates> directions {
        {1,1}, {-1,1}, {-1,-1}, {1,-1},
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