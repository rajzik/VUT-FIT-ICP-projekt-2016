#pragma once

//#include <stdlib.h>
//#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>

class player
{
    protected:
        int score;
        std::string name;
        bool black;
        bool computer;
    public:
        player(std::string name, bool black, bool computer);

        int getScore();
        void setScore(int score);

        std::string getName();
        bool isBlack();
};
