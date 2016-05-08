/**
 * @file   main-gui.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  main file for GUI application
 */

#include "game-gui.h"

/**
 * @brief  input point for GUI application
 * @param  argc parameters count
 * @param  argv parameters array
 * @return return value returned from game run
 */
int main(int argc, char * argv[])
{
    gameGui * game = new gameGui(argc, argv);

    return game->run();
}
