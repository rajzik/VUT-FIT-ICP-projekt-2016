#pragma once

#include "game.h"
#include "console.h"

class gameCli : public game
{
public:

    gameCli(bool computer, int size);
    ~gameCli();


    void draw();
};
