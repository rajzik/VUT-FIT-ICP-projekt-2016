/**
 * @file   player.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
 */
 
#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

/**
 * @brief Game player class, contains score, name, color, and methods
 */
class player
{
    protected:
        /**
        * @brief score var
        */
        int score;
        /**
        * @brief name var
        */
        std::string name;
        /**
        * @brief black var
        */
        bool black;
    public:
        /**
        * @brief Player constructor
        * @param name Name of player for later expansion
        * @param black if player is black
        * @param computer if player is computer
        */
        player(std::string name, bool black, bool computer);
        /**
        * @brief getter for score
        * @return score
        */
        int getScore();
        /**
        * @brief setter for score
        * @param score
        */
        void setScore(int score);
        /**
         * @brief Computer var
         */
        bool computer;
        /**
        * @brief getter for name
        * @return name
        */
        std::string getName();
        /**
        * @brief getter for color
        * @return color
        */
        bool isBlack();
};
