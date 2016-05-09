/**
 * @file   game-gui.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  GUI application
 */

#pragma once

#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <cstdlib>
#include <QApplication>

/**
 * @brief GUI class contains GUI application components
 */
class gameGui
{
private:
    /**
     * @brief Application class
     */
    QApplication * a;
    /**
     * @brief Application window class
     */
    MainWindow * window;
public:
    /**
     * @brief gameGui contructor, create QT application
     * @param argc main application arguments count
     * @param argv main application arguments array
     */
    gameGui(int argc, char * argv[]);
    /**
     * @brief create window, init game and run application
     */
    void run();
    /**
     * @brief delete QT application and window
     */
    ~gameGui();
};
