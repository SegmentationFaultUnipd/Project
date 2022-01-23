//AUTORE: Filippo Niero
#ifndef REPLAYMANAGER_H
#define REPLAYMANAGER_H

#include "Players/ReplayPlayer.h"
#include "Board.h"
#include "Color.h"
#include <fstream>
#include <iostream>
namespace chess {

    class ReplayManager {
        public:
            ReplayManager(std::string input_file, std::ifstream& input, std::ostream &output, bool need_to_pause, ReplayPlayer &player1, ReplayPlayer &player2);
           	void play(std::ostream &output);
		
        private:
			ReplayPlayer &player1_, &player2_;
			Board board;
			Color current_color_;
			bool need_to_pause_;
			int last_move_;
			std::string final_outcome;
			ReplayPlayer& currentPlayer();
			void nextPlayer();
			ReplayPlayer& getWhitePlayer();
			ReplayPlayer& getBlackPlayer();

			ReplayPlayer& getPlayerFromMoveNumber(int move_number);

			void addMove(int move_number, std::string first_coord_string, std::string second_coord_string);

			void addPromotion(int move_number, std::string promotion_string);
		
    };

} //namespace chess

#endif //REPLAYMANAGER_H