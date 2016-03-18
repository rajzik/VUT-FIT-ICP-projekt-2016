#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#include "player.h"

enum color
{
    EMPTY,
    BLACK,
    WHITE
};

class game{
    protected:
        int size;
        int **gameField;
        player * player1, * player2;
        std::stack<std::string> * history, * future;
        std::vector<std::pair<int, int>> p1Moves;
        std::vector<std::pair<int, int>> p2Moves;

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
        std::vector<std::pair<int, int>> * checkRules(bool black);
        virtual void run();
        virtual void draw();
};








