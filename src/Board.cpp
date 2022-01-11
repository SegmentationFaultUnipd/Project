#include "Board.h"

chess::Board::Board() {
    char setup[8][8] = {
        ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' ',
        'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        'R', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };

    /*
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
    */
    // Initialize pointer matrix
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            board_[i][j] = nullptr;

    // Insert pieces from setup, white (lower char) with lower rank
    for (short r = 7; r >= 0; r--) {
        for (short f = 0; f < 8; f++) {
            char piece = setup[r][f];

            // Adding in matrix
            Color pieceColor = islower(piece) ? WHITE : BLACK;
            board_[f][r] = std::move(makePiece(piece, {f,r}, pieceColor));
            
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
bool chess::Board::move(Coordinates from, Coordinates to) {
    assert(from.file >= 0 && from.file < 8);
    assert(from.rank >= 0 && from.rank < 8);
    assert(to.file >= 0 && to.file < 8);
    assert(to.rank >= 0 && to.rank < 8);

    if (!isEmpty(from) && at(from).canMove(to, *this) ) {
        if (at(from).ascii() == 'R' && abs(from.file - to.file) > 1)
            return castle(from, to);
        else
            return updatePosition(from, to);
    }
    return false;
}

bool chess::Board::updatePosition(Coordinates from, Coordinates to) {
    // Update piece position in members
    at(from).move(to);

    // Update piece position
    for (Coordinates& piece : getPieces(at(from).color())) {
        if (piece == from) {
            piece = to;
            break;
        }
    }

    // Eat piece
    if (!isEmpty(to))
        getPieces(at(to).color()).remove(to);

    // Update matrix
    board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
    board_[from.file][from.rank] = nullptr;

    return true;
}

bool chess::Board::tryMove(Coordinates from, Coordinates to) {
    bool kingInCheck;
    std::unique_ptr<Piece> movingPiece, landingPiece;

    if (isEmpty(from))
        return false;

    // Save old state
    movingPiece = copyPiece(at(from));
    if (!isEmpty(to)) 
        landingPiece = copyPiece(at(to)); // ate a piece

    // Movement in matrix
    board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
    board_[from.file][from.rank] = nullptr;
    
    kingInCheck = isKingInCheck(movingPiece->color());

    // Reset
    board_[from.file][from.rank] = std::move(movingPiece);
    board_[to.file][to.rank] = std::move(landingPiece);

    return !kingInCheck; // Move is correct if king is not in check
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
bool chess::Board::isThreaten(chess::Coordinates coords, chess::Color pieceColor) {
    King king{coords, pieceColor};
    //Queen queen{coords, pieceColor};
    Rook rook{coords, pieceColor};
    Bishop bishop{coords, pieceColor};
    Knight knight{coords, pieceColor};
    Pawn pawn{coords, pieceColor};

    const Piece* possiblePieces[] = { &king, /*&queen,*/ &rook, &bishop, &knight, &pawn };

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

bool chess::Board::isKingInCheck(chess::Color kingColor) {
    // King always at front
    return isThreaten(getPieces(kingColor).front(), kingColor);
}

void chess::Board::promote(Coordinates pawnCoords, char piece) {
    Color pieceColor = at(pawnCoords).color();
    board_[pawnCoords.file][pawnCoords.rank] = std::move(makePiece(piece, pawnCoords, pieceColor));
}

std::unique_ptr<chess::Piece> chess::Board::makePiece(char c, Coordinates coords, Color pieceColor) {
    switch (toupper(c))
    {
    case 'R':
        return std::make_unique<King>(coords, pieceColor);
    case 'D':
        //return std::make_unique<Queen>(coords, pieceColor);
        break;
    case 'T':
        return std::make_unique<Rook>(coords, pieceColor);
    case 'A':
        return std::make_unique<Bishop>(coords, pieceColor);
    case 'C':
        return std::make_unique<Knight>(coords, pieceColor);
    case 'P':
        return std::make_unique<Pawn>(coords, pieceColor);

    default:
        return nullptr;
    }
}

bool chess::Board::castle(Coordinates from, Coordinates to) {
    //FILIPPO NIERO
    // Ricorda che l'arrocco è una mossa del re e le coordinate 'to' non sono quelle della torre
    // ma sono le coordinate della casa in cui andrà il Re.

    // Puoi usare updatePosition

    return false;
}

std::unique_ptr<chess::Piece> chess::Board::copyPiece(Piece& piece) {
    return makePiece(piece.ascii(), {piece.file(), piece.rank()}, piece.color());
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