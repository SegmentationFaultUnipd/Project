#include "GameManager.h"


void chess::GameManager::createLogFile() {
	time_t now = time(NULL);
	tm *now_localtime = localtime(&now);
	std::string year =  std::to_string(1900 + now_localtime->tm_year);
	//Formato: chesslog_DDMMYYYY_HHmm.txt
	file_name_ = "chesslog_" + padTime(now_localtime->tm_mday)  + padTime(now_localtime->tm_mon + 1) + year + "_" + padTime(now_localtime->tm_hour) +""+ padTime(now_localtime->tm_min) + ".txt";
	//Save stream, overwrite file if it already exists
	log_stream_.open(file_name_, std::ofstream::trunc);
	log_stream_<<"PLAYER1:"<<player1_.getColor()<<std::endl;
	log_stream_<<"PLAYER2:"<<player2_.getColor()<<std::endl;
}

std::string chess::GameManager::padTime(int x) {
	if(x < 10) {
		return "0" + std::to_string(x);
	}
	return std::to_string(x);
}

chess::Player& chess::GameManager::currentPlayer() {
	if (current_color_ == player1_.getColor())
		return player1_;
	else
		return player2_;
}

void chess::GameManager::nextPlayer() {
	current_color_ = opposite(current_color_);
}

void chess::GameManager::play() {
	current_move_ = 0;//Contatore delle mosse: serve per le partite tra due PC, perché devono finire dopo max_moves mosse
	current_color_ = WHITE; //Seleziona il giocatore iniziale
	bool infinite_game = (max_moves_ == -1);
	bool isGameEnded = false;
	while(!isGameEnded && (infinite_game || current_move_ < max_moves_)) {
		Coordinates from, to;
		bool isValid = false;

		std::cout << "Tocca al " << (current_color_ == WHITE ? "bianco\n" : "nero\n");
		do {
			currentPlayer().nextTurn(board, from, to);
			isValid = !board.isEmpty(from) && board.at(from).color() == current_color_ && board.move(from, to);
			if (!isValid)
				std::cout << "Mossa non consentita" << std::endl;
		} while (!isValid);

		logMove(current_move_, from, to);

		// Promozione
		if(board.at(to).ascii()=='P' && (to.rank == 0 || to.rank == 7) ) {
			char chosen = currentPlayer().choosePromotion();
			board.promote(to, chosen);
			logPromotion(current_move_, chosen, to);
		}

		nextPlayer();
		
		//Check if player has available moves
		std::list<Coordinates> pieces = board.getPiecesCoords(current_color_);
		bool player_has_at_least_1_move = false;
		for(auto piece : pieces) {
			std::cout << piece << ": \n";
			if(board.legalMovesOf(board.at(piece)).size() > 0) {
				player_has_at_least_1_move = true;
				break;
			}
		}

		if(!player_has_at_least_1_move) {
			if(board.isKingInCheck(current_color_)) {
				//Scacco matto
				log_stream_<<"---"<<std::endl;
				log_stream_<<((current_color_ == player1_.getColor())?"Player1":"Player2")<<" has no valid moves and his king is in check";
				nextPlayer();
				win(currentPlayer());
			}else {
				//Parità
				log_stream_<<"---"<<std::endl;
				log_stream_<<((current_color_ == player1_.getColor())?"Player1":"Player2")<<" has no valid moves but his king is not in check";
				draw();
			}
		}

		if(!infinite_game) {
			current_move_++;
		}

	}
	log_stream_<<"---"<<std::endl;

	if(current_move_ >= max_moves_) {
		std::cout << "Numero di mosse previsto raggiunto. " << std::endl;
		draw();
	}
	cleanUp();
}

void chess::GameManager::win(Player &winner) {
	std::string win_message_part = (winner.getColor() == player1_.getColor())? "PLAYER 1": "PLAYER 2";
	std::cout << win_message_part<<" vince!!!" << std::endl;
	log_stream_ << win_message_part<<" vince!!!" << std::endl;
}

void chess::GameManager::draw() {
	std::cout << "Patta! " <<std::endl;
	log_stream_<<"Patta! "<<std::endl;
}

void chess::GameManager::cleanUp() {
	log_stream_.close();
}

void chess::GameManager::logMove(int move_number, Coordinates from, Coordinates to) {
	log_stream_<< move_number << " " << from.toNotation() << " " << to.toNotation() << std::endl;
}

void chess::GameManager::logPromotion(int move_number, char piece, Coordinates position) {
	log_stream_ << move_number << " " << position.toNotation() << "=" << (char)toupper(piece)<<std::endl;
}