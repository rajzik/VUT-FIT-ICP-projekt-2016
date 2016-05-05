#pragma once

#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
//#include <QPushButton>

class gameGui
{
private:
    QApplication * a;
    MainWindow * window;
public:
    gameGui(int argc, char * argv[]);
    void run();
    ~gameGui();
};
