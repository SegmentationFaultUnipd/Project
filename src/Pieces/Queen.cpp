/**
 * @file Queen.cpp
 * @author Tommaso Leoni
 * @date 2022-01-23
 */

#include "Queen.h"

bool chess::Queen::canMoveAt(Coordinates coords, Board& board) const {
    //Queen can move as much as she wants both horizontally, vertically or diagonally
    //It mixes the movement of a Bishop with the move of a Rook
    //Can't land on a piece of the same color
    if(!board.isEmpty(coords) && board.at(coords).color() == this->color()) {
        return false;
    }
    //Can' stay stationary
    if(position_.file == coords.file && position_.rank == coords.rank) {
        return false;
    }

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
    else if(delta_rank == 0){
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
            if (canMoveAt(coords, board)
                && !board.isKingInCheckAfterMove(position_, coords)) {
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
