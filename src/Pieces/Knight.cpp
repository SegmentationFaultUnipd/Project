#include "Knight.h"

bool chess::Knight::canMove(Coordinates coords, chess::Board& board) const {
    short delta_file = coords.file - file();
    short delta_rank = coords.rank - rank();

    //Knight moves with 3 total steps, so the manahattan distance must be 3
    if (abs(delta_file) + abs(delta_rank) == 3 && delta_file != 0 && delta_rank != 0) {
        return board.isEmpty(coords) || board.at(coords).color() != this->color();
    }
    return false;
};

bool chess::Knight::canMove(chess::Board& board) const {
    for(const Coordinates& candidate : candidateMoves_())
        if (candidate.inBounderies(0,7,0,7) && canMove(candidate, board))
            return true;
    return false;
};

std::vector<chess::Coordinates> chess::Knight::legalMoves(Board& board) const {
    std::vector<Coordinates> moves;

    for(const Coordinates& candidate : candidateMoves_())
        if (candidate.inBounderies(0,7,0,7) && canMove(candidate, board))
            moves.push_back(candidate);
    return moves;
}

/*
std::vector<chess::Coordinates> chess::Knight::takeablePieces(Board& board) const {
    std::vector<Coordinates> pieces;

    for(Coordinates& candidate : candidateMoves_())
        if (candidate.inBounderies(0,7,0,7) && canMove(candidate, board) && !board.at(candidate).isEmpty())
            pieces.push_back(candidate);
    return pieces;
}*/

// Constant time
const std::vector<chess::Coordinates> chess::Knight::candidateMoves_() const{
    return {
      {file() + 1, rank() + 2}, {file() + 2, rank() + 1}, //Up-right
      {file() + 1, rank() - 2}, {file() + 2, rank() - 1}, //Down-right
      {file() - 1, rank() + 2}, {file() - 2, rank() + 1}, //Up-left
      {file() - 1, rank() - 2}, {file() - 2, rank() - 1}, //Down-left
    };
}