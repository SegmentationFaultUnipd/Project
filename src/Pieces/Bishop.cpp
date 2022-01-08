#include "Bishop.h"

bool chess::Bishop::canMove(short to_file, short to_rank, Board& board) const {
    //Bishop can only move diagonally
    //To move diagonally it should move the same amount vertically and horizontally

    //Can't land on a piece of the same color
    if(board.at(to_file, position_.rank).color() == this->color()) {
        return false;
    }
    //Can' stay stationary
    if(position_.file == to_file && position_.rank == to_rank) {
        return false;
    }
    
    //Getting the movement in each direction
    short delta_file = position_.file - to_file;
    short delta_rank = position_.rank - to_rank;
    //Verify if the route is free
    if(delta_file == delta_rank || delta_file == -delta_rank) {
        short x = position_.file, y = position_.rank;
        //Moving down-left
        if(delta_rank < 0 && delta_file > 0) {
            while(x > to_file && y < to_rank) {
                if(!board.isEmpty(x, y)) {
                    return false;
                }
                x--;
                y++;
            }
            return true;
        }
        //Moving down-right
        if(delta_rank < 0 && delta_file < 0) {
            while(x < to_file && y < to_rank) {
                if(!board.isEmpty(x, y)) {
                    return false;
                }
                x++;
                y++;
            }
            return true;
        }
        //Moving up-left
        if(delta_rank > 0 && delta_file > 0) {
            while(x > to_file && y > to_rank) {
                if(!board.isEmpty(x, y)) {
                    return false;
                }
                x--;
                y--;
            }
            return true;
        }
        //Moving up-right
        if(delta_rank > 0 && delta_file < 0) {
            while(x < to_file && y > to_rank) {
                if(!board.isEmpty(x, y)) {
                    return false;
                }
                x++;
                y--;
            }
            return true;
        }
    }
}

std::vector<chess::Coordinates> chess::Bishop::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    short to_file, to_rank;

    //UPPER VERTICALS
    //left
    to_file = position_.file - 1;
    to_rank = position_.rank - 1;
    while(to_file >= 0 && to_rank >= 0) {
        //Can't move past an obstacle
        if(!board.isEmpty(to_file, to_rank)) {
            //Can move to eat a piece of different color
            if(board.at(to_file, to_rank).color() != this->color()) {
                moves.push_back(chess::Coordinates{to_file, to_rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{to_file, to_rank});
        to_file--;
        to_rank--;
    }
    //right
    to_file = position_.file + 1;
    to_rank = position_.rank - 1;
    while(to_file < 8 && to_rank >= 0) {
        //Can't move past an obstacle
        if(!board.isEmpty(to_file, to_rank)) {
            //Can move to eat a piece of different color
            if(board.at(to_file, to_rank).color() != this->color()) {
                moves.push_back(chess::Coordinates{to_file, to_rank});
            }
            break;
        }
        moves.push_back(chess::Coordinates{to_file, to_rank});
        to_file++;
        to_rank--;
    }
    //LOWER VERTICALS
    //left
    


}