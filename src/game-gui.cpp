#include "game-gui.h"

gameGui::gameGui(int argc, char *argv[])
{    
    int width = 50 + DEFAULT_SIZE*60;
    int height = 225 + DEFAULT_SIZE*60;
    a = new QApplication(argc, argv);
    window = new MainWindow(width, height);
    window->setFixedSize(width, height);
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
