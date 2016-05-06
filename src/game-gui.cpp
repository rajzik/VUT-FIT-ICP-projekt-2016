#include "game-gui.h"

gameGui::gameGui(int argc, char *argv[])
{
    a = new QApplication(argc, argv);
    window = new MainWindow();

    window->init(DEFAULT_SIZE);
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
