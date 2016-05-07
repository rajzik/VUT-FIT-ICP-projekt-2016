/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */

#include "game-gui.h"

gameGui::gameGui(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    window = new MainWindow();

    window->init(DEFAULT_SIZE, HUMAN);
    window->show();
    a->exec();
}

void gameGui::run()
{

}

gameGui::~gameGui()
{
    delete window;
    delete a;
}
