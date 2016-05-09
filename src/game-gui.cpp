/**
 * @file   game-gui.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  generating of QT application
 */

#include "game-gui.h"

gameGui::gameGui(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    window = new MainWindow();
    window->init();
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
