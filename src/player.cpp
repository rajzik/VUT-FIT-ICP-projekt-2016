#include "player.h"


player::player(std::string name, bool black, bool computer)
{
    player::name = name;
    player::black = black;
    player::computer = computer;
}

int player::getScore(){
    return score;
}

void player::setScore(int score){
    player::score = score;
}

std::string player::getName(){
    return name;
}

bool player::isBlack(){
    return black;
}





