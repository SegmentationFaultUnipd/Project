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

    //HORIZONTAL MOVEMENT
    //Right
    coords.file = position_.file + 1;
    while(coords.file < 8) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, position_.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, position_.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file++;
    }
    //Left
    coords.file = position_.file - 1;
    while(coords.file >= 0) {
        if(!board.isEmpty({coords.file, position_.rank})) {
            if(board.at({coords.file, position_.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file--;
    }
    
    //VERTICAL MOVEMENT
    //Down
    coords.rank = position_.rank + 1;
    while(coords.file < 8) {
        if(!board.isEmpty({position_.file, coords.rank})) {
            if(board.at({position_.file, coords.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file++;
    }
    //Up
    coords.rank = position_.rank - 1;
    while(coords.file >= 0) {
        if(!board.isEmpty({position_.file, coords.rank})) {
            if(board.at({position_.file, coords.rank}).color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        coords.file--;
    }

    return false;
}

std::vector<chess::Coordinates> chess::Rook::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};
    Coordinates coords;

    //HORIZONTAL MOVEMENT
    //Right
    coords.file = position_.file + 1;
    while(coords.file < 8) {
        //Can't move past an obstacle
        if(!board.isEmpty({coords.file, position_.rank})) {
            //Can move to eat a piece of different color
            if(board.at({coords.file, position_.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{coords.file, position_.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{coords.file, position_.rank});
        coords.file++;
    }
    //Left
    coords.file = position_.file - 1;
    while(coords.file >= 0) {
        if(!board.isEmpty({coords.file, position_.rank})) {
            if(board.at({coords.file, position_.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{coords.file, position_.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{coords.file, position_.rank});
        coords.file--;
    }
    
    //VERTICAL MOVEMENT
    //Down
    coords.rank = position_.rank + 1;
    while(coords.rank < 8) {
        if(!board.isEmpty({position_.file, coords.rank})) {
            if(board.at({position_.file, coords.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{position_.file, coords.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{position_.file, coords.rank});
        coords.file++;
    }
    //Up
    coords.rank = position_.rank - 1;
    while(coords.rank >= 0) {
        if(!board.isEmpty({position_.file, coords.rank})) {
            if(board.at({position_.file, coords.rank}).color() != this->color()) {
                moves.push_back(chess::Coordinates{position_.file, coords.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{position_.file, coords.rank});
        coords.file--;
    }

    return moves;
}