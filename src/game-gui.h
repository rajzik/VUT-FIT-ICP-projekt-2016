/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */
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
