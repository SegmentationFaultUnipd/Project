#include "HumanPlayer.h"

void chess::HumanPlayer::nextTurn(Board& board, chess::Coordinates& from, chess::Coordinates& to) const {
    bool correct_notation = false;
    std::string input_from, input_to;
    do {
        std::cout << "Prossima mossa: ";
        std::cin >> input_from >> input_to;

        for(char& c : input_from)
            c = tolower(c);
        for(char& c : input_to)
            c = tolower(c);

        if (input_from == "xx" && input_to == "xx") {
            std::cout << board << "\n";
            correct_notation = false;
        } else {
            correct_notation = verifyNotation(input_from) && verifyNotation(input_to);
            if (!correct_notation)
                std::cout << "Notazione errata\n";
        }
        
    } while (!correct_notation);

    from = Coordinates{input_from};
    to = Coordinates{input_to};
}

bool chess::HumanPlayer::verifyNotation(std::string coords) const {
    if (coords.size() != 2)
        return false;

    short f = (char)tolower(coords[0]) - 'a' + 1;
    short r = coords[1] - '0';

    return f >= 1 && f <= 8 && r >= 1 && r <= 8;
}