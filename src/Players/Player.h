//AUTORE: Filippo Niero
#ifndef PLAYER_H
#define PLAYER_H

#include <list>

#include "../Coordinates.h"
#include "../Color.h"
#include "../Board.h"
namespace chess {

    class Player {
        public:
            /**
             * @brief Specifica la prossima mossa da effettuare.
             * 
             * @param board la scacchiera in cui effettuare le mossa
             * @param from conterrà la coordinata di inzio mossa
             * @param to conterrà la coordinata di fine mossa
             */
            virtual void nextTurn(Board& board, Coordinates& from, Coordinates& to) = 0;

            /**
             * @brief Si occupa di decidere il pezzo in cui promuovere un pedone.
             * 
             * @return carattere ascii masiucolo in cui promuovere il pedone.
             */
            virtual char choosePromotion() = 0;

            Color getColor() { return color_; }
            
        protected:
            Player(Color color) : color_{color} {};
            Color color_;
    };

}

#endif //PLAYER_H