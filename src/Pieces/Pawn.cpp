#include "Pawn.h"

void chess::Pawn::move(Coordinates new_position) {
    position_ = new_position;
    hasMoved = true;
}

bool chess::Pawn::canMoveAt(Coordinates coords, Board& board) const {
    //The pawn can make 3 different moves, 1 only if it hasn't yet moved
	std::cerr <<"Pawn::canMoveAt::START"<<std::endl;
	std::cerr << "Pawn is in coordinates... "<<file()<< " "<< rank() << ": "<<position_.toNotation() << std::endl;
	std::cerr <<"Pawn::canMoveAt::1Calling isEnPassantMove with from: "<<position_.file << " " <<position_.rank<<std::endl;

    //Can't stay stationary
    if(position_ == coords) {
        return false;
    }
	std::cerr <<"Pawn::canMoveAt::2Calling isEnPassantMove with from: "<<position_.file << " " <<position_.rank<<std::endl;

    //Can't land on a piece of the same color
    if (!board.isEmpty(coords) && board.at(coords).color() == this->color()) {
        return false;
    }
	std::cerr <<"Pawn::canMoveAt::3Calling isEnPassantMove with from: "<<position_.file << " " <<position_.rank<<std::endl;

    //Can't make a move that would cause a self check
    if(board.moveCauseSelfCheck(position_, coords)) {
        return false;
    }
	std::cerr <<"Pawn::canMoveAt::FIRST CHECKS"<<std::endl;

    //The pawn is trying to en pass
	std::cerr <<"Pawn::canMoveAt::4Calling isEnPassantMove with from: "<<position_.file << " " <<position_.rank<<std::endl;
    if(board.isEnPassantMove({position_.file, position_.rank}, coords)) {
        return true;
    }
	std::cerr <<"Pawn::canMoveAt::ENPASSANT"<<std::endl;
    
    //Check the pawn color
    short color_n;
    if(this->color() == WHITE) {
        color_n = 1;
    }
    else {
        color_n = -1;
    }
	std::cerr <<"Pawn::canMoveAt::CHECK COLOR"<<std::endl;


    //The pawn moves two steps forward (if it hasn't yet moved)
    bool two_up = coords.file == position_.file && coords.rank == (position_.rank + (2 * color_n));
    if(two_up && !hasMoved && board.isEmpty(coords) && board.isEmpty({coords.file, position_.rank + (1 * color_n)})) {
        Coordinates from, to;
        to = {position_.file, position_.rank + (1 * color_n)};
        //If there is a pawn on the right it can then en pass
        from = {position_.file + 1, position_.rank + (2 * color_n)};
        if(from.inBounderies() && !board.isEmpty(from) && board.at(from).ascii() == 'P') {
            board.addAvailableEnPassant(from, to);
        }
        //If there is a pawn on the left it can then en pass
        from = {position_.file - 1, position_.rank + (2 * color_n)};
        if(from.inBounderies() && !board.isEmpty(from) && board.at(from).ascii() == 'P'){
            board.addAvailableEnPassant(from, to);
        }
        return true;
    }
	std::cerr <<"Pawn::canMoveAt::BULK IF"<<std::endl;
    
    //The pawn moves one step forward (if the tile is free)
    bool one_up = coords.file == position_.file && coords.rank == (position_.rank + (1 * color_n));
    if(one_up && board.isEmpty(coords)) {
        return true;
    }
	std::cerr <<"Pawn::canMoveAt::SMALL IFS"<<std::endl;

    //The pawn moves diagonally (if there's a opponent piece to eat)
    bool diag_right = coords.file == (position_.file + 1) && coords.rank == (position_.rank + (1 * color_n));
    bool diag_left = coords.file == (position_.file - 1) && coords.rank == (position_.rank + (1 * color_n));
    if((diag_right || diag_left) && !board.isEmpty(coords) && board.isOppositeColor(coords, this->color())) {
        return true;
    }
	std::cerr <<"Pawn::canMoveAt::FINAL"<<std::endl;


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
    if(position_.rank - 2 >= 0 && canMoveAt({position_.file, position_.rank + (2 * color_n)}, board)) {
            return true;
    }

    if(position_.rank - 1 >= 0) {
        //The pawn can move one step
        bool one_step = canMoveAt({position_.file, position_.rank + (1 * color_n)}, board);
        //The pawn can move diagonally
        bool eat_right = canMoveAt({position_.file + 1, position_.rank + (1 * color_n)}, board);
        bool eat_left = canMoveAt({position_.file - 1, position_.rank + (1 * color_n)}, board);
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
    if(position_.rank - 2 >= 0 && canMoveAt({position_.file, position_.rank + (2 * color_n)}, board)) {
        moves.push_back(Coordinates{position_.file, position_.rank + (2 * color_n)});
    }

    if(position_.rank - 1 >= 0) {
        //Single move up
        if(canMoveAt({position_.file, position_.rank - 1}, board)) {
            moves.push_back(Coordinates{position_.file, position_.rank + (1 * color_n)});
        }
        //Diagonal eating moves
        if(position_.file + 1 < 8 && canMoveAt({position_.file + 1, position_.rank + (1 * color_n)}, board)) {
            moves.push_back(Coordinates{position_.file + 1, position_.rank + (1 * color_n)});
        }
        if(position_.file - 1 >= 0 && canMoveAt({position_.file - 1, position_.rank + (1 * color_n)}, board)) {
            moves.push_back(Coordinates{position_.file - 1, position_.rank + (1 * color_n)});
        }
    }

    return moves;
}