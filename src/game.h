/**
 * @file   game.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  application core logic
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
#include <boost/algorithm/string.hpp>
#include "player.h"
#include "enums.h"

#define DEFAULT_SIZE 8

/**
 * @brief Core game logic class
 */
class game{
    protected:
        int size;
        int **gameField;
        player * player1, * player2;
        std::vector<move> * history, * future;
        bool actualPlayer1;
        bool easyComputer;        
        /**
         * @brief clear history and future stacks
         */
        void clearHistory();
        void timeTravel();
        int checkDirection(bool write, int x, int y, int xDirection, int yDirection);
        void changeScore();
        int colorPath(bool write, int x, int y, int endX, int endY);
        void initGameField();
        /**
         * @brief check move possibilities
         * @return 0 actualPlayer can play, 1 actualPlayer can't play, 2 nobody can play
         */
        int impossibleMove();
        /**
         * @brief perform one computer move
         */
        void computerMove();
    public:
        /**
         * @brief Game constructor
         */
        game();
        /**
         * @brief Game destructor
         */
        ~game();
        /**
         * @brief Save actual game (size, player definition, history and future)
         * @return true on success, false when failed
         */
        bool saveGame();
        /**
         * @brief Load game from ./save folder by filename
         * @param filename
         * @return true on success, false when failed
         */
        bool loadGame(std::string filename);
        /**
         * @brief Perform step from future
         * @return true on success, false when failed
         */
        bool nextStep();
        /**
         * @brief Go back in hisory
         * @return true on success, false when failed
         */
        bool prevStep();
        /**
         * @brief Try to make specified game move
         * @param write field change persmission
         * @param x
         * @param y
         * @param clearHistory clear future
         * @return true on success, false when failed
         */
        bool makeMove(bool write, int x, int y,  bool clearFuture = true);
        /**
         * @brief Check move possibilities
         * @param write field change persmission
         * @param x
         * @param y
         * @return score change
         */
        int checkMove(bool write, int x, int y);
        /**
         * @brief change game field at coordinates x/y to actualPlayer color
         * @param x
         * @param y
         */
        void changeField(int x, int y);
        /**
         * @brief player initializatino
         * @param nameOne player1 name
         * @param nameTwo player2 name
         * @param oppositePlayer type of opposite player (human, easy computer, hard computer)
         */
        void initPlayers(std::string nameOne, std::string nameTwo, int oppositePlayer);
        /**
         * @brief Virtual method for game start
         */
        virtual void run();
        /**
         * @brief Virtual method for game redraw
         */
        virtual void draw();
};
