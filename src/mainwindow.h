#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QMovie>
#include "game.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public game
{
    Q_OBJECT

public:
    explicit MainWindow(int width, int height, QWidget *parent = 0);
    void draw();
    void run();
    void init();
    ~MainWindow();
    void Popupdialog();
private slots:
    void openHelp();
    void saveGame();
    void newGame();
    void openSettings();
    void loadGame();
    void exitGame();
    void handleButton();
private:
    QPushButton *maze_button[8][8];
    QPushButton *ui_button[5];
    QMovie *animations[2];
    Ui::MainWindow *ui;
    int windowSize[2];
};

#endif // MAINWINDOW_H
