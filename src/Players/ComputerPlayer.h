//AUTORE: Filippo Niero
#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <iostream>

#include "Player.h"
#include "../Coordinates.h"
#include "../Color.h"

namespace chess {
    /**
     * @brief Rappresenta un player non umano
     * 
     */
    class ComputerPlayer : public Player {
        public:
            ComputerPlayer(unsigned int seed, Color color);
            void nextTurn(Board &board, Coordinates &from, Coordinates &to) override;
			char choosePromotion() override;
        private:

    };
}

#endif //COMPUTERPLAYER_H