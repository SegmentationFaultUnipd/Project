#include <thread>         
#include <chrono>  
#include <fstream>
#include <iostream>

#include "ReplayManager.h"

chess::ReplayManager::ReplayManager(std::string input_file, std::ifstream& input, std::ostream &output, bool need_to_pause, ReplayPlayer &player1, ReplayPlayer &player2) : need_to_pause_(need_to_pause), player1_(player1), player2_(player2) {	
	output << "Replay della partita "<<input_file << std::endl;
	output << "Player1: " << ColorNames[player1_.getColor()] << std::endl;
	output << "Player2: " << ColorNames[player2_.getColor()] << std::endl;
	int prec_move_number = -1;
	std::string s;
	while(getline(input, s)) {
		if(s == "---") {
			//Partita finita
			last_move_ = prec_move_number;
			//Leggo il messaggio finale
			getline(input, s);
			final_outcome = s;
			break;
		}
		std::stringstream sstream(s);
		std::string token;
		sstream >> token;
		int curr_move_number = std::stoi(token);
		//Promotion or "normal" move?
		if(curr_move_number == prec_move_number) {//Promotion
			std::string promotion_str;
			sstream >> promotion_str;
			addPromotion(curr_move_number, promotion_str);
		} else {//Normal move
			std::string first_coord_string, second_coord_string;
			sstream >> first_coord_string >> second_coord_string;
			addMove(curr_move_number, first_coord_string, second_coord_string);
		}
		prec_move_number = curr_move_number;
	}
}

void chess::ReplayManager::play(std::ostream &output) {
	current_color_ = WHITE; //Seleziona il giocatore iniziale
	int current_move = 0;
	while(current_move <= last_move_) {
		Coordinates from, to;
		bool isValid = false;
		if(currentPlayer().availableMoves() > 0) {
			currentPlayer().nextTurn(board, from, to);
		} else {
			output << "Problema durante il replay, la partita non è ancora finita ma il giocatore ha esaurito le mosse " << std::endl;
			return;
		}

		isValid = !board.isEmpty(from) && board.at(from).color() == current_color_ && board.move(from, to);
		if (!isValid) {
			output << "Problema durante il replay, la mossa "<<from.toNotation() << " " << to.toNotation() << " non è consentita"<<std::endl;
			return;
		}

		// Promozione
		if(board.at(to).ascii()=='P' && (to.rank == 0 || to.rank == 7)) {
			if(currentPlayer().availablePromotions() > 0) {
				char chosen = currentPlayer().choosePromotion();
				board.promote(to, chosen);
				output << "Promozione avvenuta in " << to.toNotation() << std::endl;
			}else {
				//Questo succede se nella partita ci sono delle promozioni in cui manca la riga in cui viene scelto il pezzo
				output << "Problema durante il replay, non sono state registrate correttamente le promozioni dei pedoni "<< std::endl;
				return;
			}
		}


		output << "Mossa #" << current_move << std::endl;

		output << board << std::endl << std::endl;

		if(need_to_pause_) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		nextPlayer();
		current_move++;
	}
	output << final_outcome <<std::endl;
}

chess::ReplayPlayer& chess::ReplayManager::currentPlayer() {
	if (current_color_ == player1_.getColor())
		return player1_;
	else
		return player2_;
}

void chess::ReplayManager::nextPlayer() {
	current_color_ = opposite(current_color_);
}
chess::ReplayPlayer& chess::ReplayManager::getWhitePlayer() {
	return (player1_.getColor() == WHITE)?player1_:player2_;
}

chess::ReplayPlayer& chess::ReplayManager::getBlackPlayer() {
	return (player1_.getColor() == BLACK)?player1_:player2_;
}


chess::ReplayPlayer& chess::ReplayManager::getPlayerFromMoveNumber(int move_number) {
	if(move_number % 2 == 0) {
		return getWhitePlayer();
	}
	return getBlackPlayer();
}

void chess::ReplayManager::addMove(int move_number, std::string first_coord_string, std::string second_coord_string) {
	ReplayPlayer& correct_player = getPlayerFromMoveNumber(move_number);
	Coordinates from = Coordinates(first_coord_string);
	Coordinates to = Coordinates(second_coord_string);
	correct_player.addMove(from, to);
}

void chess::ReplayManager::addPromotion(int move_number, std::string promotion_string) {
	ReplayPlayer& correct_player = getPlayerFromMoveNumber(move_number);
	char chosen_piece = promotion_string.at(promotion_string.find('=')+1);
	Coordinates position = Coordinates(promotion_string.substr(0, 2));
	correct_player.addPromotion(position, chosen_piece);
}
