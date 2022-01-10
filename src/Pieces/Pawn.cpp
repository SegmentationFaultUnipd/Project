#include "Pawn.h"

void chess::Pawn::move(Coordinates new_position) {
    position_ = new_position;
    hasMoved = true;
}

bool chess::Pawn::canMove(Coordinates coords, Board& board) const {
    //The pawn can make 3 different moves, 1 only if it hasn't yet moved

    //Can't stay stationary
    if(position_ == coords) {
        return false;
    }
    //Can't land on a piece of the same color
    if (!board.isEmpty(coords) && board.at(coords).color() == this->color()) {
        return false;
    }
    
    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {

        //The pawn moves two steps forward (if it hasn't yet moved)
        bool two_up = coords.file == position_.file && coords.rank == (position_.rank + 2);
        if(two_up && !hasMoved && board.isEmpty(coords) && board.isEmpty({coords.file, position_.rank + 1})) {
            return true;
        }
        
        //The pawn moves one step forward (if the tile is free)
        bool one_up = coords.file == position_.file && coords.rank == (position_.rank + 1);
        if(one_up && board.isEmpty(coords)) {
            return true;
        }

        //The pawn moves diagonally (if there's a opponent piece to eat)
        bool diag_right = coords.file == (position_.file + 1) && coords.rank == (position_.rank + 1);
        bool diag_left = coords.file == (position_.file - 1) && coords.rank == (position_.rank + 1);
        if((diag_right || diag_left) && !board.isEmpty(coords) && board.at(coords).color() == chess::BLACK) {
            return true;
        }

        return false;
    }
    //THE PAWN IS BLACK
    else {
        //The pawn moves two steps forward (if it hasn't yet moved)
        bool two_up = coords.file == position_.file && coords.rank == (position_.rank - 2);
        if(two_up && !hasMoved && board.isEmpty(coords) && board.isEmpty({coords.file, position_.rank - 1})) {
            return true;
        }
        
        //The pawn moves one step forward (if the tile is free)
        bool one_up = coords.file == position_.file && coords.rank == (position_.rank - 1);
        if(one_up && board.isEmpty(coords)) {
            return true;
        }

        //The pawn moves diagonally (if there's a opponent piece to eat)
        bool diag_right = coords.file == (position_.file + 1) && coords.rank == (position_.rank - 1);
        bool diag_left = coords.file == (position_.file - 1) && coords.rank == (position_.rank - 1);
        if((diag_right || diag_left) && !board.isEmpty(coords) && board.at(coords).color() == chess::WHITE) {
            return true;
        }
    }
    return false;
}

bool chess::Pawn::canMove(Board& board) const {
    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {
        //The pawn can move two steps forward
        if(position_.rank - 2 >= 0 && canMove({position_.file, position_.rank - 2}, board)) {
            return true;
        }

        if(position_.rank - 1 >= 0) {
            //The pawn can move one step
            bool one_step = canMove({position_.file, position_.rank - 1}, board);
            //The pawn can move diagonally
            bool eat_right = canMove({position_.file + 1, position_.rank - 1}, board);
            bool eat_left = canMove({position_.file - 1, position_.rank - 1}, board);
            if(one_step || eat_right || eat_left) {
                return true;
            }
        }
    }
    //THE PAWN IS BLACK
    if(this->color() == chess::BLACK) {
        //The pawn can move two steps forward
        if(position_.rank + 2 < 8 && canMove({position_.file, position_.rank + 2}, board)) {
            return true;
        }

        if(position_.rank + 1 >= 0) {
            //The pawn can move one step
            bool one_step = canMove({position_.file, position_.rank + 1}, board);
            //The pawn can move diagonally
            bool eat_right = canMove({position_.file + 1, position_.rank + 1}, board);
            bool eat_left = canMove({position_.file - 1, position_.rank + 1}, board);
            if(one_step || eat_right || eat_left) {
                return true;
            }
        }
    }

    return false;
}

std::vector<chess::Coordinates> chess::Pawn::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {
        //Double move up
        if(position_.rank - 2 >= 0 && canMove({position_.file, position_.rank - 2}, board)) {
            moves.push_back(Coordinates{position_.file, position_.rank - 2});
        }

        if(position_.rank - 1 >= 0) {
            //Single move up
            if(canMove({position_.file, position_.rank - 1}, board)) {
                moves.push_back(Coordinates{position_.file, position_.rank - 1});
            }
            //Diagonal eating moves
            if(position_.file + 1 < 8 && canMove({position_.file + 1, position_.rank - 1}, board)) {
                moves.push_back(Coordinates{position_.file + 1, position_.rank - 1});
            }
            if(position_.file - 1 >= 0 && canMove({position_.file - 1, position_.rank - 1}, board)) {
                moves.push_back(Coordinates{position_.file - 1, position_.rank - 1});
            }
        }
    }
    //THE PAWN IS BLACK
    if(this->color() == chess::BLACK) {
        if(position_.rank + 2 < 8 && canMove({position_.file, position_.rank + 2}, board)) {
            moves.push_back(Coordinates{position_.file, position_.rank + 2});
        }

        if(position_.rank + 1 >= 0) {
            if(canMove({position_.file, position_.rank + 1}, board)) {
                moves.push_back(Coordinates{position_.file, position_.rank + 1});
            }
            if(position_.file + 1 < 8 && canMove({position_.file + 1, position_.rank + 1}, board)) {
                moves.push_back(Coordinates{position_.file + 1, position_.rank + 1});
            }
            if(position_.file - 1 >= 0 && canMove({position_.file - 1, position_.rank + 1}, board)) {
                moves.push_back(Coordinates{position_.file - 1, position_.rank + 1});
            }
        }
    }

    return moves;
}