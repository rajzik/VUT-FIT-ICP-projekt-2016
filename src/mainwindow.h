/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    QPushButton *maze_buttons[12][12]; // not good
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
    void init(int size, int oppositePlayer);
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

#endif // MAINWINDOW_H
