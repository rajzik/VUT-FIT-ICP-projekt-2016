#include <iostream>
#include <cstdlib>
#include "game.h"
#include "game-gui.h"
#include "player.h"


int main(){

    gameGui * game = new gameGui(false, 8);
   
    game->run();
    return 0;
}
