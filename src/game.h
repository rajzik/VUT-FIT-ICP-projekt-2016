#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#include <algorithm>
#include <math.h>
#include "player.h"

enum color
{
    EMPTY,
    BLACK,
    WHITE
};


typedef struct move{
    bool player;
    int x;
    int y;
} move;


class game{
    protected:
        int size;
        int **gameField;
        player * player1, * player2;
        std::stack<move> * history, * future;

        
        int checkDirection(bool black, int x, int y, int xDirection, int yDirection);
        void changeScore(bool black, int newScore);
        void colorPath(bool color, int x, int y, int endX, int endY);
        void initGameField();
        void changeFiled(bool black, int x, int y);
    public:
        game(bool computer, int size);
        ~game();
        

        bool saveGame();
        bool loadGame();

        void nextStep();
        void prevStep();
        
        bool makeMove(bool black, int x, int y);
        bool checkMove(bool black, int x, int y);
        void changeField(bool black, int x, int y);
        void initPlayers(std::string nameOne, std::string nameTwo, bool computer);
        virtual void run();
        virtual void draw();
};








