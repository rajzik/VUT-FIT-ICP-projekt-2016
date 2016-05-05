#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
//#include "enums.h"

/*
#include "game.h"
#include <QString>
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_set(new Ui::MainWindow),
    game()
{
    ui_set->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui_set;
}

/* Obnoveni barvy talcitek podle hraci plochy */
void MainWindow::draw()
{
    for (int i =0; i < game::size; i++) {
        for (int j =0; j < game::size; j++) {
            switch (gameField[i][j]) {
                case EMPTY:
                    maze_button[i][j]->setStyleSheet("background-color: white");
                    break;
                case BLACK:
                    maze_button[i][j]->setStyleSheet("background-color: black");
                    break;
                case WHITE:
                    maze_button[i][j]->setStyleSheet("background-color: red");
                    break;
                default: // Chybovy stav
                    maze_button[i][j]->setStyleSheet("background-color: green");
                    break;
            }
        }
    }
    /*ui_set->label_1->setText(QString::number(players[0]->getScore()));
    ui_set->label_2->setText(QString::number(players[1]->getScore()));
    ui_set->label_3->setText(QString::fromStdString(players[actualPlayer]->getName()));*/
}

void MainWindow::printHelp()
{
    QMessageBox msgBox;

    msgBox.setText("Toto okno obsahuje nápovědu.");
    msgBox.exec();
}

void MainWindow::init()
{
    /* Tlacitka hraci plochy */
    for (int i =0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            maze_button[i][j] = new QPushButton(this);
            maze_button[i][j]->setGeometry(QRect(QPoint(20+50*i, 100+50*j),
            QSize(50, 50)));
            connect(maze_button[i][j], SIGNAL (released()), this, SLOT (handleButton()));
        }
    }
    /* Ovladaci tlacitka */
    for (int i =0; i < 5; i++) {
        ui_button[i] = new QPushButton(this);
        ui_button[i]->setGeometry(QRect(QPoint(20 + 80*i, 20),
        QSize(70, 30)));
    }
    connect(ui_button[0], SIGNAL (released()), this, SLOT (printHelp()));
    ui_button[0]->setText("Nápověda");
}

/* Provede akci podle stisknuteho tlacitka */
void MainWindow::handleButton()
{
    for(int i = 0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            if (sender() == maze_button[i][j]) {
                makeMove(true, i, j);
                draw();
            }
        }
    }
}
