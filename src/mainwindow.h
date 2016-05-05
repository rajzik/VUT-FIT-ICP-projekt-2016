#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "game.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow, public game
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void draw();
    void init();
    ~MainWindow();
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
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
