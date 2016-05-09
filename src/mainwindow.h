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
#include <QTimer>
#include <QThread>
#include <ui_mainwindow.h>
#include "game.h"

/**
 * @brief Make all dialogs same width
 */
#define MSGBOXSPACER QString("\n                                                           ") /* QT hack to resize QMessagebox*/
/**
 * @brief Delay after warning and computer mve speed
 */
#define PAUSEDELAY 500

namespace Ui {
    class MainWindow;
}

/**
 * @brief GUI class contains graphics and GUI methods for graphic game
 */
class MainWindow : public QMainWindow, public game
{
    Q_OBJECT
private:
    /**
     * @brief Gae field buttons matix
     */
    QPushButton ***maze_buttons;
    /**
     * @brief Black player background animation
     */
    QMovie *blackAnimation;
    /**
     * @brief White player background animation
     */
    QMovie *whiteAnimation;
    /**
     * @brief Animation for wrong moves
     */
    QMovie *wrongMoveAnimation;
    /**
     * @brief Back in time animation
     */
    QMovie *leftStepAnimation;
    /**
     * @brief To the future animation
     */
    QMovie *rightStepAnimation;
    /**
     * @brief Warning animation (player skipped)
     */
    QMovie *warningAnimatrion;
    /**
     * @brief Application UI class
     */
    Ui::MainWindow *ui;
    /**
     * @brief Game window width
     */
    int windowWidth;
    /**
     * @brief Game window height
     */
    int windowHeight;
    /**
     * @brief Middle of the game window
     */
    QPoint appMiddle;
    /**
     * @brief True when game is paused, game buttons are disabled
     */
    bool sleeper;
    /**
     * @brief Redraw buttons, score, animations
     */
    void draw();
    /**
     * @brief Playing "loop", check move possibilities, skips, game over
     */
    void run();
    /**
     * @brief Init buttons matrix, place them, connect to functions
     */
    void initButtons();
    /**
     * @brief Init labels posstition, load animations, set backgrounds
     */
    void initGraphics();
    /**
     * @brief Connects menu bar buttons to functions
     */
    void connectSlots();
    /**
     * @brief Delete field buttons
     */
    void clearButtons();
    /**
     * @brief Refresh middle point to show dialog
     */
    void centerAppMiddle();
    /**
     * @brief Pause game (inactive buttons)
     */
    void pauseGame();
public:
    /**
     * @brief Application window constructor, setup ui from mainwindow.iu file
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief Init game at start
     */
    void init();
    /**
     * @brief Call graphics init methods
     */
    void initUi();
    /**
     * @brief Application window destructor, delete ui
     */
    ~MainWindow();
private slots:
    /**
     * @brief Open about dialog
     */
    void openAbout();
    /**
     * @brief Open help dialog
     */
    void openHelp();
    /**
     * @brief Open save dialog, save game
     */
    void saveGame();
    /**
     * @brief Open dialog, get info from user, init new game
     */
    void newGame();
    /**
     * @brief Open load dialog, load game
     */
    void loadGame();
    /**
     * @brief Exit game with code 0
     */
    void exitGame();
    /**
     * @brief React on button click
     */
    void handleButton();
    /**
     * @brief Go to the future!
     */
    void redoHistory();
    /**
     * @brief Go back in time
     */
    void undoHistory();
    /**
     * @brief Continue game (activate buttons)
     */
    void continueGame();
};
