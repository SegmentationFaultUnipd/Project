#include "Queen.h"

bool chess::Queen::canMove(Coordinates coords, Board& board) const {
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
}

bool chess::Queen::canMove(Board& board) const {
    Coordinates coords;

    //MOVING LIKE A BISHOP 
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
    
    //MOVING LIKE A ROOK
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

std::vector<chess::Coordinates> chess::Queen::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    Coordinates coords;
    
    //BISHOP MOVES
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
    
    //ROOK MOVES
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