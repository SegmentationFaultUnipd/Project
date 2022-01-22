#include <fstream>
#include <iostream>

#include "ReplayManager.h"
#include "Color.h"

int main (int argc, char* argv[]) {
	
  	std::ifstream input;
	try {
		input.open ("../tests/general_game.txt");
		std::string s;
		std::getline(input, s);
		chess::ReplayPlayer player1 = {static_cast<chess::Color>(stoi(s.substr(s.find(':'+1))))};
		std::getline(input, s);
		chess::ReplayPlayer player2 = {static_cast<chess::Color>(stoi(s.substr(s.find(':'+1))))};
		chess::ReplayManager rManager = {input, std::cout, true, player1, player2};
		rManager.play();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "Exception opening/reading/closing file\n";
	}
}


