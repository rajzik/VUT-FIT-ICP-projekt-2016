#pragma once

#include "game.h"
#include "console.h"

class gameCli : public game
{
private: 
    console consol;    
        
    std::string dummyPlayer;
    int dummyScore;
    
public:

    gameCli(bool computer, int size);
    ~gameCli();

    void printHelp();
    void draw();
    void drawScore();
    void run();
        
};
