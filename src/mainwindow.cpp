#include "mainwindow.h"

MainWindow::MainWindow(int width, int height, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), game()
{
    ui->setupUi(this);
    windowSize[0] = width;
    windowSize[1] = height;
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
            maze_button[i][j]->setGeometry(QRect(QPoint(30+60*i, 205+60*j), QSize(50, 50)));
            maze_button[i][j]->setIconSize(QSize(50,50));
            connect(maze_button[i][j], SIGNAL (released()), this, SLOT (handleButton()));
        }
    }
    /* Propojeni akci a tlacitek v menu */
    connect(ui->actionNova, SIGNAL (triggered()), this, SLOT (newGame()));
    connect(ui->actionNastaveni, SIGNAL (triggered()), this, SLOT (openSettings()));
    connect(ui->actionOaplikaci, SIGNAL (triggered()), this, SLOT (openHelp()));
    connect(ui->actionUkoncit, SIGNAL (triggered()), this, SLOT (exitGame()));
    connect(ui->actionUlozit, SIGNAL (triggered()), this, SLOT (saveGame()));
    connect(ui->actionNahrat, SIGNAL (triggered()), this, SLOT (loadGame()));
    animations[0] = new QMovie("../graphics/black_120.gif");
    animations[1] = new QMovie("../graphics/white_120.gif");
    /*Nastaveni labelu */
    ui->lblP2Color->setGeometry(QRect(QPoint(windowSize[0]-50-120, 20), QSize(120, 120)));
    ui->lblP2Color->setMovie(animations[1]);
    animations[0]->start();
    ui->lblP1Color->setMovie(animations[0]);
    animations[1]->start();
    ui->centralWidget->setStyleSheet("background-color: rgb(128, 128, 128);"); // barva pozadi
    ui->lblP1Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
    ui->lblP2Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
    ui->lblP2Score->setGeometry(QRect(QPoint(windowSize[0]-50-120, 20), QSize(120, 120)));
}

/* Obnoveni barvy talcitek podle hraci plochy */
void MainWindow::draw()
{    
    for (int i =0; i < game::size; i++) {
        for (int j =0; j < game::size; j++) {
            switch (gameField[i][j]) {
                case EMPTY:
                    maze_button[i][j]->setIcon(QIcon("../graphics/empty_50.bmp"));
                    break;
                case BLACK:
                    maze_button[i][j]->setIcon(QIcon("../graphics/black_50.png"));
                    break;
                case WHITE:
                    maze_button[i][j]->setIcon(QIcon("../graphics/white_50.png"));
                    break;
            }
        }
    }    
    ui->lblP1Score->setText(QString::number(player1->getScore()));
    ui->lblP2Score->setText(QString::number(player2->getScore()));
    if (actualPlayer1) {
        animations[0]->start();
        animations[1]->stop();
    } else {
        animations[0]->stop();
        animations[1]->start();
    }
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
                } else {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("HRA 2016");
                    msgBox.setText("Neplatný tah");
                    msgBox.exec();
                }
                draw();
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

void MainWindow::run()
{}
