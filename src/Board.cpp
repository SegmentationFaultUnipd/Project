#include "Board.h"

chess::Board::Board() {
    char setup[8][8] = {
        't', 'c', 'a', 'd', 'r', 'a', 'c', 't',
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
        'T', 'C', 'A', 'D', 'R', 'A', 'C', 'T'
    };

    // Initialize pointer matrix
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            board_[i][j] = nullptr;

    // Insert pieces from setup, white (lower char) with lower rank
    for (short r = 7; r >= 0; r--) {
        for (short f = 0; f < 8; f++) {
            char piece = setup[r][f];

            // Adding in matrix
            board_[f][r] = std::move(makePiece(f, r, piece));
            
            // Adding coordinates in color-specific vectors, with king always at front
            if (islower(piece)) {
                if (piece == 'r')
                    white_pieces_.push_front({f,r});
                else
                    white_pieces_.push_back({f,r});
            } else  {
                if (piece == 'R')
                    black_pieces_.push_front({f,r});
                else
                    black_pieces_.push_back({f,r});
            }

        }
    }
}

bool chess::Board::isEmpty(short file, short rank) const {
    return board_[file][rank] == nullptr;
}
bool chess::Board::isEmpty(chess::Coordinates coords) const {
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
bool chess::Board::isThreatenBy(chess::Coordinates coords, chess::Color pieceColor) {
    King king{coords.file, coords.rank, pieceColor};
    //Queen queen{coords.file, coords.rank, opposite(attackerColor)};
    //Rook rook{coords.file, coords.rank, opposite(attackerColor)};
    //Bishop bishop{coords.file, coords.rank, opposite(attackerColor)};
    Knight knight{coords.file, coords.rank, pieceColor};
    //Pawn pawn{coords.file, coords.rank, opposite(attackerColor)};

    const Piece* possiblePieces[] = {
        &king,
        //&queen,
        //&rook,
        //&bishop,
        &knight
        //&pawn
    };

    for (const Piece* piece : possiblePieces) {
        std::vector<chess::Coordinates> moves = piece->legalMoves(*this);

        for (chess::Coordinates move : moves) {
            if (at(move.file, move.rank).ascii() == piece->ascii()
                && at(move.file, move.rank).color() != piece->color())
            {
                return true;
            }
        }
    }
    return false;
}

std::unique_ptr<chess::Piece> chess::Board::makePiece(short file, short rank, char c) {
    Color pieceColor = islower(c) ? WHITE : BLACK;
    switch (toupper(c))
    {
    case 'R':
        return std::make_unique<King>(file, rank, pieceColor);
    case 'D':
        // Donna
        break;
    case 'T':
        return std::make_unique<Rook>(file, rank, pieceColor);
    case 'A':
        // Alfiere
        break;
    case 'C':
        return std::make_unique<Knight>(file, rank, pieceColor);
    case 'P':
        // Pedone
        break;
    default:
        return nullptr;
    }
}

// Print the board. For every piece it prints its ascii character, lower if white,
// upper if black. It prints a blank space if there is no piece.
// It also prints the files and ranks coordinates.
std::ostream& chess::operator<<(std::ostream& os, Board& board) {

    for (short r = 7; r >= 0; r--) {
        os << r+1 << " ";
        for (short f = 0; f < 8; f++) {
            if (board.isEmpty(f, r))
                os << " ";
            else {
                char c = board.at(f, r).ascii();
                os << (board.at(f, r).color() == Color::WHITE ? (char)tolower(c) : (char)toupper(c));
            };
        }
        os << "\n";
    }
    os << "\n  ABCDEFGH\n";
    return os;
}