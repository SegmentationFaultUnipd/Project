#include "Pawn.h"

// Testing if the move is legal for a pawn
bool chess::Pawn::canMove(short to_file, short to_rank, const Board& board){
    Piece* destination =  board.at(to_file, to_rank);
    // If it hasn't moved yet it can move upward twice
    if(!has_moved_){
        bool is_moving_up_twice = (to_file == file()) && (to_rank == (rank() + 2);
        if(is_moving_up_twice && (destination == nullptr)){
            has_moved_ = true;
            return true;
        }
    }
    // If the next rank is free it can move
    bool is_moving_up = (to_file == file()) && (to_rank == (rank() + 1));
    if(is_moving_up && (destination == nullptr)){
        if(!has_moved_) { has_moved_ = true; }
        return true;
    }
    
    // If it's a diagonal move that can eat it can move
    bool is_moving_diagonal = ((to_file == file() - 1) || (to_file == file() + 1)) && (to_rank == (rank() + 1));
    if(is_moving_diagonal && (destination->isWhite() != isWhite()){
        if(!has_moved_) { has_moved_ = true; }
        return true;
    }

    return false;
}

