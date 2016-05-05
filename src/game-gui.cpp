#include "game-gui.h"
#include "mainwindow.h"
#include <QApplication>

gameGui::gameGui(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    window = new MainWindow();
    window->setFixedSize(40 + DEFAULT_SIZE*50, 120 + DEFAULT_SIZE*50);
    window->init();
    window->show();
    window->draw();
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
