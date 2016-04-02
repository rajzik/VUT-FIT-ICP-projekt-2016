#include "game-gui.h"
#include "mainwindow.h"
#include <QApplication>

gameGui::gameGui(bool computer, int size, int argc, char *argv[]) : game(computer, size)
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
