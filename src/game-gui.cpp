/**
 * @file   game-gui.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  generating of QT application
 */

#include "game-gui.h"

/**
 * @brief gameGui contructor, create QT application
 *
 * @param argc main application arguments count
 * @param argv main application arguments array
 */
gameGui::gameGui(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
}

/**
 * @brief create window, init game and run application
 */
int gameGui::run()
{
    window = new MainWindow();
    window->init();
    window->show();
    return a->exec();
}

/**
 * @brief delete QT application and window
 */
gameGui::~gameGui()
{
    delete window;
    delete a;
}
