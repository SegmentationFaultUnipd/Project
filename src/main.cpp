#include <iostream>


#include "GameManager.h"
#include "Board.h"
#include "Coordinates.h"
#include "Color.h"

#include "Players/Player.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"

int main(int argc, char* argv[]) {

    chess::HumanPlayer p1{chess::Color::WHITE};
    chess::HumanPlayer p2{chess::Color::BLACK};

    chess::GameManager game{&p1, &p2, 50};
    game.play();

    return 0;
}