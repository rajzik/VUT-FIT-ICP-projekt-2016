#include <iostream>
#include <cstdlib>
#include "game.h"
#include "game-cli.h"
#include "player.h"


int main(){

    gameCli * game = new gameCli(false, 8);
   
    game->run();
    return 0;
}
