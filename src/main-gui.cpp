#include "game-gui.h"

int main(int argc, char * argv[])
{
    gameGui * game = new gameGui(argc, argv);

    game->run();
}
