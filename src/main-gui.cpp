/**
 * @file   main-gui.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
 *
 */

#include "game-gui.h"

int main(int argc, char * argv[])
{
    gameGui * game = new gameGui(argc, argv);

    game->run();
}
