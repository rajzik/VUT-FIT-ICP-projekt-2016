/**
 * @file   game.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
 */

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
        std::vector<move> * history, * future;
        bool actualPlayer1;
        bool easyComputer;
        
        void timeTravel();
        int checkDirection(bool write, int x, int y, int xDirection, int yDirection);
        void changeScore();
        int colorPath(bool write, int x, int y, int endX, int endY);
        void initGameField();
        int impossibleMove();
        void computerMove();
    public:
        game();
        ~game();


        bool saveGame();
        bool loadGame(std::string filename);

        bool nextStep();
        bool prevStep();
        
        int makeMove(bool write, int x, int y,  bool clearHistory = true);
        int checkMove(bool write, int x, int y);
        void changeField(int x, int y);
        void initPlayers(std::string nameOne, std::string nameTwo, int oppositePlayer);
        virtual void run();
        virtual void draw();
};








