/**
 * @file GameManager.h
 * @author Filippo Niero
 * @date 2022-01-23
 */
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
            GameManager(Player &player1, Player &player2)
			: player1_(player1), player2_(player2), max_moves_(-1) {
				createLogFile();
			}

			/**
			 * @brief Inizia il ciclo di gioco.
			 */
           	void play();

			/**
			 * @brief Salva la mossa indicata nel log.
			 * 
			 * @param move_number Numero della mossa (la prima mossa è 0).
			 * @param from Coordinate di partenza.
			 * @param to Coordinate di arrivo.
			 */
			void logMove(int move_number, Coordinates from, Coordinates to);
			void logPromotion(int move_number, char piece, Coordinates position);
			
        private:
			Player &player1_, &player2_;
			Board board;
			int max_moves_; //Per max_moves = -1, va avanti indefinitivamente
			int current_move_ = 0;
			Color current_color_;
			std::string file_name_;
			std::ofstream log_stream_;

			Player& currentPlayer();
			void nextPlayer();
			void win(Player &winner);
			void draw();
			void createLogFile();
			std::string padTime(int x);
			void cleanUp();

			Player& selectStartingPlayer(Player& player1, Player& player2) {
				return (player1.getColor()== WHITE) ? player1 : player2;
			}
		
    };

} //namespace chess

#endif //GAMEMANAGER_H