//#include <stdlib>
#include <iostream>
#include <cstdlib>
#include "game.h"

int main(){

    player * p;

    p = new player("Petr", true, false);
    std::cout << p->getName() << std::endl;
}
