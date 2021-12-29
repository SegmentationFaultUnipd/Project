#include "Board.h"

chess::Board::Board() {

    //Inserting test pieces
    for (short file = 0; file < 8; file++) {
        white_pieces_.push_back(Piece{file, 0, true});
        white_pieces_.push_back(Piece{file, 1, true});

        black_pieces_.push_back(Piece{file, 6, false});
        black_pieces_.push_back(Piece{file, 7, false});
    }

    //Constructing pointer matrix
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            board_[i][j] = nullptr;

    for (Piece &wp : white_pieces_)
        board_[wp.file()][wp.rank()] = &wp;
    for (Piece &bp : black_pieces_)
        board_[bp.file()][bp.rank()] = &bp;
}

//Movement with no control.
void chess::Board::move(short from_file, short from_rank, short to_file, short to_rank) {
    Piece* moving_piece = board_[from_file][from_rank];

    if (moving_piece != nullptr && moving_piece->canMove(to_file, to_rank, *this) ) {   
        //Moving in matrix
        board_[to_file][to_rank] = board_[from_file][from_rank];
        board_[from_file][from_rank] = nullptr;

        //Update piece position
        moving_piece->move(to_file, to_rank);
    } else {
        //ILLEGAL MOVEMENT, exception?
    }
}

//Print board, for every piece prints w/b based on the color.
std::ostream& chess::operator<<(std::ostream& os, const Board& board) {

    for (size_t r = 8; r > 0; r--) {
        os << r << " ";
        for (size_t f = 0; f < 8; f++) {
            if (board.at(f, r-1) == nullptr)
                os << " ";
            else
                os << (board.at(f, r-1)->isWhite() ? "w" : "B");
        }
        os << "\n";
    }
    os << "\n  ABCDEFGH\n";
    return os;
}