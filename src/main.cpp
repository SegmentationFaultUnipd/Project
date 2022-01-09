#include <iostream>

#include "Board.h"
#include "Coordinates.h"
#include "Color.h"
#include "Players/HumanPlayer.h"

int main() {

    chess::Board board;

    chess::Piece& p = board.at({7,7});
    std::vector<chess::Coordinates> moves = p.legalMoves(board);
    std::cout << p.ascii() << (char)(p.file() + 'a') << p.rank()+1 << " {";
    for (chess::Coordinates move : moves)
        std::cout << (char)(move.file + 'a') << move.rank + 1 << ", ";
    std::cout << "}" << std::endl;

    chess::Piece& p2 = board.at({4,7});
    std::vector<chess::Coordinates> moves2 = p2.legalMoves(board);
    std::cout << p2.ascii() << (char)(p2.file() + 'a') << p2.rank()+1 << " {";
    for (chess::Coordinates move : moves2)
        std::cout << (char)(move.file + 'a') << move.rank + 1 << ", ";
    std::cout << "}" << std::endl;

    /*
    chess::HumanPlayer hp{board.getPieces(chess::Color::WHITE), chess::Color::WHITE};
    chess::Coordinates from, to;
    bool showBoard = false;
    
    hp.nextTurn(from, to);

    std::cout << (char)(from.file + 'a') << from.rank + 1 << " "
              << (char)(to.file + 'a')   << to.rank + 1   << "\n";


    

    std::vector<chess::Coordinates> legalMoves = board.legalMovesOf(board.at(6,5));

    for (chess::Coordinates c : legalMoves)
        std::cout << c.file << "," << c.rank << "\n";
    */

    std::cout << board << std::endl;

    return 0;
}