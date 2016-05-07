#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include "player.h"
#include "enums.h"

#define DEFAULT_SIZE 8

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
        bool actualPlayer1;
        
        int checkDirection(bool write, int x, int y, int xDirection, int yDirection);
        void changeScore();
        int colorPath(bool write, int x, int y, int endX, int endY);
        void initGameField();        
        int impossibleMove();
    public:
        game();
        ~game();
        

        bool saveGame();
        bool loadGame(std::string filename);

        void nextStep();
        void prevStep();
        
        bool makeMove(bool write, int x, int y);
        bool checkMove(bool write, int x, int y);
        void changeField(int x, int y);
        void initPlayers(std::string nameOne, std::string nameTwo, bool computer);
        virtual void run();
        virtual void draw();
};








