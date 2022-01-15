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
    short delta_file = position_.file - coords.file;
    short delta_rank = position_.rank - coords.rank;
    //Verify if the route is free
    if(abs(delta_file) == abs(delta_rank)) {
        short x = position_.file, y = position_.rank;
        //Moving down-left
        if(delta_rank < 0 && delta_file > 0) {
            while(x > coords.file && y < coords.rank) {
                x--;
                y++;
                if(!board.isEmpty({x, y})) {
                    return false;
                }
            }
            return true;
        }
        //Moving down-right
        if(delta_rank < 0 && delta_file < 0) {
            while(x < coords.file && y < coords.rank) {
                x++;
                y++;
                if(!board.isEmpty({x, y})) {
                    return false;
                }
            }
            return true;
        }
        //Moving up-left
        if(delta_rank > 0 && delta_file > 0) {
            while(x > coords.file && y > coords.rank) {
                x--;
                y--;
                if(!board.isEmpty({x, y})) {
                    return false;
                }
            }
            return true;
        }
        //Moving up-right
        if(delta_rank > 0 && delta_file < 0) {
            while(x < coords.file && y > coords.rank) {
                x++;
                y--;
                if(!board.isEmpty({x, y})) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

bool chess::Bishop::canMove(Board& board) const {
    Coordinates coords;

    //UPPER VERTICALS
    //left
    coords.file = position_.file - 1;
    coords.rank = position_.rank - 1;
    while(coords.file >= 0 && coords.rank >= 0) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file--;
        coords.rank--;
    }
    //right
    coords.file = position_.file + 1;
    coords.rank = position_.rank - 1;
    while(coords.file < 8 && coords.rank >= 0) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file++;
        coords.rank--;
    }
    //LOWER VERTICALS
    //left
    coords.file = position_.file - 1;
    coords.rank = position_.rank + 1;
    while(coords.file >= 0 && coords.rank < 8) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file--;
        coords.rank++;
    }
    //right
    coords.file = position_.file + 1;
    coords.rank = position_.rank + 1;
    while(coords.file < 8 && coords.rank < 8) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file++;
        coords.rank++;
    }

    return false;
}

std::vector<chess::Coordinates> chess::Bishop::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    Coordinates coords;

    //UPPER VERTICALS
    //left
    coords.file = position_.file - 1;
    coords.rank = position_.rank - 1;
    while(coords.file >= 0 && coords.rank >= 0) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{coords.file, coords.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{coords.file, coords.rank});
        coords.file--;
        coords.rank--;
    }
    //right
    coords.file = position_.file + 1;
    coords.rank = position_.rank - 1;
    while(coords.file < 8 && coords.rank >= 0) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{coords.file, coords.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{coords.file, coords.rank});
        coords.file++;
        coords.rank--;
    }
    //LOWER VERTICALS
    //left
    coords.file = position_.file - 1;
    coords.rank = position_.rank + 1;
    while(coords.file >= 0 && coords.rank < 8) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{coords.file, coords.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{coords.file, coords.rank});
        coords.file--;
        coords.rank++;
    }
    //right
    coords.file = position_.file + 1;
    coords.rank = position_.rank + 1;
    while(coords.file < 8 && coords.rank < 8) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, coords.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, coords.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{coords.file, coords.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{coords.file, coords.rank});
        coords.file++;
        coords.rank++;
    }

    return moves;
}