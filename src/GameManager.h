#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Players/Player.h"
#include "Board.h"
#include "Color.h"
#include <ctime>
#include <fstream>
namespace chess {

    class GameManager {
        public:
			//Nota: current_player viene inizializzato a player1 nel costruttore, ma una volta che viene chiamato GameManager::play() viene corretto con il giocatore che ha il bianco
            GameManager(Player &player1, Player &player2, int max_moves) : player1_(player1), player2_(player2), max_moves_(max_moves), current_color(WHITE) {
				createLogFile();
			}
           	void play();
			void logMove(int move_number, Coordinates from, Coordinates to);
			void logPromotion(int move_number, char piece, Coordinates position);
			
        private:
			Player &player1_, &player2_;
			Board board;
			int max_moves_;//If max_moves is -1, go on forever
			int current_move = 0;
			Color current_color;
			std::string file_name;
			std::ofstream log_stream;

			Player& currentPlayer();
			void nextPlayer();
			void win(Player &winner);
			void draw();
			void createLogFile();
			std::string padTime(int x);
			void cleanUp();

			static Player& selectStartingPlayer(Player& player1, Player& player2) {
				return (player1.getColor()== WHITE)?player1: player2;
			}
		
    };

} //namespace chess

#endif //GAMEMANAGER_H