/**
 * @file   player.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
 */

#include "player.h"

player::player(std::string name, bool black, bool computer)
{
    player::name = name;
    player::black = black;
    player::computer = computer;
    player::score = 2;
}

int player::getScore() {
    return score;
}

void player::setScore(int score) {
    player::score = score;
}

std::string player::getName() {
    return name;
}

bool player::isBlack() {
    return black;
}
