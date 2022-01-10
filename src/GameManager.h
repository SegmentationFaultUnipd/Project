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
            GameManager(Player* player1, Player* player2, int max_moves);
           	void play();
			void logMove(Coordinates from, Coordinates to);
			void logPromotion(char piece, Coordinates position);
			
        private:
			Player *player1_, *player2_;
			Board board;
			int max_moves_;//If max_moves is -1, go on forever
			int current_move = 0;
			Player* current_player;
			std::string file_name;
			std::ofstream log_stream;

			void nextPlayer();
			void win(Player* winner);
			void createLogFile();
			std::string padTime(int x);
			void cleanUp();

		
    };

} //namespace chess

#endif //GAMEMANAGER_H