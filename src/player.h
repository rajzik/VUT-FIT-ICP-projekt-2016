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
        int score;
        std::string name;
        bool black;

    public:
        player(std::string name, bool black, bool computer);
        bool computer;
        int getScore();
        void setScore(int score);

        std::string getName();
        bool isBlack();
};
