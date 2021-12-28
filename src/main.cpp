
#include <iostream>
#include "Board.h"

int main() {
    chess::Board board;
    
    board.move(4,6, 4,7);
    board.move(4,6, 4,5);
    board.move(4,6, 6,5);

    std::cout << board << std::endl;
    return 0;
}