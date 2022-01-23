/**
 * @file Replay.cpp
 * @author Filippo Niero
 * @date 2022-01-23
 */

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
	std::vector<std::string> args(argv, argv+argc);//Confronti facile con stringhe
	//Check arguments
	if(argc <= 2 || args[1] == "?") {
		printUsage();
		return 0;
	}
	if(args[1] != "f" && args[1] != "v") {//Argomento non riconosciuto
		std::cout << "Argomento non riconosciuto " << std::endl;
		printUsage();
		return 0;
	}
	if(args[1] == "f" && argc != 4) {//Output su file, con file non specificato
		printUsage();
		return 0;
	}
	if(args[1] == "v" && argc != 3) {//Output su file, con file non specificato
		printUsage();
		return 0;
	}
  	std::ifstream input;
	try {
		std::string input_file_name = args[2];
		input.open(input_file_name);
		std::string s;
		std::getline(input, s);
		chess::ReplayPlayer player1 = {static_cast<chess::Color>(s.at(s.find(':')+1) - '0')};
		std::getline(input, s);
		chess::ReplayPlayer player2 = {static_cast<chess::Color>(s.at(s.find(':')+1) - '0')};

		if(args[1] == "v") {
			std::cout << "Visualizzazione del replay..." <<std::endl;
			chess::ReplayManager rManager =  {input_file_name, input, std::cout, true, player1, player2};
			rManager.play(std::cout);
		}else {
			std::cout << "Salvataggio del replay su file..." <<std::endl;
			std::ofstream output_stream;
			output_stream.open(args[3], std::ofstream::trunc);
			chess::ReplayManager rManager =  {input_file_name, input, output_stream, false, player1, player2};
			rManager.play(output_stream);
			output_stream.close();
		}
		std::cout << "Replay finito" <<std::endl;
	}
	catch (std::ios_base::failure e) {
		std::cout << "Problema durante la lettura/scrittura dei file" << std::endl;
		std::cerr << e.what() << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << "Il file non ha un formato corretto" << std::endl;
		std::cerr << e.what() << std::endl;
	}
}