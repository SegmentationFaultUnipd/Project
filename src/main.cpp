/**
 * @file main.cpp
 * @author Filippo Mazzarotto
 * @date 2022-01-23
 */
#include <iostream>

#include "GameManager.h"
#include "Color.h"

#include "Players/Player.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"

void printUsage();
chess::Color selectRandomColor();
bool validArguments(const std::vector<std::string>& args);
std::unique_ptr<chess::Player> selectPlayer(char player_type, chess::Color player_color);

int main(int argc, char *argv[]) {
	std::vector<std::string> args{argv, argv+argc};

	if (validArguments(args)) {
		std::unique_ptr<chess::Player> player_1 = selectPlayer(args[1][0], selectRandomColor());
		std::unique_ptr<chess::Player> player_2 = selectPlayer(args[1][1], opposite(player_1->getColor()));

		chess::GameManager game{*player_1, *player_2};
		if (args[1] == "cc") {
			game.setMaxMoves(500);
		}

		game.play();

	} else {
		printUsage();
	}
	
    return 0;
}

bool validArguments(const std::vector<std::string>& args) {
	return args.size() == 2
		&& args[1].size() == 2
		&& (args[1][0] == 'p' || args[1][0] == 'c')
		&& (args[1][1] == 'p' || args[1][1] == 'c');
}

void printUsage() {
	std::cout << "Uso corretto: scacchiera [pp|pc|cc]"<< std::endl;
	std::cout << "\targomento pc: inizia una partita giocatore vs computer" << std::endl;
	std::cout << "\targomento cc: inizia una partita computer vs computer, con massimo 500 mosse" << std::endl;
	std::cout << "\targomento pp: inizia una partita player vs player" << std::endl;
}

chess::Color selectRandomColor() {
	if(rand() % 2 == 0) {
		return chess::WHITE;
	} else {
		return chess::BLACK;
	}
}

std::unique_ptr<chess::Player> selectPlayer(char player_type, chess::Color player_color) {
	switch (player_type)
	{
	case 'p':
		return std::make_unique<chess::HumanPlayer>(player_color);
	case 'c':
		return std::make_unique<chess::ComputerPlayer>(rand(), player_color);
	default:
		return nullptr;
	}
}