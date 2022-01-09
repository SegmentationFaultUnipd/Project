#include <iostream>

#include "Board.h"
#include "Coordinates.h"
#include "Color.h"
#include "Players/HumanPlayer.h"

int main() {
    chess::Board board;

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

    board.move(1,0, 0,2);
    board.move(0,2, 0,0);
    std::cout << board.isThreatenBy({0,6}, chess::Color::WHITE) << "\n";

    std::cout << board << std::endl;
    return 0;
}