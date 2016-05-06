#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <ui_mainwindow.h>
#include <QMessageBox>
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
    QPushButton *maze_buttons[8][8];
    QMovie *blackAnimation;
    QMovie *whiteAnimation;
    Ui::MainWindow *ui;
    int windowWidth;
    int windowHeight;
    void draw();
    void run();
    void initButtons();
    void initGraphics();
    void connectSlots();
    void Popupdialog();
    void clearButtons();
    void disableButtons();
public:
    explicit MainWindow(QWidget *parent = 0);
    void init(int size);
    ~MainWindow();
private slots:
    void openHelp();
    void saveGame();
    void newGame();    
    void loadGame();
    void exitGame();
    void handleButton();
    void redoHistory();
    void undoHistory();
};

#endif // MAINWINDOW_H
