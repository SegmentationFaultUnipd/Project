#include "HumanPlayer.h"

void chess::HumanPlayer::nextTurn(Board &board, chess::Coordinates &from, chess::Coordinates &to) {
    bool correct_notation = false;
    std::string input_from, input_to;
    do {
        std::cout << "Prossima mossa: ";
        std::cin >> input_from >> input_to;
        correct_notation = verifyNotation(input_from) && verifyNotation(input_to);
		if(input_from == "XX" && input_to == "XX") { //Print current state of the board
			std::cout << board;
		}
    } while (!correct_notation);

    from = Coordinates{input_from};
	to = Coordinates{input_to};
}

bool chess::HumanPlayer::verifyNotation(std::string coords) {
    if (coords.size() != 2)
        return false;

    short f = (char)tolower(coords[0]) - 'a' + 1;
    short r = coords[1] - '0';

    return f >= 1 && f <= 8 && r >= 1 && r <= 8;
}