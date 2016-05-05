#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
//#include "enums.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game()
{
    ui->setupUi(this);
    initPlayers("Player 1", "Player 2", 1);
    game::size = DEFAULT_SIZE;
    initGameField();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    /* Tlacitka hraci plochy */
    for (int i =0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            maze_button[i][j] = new QPushButton(this);
            maze_button[i][j]->setGeometry(QRect(QPoint(20+60*i, 100+60*j), QSize(50, 50)));
            maze_button[i][j]->setIconSize(QSize(50,50));
            connect(maze_button[i][j], SIGNAL (released()), this, SLOT (handleButton()));
        }
    }
    connect(ui->actionNova, SIGNAL (triggered()), this, SLOT (newGame()));
    connect(ui->actionNastaveni, SIGNAL (triggered()), this, SLOT (openSettings()));
    connect(ui->actionOaplikaci, SIGNAL (triggered()), this, SLOT (openHelp()));
    connect(ui->actionUkoncit, SIGNAL (triggered()), this, SLOT (exitGame()));
    connect(ui->actionUlozit, SIGNAL (triggered()), this, SLOT (saveGame()));
    connect(ui->actionNahrat, SIGNAL (triggered()), this, SLOT (loadGame()));
}

/* Obnoveni barvy talcitek podle hraci plochy */
void MainWindow::draw()
{
    for (int i =0; i < game::size; i++) {
        for (int j =0; j < game::size; j++) {
            switch (gameField[i][j]) {
                case EMPTY:
                    //maze_button[i][j]->setStyleSheet("background-color: white");
                    maze_button[i][j]->setIcon(QIcon("../graphics/empty.png"));
                    break;
                case BLACK:
                    maze_button[i][j]->setIcon(QIcon("../graphics/black.png"));
                    break;
                case WHITE:
                    maze_button[i][j]->setIcon(QIcon("../graphics/red.png"));
                    break;
            }
        }
    }    
    ui->lblP1Score->setText(QString::number(player1->getScore()));
    ui->lblP2Score->setText(QString::number(player2->getScore()));
    ui->lblWho->setText(actualPlayer1?"<":">");
}

void MainWindow::openHelp()
{
    QMessageBox msgBox;

    msgBox.setText("Nápověda");
    msgBox.exec();
}

void MainWindow::openSettings()
{
    QMessageBox msgBox;

    msgBox.setText("Nastaveni");
    msgBox.exec();
}

void MainWindow::newGame()
{
    game::initPlayers("Player 1", "Player 2", 1);
    game::initGameField();
    draw();
}

void MainWindow::saveGame()
{
    game::saveGame();
    QMessageBox msgBox;

    msgBox.setWindowTitle("HRA 2016");
    msgBox.setText("Hra uložena.");
    msgBox.exec();
}

void MainWindow::loadGame()
{
    Popupdialog();

    //game::loadGame("save.file");
}

void MainWindow::exitGame()
{
    exit(0);
}

/* Provede akci podle stisknuteho tlacitka */
void MainWindow::handleButton()
{
    for(int i = 0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            if (sender() == maze_button[i][j]) {
                if (makeMove(actualPlayer1, i, j)) {
                    actualPlayer1 = !actualPlayer1;
                    draw();
                } else {
                    draw();
                    maze_button[i][j]->setIcon(QIcon("../graphics/wrong.png"));
                }
            }
        }
    }
}

void MainWindow::Popupdialog()
{
      QInputDialog inputdialog;
      QStringList items;
             items << tr("Spring") << tr("Summer");


     // bool val = QObject::connect(inputdialog,SIGNAL(textValueChanged(const QString &text)),this,SLOT(selText( const QString & text )));
           bool val =  QObject::connect(&inputdialog,SIGNAL(textValueChanged(const QString &)),this,SLOT(selText(const QString &)));

           bool ok;

           inputdialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
           inputdialog.setComboBoxItems(items);
           inputdialog.exec();

           //QString item = inputdialog.getItem(this,        tr("QInputDialog::getItem()"),tr("Season:"), items, 0, false, &ok);
}
