/**
 * @file   mainwindow.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  My dream class
 */

#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QDateTime>
#include <QMovie>
#include <QStringList>
#include <QDir>
#include <iostream>
#include "game.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public game
{
    Q_OBJECT
private:
    QPushButton ***maze_buttons;
    QMovie *blackAnimation;
    QMovie *whiteAnimation;
    QMovie *wrongMoveAnimation;
    QMovie *leftStepAnimation;
    QMovie *rightStepAnimation;
    QMovie *centerAnimation;
    Ui::MainWindow *ui;
    int windowWidth;
    int windowHeight;
    QPoint appMiddle;
    void draw();
    void run();
    void initButtons();
    void initGraphics();
    void connectSlots();    
    void clearButtons();
public:
    explicit MainWindow(QWidget *parent = 0);
    void init();
    void initUi();
    ~MainWindow();
private slots:
    void openAbout();
    void saveGame();
    void newGame();    
    void loadGame();
    void exitGame();
    void handleButton();
    void redoHistory();
    void undoHistory();
};
