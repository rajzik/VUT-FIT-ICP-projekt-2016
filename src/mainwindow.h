/**
 * @file   mainwindow.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  class from gui part
 */

#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QMovie>
#include <QStringList>
#include <QSpacerItem>
#include <QGridLayout>
#include <QDir>
#include <ui_mainwindow.h>
#include "game.h"

#define msgBoxSpacer QString("\n                                                           ") /* QT hack to resize QMessagebox*/

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
    /**
     * @brief redraw buttons, score, animations
     */
    void draw();
    /**
     * @brief playing "loop", check move possibilities, skips, game over
     */
    void run();
    /**
     * @brief init buttons matrix, place them, connect to functions
     */
    void initButtons();
    /**
     * @brief init labels posstition, load animations, set backgrounds
     */
    void initGraphics();
    /**
     * @brief connects menu bar buttons to functions
     */
    void connectSlots();
    /**
     * @brief delete field buttons
     */
    void clearButtons();
    /**
     * @brief refresh middle point to show dialog
     */
    void centerAppMiddle();
public:
    /**
     * @brief application window constructor, setup ui from mainwindow.iu file
     *
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief init game at start
     */
    void init();
    /**
     * @brief call graphics init methods
     */
    void initUi();
    /**
     * @brief application window destructor, delete ui
     */
    ~MainWindow();
private slots:
    /**
     * @brief open about dialog
     */
    void openAbout();
    /**
     * @brief open save dialog, save game
     */
    void saveGame();
    /**
     * @brief open dialog, get info from user, init new game
     */
    void newGame();
    /**
     * @brief open load dialog, load game
     */
    void loadGame();
    /**
     * @brief exit game with code 0
     */
    void exitGame();
    /**
     * @brief react on button click
     */
    void handleButton();
    /**
     * @brief go to the future!
     */
    void redoHistory();
    /**
     * @brief go back in time
     */
    void undoHistory();
};
