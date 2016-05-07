/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */

#include <iostream>
#include <cstdlib>
#include "game.h"
#include "game-cli.h"
#include "player.h"


int main(){

    gameCli * game = new gameCli();
   
    game->run();
    return 0;
}
