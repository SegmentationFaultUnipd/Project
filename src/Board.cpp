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
            board_[f][r] = std::move(makePiece({f,r}, piece));
            
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

bool chess::Board::isEmpty(chess::Coordinates coords) const {
    return board_[coords.file][coords.rank] == nullptr;
}

chess::Piece& chess::Board::at(Coordinates coords) {
    assert(!isEmpty(coords));
    return *board_[coords.file][coords.rank];
}

// Move the piece 
void chess::Board::move(Coordinates from, Coordinates to) {
    assert(from.file >= 0 && from.file < 8);
    assert(from.rank >= 0 && from.rank < 8);
    assert(to.file >= 0 && to.file < 8);
    assert(to.rank >= 0 && to.rank < 8);
    
    if (isEmpty(from))
        return; //Illegal Movement

    Piece& moving_piece = at(from);
    if (moving_piece.canMove(to, *this) ) {

        // Eat piece
        if (!isEmpty(to)
            && at(to).color() != at(from).color())
        {
            getPieces(board_[to.file][to.rank]->color()).remove({to.file, to.rank});
        }

        // Moving in matrix
        board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
        board_[from.file][from.rank] = nullptr;

        // Update piece position
        moving_piece.move(to);
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
    King king{coords, pieceColor};
    //Queen queen{coords.file, coords.rank, pieceColor};
    Rook rook{coords, pieceColor};
    //Bishop bishop{coords.file, coords.rank, pieceColor};
    Knight knight{coords, pieceColor};
    //Pawn pawn{coords.file, coords.rank, pieceColor};

    const Piece* possiblePieces[] = {
        &king,
        //&queen,
        &rook,
        //&bishop,
        &knight
        //&pawn
    };

    for (const Piece* piece : possiblePieces) {
        std::vector<chess::Coordinates> moves = piece->legalMoves(*this);

        for (chess::Coordinates move : moves) { 
            if (!isEmpty(move)
                && at(move).ascii() == piece->ascii()
                && at(move).color() != piece->color())
            {
                return true;
            }
        }
    }
    return false;
}

std::unique_ptr<chess::Piece> chess::Board::makePiece(Coordinates coords, char c) {
    Color pieceColor = islower(c) ? WHITE : BLACK;
    switch (toupper(c))
    {
    case 'R':
        return std::make_unique<King>(coords, pieceColor);
    case 'D':
        // Donna
        break;
    case 'T':
        return std::make_unique<Rook>(coords, pieceColor);
    case 'A':
        // Alfiere
        break;
    case 'C':
        return std::make_unique<Knight>(coords, pieceColor);
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
            if (board.isEmpty({f,r}))
                os << " ";
            else {
                char c = board.at({f,r}).ascii();
                os << (board.at({f,r}).color() == Color::WHITE ? (char)tolower(c) : (char)toupper(c));
            };
        }
        os << "\n";
    }
    os << "\n  ABCDEFGH\n";
    return os;
}