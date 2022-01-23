//AUTORE: Filippo Mazzarotto
#include "Board.h"

chess::Board::Board()
{
    char ascii_setup[8][8] = {
        //1   2    3    4    5    6    7    8
        't', 'p', ' ', ' ', ' ', ' ', 'P', 'T', //a
        'c', 'p', ' ', ' ', ' ', ' ', 'P', 'C', //b
        'a', 'p', ' ', ' ', ' ', ' ', 'P', 'A', //c
        'd', 'p', ' ', ' ', ' ', ' ', 'P', 'D', //d
        'r', 'p', ' ', ' ', ' ', ' ', 'P', 'R', //e
        'a', 'p', ' ', ' ', ' ', ' ', 'P', 'A', //f
        'c', 'p', ' ', ' ', ' ', ' ', 'P', 'C', //g
        't', 'p', ' ', ' ', ' ', ' ', 'P', 'T', //h
    };

    for (short r = 0; r < 8; r++) {
        for (short f = 0; f < 8; f++) {
            char ascii_piece{ascii_setup[f][r]};
            Coordinates coords{f, r};
            Color color = islower(ascii_piece) ? WHITE : BLACK;

            if (ascii_piece != ' ')
                addPiece_(ascii_piece, coords, color);
        }
    }
}

chess::Board::Board(const Board& to_copy) {
    for (int file = 0; file < 8; ++file) {
        for (int rank = 0; rank < 8; ++rank) {
            if (!to_copy.isEmpty({file, rank}))
                board_[file][rank] = clonePiece_(to_copy.at({file, rank}));
        }
    }

    this->black_coords_ = to_copy.black_coords_;
    this->white_coords_ = to_copy.white_coords_;
    this->available_en_passants_ = to_copy.available_en_passants_;
}

void chess::Board::addPiece_(char asciiPiece, Coordinates coords, Color color) {
    std::unique_ptr<Piece> pieceToAdd = makePiece_(asciiPiece, coords, color);
    addPieceToMatrix_(pieceToAdd, coords);
    addPieceCoords_(coords);
}

void chess::Board::addPieceToMatrix_(std::unique_ptr<Piece>& pieceToAdd, Coordinates coords) {
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

const chess::Piece& chess::Board::at(Coordinates coords) const
{
    assert(!isEmpty(coords));
    return *board_[coords.file][coords.rank];
}

chess::Piece &chess::Board::at(Coordinates coords)
{
    assert(!isEmpty(coords));
    return *board_[coords.file][coords.rank];
}

bool chess::Board::isKingInCheckAfterMove(Coordinates from, Coordinates to) {
    Board copy{*this};

    copy.handleMoveType_(from, to);

    return copy.isKingInCheck( at(from).color());
}

// Move the piece
bool chess::Board::move(Coordinates from, Coordinates to)
{
    assert(!isEmpty(from));
    assert(from.inBounderies());
    assert(to.inBounderies());

    Color current_color = at(from).color();

    bool is_valid_move = at(from).canMoveAt(to, *this) && !isKingInCheckAfterMove(from, to);

    if (is_valid_move) {
        handleMoveType_(from, to);
        clearEnPassants_(current_color);
    }

    return is_valid_move;
}

void chess::Board::handleMoveType_(Coordinates from, Coordinates to) {
    if (isEnPassantMove(from, to))
        doEnPassantMove(from, to);
    else if (isCastlingMove(from, to))
        doCastlingMove(from, to);
    else
        updatePosition_(from, to);
}

void chess::Board::doCastlingMove(Coordinates from, Coordinates to)
{
    Color castling_color = at(from).color();

    bool castle_queenside = to.file < 4;

    Coordinates rook_old_coords, rook_new_coords;
    if (castle_queenside) {
        rook_old_coords = {LEFT_FILE, to.rank};
        rook_new_coords = {to.file + 1, to.rank};
    } else {
        rook_old_coords = {RIGHT_FILE, to.rank};
        rook_new_coords = {to.file - 1, to.rank};
    }

    updatePosition_(from, to);
    updatePosition_(rook_old_coords, rook_new_coords);
}

void chess::Board::doEnPassantMove(Coordinates from, Coordinates to)
{
    Coordinates piece_to_eat;
    if (to.rank > from.rank)
        piece_to_eat = {to.file, to.rank - 1};
    else
        piece_to_eat = {to.file, to.rank + 1};

    updatePosition_(from, to);
    removePiece_(piece_to_eat);
}

bool chess::Board::isCastlingMove(Coordinates from, Coordinates to)
{
    return at(from).ascii() == 'R' && abs(from.file - to.file) > 1;
}

bool chess::Board::isEnPassantMove(Coordinates from, Coordinates to)
{
    Color color = at(from).color();

    std::pair<Coordinates, Coordinates> candidate_move{from, to};

    for (auto available_en_passant : available_en_passants_)
        if (candidate_move == available_en_passant)
            return true;

    return false;
}

void chess::Board::addAvailableEnPassant(Coordinates from, Coordinates to)
{
    available_en_passants_.push_back({from, to});
}

void chess::Board::clearEnPassants_(Color of_color)
{
    available_en_passants_.remove_if([this, of_color](std::pair<Coordinates, Coordinates> move) {
        if (isEmpty(move.first))
            return at(move.second).color() == of_color;
        return at(move.first).color() == of_color;
    });
}

void chess::Board::removePiece_(Coordinates coords) {
    if (isEmpty(coords))
        return;

    Color color = at(coords).color();
    getPiecesCoords(color).remove(coords);
    board_[coords.file][coords.rank] = nullptr;
}

void chess::Board::updatePosition_(Coordinates from, Coordinates to)
{
    // Update position in own members
    at(from).move(to, *this);

    // Update piece position in piece list
    std::list<Coordinates>& own_color_pieces_coords = getPiecesCoords(at(from).color());
    for (Coordinates &piece_coords : own_color_pieces_coords) {
        if (piece_coords == from) {
            piece_coords = to;
            break;
        }
    }

    // Eat piece
    if (!isEmpty(to))
        getPiecesCoords(at(to).color()).remove(to);

    // Finally, update matrix
    board_[to.file][to.rank] = std::move(board_[from.file][from.rank]);
    board_[from.file][from.rank] = nullptr;
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

bool chess::Board::isEmptyOrOppositeColor(Coordinates landing_square, Color piece_color) const {
    return isEmpty(landing_square) || at(landing_square).color() != piece_color;
}

bool chess::Board::isOppositeColor(Coordinates landing_square, Color piece_color) const {
    return !isEmpty(landing_square) && at(landing_square).color() != piece_color;
}

// Fact: Having two pieces of the same type P1 and P2, if P1 can take P2 then P2 can take P1.
// Only exception: en passant
bool chess::Board::isThreatened(Coordinates square, Color piece_color)
{
    const std::unique_ptr<Piece> dummy_pieces[] = {
       	//std::make_unique<King>(square, piece_color),
        std::make_unique<Queen>(square, piece_color),
        std::make_unique<Rook>(square, piece_color),
        std::make_unique<Bishop>(square, piece_color),
        std::make_unique<Knight>(square, piece_color),
        std::make_unique<Pawn>(square, piece_color),
    };

    for (const auto& dummy_piece : dummy_pieces) {
        const std::vector<Piece*> &possible_threats = dummy_piece->takeablePieces(*this);

        for (Piece *possible_threat : possible_threats) {
            if (dummy_piece->ascii() == possible_threat->ascii()) {
                return true;
            }
        }
    }

    //Exception: en passants
    for (std::pair<Coordinates, Coordinates> en_passant : available_en_passants_) {
        Coordinates& landing_square = en_passant.second;
        if (landing_square == square) {
            return true;
        }
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

std::unique_ptr<chess::Piece> chess::Board::clonePiece_(const Piece &piece) const
{
    Piece& to_copy = const_cast<Piece&>(piece);
    switch(piece.ascii())
    {
    case 'R':
        return std::make_unique<King>(static_cast<King&>(to_copy));
    case 'D':
        return std::make_unique<Queen>(static_cast<Queen&>(to_copy));
    case 'T':
        return std::make_unique<Rook>(static_cast<Rook&>(to_copy));
    case 'A':
        return std::make_unique<Bishop>(static_cast<Bishop&>(to_copy));
    case 'C':
        return std::make_unique<Knight>(static_cast<Knight&>(to_copy));
    case 'P':
        return std::make_unique<Pawn>(static_cast<Pawn&>(to_copy));
    }
    return nullptr;
}

std::ostream &chess::operator<<(std::ostream &os, const Board &board)
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
