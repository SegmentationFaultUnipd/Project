//AUTORE: Filippo Niero
#ifndef REPLAYPLAYER_H
#define REPLAYPLAYER_H

#include <iostream>

#include "Player.h"
#include "../Coordinates.h"
#include "../Color.h"

namespace chess {
    class ReplayPlayer : public Player {
        public:
            ReplayPlayer(Color color) : Player{color}, curr_index_moves_(0), curr_index_promotions_(0) {};
            void nextTurn(Board& board, Coordinates& from, Coordinates& to) override;
            char choosePromotion() override;
            void addMove(Coordinates from, Coordinates to);
            void addPromotion(Coordinates position, char chosen_piece);
            int availableMoves();
            int availablePromotions();
        private:
            std::vector<std::pair<Coordinates, Coordinates>> moves_;
            std::vector<char> promotions_;
            int curr_index_moves_;
            int curr_index_promotions_;

    };
}

#endif //REPLAYPLAYER_H