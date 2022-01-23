#include "ReplayPlayer.h"

void chess::ReplayPlayer::nextTurn(Board& board, chess::Coordinates& from, chess::Coordinates& to) {
    std::pair<Coordinates, Coordinates> current_move = moves_.at(curr_index_moves_++);
    from = current_move.first;
    to = current_move.second;
}

char chess::ReplayPlayer::choosePromotion() {
    return promotions_.at(curr_index_promotions_++);
}

void chess::ReplayPlayer::addMove(Coordinates from, Coordinates to) {
	moves_.push_back({from, to});
}
void chess::ReplayPlayer::addPromotion(Coordinates position, char chosen_piece) {
	promotions_.push_back(chosen_piece);
}

int chess::ReplayPlayer::availableMoves() {
    return moves_.size() - curr_index_moves_;
}


int chess::ReplayPlayer::availablePromotions() {
    return promotions_.size() - curr_index_promotions_;
}