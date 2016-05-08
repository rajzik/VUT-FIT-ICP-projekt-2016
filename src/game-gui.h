/**
 * @file   game-gui.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
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
