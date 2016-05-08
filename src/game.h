/**
 * @file   game.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
<<<<<<< HEAD
 * @brief 
 *
=======
 * @brief
>>>>>>> 228e378fa12da0f083bfb200710fc3133f2c4c28
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
#include <iomanip>
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
        
        void clearHistory();
        void timeTravel();
        int checkDirection(bool write, int x, int y, int xDirection, int yDirection);
        void changeScore();
        int colorPath(bool write, int x, int y, int endX, int endY);
        void initGameField();
        int impossibleMove();
        void computerMove();
    public:
        /**
         * Constructor of Game called by kids
         *
         */
        game();
        /**
         * Destructor of Game called by kids
         *
         */
        ~game();


        bool saveGame();
        bool loadGame(std::string filename);

        bool nextStep();
        bool prevStep();
        
        int makeMove(bool write, int x, int y,  bool clearHistory = true);
        int checkMove(bool write, int x, int y);
        void changeField(int x, int y);
        /**
        * Initialization of
        *
        */
        void initPlayers(std::string nameOne, std::string nameTwo, int oppositePlayer);
        virtual void run();
        virtual void draw();
};








