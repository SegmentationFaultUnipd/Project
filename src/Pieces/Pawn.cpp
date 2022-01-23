//AUTORE: Tommaso Leoni
#include "Pawn.h"

void chess::Pawn::move(Coordinates new_position, Board& board) {
    has_moved = true;
    short delta_rank;
    if(this->color() == WHITE) {
        delta_rank = 1;
    }
    else {
        delta_rank = -1;
    }

    bool two_up = new_position.file == position_.file && new_position.rank == (position_.rank + (2 * delta_rank));
    if(two_up) {
        Coordinates from, to;
        to = {position_.file, position_.rank + (1 * delta_rank)};
        //If there is a pawn on the right it can then en pass
        from = {position_.file + 1, position_.rank + (2 * delta_rank)};
        if(from.inBounderies() && board.isOppositeColor(from, this->color()) && board.at(from).ascii() == 'P') {
            board.addAvailableEnPassant(from, to);
        }
        //If there is a pawn on the left it can then en pass
        from = {position_.file - 1, position_.rank + (2 * delta_rank)};
        if(from.inBounderies() && board.isOppositeColor(from, this->color()) && board.at(from).ascii() == 'P'){
            board.addAvailableEnPassant(from, to);
        }
    }

    position_ = new_position;
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
    //The pawn is trying to en pass
    if(board.isEnPassantMove({position_.file, position_.rank}, coords)) {
        return true;
    }

    //Check the pawn color
    short delta_rank;
    if(this->color() == WHITE) {
        delta_rank = 1;
    }
    else {
        delta_rank = -1;
    }
    //The pawn is moving two steps forward (if it hasn't yet moved)
    bool two_up = coords.file == position_.file && coords.rank == (position_.rank + (2 * delta_rank));
    if(two_up && !has_moved && board.isEmpty(coords) && board.isEmpty({coords.file, position_.rank + (1 * delta_rank)})) {
        return true;
    }

    //The pawn is moving one step forward (if the tile is free)
    bool one_up = coords.file == position_.file && coords.rank == (position_.rank + (1 * delta_rank));
    if(one_up && board.isEmpty(coords)) {
        return true;
    }

    //The pawn is moving diagonally (if there's a opponent piece to take)
    bool diag_right = coords.file == (position_.file + 1) && coords.rank == (position_.rank + (1 * delta_rank));
    bool diag_left = coords.file == (position_.file - 1) && coords.rank == (position_.rank + (1 * delta_rank));
    if((diag_right || diag_left) && board.isOppositeColor(coords, this->color())) {
        return true;
    }

    return false;
}

bool chess::Pawn::canMove(Board& board) const {
    //Check the pawn color
    short delta_rank = (color() == WHITE)?1:-1;
    //The pawn can move two steps forward
    Coordinates double_up {position_.file, position_.rank + (2 * delta_rank)};
    if(double_up.inBounderies() && canMoveAt(double_up, board) && !board.isKingInCheckAfterMove(position_, double_up)) {
		return true;
    }
    //Single move up
	Coordinates single_up {position_.file, position_.rank + delta_rank};
	if(single_up.inBounderies() && canMoveAt(single_up, board) && !board.isKingInCheckAfterMove(coordinates(), single_up)) {
		return true;
	}
	//Diagonal eating moves
	Coordinates diag_right {position_.file + 1, position_.rank + delta_rank};
	if(diag_right.inBounderies() && canMoveAt(diag_right, board) && !board.isKingInCheckAfterMove(coordinates(), diag_right)) {
		return true;
	}
	Coordinates diag_left {position_.file - 1, position_.rank + delta_rank};
	if(diag_left.inBounderies() && canMoveAt(diag_left, board) && !board.isKingInCheckAfterMove(coordinates(), diag_left)) {
		return true;
	}

    return false;
}

std::vector<chess::Coordinates> chess::Pawn::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};
    //Check the pawn color
    short delta_rank = (color() == WHITE)?1:-1;
    //Double move up
    Coordinates double_up {position_.file, position_.rank + (2 * delta_rank)};
    if(double_up.inBounderies() && canMoveAt(double_up, board)) {
        moves.push_back(double_up);
    }

	//Single move up
	Coordinates single_up {position_.file, position_.rank + delta_rank};
	if(single_up.inBounderies() && canMoveAt(single_up, board)) {
		moves.push_back(single_up);
	}
	//Diagonal eating moves
	Coordinates diag_right {position_.file + 1, position_.rank + delta_rank};
	if(diag_right.inBounderies() && canMoveAt(diag_right, board)) {
		moves.push_back(diag_right);
	}
	Coordinates diag_left {position_.file - 1, position_.rank + delta_rank};
	if(diag_left.inBounderies() && canMoveAt(diag_left, board)) {
		moves.push_back(diag_left);
	}

    return moves;
}
