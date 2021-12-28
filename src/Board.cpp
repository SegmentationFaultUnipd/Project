#include "Board.h"

chess::Board::Board() {

    //Inserting test pieces
    for (short file = 0; file < 8; file++) {
        white_pieces_.push_back(new Knight{file, 0, Color::WHITE});
        white_pieces_.push_back(new Knight{file, 1, Color::WHITE});

        black_pieces_.push_back(new Knight{file, 6, Color::BLACK});
        black_pieces_.push_back(new Knight{file, 7, Color::BLACK});
    }

    //Constructing pointer matrix
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            board_[i][j] = nullptr;

    for (Piece* wp : white_pieces_)
        board_[wp->file()][wp->rank()] = wp;
    for (Piece* bp : black_pieces_)
        board_[bp->file()][bp->rank()] = bp;
}

chess::Board::~Board() {
    while (white_pieces_.size() != 0)
        white_pieces_.pop_back();
    while (black_pieces_.size() != 0)
        black_pieces_.pop_back();

    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            delete board_[i][j];
}

chess::Piece* chess::Board::at(short file, short rank) {
    return board_[file][rank];
}

//Movement with no control.
void chess::Board::move(short from_file, short from_rank, short to_file, short to_rank) {
    Piece* moving_piece = board_[from_file][from_rank];

    if (moving_piece != nullptr && moving_piece->canMove(to_file, to_rank, board_) ) {   
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
std::ostream& chess::operator<<(std::ostream& os, Board& board) {

    for (size_t r = 8; r > 0; r--) {
        os << r << " ";
        for (size_t f = 0; f < 8; f++) {
            if (board.at(f, r-1) == nullptr)
                os << " ";
            else {
                char c = board.at(f, r-1)->ascii();
                os << (board.at(f, r-1)->color() == Color::WHITE ? (char)tolower(c) : (char)toupper(c));
            };
        }
        os << "\n";
    }
    os << "\n  ABCDEFGH\n";
    return os;
}