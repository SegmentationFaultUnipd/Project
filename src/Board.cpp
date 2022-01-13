#include "Board.h"

chess::Board::Board() {
    char setup[8][8] = {
        'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'C', ' ', 
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
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
            if (setup[r][f] != ' ') {
                char piece = setup[r][f];
                Coordinates coords{f,r};
                Color color = islower(piece) ? WHITE : BLACK;

                // Adding in matrix
                board_[f][r] = std::move(makePiece(piece, coords, color));
                
                // Adding coordinates in vector, king always at front
                if (at(coords).ascii() == 'R')
                    getPieces(color).push_front(coords);
                else
                    getPieces(color).push_back(coords);
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
        if (isCastlingMove(from, to))
            return castle(from, to);
        else if (isEnPassantMove(from, to))
            return enPassant(from, to);
        else
            return updatePosition(from, to);
    }
    return false;
}

bool chess::Board::castle(Coordinates from, Coordinates to) {
    // FILIPPO NIERO

    // Ricorda che l'arrocco è una mossa del re e le coordinate 'to' non sono quelle della torre
    // ma sono le coordinate della casa in cui andrà il Re.

    // Puoi usare updatePosition

    return false;
}

bool chess::Board::enPassant(Coordinates from, Coordinates to) {
    // TOMMASO

    // Puoi usare updatePosition
}

bool chess::Board::isCastlingMove(Coordinates from, Coordinates to) {
    return at(from).ascii() == 'R' && (from.file - to.file) > 0;
}

bool chess::Board::isEnPassantMove(Coordinates from, Coordinates to) {
    std::pair<Coordinates, Coordinates> candidateMove{from, to};
    for (std::pair<Coordinates, Coordinates> move : availableEnPassants_)
        if (move == candidateMove) 
            return true;
    return false;
}


void chess::Board::addToAvailableEnPassants(Coordinates from, Coordinates to) {
    availableEnPassants_.push_back({from, to});
}

void chess::Board::emptyEnPassant() {
    availableEnPassants_ = {};
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

// Refactor to "causeSelfCheck"
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
bool chess::Board::isThreatened(chess::Coordinates coords, chess::Color pieceColor) {
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
    return isThreatened(getPieces(kingColor).front(), kingColor);
}

void chess::Board::promote(Coordinates pawnCoords, char piece) {
    Color pieceColor = at(pawnCoords).color();
    board_[pawnCoords.file][pawnCoords.rank] = std::move(makePiece(piece, pawnCoords, pieceColor));
}

std::unique_ptr<chess::Piece> chess::Board::makePiece(char c, Coordinates coords, Color pieceColor) const {
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

std::unique_ptr<chess::Piece> chess::Board::copyPiece(Piece& piece) const {
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