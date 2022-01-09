#include "GameManager.h"

chess::GameManager::GameManager(Player* player1, Player* player2, int max_moves) {
	board = Board();
	createLogFile();
}




void chess::GameManager::createLogFile() {
	std::string name = "chesslog_";
}

void chess::GameManager::nextPlayer() {
	if(current_player == player1) {
		current_player = player2;
	} else {
		current_player = player1;
	}
}

void chess::GameManager::play() {
	current_move = 0;
	current_player = (player1->getColor() == WHITE)? player1:player2; 
	bool infinite_game = (max_moves == -1);
	bool isGameEnded = false;
	while(!isGameEnded && infinite_game && current_move < max_moves) {
		Coordinates from, to;
		bool isValid = false;
		if(current_player == player1) {
			//If player1's King is in check, try to see if there is a move to save the King
			if(board.isKingInCheck(player1->getColor())) {
				bool foundAMove = false;
				std::list<Coordinates> pieces = board.getPieces(player1->getColor());
				for(auto coords : pieces) {
					if(board.legalMovesOf(board.at(coords)).size() > 0) {
						//Found a move that saves the King
						foundAMove = true;
						break;
					}
				}

				if(!foundAMove) {
					//Player1 Lost
					win(player2);
					isGameEnded = true;
				}
			}
			while(!isValid) {
				player1->nextTurn(board, from, to);
				isValid = board.move(from, to);
			}

			//Check for promotion
			if(toupper(board.at(to).ascii()) == 'P' && to.rank == 0 || to.rank == 7) {
				char chosen_piece = player1->choosePromotion();
				board.promote(to, chosen_piece);
			} 
		}else {
			//If player1's King is in check, try to see if there is a move to save the King
			if(board.isKingInCheck(player2->getColor())) {
				bool foundAMove = false;
				std::list<Coordinates> pieces = board.getPieces(player2->getColor());
				for(auto coords : pieces) {
					if(board.legalMovesOf(board.at(coords)).size() > 0) {
						//Found a move that saves the King
						foundAMove = true;
						break;
					}
				}

				if(!foundAMove) {
					//Player2 Lost
					win(player1);
					isGameEnded = true;
				}
			}
			while(!isValid) {
				player2->nextTurn(board, from, to);
				isValid = board.move(from, to);
			}

			//Check for promotion
			if(toupper(board.at(to).ascii()) == 'P' && to.rank == 0 || to.rank == 7) {
				char chosen_piece = player2->choosePromotion();
				board.promote(to, chosen_piece);
			} 
		}

		//TODO log the move
		
		nextPlayer();

		if(!infinite_game)
			current_move++;
	}

	if(current_move >= max_moves) {
		std::cout << "Number of moves reached. " << std::endl;
	}
	//TODO close everything, free up memory etc

}

void chess::GameManager::win(Player* winner) {
	if(winner == nullptr) {
		std::cout << "Draw! " <<std::endl;
	} else {
		std::string win_message_part = (winner == player1)? "PLAYER 1": "PLAYER 2";
		std::cout << "The winner is "<<win_message_part<<"!!!"<<std::endl;
	}
}