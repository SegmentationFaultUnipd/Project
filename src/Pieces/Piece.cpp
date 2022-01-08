#include "Piece.h"


std::vector<chess::Coordinates> chess::Piece::takeablePieces(Board& board) const {
	std::vector<Coordinates> moves = legalMoves(board);
	std::vector<Coordinates> result;
	for(auto coord: moves) {
		if(!board.isEmpty(coord)) {
			result.push_back(coord);
		}
	}
	return result;
}
