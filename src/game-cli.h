/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */

#pragma once

#include "game.h"
#include "console.h"

class gameCli : public game
{
private: 
    console consol;    
    std::string message;
    std::string Emessage;
    bool actualPlayer;
    void printSavedGame();
    void printGameOver();
    
public:
    gameCli();
    ~gameCli();
    void getGameInfo();
    void printHelp();
    void draw();
    void drawScore();
    void run();
        
};
