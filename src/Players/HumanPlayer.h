#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <iostream>

#include "Player.h"
#include "../Coordinates.h"
#include "../Color.h"

namespace chess {
    class HumanPlayer : public Player {
        public:
            HumanPlayer(std::list<Coordinates> pieces, Color color) : Player{pieces, color} {};
            void nextTurn(Coordinates& from, Coordinates& to) const override;
            bool hasLegalMoves() const override;
        private:
            bool verifyNotation(std::string coords) const;
    };
}

#endif //HUMANPLAYER_H