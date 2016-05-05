#include "game-gui.h"

gameGui::gameGui(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    window = new MainWindow();
    window->setFixedSize(40 + DEFAULT_SIZE*60, 120 + DEFAULT_SIZE*60);
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
