#include "GameManager.h"


void chess::GameManager::createLogFile() {
	time_t now = time(0);
	tm *now_localtime = localtime(&now);
	std::string year =  "" + (1900 + now_localtime->tm_year);
	//Formato: chesslog_DDMMYYYY_HHmm.txt
	file_name = "chesslog_" + padTime(now_localtime->tm_mday) + padTime(now_localtime->tm_mon) + year + "_" + padTime(now_localtime->tm_hour) + padTime(now_localtime->tm_min);
	//Save stream, overwrite file if it already exists
	log_stream.open(file_name, std::ofstream::trunc);
	log_stream<<"PLAYER1:"<<player1_.getColor()<<std::endl;
	log_stream<<"PLAYER2:"<<player2_.getColor()<<std::endl;
}

std::string chess::GameManager::padTime(int x) {
	if(x < 10) {
		return "0" + x;
	}
	return "" + x;
}

chess::Player& chess::GameManager::currentPlayer() {
	if (current_color == player1_.getColor())
		return player1_;
	else
		return player2_;
}

void chess::GameManager::nextPlayer() {
	current_color = opposite(current_color);
}

void chess::GameManager::play() {
	current_move = 0;//Contatore delle mosse: serve per le partite tra due PC, perché devono finire dopo max_moves mosse
	current_color = WHITE; //Seleziona il giocatore iniziale
	bool infinite_game = (max_moves_ == -1);
	bool isGameEnded = false;

	while(!isGameEnded && (infinite_game || current_move < max_moves_)) {
		Coordinates from, to;
		bool isValid = false;

		std::cout << "Tocca al " << (current_color == WHITE ? "bianco\n" : "nero\n");

		do {
			currentPlayer().nextTurn(board, from, to);
			isValid = !board.isEmpty(from) && board.at(from).color() == current_color && board.move(from, to);
			if (!isValid)
				std::cout << "Mossa non consentita\n";
		} while (!isValid);

		//TODO log the move
		logMove(from, to);

		// Promozione
		if(board.at(to).ascii()=='P' && (to.rank == 0 || to.rank == 7) ) {
			char chosen = currentPlayer().choosePromotion();
			board.promote(to, chosen);
			logPromotion(chosen, to);
		}

		nextPlayer();
		
		//Check if player has available moves
		std::list<Coordinates> pieces = board.getPiecesCoords(current_color);
		bool player_has_at_least_1_move = false;
		for(auto coords: pieces) {
			if(board.legalMovesOf(board.at(coords)).size() > 0) {
				player_has_at_least_1_move = true;
				break;
			}
		}

		if(!player_has_at_least_1_move) {
			if(board.isKingInCheck(current_color)) {
				//Scacco matto
				log_stream<<"---"<<std::endl;
				log_stream<<((current_color == player1_.getColor())?"Player1":"Player2")<<" has no valid moves and his king is in check";
				nextPlayer();
				win(currentPlayer());
			}else {
				//Parità
				log_stream<<"---"<<std::endl;
				log_stream<<((current_color == player1_.getColor())?"Player1":"Player2")<<" has no valid moves but his king is not in check";
				draw();
			}
		}
		if(!infinite_game) {
			current_move++;
		}
	}
	log_stream<<"---"<<std::endl;

	if(current_move >= max_moves_) {
		std::cout << "Number of moves reached. " << std::endl;
		draw();
	}
	//TODO close everything, free up memory etc
	cleanUp();
}

void chess::GameManager::win(Player &winner) {
	std::string win_message_part = (winner.getColor() == player1_.getColor())? "PLAYER 1": "PLAYER 2";
	std::cout << "The winner is "<<win_message_part<<"!!!"<<std::endl;
	log_stream<<"The winner is "<<win_message_part<<"!!!"<<std::endl;
}

void chess::GameManager::draw() {
	std::cout << "Draw! " <<std::endl;
		log_stream<<"Draw! "<<std::endl;
}

void chess::GameManager::cleanUp() {
	log_stream.close();
}

void chess::GameManager::logMove(Coordinates from, Coordinates to) {
	//TODO
	//log_stream<<from.toString()<<" "<<toString()<<std::endl;
}

void chess::GameManager::logPromotion(char piece, Coordinates position) {
	//TODO
	//log_stream << "### " <<piece << position.toString();
}