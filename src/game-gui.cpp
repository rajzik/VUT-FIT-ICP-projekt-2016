#include "game-gui.h"
#include "mainwindow.h"
#include <QApplication>

gameGui::gameGui(int argc, char *argv[]) : game()
{
    a = new QApplication(argc, argv);
    window = new MainWindow();

    window->show();
    a->exec();
}
     
gameGui::~gameGui()
{
    delete window;
    delete a;
}

void gameGui::draw()
{
    window->draw();
}
