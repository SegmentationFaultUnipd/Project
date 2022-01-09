#include "Pawn.h"

bool chess::Pawn::canMove(Coordinates coords, Board& board) const {
    //Can't stay stationary
    if(position_.file == coords.file && position_.rank == coords.rank) {
        return false;
    }

    //The pawn can make 3 different moves, 1 only if it hasn't yet moved
    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {
        //The pawn moves two steps forward (if it hasn't yet moved)
        bool two_up = coords.file == position_.file && coords.rank == (position_.rank - 2);
        if(two_up && !hasMoved && board.isEmpty(to_file, to_rank)) {
            return true;
        }
        
        //The pawn moves one step forward (if the tile is free)
        bool one_up = coords.file == position_.file && coords.rank == (position_.rank - 1);
        if(one_up && board.isEmpty(to_file, to_rank)) {
            return true;
        }

        //The pawn moves diagonally (if there's a opponent piece to eat)
        bool diag_1 = coords.file == (position_.file + 1) && coords.rank == (position_.rank - 1);
        bool diag_2 = coords.file == (position_.file - 1) && coords.rank == (position_.rank - 1);
        if((diag_1 || diag_2) && board.at(coords).color() == chess::BLACK) {
            return true;
        }

        return false;
    }
    //THE PAWN IS BLACK
    else {
        //The pawn moves two steps forward (if it hasn't yet moved)
        bool two_up = coords.file == position_.file && coords.rank == (position_.rank + 2);
        if(two_up && !hasMoved && board.isEmpty(coords)) {
            return true;
        }
        
        //The pawn moves one step forward (if the tile is free)
        bool one_up = coords.file == position_.file && coords.rank == (position_.rank + 1);
        if(one_up && board.isEmpty(coords)) {
            return true;
        }

        //The pawn moves diagonally (if there's a opponent piece to eat)
        bool diag_1 = coords.file == (position_.file + 1) && coords.rank == (position_.rank + 1);
        bool diag_2 = coords.file == (position_.file - 1) && coords.rank == (position_.rank + 1);
        if((diag_1 || diag_2) && board.at(coords).color() == chess::WHITE) {
            return true;
        }

        return false;
    }
}

bool chess::Pawn::canMove(Board& board) const {
    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {
        if(position_.rank - 2 >= 0 && !hasMoved && board.isEmpty(position_.file, position_.rank - 2)) {
            return true;
        }

        if(position_.rank - 1 >= 0) {
            if(board.isEmpty(position_.file, position_.rank - 1)) {
                return true;
            }
            if(position_.file + 1 < 8 && board.at(position_.file + 1, position_.rank - 1).color() == chess::BLACK) {
                return true;
            }
            if(position_.file - 1 >= 0 && board.at(position_.file - 1, position_.rank - 1).color() == chess::BLACK) {
                return true;
            }
        }
    }
    //THE PAWN IS BLACK
    if(this->color() == chess::BLACK) {
        if(position_.rank + 2 >= 0 && !hasMoved && board.isEmpty(position_.file, position_.rank + 2)) {
            return true;
        }

        if(position_.rank + 1 >= 0) {
            if(board.isEmpty({position_.file, position_.rank + 1})) {
                return true;
            }
            if(position_.file + 1 < 8 && board.at({position_.file + 1, position_.rank + 1}).color() == chess::WHITE) {
                return true;
            }
            if(position_.file - 1 >= 0 && board.at({position_.file - 1, position_.rank + 1}).color() == chess::WHITE) {
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
        if(position_.rank - 2 >= 0 && !hasMoved && board.isEmpty(position_.file, position_.rank - 2)) {
            moves.push_back(chess::Coordinates{position_.file, position_.rank - 2});
        }

        if(position_.rank - 1 >= 0) {
            //Single move up
            if(board.isEmpty(position_.file, position_.rank - 1)) {
                moves.push_back(chess::Coordinates{position_.file, position_.rank - 1});
            }
            //Diagonal eating moves
            if(position_.file + 1 < 8 && board.at(position_.file + 1, position_.rank - 1).color() == chess::BLACK) {
                moves.push_back(chess::Coordinates{position_.file + 1, position_.rank - 1});
            }
            if(position_.file - 1 >= 0 && board.at(position_.file - 1, position_.rank - 1).color() == chess::BLACK) {
                moves.push_back(chess::Coordinates{position_.file - 1, position_.rank - 1});
            }
        }
    }
    //THE PAWN IS BLACK
    if(this->color() == chess::BLACK) {
        if(position_.rank + 2 >= 0 && !hasMoved && board.isEmpty(position_.file, position_.rank + 2)) {
            moves.push_back(chess::Coordinates{position_.file, position_.rank + 2});
        }

        if(position_.rank + 1 >= 0) {
            if(board.isEmpty(position_.file, position_.rank + 1)) {
                moves.push_back(chess::Coordinates{position_.file, position_.rank + 1});
            }
            if(position_.file + 1 < 8 && board.at(position_.file + 1, position_.rank + 1).color() == chess::WHITE) {
                moves.push_back(chess::Coordinates{position_.file + 1, position_.rank + 1});
            }
            if(position_.file - 1 >= 0 && board.at(position_.file - 1, position_.rank + 1).color() == chess::WHITE) {
                moves.push_back(chess::Coordinates{position_.file - 1, position_.rank + 1});
            }
        }
    }

    return moves;
}