#include "Pawn.h"

void chess::Pawn::move(Coordinates new_position) {
    position_ = new_position;
    hasMoved = true;
}

bool chess::Pawn::canMoveAt(Coordinates coords, Board& board) const {
    //The pawn can make 3 different moves, 1 only if it hasn't yet moved

    //Can't stay stationary
    if(position_ == coords) {
        return false;
    }

    //Can't land on a piece of the same color
    if (!board.isEmpty(coords) && board.at(coords).color() == this->color()) {
        return false;
    }

    //Can't make a move that would cause a self check
    if(board.moveCauseSelfCheck(position_, coords)) {
        return false;
    }

    //The pawn is trying to en pass
    if(board.isEnPassantMove({position_.file, position_.rank}, coords)) {
        return true;
    }
    
    //Check the pawn color
    short color_n;
    if(this->color() == WHITE) {
        color_n = 1;
    }
    else {
        color_n = -1;
    }


    //The pawn moves two steps forward (if it hasn't yet moved)
    bool two_up = coords.file == position_.file && coords.rank == (position_.rank + (2 * color_n));
    if(two_up && !hasMoved && board.isEmpty(coords) && board.isEmpty({coords.file, position_.rank + (1 * color_n)})) {
        Coordinates from, to;
        to = {position_.file, position_.rank + (1 * color_n)};
        //If there is a pawn on the right it can then en pass
        from = {position_.file + 1, position_.rank + (2 * color_n)};
        if(from.inBounderies() && board.isOppositeColor(from, this->color()) && board.at(from).ascii() == 'P') {
            board.addAvailableEnPassant(from, to);
        }
        //If there is a pawn on the left it can then en pass
        from = {position_.file - 1, position_.rank + (2 * color_n)};
        if(from.inBounderies() && board.isOppositeColor(from, this->color()) && board.at(from).ascii() == 'P'){
            board.addAvailableEnPassant(from, to);
        }
        return true;
    }
    
    //The pawn moves one step forward (if the tile is free)
    bool one_up = coords.file == position_.file && coords.rank == (position_.rank + (1 * color_n));
    if(one_up && board.isEmpty(coords)) {
        return true;
    }

    //The pawn moves diagonally (if there's a opponent piece to eat)
    bool diag_right = coords.file == (position_.file + 1) && coords.rank == (position_.rank + (1 * color_n));
    bool diag_left = coords.file == (position_.file - 1) && coords.rank == (position_.rank + (1 * color_n));
    if((diag_right || diag_left) && !board.isEmpty(coords) && board.isOppositeColor(coords, this->color())) {
        return true;
    }

    return false;
}

bool chess::Pawn::canMove(Board& board) const {
    //Check the pawn color
    short color_n;
    if(this->color() == WHITE) {
        color_n = 1;
    }
    else {
        color_n = -1;
    }
    //The pawn can move two steps forward
    Coordinates double_up {position_.file, position_.rank + (2 * color_n)};
    if(double_up.inBounderies() && canMoveAt(double_up, board)) {
            return true;
    }
    if(position_.rank - 1 >= 0) {
        //The pawn can move one step
        Coordinates single_up {position_.file, position_.rank - 1};
        bool one_step = single_up.inBounderies() && canMoveAt(single_up, board);
        //The pawn can move diagonally
        Coordinates diag_right {position_.file + 1, position_.rank + (1 * color_n)};
        bool eat_right = diag_right.inBounderies() && canMoveAt(diag_right, board);
        Coordinates diag_left {position_.file - 1, position_.rank + (1 * color_n)};
        bool eat_left = diag_left.inBounderies() && canMoveAt(diag_left, board);
        if(one_step || eat_right || eat_left) {
            return true;
        }
    }

    return false;
}

std::vector<chess::Coordinates> chess::Pawn::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};
    //Check the pawn color
    short color_n;
    if(this->color() == WHITE) {
        color_n = 1;
    }
    else {
        color_n = -1;
    }
    //Double move up
    Coordinates double_up {position_.file, position_.rank + (2 * color_n)};
    if(position_.rank - 2 >= 0 && double_up.inBounderies() && canMoveAt(double_up, board)) {
        moves.push_back(double_up);
        std::cout << double_up << ", ";
    }

    if(position_.rank - 1 >= 0) {
        //Single move up
        Coordinates single_up {position_.file, position_.rank - 1};
        if(single_up.inBounderies() && canMoveAt(single_up, board)) {
            moves.push_back(single_up);
        }
        //Diagonal eating moves
        Coordinates diag_right {position_.file + 1, position_.rank + (1 * color_n)};
        if(diag_right.inBounderies() && canMoveAt(diag_right, board)) {
            moves.push_back(diag_right);
        }
        Coordinates diag_left {position_.file - 1, position_.rank + (1 * color_n)};
        if(diag_left.inBounderies() && canMoveAt(diag_left, board)) {
            moves.push_back(diag_left);
        }
    }

    return moves;
}