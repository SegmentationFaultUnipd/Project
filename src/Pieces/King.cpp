#include "King.h"
bool chess::King::canMoveAt(Coordinates coords, chess::Board& board) const {
	if(canCastle(coords, board)) {
		return true;
	}
    short delta_file = abs(coords.file - file());
    short delta_rank = abs(coords.rank - rank());

	//King can move at maximum 1 square in all the directions
    if(delta_file > 1 || delta_rank > 1 || (coords.rank == file() && coords.file == rank())) {
		return false;
	}


	if (board.isEmpty(coords) || board.at(coords).color() != this->color())
		return !board.moveCauseSelfCheck(this->coordinates(), coords);
	
	return false;//Last case: King is trying to capture a piece of the same color
};



bool chess::King::canMove(chess::Board& board) const {
    for (short d_file = -1; d_file <= 1; d_file++) {
       	for (short d_rank = -1; d_rank <= 1; d_rank++) {
			if (d_file == 0 && d_rank == 0)
				continue;

			if(d_file + file() >= 0 && d_file + file() < 8 && d_rank + rank() >= 0 && d_rank + rank() < 8) {//file, rank in valid range
				if(canMoveAt({d_file + file(), d_rank + rank()}, board)) {
					return true;
				}
			} 
    	}
    }
	int right_rank = (color() == WHITE)?0:7;

	if(canCastle({2 ,right_rank}, board)) {
		return true;
	}
	
	if(canCastle({6 ,right_rank}, board)) {
		return true;
	}
    return false;
};

std::vector<chess::Coordinates> chess::King::legalMoves(chess::Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    for (short d_file = -1; d_file <= 1; d_file++) {
       	for (short d_rank = -1; d_rank <= 1; d_rank++) {
			if (d_file == 0 && d_rank == 0)
				continue;

			if(d_file + file() >= 0 && d_file + file() < 8 && d_rank + rank() >= 0 && d_rank + rank() < 8) {//file, rank in valid range
				if(canMoveAt({d_file + file(), d_rank + rank()}, board)) {
					moves.push_back({d_file + file(),  d_rank + rank()});
				}
			} 
    	}
    }
	int right_rank = (color() == WHITE)?0:7;

	if(canCastle({2 ,right_rank}, board)) {
		moves.push_back({2, right_rank});
	}
	
	if(canCastle({6 ,right_rank}, board)) {
		moves.push_back({6, right_rank});
	}

    return moves;
}


bool chess::King::canCastle(Coordinates to_coords, chess::Board& board) const {
	//If the king has moved, you can't castle
	if(has_moved) {
		return false;
	}
	//Check that the target position is valid. 
	if(to_coords.rank != rank() || (to_coords.file == 2 || to_coords.file == 6)) {
		return false;
	}
	bool castlingKingSide = to_coords.file == 6;
	//Getting the rook
	Coordinates rook_coords = {(castlingKingSide)?7:0, rank()};
	// Check that the rook_coords are actually the positions of a rook, also check for the right color
	if(board.isEmpty(rook_coords)) {
		return false;
	}
	Piece& rook_piece = board.at(rook_coords);
	if(rook_piece.ascii() != 'T' || rook_piece.color() != color()) {
		return false;
	}
	Rook& rook = static_cast<Rook&>(rook_piece);
	//Check that the tower has not moved yet
	if(rook.hasMoved()) {
		return false;
	}
	int delta = (castlingKingSide)?1:-1;
	
	//Check that the squares in between are empty
	if(!board.isEmpty({file() + delta, rank()}) || !board.isEmpty({file() + 2*delta, rank()})) {
		return false;
	}
	//Check that the king is not in check for every position
	for(int i = 0; i < 3; i++) {
		if(board.isThreatened({file() + i * delta, rank()}, color())) {
			return false;
		}
	}
	//Last position of the king must not be in check
	return !board.moveCauseSelfCheck(this->coordinates(), to_coords);
}


void chess::King::move(Coordinates new_position) {
	position_ = new_position;
	has_moved = true;
}
