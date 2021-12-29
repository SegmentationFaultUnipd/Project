#include "King.h"

bool chess::King::canMove(short to_file, short to_rank, Piece* board[8][8]) {
    short delta_file = abs(to_file - file());
    short delta_rank = abs(to_rank - rank());

	//King can move at maximum 1 square in all the directions
    if(delta_file > 1 || delta_rank > 1 || (to_file == file() && to_rank == rank())) {
		return false;
	}
	const Piece* landing_piece = board[to_file][to_rank];
	return landing_piece == nullptr || landing_piece->color() != this->color();
};

bool chess::King::canMove(Piece* board[8][8]) {
    for (short d_file = -1; d_file <= 1; d_file++) {
       	for (short d_rank = -1; d_rank <= 1; d_rank++) {
			if (d_file == 0 && d_rank == 0)
				continue;

			if(d_file + file() >= 0 && d_file + file() < 8 && d_rank + rank() >= 0 && d_rank < 8) {//file, rank in valid range
				if(canMove(d_file + file(), d_rank + rank(), board)) {
					return true;
				}
			} 
    	}
    }
    return false;
};

std::vector<chess::Coordinates> chess::King::legalMoves(Piece* board[8][8]) {
    std::vector<chess::Coordinates> moves = {};

    for (short d_file = -1; d_file <= 1; d_file++) {
       	for (short d_rank = -1; d_rank <= 1; d_rank++) {
			if (d_file == 0 && d_rank == 0)
				continue;

			if(d_file + file() >= 0 && d_file + file() < 8 && d_rank + rank() >= 0 && d_rank < 8) {//file, rank in valid range
				if(canMove(d_file + file(), d_rank + rank(), board)) {
					moves.push_back(chess::Coordinates{d_file + file(),  d_rank + rank()});
				}
			} 
    	}
    }
    return moves;
}