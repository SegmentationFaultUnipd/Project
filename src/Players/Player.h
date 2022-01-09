#ifndef PLAYER_H
#define PLAYER_H

#include <list>

#include "../Coordinates.h"
#include "../Color.h"
#include "../Board.h"
namespace chess {

    class Player {
        public:
            virtual void nextTurn(Coordinates& from, Coordinates& to) const = 0;
            virtual bool hasLegalMoves() const = 0;
            
        protected:
            Player(Color color) : color_{color} {};
            Color color_;
    };

}

#endif //PLAYER_H