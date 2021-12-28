#include "Knight.h"

bool chess::Knight::canMove(short to_file, short to_rank, Piece* board[8][8]) {
    short delta_file = to_file - file();
    short delta_rank = to_rank - rank();

    //Knight moves with 3 total steps, so the manahattan distance must be 3
    if (delta_file * delta_rank != 0 && abs(delta_file) + abs(delta_rank) == 3) {
        Piece* landing_piece = board[to_file][to_rank];
        return landing_piece == nullptr || landing_piece->color() != this->color();
    }
    std::cout << "Impossible movement\n";
    return false;
};

bool chess::Knight::canMove(Piece* board[8][8]) {
    return true;
};

std::vector<chess::Coordinates> chess::Knight::legalMoves(Piece* board[8][8]) {
    return {};
}