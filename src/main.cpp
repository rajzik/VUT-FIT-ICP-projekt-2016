//#include <stdlib>
#include <iostream>
#include <cstdlib>
#include "game.h"
#include "game-cli.h"
#include "player.h"


int main(){

   

    // player * p;

    // p = new player("Petr", true, false);
    // std::cout << p->getName() << std::endl;
    
    gameCli * game = new gameCli(false, 8);
   
    game->draw();
    
}
