#include <fstream>
#include <iostream>

#include "ReplayManager.h"
#include "Color.h"

void printUsage() {
	std::cout << "Uso corretto: replay {v|f} nome_file_log [nome_file_output_replay]" << std::endl;
	std::cout << "\targomento v nome_file_log: stampa a video il replay del file di log indicato, una mossa al secondo" << std::endl;
	std::cout << "\targomento f nome_file_log nome_file_output_replay: scrive su file il replay del file di log indicato" << std::endl;

}

int main (int argc, char* argv[]) {
	// Read file
	if(argc <= 1 || argv[0] == "--help") {
		printUsage();
		return 0;
	}
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
		std::cerr << "Problema durante la lettura del file\n";
	}
}