#include "Rook.h"

bool chess::Rook::canMove(short to_file, short to_rank, Board& board) {
    //Rook will only move horizontally or vertically
    //If it's moving vertically it will keep a fixed rank while changing the file and viceversa
    
    //Can't land on a piece of the same color
    if(board.at(to_file, position_.rank)->color() == this->color()) {
        return false;
    }

    //VERTICAL MOVEMENT
    if(to_rank == position_.rank) {
        //Is moving down vertically
        if(to_file > position_.file) {
            //Checking if the route is free
            for(int i = position_.file + 1; i < to_file; i++){
                if(board.at(i, position_.rank) != nullptr) {
                    return false;
                }
            }
            return true;
        }
        //Is moving up vertically
        if(to_file < position_.file) {
            for(int i = position_.file - 1; i > to_file; i--) {
                if(board.at(i, position_.rank) != nullptr) {
                    return false;
                }
            }
            return true;
        }
    }
    //HORIZONTAL MOVEMENT
    if(to_file == position_.file) {
        //Is moving right horizontally
        if(to_rank > position_.rank) {
            for(int i = position_.rank + 1; i < to_rank; i++) {
                if(board.at(position_.file, i) != nullptr) {
                    return false;
                }
            }
            return true;
        }
        //Is moving left horizontally
        if(to_rank < position_.rank) {
            for(int i = position_.rank - 1; i > to_rank; i--) {
                if(board.at(position_.file, i) != nullptr) {
                    return false;
                }
            }
            return true;
        }
    }

    return false;
}

bool chess::Rook::canMove(Board& board) {
    short to_file, to_rank;

    //HORIZONTAL MOVEMENT
    //Right
    to_file = position_.file + 1;
    while(to_file < 8) {
        //Can't move past an obstacle
        if(board.at(to_file, position_.rank) != nullptr) {
            //Can move to eat a piece of different color
            if(board.at(to_file, position_.rank)->color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        to_file++;
    }
    //Left
    to_file = position_.file - 1;
    while(to_file >= 0) {
        if(board.at(to_file, position_.rank) != nullptr) {
            if(board.at(to_file, position_.rank)->color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        to_file--;
    }
    
    //VERTICAL MOVEMENT
    //Down
    to_rank = position_.rank + 1;
    while(to_file < 8) {
        if(board.at(position_.file, to_rank) != nullptr) {
            if(board.at(position_.file, to_rank)->color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        to_file++;
    }
    //Up
    to_rank = position_.rank - 1;
    while(to_file >= 0) {
        if(board.at(position_.file, to_rank) != nullptr) {
            if(board.at(position_.file, to_rank)->color() != this->color()) {
                return true;
            }
            break;
        }
        return true;
        to_file--;
    }

    return false;
}

std::vector<chess::Coordinates> chess::Rook::legalMoves(Board& board) {
    std::vector<chess::Coordinates> moves = {};
    short to_file, to_rank;

    //HORIZONTAL MOVEMENT
    //Right
    to_file = position_.file + 1;
    while(to_file < 8) {
        //Can't move past an obstacle
        if(board.at(to_file, position_.rank) != nullptr) {
            //Can move to eat a piece of different color
            if(board.at(to_file, position_.rank)->color() != this->color()) {
                moves.push_back(chess::Coordinates{to_file, position_.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{to_file, position_.rank});
        to_file++;
    }
    //Left
    to_file = position_.file - 1;
    while(to_file >= 0) {
        if(board.at(to_file, position_.rank) != nullptr) {
            if(board.at(to_file, position_.rank)->color() != this->color()) {
                moves.push_back(chess::Coordinates{to_file, position_.rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{to_file, position_.rank});
        to_file--;
    }
    
    //VERTICAL MOVEMENT
    //Down
    to_rank = position_.rank + 1;
    while(to_file < 8) {
        if(board.at(position_.file, to_rank) != nullptr) {
            if(board.at(position_.file, to_rank)->color() != this->color()) {
                moves.push_back(chess::Coordinates{position_.file, to_rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{position_.file, to_rank});
        to_file++;
    }
    //Up
    to_rank = position_.rank - 1;
    while(to_file >= 0) {
        if(board.at(position_.file, to_rank) != nullptr) {
            if(board.at(position_.file, to_rank)->color() != this->color()) {
                moves.push_back(chess::Coordinates{position_.file, to_rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{position_.file, to_rank});
        to_file--;
    }

    return moves;
}