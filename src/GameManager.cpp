#include "GameManager.h"

chess::GameManager::GameManager(Player* player1, Color color1, Player* player2, Color color2, int max_moves) {
	board = Board();

	//TODO generate log file

}


void chess::GameManager::play() {
	current_move = 0;
	current_turn = (color1 == WHITE); 
	bool infinite_game = (max_moves == -1);
	bool isGameEnded = false;
	while(!isGameEnded && infinite_game && current_move < max_moves) {
		if(current_turn) {
			//Player 1 decides a move
			//If Player1 is under check, ask for another move (if present) or else stop everything, Player 2 wins
			//Otherwise finalize the move
		}else {
			//Player 2 decides a move
			//If Player2 is under check, ask for another move (if present) or else stop everything, Player 1 wins
			//Otherwise finalize the move
		}

		//TODO log the move
		
		current_turn = !current_turn;
		if(!infinite_game)
			current_move++;
	}
	//TODO close everything, free up memory etc

}