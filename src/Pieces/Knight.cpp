#include "Knight.h"

bool chess::Knight::canMove(short to_file, short to_rank, chess::Board& board) const {
    short delta_file = to_file - file();
    short delta_rank = to_rank - rank();

    //Knight moves with 3 total steps, so the manahattan distance must be 3
    if (delta_file * delta_rank != 0 && abs(delta_file) + abs(delta_rank) == 3) {
        return board.isEmpty(to_file, to_rank) || board.at(to_file, to_rank).color() != this->color();
    }
    return false;
};

bool chess::Knight::canMove(chess::Board& board) const {
    short file, rank_upper, rank_lower;

    for (short delta_file = -2; delta_file <= 2; delta_file++) {
        if (delta_file == 0)
            continue;

        file = position_.file + delta_file;
        rank_upper = position_.rank + abs(3 - abs(delta_file));
        rank_lower = position_.rank - abs(3 - abs(delta_file));

        if (file >= 0 && file < 8) {
            if (rank_upper >= 0 && rank_upper < 8 && canMove(file, rank_upper, board))
                return true;

            if (rank_lower >= 0 && rank_lower < 8 && canMove(file, rank_lower, board))
                return true;
        }
    }
    return false;
};

std::vector<chess::Coordinates> chess::Knight::legalMoves(Board& board) const {
    std::vector<chess::Coordinates> moves = {};

    short file, rank_upper, rank_lower;

    for (short delta_file = -2; delta_file <= 2; delta_file++) {
        if (delta_file == 0)
            continue;

        file = position_.file + delta_file;
        rank_upper = position_.rank + abs(3 - abs(delta_file));
        rank_lower = position_.rank - abs(3 - abs(delta_file));

        if (file >= 0 && file < 8) {
            if (rank_upper >= 0 && rank_upper < 8
                && canMove(file, rank_upper, board))
            {
                moves.push_back(chess::Coordinates{file, rank_upper});
            }

            if (rank_lower >= 0 && rank_lower < 8
                && canMove(file, rank_lower, board))
            {
                moves.push_back(chess::Coordinates{file, rank_lower});
            }
        }
    }
    return moves;
}

/*
std::vector<chess::Coordinates> chess::Knight::takeablePieces(Board& board) const {
    std::vector<chess::Coordinates> pieces = {};
    short file, rank_upper, rank_lower;

    for (short delta_file = -2; delta_file <= 2; delta_file++) {
        if (delta_file == 0)
            continue;

        // Calculate movements in the same file.
        // The movement must be made with manhattan distance = 3
        file = position_.file + delta_file;
        rank_upper = position_.rank + abs(3 - abs(delta_file));
        rank_lower = position_.rank - abs(3 - abs(delta_file));

        // Check if the movements are possible and if take a piece
        if (file >= 0 && file < 8) {
            if (rank_upper >= 0 && rank_upper < 8
                && canMove(file, rank_upper, board)
                && !board.isEmpty(file, rank_upper))
            {
                pieces.push_back(chess::Coordinates{file, rank_upper});
            }

            if (rank_lower >= 0 && rank_lower < 8
                && canMove(file, rank_lower, board)
                && !board.isEmpty(file, rank_lower))
            {
                pieces.push_back(chess::Coordinates{file, rank_lower});
            }
        }
    }

    return pieces;
}*/