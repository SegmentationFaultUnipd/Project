#include "Bishop.h"

bool chess::Bishop::canMoveAt(Coordinates coords, Board& board) const {
    std::cout << "checking";
    //Bishop can only move diagonally
    //To move diagonally it should move the same amount vertically and horizontally

    //Can't land on a piece of the same color
    if(!board.isEmpty(coords) && board.at(coords).color() == this->color()) {
        std::cout << coords << std::endl;
        std::cout << board.at(coords).ascii() << std::endl;
        return false;
    }
    //Can' stay stationary
    if(position_ == coords) {
        std::cout << "2\n";
        return false;
    }
    //Can't make a move that would cause a self check
    if(board.moveCauseSelfCheck(position_, coords)) {
        std::cout << "3\n";
        return false;
    }
    
    //Getting the movement in each direction
    short delta_file = coords.file - position_.file;
    short delta_rank = coords.rank - position_.rank;
    //Verify if the route is free
    if(abs(delta_file) == abs(delta_rank)) {
        short x = position_.file, y = position_.rank;
        //Moving down-left
        if(delta_rank < 0 && delta_file > 0) {
            while(x > coords.file && y < coords.rank) {
                x--;
                y++;
                if(!board.isEmpty({x, y})) {
                    std::cout << "4\n";
                    return false;
                }
            }
            std::cout << "5\n";
            return true;
        }
        //Moving down-right
        if(delta_rank < 0 && delta_file < 0) {
            while(x < coords.file && y < coords.rank) {
                x++;
                y++;
                if(!board.isEmpty({x, y})) {
                    std::cout << "6\n";
                    return false;
                }
            }
            std::cout << "7\n";
            return true;
        }
        //Moving up-left
        if(delta_rank > 0 && delta_file > 0) {
            while(x > coords.file && y > coords.rank) {
                x--;
                y--;
                if(!board.isEmpty({x, y})) {
                    return false;
                    std::cout << "8\n";
                }
            }
            std::cout << "9\n";
            return true;
        }
        //Moving up-right
        if(delta_rank > 0 && delta_file < 0) {
            while(x < coords.file && y > coords.rank) {
                x++;
                y--;
                if(!board.isEmpty({x, y})) {
                    std::cout << "10\n";
                    return false;
                }
            }
            std::cout << "11\n";
            return true;
        }
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
            if(canMoveAt(coords, board)) {
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