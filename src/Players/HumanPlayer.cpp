//AUTORE: Filippo Mazzarotto
#include "HumanPlayer.h"

void chess::HumanPlayer::stringToLower(std::string &string) {
    for(char& c : string)
        c = tolower(c);
}

void chess::HumanPlayer::nextTurn(Board& board, chess::Coordinates& from, chess::Coordinates& to) {
    bool correct_notation = false;
    std::string input_from, input_to;

    do {
        std::cout << "Prossima mossa: ";

        std::cin >> input_from >>input_to;

        stringToLower(input_from);
        stringToLower(input_to);

        correct_notation = verifyNotation(input_from) && verifyNotation(input_to);

        if (!correct_notation) {
            if (input_from == "xx" && input_to == "xx")
                std::cout << board << "\n";
            else
				std::cout << "Notazione errata\n";
        }
        
    } while (!correct_notation);

    from = Coordinates{input_from};
    to = Coordinates{input_to};
}

bool chess::HumanPlayer::verifyNotation(std::string coords) const {
    if (coords.size() != 2)
        return false;

    short f = coords[0] - 'a';
    short r = coords[1] - '1';

    return Coordinates{f,r}.inBounderies();
}

char chess::HumanPlayer::choosePromotion() {
    std::string s;
	char piece;
    bool valid_input ;
    std::cout << "Promuovi in [D|T|A|C]: ";
    do {
        std::cin >> s;
		valid_input = false;
		if(s.size() == 1) {
	        piece = toupper(piece);
			valid_input = isValidPromotionPiece(piece);
		}

        

        if (valid_input)
            std::cout << "\nPromozione in " << piece << std::endl;
        else
            std::cout << "Inserire un carattere tra [D|T|A|C]: ";

    } while (!valid_input);

    return piece;
}

bool chess::HumanPlayer::isValidPromotionPiece(const char piece) const {
    return piece == 'D' || piece == 'T' || piece == 'A' || piece == 'C';
}