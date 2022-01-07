#include "King.h"
bool chess::King::canMove(short to_file, short to_rank, chess::Board& board) {
    short delta_file = abs(to_file - file());
    short delta_rank = abs(to_rank - rank());

	//King can move at maximum 1 square in all the directions
    if(delta_file > 1 || delta_rank > 1 || (to_file == file() && to_rank == rank())) {
		return false;
	}
	const Piece* landing_piece = board.at(to_file, to_rank);
	
	return landing_piece == nullptr || landing_piece->color() != this->color();
};



bool chess::King::canMove(chess::Board& board) {
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

std::vector<chess::Coordinates> chess::King::legalMoves(chess::Board& board) {
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


bool chess::King::canCastle(short to_file, short to_rank, chess::Board& board) {
	if(hasMoved()) {
		return false;
	}
	//TODO Check that the to_file and to_rank are actually the positions of the towers, based also on the right color
	//TODO check that the tower has not moved yet
	//TODO Check that the squares in between are empty
	//TODO Check that the king is not in check for every position
	return true;
}


bool chess::King::isInCheck(short king_file, short king_rank, chess::Board& board) {
	//For all the moves that the enemy can do, check if at least one move could capture the king at that position
	Color enemy_color = (color() == WHITE) ? BLACK : WHITE;
	std::list<Coordinates> enemy_coords = board.getPieces(enemy_color);
	
	for(auto coords : enemy_coords) {
		std::vector<Coordinates> moves = board.at(coords)->legalMoves(board);
		for(auto target: moves) {
			if(target.file == king_file && target.rank == king_rank) {
				return true;
			}
		} 
	}
	
	return false;

}