
#pragma once

#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <stack>
#include <new>


enum color
{
    EMPTY,
    BLACK, 
    WHITE
};


class game{
    protected:
    std::stack<std::string> * history, * future;
    player * player1, * player2;
    int size;
    int **gameField;


    void initGameField();
    void changeFiled(bool black, int x, int y);
    public:
    game(bool computer, int size);
    
    
    bool saveGame();
    bool loadGame();
    
    void nextStep();
    void prevStep();
    
    bool makeMove(bool black, int x, int y);
    void changeField(bool black, int x, int y);
    

    virtual void draw();
    
};








