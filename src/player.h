
#pragma once 
#include <stdlib.h>
#include <stdio.h>
#include <string>


class player
{
    public:
        player(std::string name, bool black, bool computer);

        int getScore();
        void setScore(int score);
        
        bool isBlack();
        
        std::string getName();
        
        

    protected:

    int score;
    std::string name;
    bool black;
    bool computer;
    
    
    
};


