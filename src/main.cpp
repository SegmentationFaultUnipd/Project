#include <iostream>

#include "GameManager.h"
#include "Color.h"

#include "Players/Player.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"

int main(int argc, char *argv[])
{
    chess::HumanPlayer p1{chess::WHITE};
    chess::HumanPlayer p2{chess::BLACK};

    chess::GameManager game{&p1, &p2, 50};
    game.play();
    
    return 0;
}