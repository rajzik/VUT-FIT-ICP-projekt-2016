#pragma once

#include "game.h"
#include "mainwindow.h"
#include <QApplication>

class gameGui : public game
{
private:
    QApplication * a;
    MainWindow * window;
public:
    gameGui(bool computer, int size, int argc, char * argv[]);
    ~gameGui();
    void draw();
};
