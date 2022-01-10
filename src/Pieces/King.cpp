#include "King.h"
bool chess::King::canMove(Coordinates coords, chess::Board& board) const {
    short delta_file = abs(coords.file - file());
    short delta_rank = abs(coords.rank - rank());

	//King can move at maximum 1 square in all the directions
    if(delta_file > 1 || delta_rank > 1 || (coords.rank == file() && coords.file == rank())) {
		return false;
	}

	/* OLD CODE
	const Piece& landing_piece = board.at(to_file, to_rank);

	return board.isEmpty(to_file, to_rank) || landing_piece.color() != this->color();
	*/

	// NEW CODE
	if (board.isEmpty(coords))
		return true;
	
	const Piece& landing_piece = board.at(coords);

	return landing_piece.color() != this->color();
	////////////
};



bool chess::King::canMove(chess::Board& board) const {
    for (short d_file = -1; d_file <= 1; d_file++) {
       	for (short d_rank = -1; d_rank <= 1; d_rank++) {
			if (d_file == 0 && d_rank == 0)
				continue;

			if(d_file + file() >= 0 && d_file + file() < 8 && d_rank + rank() >= 0 && d_rank + rank() < 8) {//file, rank in valid range
				if(canMove({d_file + file(), d_rank + rank()}, board)) {
					return true;
				}
			} 
    	}
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
				if(canMove({d_file + file(), d_rank + rank()}, board)) {
					moves.push_back({d_file + file(),  d_rank + rank()});
				}
			} 
    	}
    }
    return moves;
}


bool chess::King::canCastle(short to_file, short to_rank, chess::Board& board) {
	if(hasMoved) {
		return false;
	}
	//TODO Check that the to_file and to_rank are actually the positions of the towers, based also on the right color
	//TODO check that the tower has not moved yet
	//TODO Check that the squares in between are empty
	//TODO Check that the king is not in check for every position
	return true;
}