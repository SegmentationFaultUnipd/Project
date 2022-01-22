#ifndef REPLAYMANAGER_H
#define REPLAYMANAGER_H

#include "Players/ReplayPlayer.h"
#include "Board.h"
#include "Color.h"
#include <ctime>
#include <fstream>
#include <iostream>
namespace chess {

    class ReplayManager {
        public:
            ReplayManager(std::ifstream& input_file, std::ostream &output, bool need_to_pause, ReplayPlayer &player1, ReplayPlayer &player2) : output_(output), need_to_pause_(need_to_pause_), player1_(player1), player2_(player2) {	
				output_ << "Player1: " << ColorNames[player1_.getColor()] << std::endl;
				output_ << "Player2: " << ColorNames[player2_.getColor()] << std::endl;
				while(input_file.good()) {
						
				}
			}
           	void play();
		
        private:
			ReplayPlayer &player1_, &player2_;
			Board board_;
			Color current_color_;
			std::ostream &output_;
			bool need_to_pause_;

			Player& currentPlayer();
			void nextPlayer();
			void cleanUp();

			static Player& selectStartingPlayer(Player& player1, Player& player2) {
				return (player1.getColor()== WHITE)?player1: player2;
			}
		
    };

} //namespace chess

#endif //REPLAYMANAGER_H