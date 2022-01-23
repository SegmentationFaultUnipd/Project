/**
 * @file ComputerPlayer.cpp
 * @author Filippo Niero
 * @date 2022-01-23
 */

#include "ComputerPlayer.h"
#include <list>

void chess::ComputerPlayer::nextTurn(Board &board, chess::Coordinates &from, chess::Coordinates &to) {
	std::list<Coordinates> my_pieces = board.getPiecesCoords(color_);

	bool chosen = false;
	while(!chosen) {
		int index_piece = rand() % my_pieces.size();
		std::list<Coordinates>::const_iterator it = my_pieces.cbegin();
		std::advance(it, index_piece);

		Piece& my_piece = board.at(*it);
		std::vector<Coordinates> moves = my_piece.legalMoves(board);
		if(moves.size() > 0) {
			//Rimuovi coordinate che non mettono in check il proprio re
			std::vector<Coordinates> valid_moves;
			for(Coordinates move: moves) {
				if(!board.isKingInCheckAfterMove(*it, move)) {
					valid_moves.push_back(move);
				}
			}
			if(valid_moves.size() > 0) {
				int index_move = rand() % valid_moves.size();
				to = valid_moves[index_move];
				from = *it;
				chosen = true;
			}
		}
	}
}

char chess::ComputerPlayer::choosePromotion() {
	char available[] = {'T','D', 'C', 'A'};
	return available[rand()%4];
}

chess::ComputerPlayer::ComputerPlayer(unsigned int seed, Color color) :  Player{color} {
	srand(seed);
}