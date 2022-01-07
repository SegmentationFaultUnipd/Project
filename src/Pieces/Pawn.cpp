#include "Pawn.h"

bool chess::Pawn::canMove(short to_file, short to_rank, Board& board) {
    Piece* to_piece = board.at(to_file, to_rank);

    //The pawn can make 3 different moves, 1 only if it hasn't yet moved
    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {
        //The pawn moves two steps forward (if it hasn't yet moved)
        bool two_up = to_file == position_.file && to_rank == (position_.rank - 2);
        if(two_up && !hasMoved && to_piece == nullptr) {
            hasMoved = true;
            return true;
        }
        
        //The pawn moves one step forward (if the tile is free)
        bool one_up = to_file == position_.file && to_rank == (position_.rank - 1);
        if(one_up && to_piece == nullptr) {
            if(!hasMoved) hasMoved = true;
            return true;
        }

        //The pawn moves diagonally (if there's a opponent piece to eat)
        bool diag_1 = to_file == (position_.file + 1) && to_rank == (position_.rank - 1);
        bool diag_2 = to_file == (position_.file - 1) && to_rank == (position_.rank - 1);
        if((diag_1 || diag_2) && to_piece->color() == chess::BLACK) {
            if(!hasMoved) hasMoved = true;
            return true;
        }

        return false;
    }
    //THE PAWN IS BLACK
    else {
        //The pawn moves two steps forward (if it hasn't yet moved)
        bool two_up = to_file == position_.file && to_rank == (position_.rank + 2);
        if(two_up && !hasMoved && to_piece == nullptr) {
            hasMoved = true;
            return true;
        }
        
        //The pawn moves one step forward (if the tile is free)
        bool one_up = to_file == position_.file && to_rank == (position_.rank + 1);
        if(one_up && to_piece == nullptr) {
            if(!hasMoved) hasMoved = true;
            return true;
        }

        //The pawn moves diagonally (if there's a opponent piece to eat)
        bool diag_1 = to_file == (position_.file + 1) && to_rank == (position_.rank + 1);
        bool diag_2 = to_file == (position_.file - 1) && to_rank == (position_.rank + 1);
        if((diag_1 || diag_2) && to_piece->color() == chess::WHITE) {
            if(!hasMoved) hasMoved = true;
            return true;
        }

        return false;
    }
}

bool chess::Pawn::canMove(Board& board) {
    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {      
        if(position_.rank - 2 >= 0 && !hasMoved && board.at(position_.file, position_.rank - 2) == nullptr) {
            return true;
        }

        if(position_.rank - 1 >= 0) {
            if(board.at(position_.file, position_.rank - 1) == nullptr) {
                return true;
            }
            if(position_.file + 1 < 8 && board.at(position_.file + 1, position_.rank - 1)->color() == chess::BLACK) {
                return true;
            }
            if(position_.file - 1 >= 0 && board.at(position_.file - 1, position_.rank - 1)->color() == chess::BLACK) {
                return true;
            }
        }
    }
    //THE PAWN IS BLACK
    if(this->color() == chess::BLACK) {      
        if(position_.rank + 2 >= 0 && !hasMoved && board.at(position_.file, position_.rank + 2) == nullptr) {
            return true;
        }

        if(position_.rank + 1 >= 0) {
            if(board.at(position_.file, position_.rank + 1) == nullptr) {
                return true;
            }
            if(position_.file + 1 < 8 && board.at(position_.file + 1, position_.rank + 1)->color() == chess::WHITE) {
                return true;
            }
            if(position_.file - 1 >= 0 && board.at(position_.file - 1, position_.rank + 1)->color() == chess::WHITE) {
                return true;
            }
        }
    }

    return false;
}


std::vector<chess::Coordinates> chess::Pawn::legalMoves(Board& board) {
    std::vector<chess::Coordinates> moves = {};

    //THE PAWN IS WHITE
    if(this->color() == chess::WHITE) {
        //Double move up    
        if(position_.rank - 2 >= 0 && !hasMoved && board.at(position_.file, position_.rank - 2) == nullptr) {
            moves.push_back(chess::Coordinates{position_.file, position_.rank - 2});
        }

        if(position_.rank - 1 >= 0) {
            //Single move up
            if(board.at(position_.file, position_.rank - 1) == nullptr) {
                moves.push_back(chess::Coordinates{position_.file, position_.rank - 1});
            }
            //Diagonal eating moves
            if(position_.file + 1 < 8 && board.at(position_.file + 1, position_.rank - 1)->color() == chess::BLACK) {
                moves.push_back(chess::Coordinates{position_.file + 1, position_.rank - 1});
            }
            if(position_.file - 1 >= 0 && board.at(position_.file - 1, position_.rank - 1)->color() == chess::BLACK) {
                moves.push_back(chess::Coordinates{position_.file - 1, position_.rank - 1});
            }
        }
    }
    //THE PAWN IS BLACK
    if(this->color() == chess::BLACK) {      
        if(position_.rank + 2 >= 0 && !hasMoved && board.at(position_.file, position_.rank + 2) == nullptr) {
            moves.push_back(chess::Coordinates{position_.file, position_.rank + 2});
        }

        if(position_.rank + 1 >= 0) {
            if(board.at(position_.file, position_.rank + 1) == nullptr) {
                moves.push_back(chess::Coordinates{position_.file, position_.rank + 1});
            }
            if(position_.file + 1 < 8 && board.at(position_.file + 1, position_.rank + 1)->color() == chess::WHITE) {
                moves.push_back(chess::Coordinates{position_.file + 1, position_.rank + 1});
            }
            if(position_.file - 1 >= 0 && board.at(position_.file - 1, position_.rank + 1)->color() == chess::WHITE) {
                moves.push_back(chess::Coordinates{position_.file - 1, position_.rank + 1});
            }
        }
    }

    return moves;
}