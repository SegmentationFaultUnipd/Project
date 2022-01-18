#include "Knight.h"

int manhattanDistance(chess::Coordinates coords1, chess::Coordinates coords2) {
    return abs(coords1.file - coords2.file) + abs(coords1.rank - coords2.rank);
}

bool chess::Knight::canMoveAt(Coordinates landing_square, chess::Board &board) const
{
    return manhattanDistance(position_, landing_square) == 3
        && landing_square.file != file()
        && landing_square.rank != rank()
        && board.isEmptyOrOppositeColor(landing_square, this->color_);
};

bool chess::Knight::canMove(chess::Board &board) const
{
    for (const Coordinates &landing_square : candidateMoves_())
        if (board.isEmptyOrOppositeColor(landing_square, this->color_))
            return true;

    return false;
};

std::vector<chess::Coordinates> chess::Knight::legalMoves(Board &board) const
{
    std::vector<Coordinates> moves;

    for (const Coordinates &landing_square : candidateMoves_())
        if (board.isEmptyOrOppositeColor(landing_square, this->color_))
            moves.push_back(landing_square);

    return moves;
}

std::vector<chess::Piece*> chess::Knight::takeablePieces(Board& board) const
{
    std::vector<Piece*> pieces;

    for(const Coordinates& landing_square : candidateMoves_())
        if (board.isOppositeColor(landing_square, this->color_))
            pieces.push_back(&board.at(landing_square));

    return pieces;
}

const std::vector<chess::Coordinates> chess::Knight::candidateMoves_() const
{
    const std::vector<Coordinates> raw_moves {
        {file() + 1, rank() + 2}, {file() + 2, rank() + 1}, // Up-right
        {file() + 1, rank() - 2}, {file() + 2, rank() - 1}, // Down-right
        {file() - 1, rank() + 2}, {file() - 2, rank() + 1}, // Up-left
        {file() - 1, rank() - 2}, {file() - 2, rank() - 1}, // Down-left
    };

    std::vector<Coordinates> moves_in_boundaries{};

    for (Coordinates move : raw_moves)
        if (move.inBounderies())
            moves_in_boundaries.push_back(move);

    return moves_in_boundaries;
}