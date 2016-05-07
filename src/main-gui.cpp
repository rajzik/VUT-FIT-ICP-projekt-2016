/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */
#include "game-gui.h"

int main(int argc, char * argv[])
{
    gameGui * game = new gameGui(argc, argv);

    game->run();
}
