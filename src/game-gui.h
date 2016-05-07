#pragma once

#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <cstdlib>
#include <QApplication>

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
