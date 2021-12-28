
#include <iostream>

#include "Board.h"
#include "Coordinates.h"

int main() {
    chess::Board board;
    
    board.move(4,6, 4,7); //Impossible movement
    board.move(4,6, 6,5);
    std::vector<chess::Coordinates> legalMoves = board.legalMovesOf(board.at(6,5));

    for (chess::Coordinates c : legalMoves)
        std::cout << (char)('a' + c.file) << c.rank + 1 << "\n";

    std::cout << board << std::endl;
    return 0;
}