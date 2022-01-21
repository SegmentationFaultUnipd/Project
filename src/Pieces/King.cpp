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

			Coordinates final_coords = {d_file + file(), d_rank + rank()};
			if(final_coords.inBounderies()) {//file, rank in valid range
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
			Coordinates final_coords = {d_file + file(), d_rank + rank()};
			if(final_coords.inBounderies()) {//file, rank in valid range
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
	if(to_coords.rank != rank() || (to_coords.file != BOARD_TARGET_KINGSIDE_CASTLE_FILE && to_coords.file != BOARD_TARGET_QUEENSIDE_CASTLE_FILE)) {
		return false;
	}

	bool castlingKingSide = to_coords.file == BOARD_TARGET_KINGSIDE_CASTLE_FILE;
	std::cerr << "Piglia la rook"<< std::endl;
	//Getting the rook
	Coordinates rook_coords = {(castlingKingSide)?BOARD_RIGHT_FILE:BOARD_LEFT_FILE, rank()};
	std::cerr << "Rook coords" << rook_coords.toNotation() << std::endl;
	// Check that the rook_coords are actually the positions of a rook, also check for the right color
	if(board.isEmpty(rook_coords)) {
		return false;
	}
	std::cerr << "Found rook" << rook_coords.toNotation() << std::endl;
	Piece& rook_piece = board.at(rook_coords);

	if(rook_piece.ascii() != 'T' || rook_piece.color() != color()) {
		return false;
	}else {
		Rook& rook = static_cast<Rook&>(rook_piece);
		//Check that the tower has not moved yet
		if(rook.hasMoved()) {
			std::cerr << "Rook has moved!!!! "<<rook_piece.ascii() << std::endl;
			return false;
		}
	}
	std::cerr << "CHECK KING THREATENED"<<std::endl;
	//The king cannot be in check
	if(board.isThreatened(coordinates(), color())) {
		std::cerr << "KING IS THREATENED "<<rook_piece.ascii() << std::endl;
		return false;
	}
	std::cerr << "Arrivato a differenza king queen"<< std::endl;
	//Check that the squares in between are empty and that the king is not in check for each position
	if(castlingKingSide) {
		checkEmptyAndNotInCheck(board, 2, castlingKingSide);
	}else {
		checkEmptyAndNotInCheck(board, 3, castlingKingSide);
	}
	
	return true;
}

bool chess::King::checkEmptyAndNotInCheck(chess::Board& board, int range, bool isKingSide) const {
	int mul = (isKingSide)?1:-1;
	for(int i = 1; i <= range; i++) {
		if(board.isEmpty({file() + i * mul,rank()}) || board.isThreatened({file() + i * mul, rank()}, color())) {
			return false;
		}
	}
	return true;
} 


void chess::King::move(Coordinates new_position) {
	position_ = new_position;
	has_moved = true;
}

/**
 * @brief 	Metodo che ritorna i pezzi che sono catturabili dal re
 * @note	Abbiamo riscritto takeablePieces per il King perché non dobbiamo considerare i due arrocchi perché causerebbe un ciclo infinito di controlli e in ogni caso 
 * 			il re non può prendere nessun pezzo facendo l'arrocco
 * @param 	board la scacchiera
 * @return 	std::vector<chess::Coordinates> le coordinate dei pezzi catturabili
 */
std::vector<chess::Piece*> chess::King::takeablePieces(Board &board) const
{
	
	std::vector<Piece*> takeable_pieces;

	 for (short d_file = -1; d_file <= 1; d_file++) {
       	for (short d_rank = -1; d_rank <= 1; d_rank++) {
			if (d_file == 0 && d_rank == 0)
				continue;
			Coordinates coords = {d_file + file(), d_rank + rank()};
			if(coords.inBounderies() && !board.isEmpty(coords)) {//file, rank in valid range
				if(canMoveAt({d_file + file(), d_rank + rank()}, board)) {
					takeable_pieces.push_back(&board.at(coords));
				}
			} 
    	}
    }
	return takeable_pieces;
}
