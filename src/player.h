/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */
 
#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

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
