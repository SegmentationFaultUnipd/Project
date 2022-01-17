#include "Board.h"

chess::Board::Board()
{
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
    for (short r = 7; r >= 0; r--)
    {
        for (short f = 0; f < 8; f++)
        {
            if (setup[r][f] != ' ')
            {
                char piece = setup[r][f];
                Coordinates coords{f, r};
                Color color = islower(piece) ? WHITE : BLACK;

                // Adding in matrix
                board_[f][r] = std::move(makePiece(piece, coords, color));

                // Adding coordinates in vector, king always at front
                if (at(coords).ascii() == 'R')
                    getPieceCoords(color).push_front(coords);
                else
                    getPieceCoords(color).push_back(coords);
            }
        }
    }
}

bool chess::Board::isEmpty(chess::Coordinates coords) const
{
    return board_[coords.file][coords.rank] == nullptr;
}

chess::Piece &chess::Board::at(Coordinates coords) const
{
    assert(!isEmpty(coords));
    return *board_[coords.file][coords.rank];
}

// Move the piece
bool chess::Board::move(Coordinates from, Coordinates to)
{
    assert(from.file >= 0 && from.file < 8);
    assert(from.rank >= 0 && from.rank < 8);
    assert(to.file >= 0 && to.file < 8);
    assert(to.rank >= 0 && to.rank < 8);

    if (!isEmpty(from) && at(from).canMoveAt(to, *this))
    {
        if (isCastlingMove(from, to))
            return doCastlingMove(from, to);
        else if (isEnPassantMove(from, to))
            return doEnPassantMove(from, to);
        else
            return updatePosition(from, to);
    }
    return false;
}

bool chess::Board::doCastlingMove(Coordinates from, Coordinates to)
{
    // FILIPPO NIERO

    // Ricorda che l'arrocco è una mossa del re e le coordinate 'to' non sono quelle della torre
    // ma sono le coordinate della casa in cui andrà il Re.

    // Puoi usare updatePosition

    return false;
}

bool chess::Board::doEnPassantMove(Coordinates from, Coordinates to)
{
    // TOMMASO
    // Puoi usare updatePosition
    return updatePosition(from, to);
}

bool chess::Board::isCastlingMove(Coordinates from, Coordinates to)
{
    return at(from).ascii() == 'R' && (from.file - to.file) > 0;
}

bool chess::Board::isEnPassantMove(Coordinates from, Coordinates to)
{
    std::pair<Coordinates, Coordinates> candidateMove{from, to};
    for (std::pair<Coordinates, Coordinates> move : available_en_passants_)
        if (move == candidateMove)
            return true;
    return false;
}

void chess::Board::addAvailableEnPassant(Coordinates from, Coordinates to)
{
    available_en_passants_.push_back({from, to});
}

void chess::Board::clearEnPassants()
{
    available_en_passants_ = {};
}

bool chess::Board::updatePosition(Coordinates from, Coordinates to)
{
    // Update piece position in members
    at(from).move(to);

    // Update piece position
    for (Coordinates &piece : getPieceCoords(at(from).color()))
    {
        if (piece == from)
        {
            piece = to;
            break;
        }
    }

    // Eat piece
    if (!isEmpty(to))
        getPieceCoords(at(to).color()).remove(to);

    // Update matrix
    board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
    board_[from.file][from.rank] = nullptr;

    return true;
}

bool chess::Board::doesMoveCauseSelfCheck(Coordinates from, Coordinates to)
{
    assert(!isEmpty(from));

    bool kingInCheck;
    std::unique_ptr<Piece> moving_piece, landing_piece;

    // Save old state
    moving_piece = copyPiece(at(from));
    if (!isEmpty(to))
        landing_piece = copyPiece(at(to));

    // Movement in matrix
    board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
    board_[from.file][from.rank] = nullptr;

    kingInCheck = isKingInCheck(moving_piece->color());

    // Reset
    board_[from.file][from.rank] = std::move(moving_piece);
    board_[to.file][to.rank] = std::move(landing_piece);

    return !kingInCheck;
}

const std::vector<chess::Coordinates> chess::Board::legalMovesOf(chess::Piece &piece)
{
    return piece.legalMoves(*this);
}

std::list<chess::Coordinates> &chess::Board::getPieceCoords(chess::Color color)
{
    if (color == WHITE)
        return white_coords_;
    return black_coords_;
}

bool chess::Board::isReachableBy(Coordinates landing_square, const Piece& piece) const {
    return isEmpty(landing_square) || at(landing_square).color() != piece.color();
}

bool chess::Board::isTakingAPiece(Coordinates landing_square, const Piece& piece) const {
    return !isEmpty(landing_square) && at(landing_square).color() != piece.color();
}

// Having two pieces of the same type P1 and P2, if P1 can take P2, then P2 can also take P1.
// Based on this fact, the function place multiple dummy pieces (one of each type)
// on the specified coordinates and check if the dummy piece can take
// a piece of the same type.
bool chess::Board::isThreatened(Coordinates square, Color piece_color)
{
    King king{square, piece_color};
    Queen queen{square, piece_color};
    Rook rook{square, piece_color};
    Bishop bishop{square, piece_color};
    Knight knight{square, piece_color};
    Pawn pawn{square, piece_color};

    const Piece* dummy_pieces[] = {&king, &queen, &rook, &bishop, &knight, &pawn};

    for (const Piece* dummy_piece : dummy_pieces)
    {
        const std::vector<Piece*> &takeable_pieces = dummy_piece->takeablePieces(*this);

        for (Piece *takeable_piece : takeable_pieces)
            if (dummy_piece->ascii() == takeable_piece->ascii()) // Found a piece that threaten the square
                return true;
    }
    return false;
}

chess::Piece &chess::Board::getKing(chess::Color king_color)
{
    // King always at front
    return at(getPieceCoords(king_color).front());
}

bool chess::Board::isKingInCheck(chess::Color king_color)
{
    return isThreatened(getKing(king_color).coordinates(), king_color);
}

void chess::Board::promote(Coordinates pawn_coords, char piece)
{
    Color pieceColor = at(pawn_coords).color();
    board_[pawn_coords.file][pawn_coords.rank] = std::move(makePiece(piece, pawn_coords, pieceColor));
}

std::unique_ptr<chess::Piece> chess::Board::makePiece(char c, Coordinates coords, Color color) const
{
    switch (toupper(c))
    {
    case 'R':
        return std::make_unique<King>(coords, color);
    case 'D':
        return std::make_unique<Queen>(coords, color);
    case 'T':
        return std::make_unique<Rook>(coords, color);
    case 'A':
        return std::make_unique<Bishop>(coords, color);
    case 'C':
        return std::make_unique<Knight>(coords, color);
    case 'P':
        return std::make_unique<Pawn>(coords, color);
    }

    return nullptr;
}

std::unique_ptr<chess::Piece> chess::Board::copyPiece(Piece &piece) const
{
    return makePiece(piece.ascii(), {piece.file(), piece.rank()}, piece.color());
}

// Print the board. For every piece it prints its ascii character, lower if white, upper if black.
// It also prints the files and ranks coordinates.
std::ostream &chess::operator<<(std::ostream &os, Board &board)
{

    for (short r = 7; r >= 0; r--)
    {
        os << r + 1 << " ";
        for (short f = 0; f < 8; f++)
        {
            if (board.isEmpty({f, r}))
                os << " ";
            else
            {
                char c = board.at({f, r}).ascii();
                os << (board.at({f, r}).color() == WHITE ? (char)tolower(c) : (char)toupper(c));
            };
        }
        os << "\n";
    }
    os << "\n  ABCDEFGH\n";
    return os;
}