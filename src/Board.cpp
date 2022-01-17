#include "Board.h"

chess::Board::Board()
{
    char asciiSetup[8][8] = {
        't', 'p', ' ', ' ', ' ', ' ', 'P', 'T',
        'c', 'p', ' ', ' ', ' ', ' ', 'P', 'C',
        'a', 'p', ' ', ' ', ' ', ' ', 'P', 'A',
        'd', 'p', ' ', ' ', ' ', ' ', 'P', 'D',
        'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R',
        'a', 'p', ' ', ' ', ' ', ' ', 'P', 'A',
        'c', 'p', ' ', ' ', ' ', ' ', 'P', 'C',
        't', 'p', ' ', ' ', ' ', ' ', 'P', 'T',
    };

    for (short r = 0; r < 8; r++) {
        for (short f = 0; f < 8; f++) {
            char asciiPiece{asciiSetup[f][r]};
            Coordinates coords{f, r};
            Color color = islower(asciiPiece) ? WHITE : BLACK;

            addPiece_(asciiPiece, coords, color);
        }
    }
}

void chess::Board::addPiece_(char asciiPiece, Coordinates coords, Color color) {
    std::unique_ptr<Piece> pieceToAdd = makePiece_(asciiPiece, coords, color);
    
    addPieceToMatrix_(pieceToAdd, coords);
    if (!isEmpty(coords))
        addPieceCoords_(coords);
}

void chess::Board::addPieceToMatrix_(std::unique_ptr<Piece>& pieceToAdd, Coordinates coords) {
    if (pieceToAdd == nullptr)
        board_[coords.file][coords.rank] = nullptr;
    else
        board_[coords.file][coords.rank] = std::move(pieceToAdd);
}

void chess::Board::addPieceCoords_(Coordinates coords) {
    Color pieceColor = at(coords).color();

    if (at(coords).ascii() == 'R')
        getPiecesCoords(pieceColor).push_front(coords);
    else
        getPiecesCoords(pieceColor).push_back(coords);
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
            return updatePosition_(from, to);
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
    return at(from).ascii() == 'R' && abs(from.file - to.file) > 1;
}

bool chess::Board::isEnPassantMove(Coordinates from, Coordinates to)
{
    std::pair<Coordinates, Coordinates> candidate_move{from, to};
    for (std::pair<Coordinates, Coordinates> available_en_passant : available_en_passants_)
        if (candidate_move == available_en_passant)
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

bool chess::Board::updatePosition_(Coordinates from, Coordinates to)
{
    // Update position in own members
    at(from).move(to);

    // Update piece position in piece list
    std::list<Coordinates>& own_color_pieces = getPiecesCoords(at(from).color());
    for (Coordinates &piece : own_color_pieces) {
        if (piece == from) {
            piece = to;
            break;
        }
    }

    // Eat piece
    if (!isEmpty(to))
        getPiecesCoords(at(to).color()).remove(to);

    // Finally, update matrix
    board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
    board_[from.file][from.rank] = nullptr;
    return true;
}

bool chess::Board::moveCauseSelfCheck(Coordinates from, Coordinates to)
{
    assert(!isEmpty(from));

    bool kingInCheck;
    std::unique_ptr<Piece> moving_piece, landing_piece;

    // Save old state
    moving_piece = copyPiece_(at(from));
    if (!isEmpty(to))
        landing_piece = copyPiece_(at(to));

    // Movement in matrix
    board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
    board_[from.file][from.rank] = nullptr;

    // Check move validity
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

std::list<chess::Coordinates> &chess::Board::getPiecesCoords(chess::Color color)
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

// Fact: Having two pieces of the same type P1 and P2, if P1 can take P2 then P2 can take P1.
// Only exception: en passant
bool chess::Board::isThreatened(Coordinates square, Color piece_color)
{
    const std::unique_ptr<Piece> dummy_pieces[] = {
        std::make_unique<King>(square, piece_color),
        std::make_unique<Queen>(square, piece_color),
        std::make_unique<Rook>(square, piece_color),
        std::make_unique<Bishop>(square, piece_color),
        std::make_unique<Knight>(square, piece_color),
        std::make_unique<Pawn>(square, piece_color),
    };

    for (const auto& dummy_piece : dummy_pieces) {
        const std::vector<Piece*> &possible_attackers = dummy_piece->takeablePieces(*this);

        for (Piece *possible_attacker : possible_attackers)
            if (dummy_piece->ascii() == possible_attacker->ascii())
                return true;
    }

    for (std::pair<Coordinates, Coordinates> en_passant : available_en_passants_) {
        Coordinates landing_square = en_passant.second;
        if (landing_square == square)
            return true;
    }
    return false;
}

chess::Piece &chess::Board::getKing(chess::Color king_color)
{
    return at(getPiecesCoords(king_color).front());
}

bool chess::Board::isKingInCheck(chess::Color king_color)
{
    return isThreatened(getKing(king_color).coordinates(), king_color);
}

void chess::Board::promote(Coordinates pawn_coords, char piece)
{
    Color pieceColor = at(pawn_coords).color();
    board_[pawn_coords.file][pawn_coords.rank] = std::move(makePiece_(piece, pawn_coords, pieceColor));
}

std::unique_ptr<chess::Piece> chess::Board::makePiece_(char c, Coordinates coords, Color color) const
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

std::unique_ptr<chess::Piece> chess::Board::copyPiece_(Piece &piece) const
{
    return makePiece_(piece.ascii(), piece.coordinates(), piece.color());
}

std::ostream &chess::operator<<(std::ostream &os, Board &board)
{
    for (short r = 7; r >= 0; r--) {
        os << r + 1 << " ";
        for (short f = 0; f < 8; f++) {
            if (board.isEmpty({f, r}))
                os << " ";
            else {
                char c = board.at({f, r}).ascii();
                os << (board.at({f, r}).color() == WHITE ? (char)tolower(c) : (char)toupper(c));
            };
        }
        os << "\n";
    }
    os << "\n  ABCDEFGH\n";
    return os;
}