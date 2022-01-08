#ifndef PLAYER_H
#define PLAYER_H

#include <list>

#include "../Coordinates.h"
#include "../Color.h"
#include "../Board.h"
namespace chess {

    class Player {
        public:
            virtual void nextTurn(Board &board, Coordinates &from, Coordinates &to) = 0;
			virtual char choosePromotion() = 0;
			Color getColor() { return color_;}
        protected:
            Player(Color color) : color_{color} {};
            Color color_;
    };

}

#endif //PLAYER_H