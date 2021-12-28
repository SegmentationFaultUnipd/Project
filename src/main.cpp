
#include <iostream>
#include "Board.h"

int main() {
    chess::Board board;
    
    board.move(4,6, 4,5);

    std::cout << board << std::endl;
    return 0;
}