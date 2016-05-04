#pragma once

#include "game.h"
#include "console.h"

class gameCli : public game
{
private: 
    console consol;    
        
    std::string dummyPlayer;
    int dummyScore;
    bool actualPlayer;
    
    
public:

    gameCli();
    ~gameCli();
    void getGameInfo();
    void printHelp();
    void draw();
    void drawScore();
    void run();
        
};
