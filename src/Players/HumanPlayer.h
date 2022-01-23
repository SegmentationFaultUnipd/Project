#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <iostream>

#include "Player.h"
#include "../Coordinates.h"
#include "../Color.h"

namespace chess {
    class HumanPlayer : public Player {
        public:
            HumanPlayer(Color color) : Player{color} {};
            void nextTurn(Board& board, Coordinates& from, Coordinates& to) override;
            char choosePromotion() override;
        private:
            bool verifyNotation(std::string coords) const;
            bool isValidPromotionPiece(const char piece) const;
            static void stringToLower(std::string &string);
    };
}

#endif //HUMANPLAYER_H