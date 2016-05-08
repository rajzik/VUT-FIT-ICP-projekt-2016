/**
 * @file   game-gui.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  generating of QT application
 */

#include "game-gui.h"

/**
 * @brief gameGui::gameGui - gameGui contructor, create QT application and run it
 *
 * @param argc main application arguments count
 * @param argv main application arguments array
 */
gameGui::gameGui(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    window = new MainWindow();

    window->init();
    window->show();
    a->exec();
}

/**
 * @brief gameGui::run - unused method (application runs from gameGui contructor)
 */
void gameGui::run()
{

}

/**
 * @brief gameGui::~gameGui - delete QT application
 */
gameGui::~gameGui()
{
    delete window;
    delete a;
}
