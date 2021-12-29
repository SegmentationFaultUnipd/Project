#ifndef PLAYER_H
#define PLAYER_H

#include <list>

#include "../Coordinates.h"
#include "../Color.h"

namespace chess {

    class Player {
        public:
            virtual void nextTurn(Coordinates *from, Coordinates *to) = 0;
        protected:
            Player(std::list<Coordinates>& pieces, Color color) : pieces_{pieces}, color_{color} {};
            Color color_;
            std::list<Coordinates>& pieces_;

    };

}

#endif //PLAYER_H