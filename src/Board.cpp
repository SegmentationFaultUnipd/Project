#include "Board.h"

chess::Board::Board() {
    //Inserting test pieces
    for (short file = 0; file < 8; file++) {
        white_pieces_.push_back(Coordinates{file, 0});
        white_pieces_.push_back(Coordinates{file, 1});

        black_pieces_.push_back(Coordinates{file, 6});
        black_pieces_.push_back(Coordinates{file, 7});
    }

    //Constructing pointer matrix
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            board_[i][j] = nullptr;

    for (Coordinates coord : white_pieces_)
        board_[coord.file][coord.rank] = std::make_unique<Knight>(coord.file, coord.rank, Color::WHITE);
    for (Coordinates coord : black_pieces_)
        board_[coord.file][coord.rank] = std::make_unique<Knight>(coord.file, coord.rank, Color::BLACK);
}

bool chess::Board::isEmpty(short file, short rank) {
    return board_[file][rank] == nullptr;
}
bool chess::Board::isEmpty(chess::Coordinates coords) {
    return board_[coords.file][coords.rank] == nullptr;
}

chess::Piece& chess::Board::at(short file, short rank) {
    assert(!isEmpty(file, rank));
    return *board_[file][rank];
}
chess::Piece& chess::Board::at(Coordinates coords) {
    assert(!isEmpty(coords.file, coords.rank));
    return *board_[coords.file][coords.rank];
}


// Move the piece 
void chess::Board::move(short from_file, short from_rank, short to_file, short to_rank) {
    assert(from_file >= 0 && from_file < 8);
    assert(from_rank >= 0 && from_rank < 8);
    assert(to_file >= 0 && to_file < 8);
    assert(to_rank >= 0 && to_rank < 8);
    
    if (isEmpty(from_file, from_rank))
        return; //Illegal Movement

    Piece& moving_piece = at(from_file, from_rank);
    if (moving_piece.canMove(to_file, to_rank, *this) ) {

        // Eat piece
        if (!isEmpty(to_file, to_rank)
            && at(to_file, to_rank).color() != at(from_file, from_rank).color())
        {
            getPieces(board_[to_file][to_rank]->color()).remove({to_file, to_rank});
        }

        // Moving in matrix
        board_[to_file][to_rank] = std::move(board_[from_file][from_rank]);
        board_[from_file][from_rank] = nullptr;

        // Update piece position
        moving_piece.move(to_file, to_rank);
    } else {
        //ILLEGAL MOVEMENT, exception?
    }
}

std::vector<chess::Coordinates> chess::Board::legalMovesOf(chess::Piece& piece) {
    return piece.legalMoves(*this);
}

std::list<chess::Coordinates>& chess::Board::getPieces(chess::Color color) {
    if (color == Color::WHITE)
        return white_pieces_;
    return black_pieces_;
}

// Check if there is a piece attacking the square
// color is the color of the square
bool chess::Board::isInCheck(chess::Coordinates coords, chess::Color color) {
    //King king{coords.file, coords.rank, color};
    //Queen queen{coords.file, coords.rank, color};
    //Rook rook{coords.file, coords.rank, color};
    //Bishop bishop{coords.file, coords.rank, color};
    Knight knight{coords.file, coords.rank, color};
    //Pawn pawn{coords.file, coords.rank, color};

    const Piece* possiblePieces[] = {
        //&king,
        //&queen
        //&rook
        //&bishop
        &knight
        //%pawn
    };

    for (const Piece* piece : possiblePieces) {
        std::vector<chess::Coordinates> moves = piece->takeablePieces(*this);

        for (chess::Coordinates move : moves) {
            if (at(move.file, move.rank).ascii() == piece->ascii() &&
                at(move.file, move.rank).color() != piece->color())
                return true;
        }
    }
    return false;
}

// Print the board. For every piece it prints its ascii character, lower if white,
// upper if black. It prints a blank space if there is no piece.
// It also prints the files and ranks coordinates.
std::ostream& chess::operator<<(std::ostream& os, Board& board) {

    for (size_t r = 8; r > 0; r--) {
        os << r << " ";
        for (size_t f = 0; f < 8; f++) {
            if (board.isEmpty(f, r-1))
                os << " ";
            else {
                char c = board.at(f, r-1).ascii();
                os << (board.at(f, r-1).color() == Color::WHITE ? (char)tolower(c) : (char)toupper(c));
            };
        }
        os << "\n";
    }
    os << "\n  ABCDEFGH\n";
    return os;
}