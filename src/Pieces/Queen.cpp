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

    //MOVING LIKE A BISHOP 
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
    
    //MOVING LIKE A ROOK
    short i;
    //HORIZONTAL MOVEMENT
    i = 1;
    while(i > -2) {
        coords.file += i;
        while(coords.inBounderies()) {
            if(canMoveAt(coords, board)) {
                return true;
            }
            coords.file += i;
        }
        coords.file = position_.file;
        i -= 2;
    }
    //VERTICAL MOVEMENT
    i = 1;
    while(i > -2) {
        coords.rank += i;
        while(coords.inBounderies()) {
            if(canMoveAt(coords,board)) {
                return true;
            }
            coords.rank += i;
        }
        coords.rank = position_.rank;
        i -= 2;
    }

    return false;
}

std::vector<chess::Coordinates> chess::Queen::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    Coordinates coords;
    
    //BISHOP MOVES
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

    //ROOK MOVES
    short i;
    //HORIZONTAL MOVEMENT
    i = 1;
    while(i > -2) {
        coords.file += i;
        while(coords.inBounderies()) {
            //Can't move past an obstacle
            if(!board.isEmpty(coords)) {
                //Can move to eat a piece of different color
                if(board.at(coords).color() != this->color() && !board.moveCauseSelfCheck(position_, coords)) {
                    std::cout << coords << " is a legal moves\n";
                    moves.push_back(coords);
                }
                break;
            }
            if(!board.moveCauseSelfCheck(position_, coords)) {
                std::cout << coords << " is a legal moves\n";
                moves.push_back(coords);
            }
            coords.file += i;
        }
        coords.file = position_.file;
        i -= 2;
    }
    //VERTICAL MOVEMENT
    i = 1;
    while(i > -2) {
        coords.rank += i;
        while(coords.inBounderies()) {
            if(!board.isEmpty(coords)) {
                if(board.at(coords).color() != this->color() && !board.moveCauseSelfCheck(position_, coords)) {
                    std::cout << coords << " is a legal moves\n";
                    moves.push_back(coords);
                }
                break;
            }
            if(!board.moveCauseSelfCheck(position_, coords)) {
                    std::cout << coords << " is a legal moves\n";
                moves.push_back(coords);
            }
            coords.rank += i;
        }
        coords.rank = position_.rank;
        i -= 2;
    }

    return moves;
}