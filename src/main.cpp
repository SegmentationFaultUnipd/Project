#include <iostream>

#include "GameManager.h"
#include "Color.h"

#include "Players/Player.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"

void printUsage() {
	std::cout << "Uso corretto: Scacchiera {pc|cc} "<< std::endl;
	std::cout << "\targomento pc: inizia una partita giocatore vs computer" << std::endl;
	std::cout << "\targomento cc: inizia una partita computer vs computer, con massimo 500 mosse" << std::endl;
}

chess::Color selectRandomColor() {
	srand(time(NULL));
	if(rand() % 2 == 0) {
		return chess::WHITE;
	}else {
		return chess::BLACK;
	}
}


int main(int argc, char *argv[]) {
	std::vector<std::string> args(argv, argv+argc);//Confronti facile con stringhe
	if(argc != 2 || (args[1] != "pc" && args[1] != "cc")) {
		printUsage();
		return 0;
	}
	chess::Player *player1, *player2;
	if(args[1] == "pc") {
		player1 = new chess::HumanPlayer(selectRandomColor());
		player2 = new chess::ComputerPlayer(rand(), opposite(player1->getColor()));
	}else {
		player1 = new chess::ComputerPlayer(rand(), selectRandomColor());
		player2 = new chess::ComputerPlayer(rand(), opposite(player1->getColor()));
	}

    chess::GameManager game{*player1, *player2, 50};
    game.play();
    
    return 0;
}
