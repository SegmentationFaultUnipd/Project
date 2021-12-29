#include "King.h"
bool chess::King::canMove(short to_file, short to_rank, Piece* board[8][8]) {
    
	//FIXME: i need the position of the enemies to check if the king is in check (call isInCheck method)
	//FIXME: If we want the check function to be inside gamemanager or in board, we would still need a reference  
	short delta_file = abs(to_file - file());
    short delta_rank = abs(to_rank - rank());

	//King can move at maximum 1 square in all the directions
    if(delta_file > 1 || delta_rank > 1 || (to_file == file() && to_rank == rank())) {
		return false;
	}
	const Piece* landing_piece = board[to_file][to_rank];
	
	return landing_piece == nullptr || landing_piece->color() != this->color();
	//TODO check that by moving the king in a particular spot, the king is not in check. If he is in check, then return false
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


bool chess::King::canCastle(short to_file, short to_rank, Piece* board[8][8],std::vector<Coordinates> enemy_positions) {
	if(hasMoved()) {
		return false;
	}
	//TODO Check that the to_file and to_rank are actually the positions of the towers, based also on the right color
	//TODO check that the tower has not moved yet
	//TODO Check that the squares in between are empty
	//TODO Check that the king is not in check for every position
	return true;
}


bool chess::King::isInCheck(short to_file, short to_rank, Piece* board[8][8],std::vector<Coordinates> enemy_positions) {

}