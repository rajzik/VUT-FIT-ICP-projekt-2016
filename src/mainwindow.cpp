#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), game(), ui(new Ui::MainWindow)
{
    /*
    ui->setupUi(this);
    game::size = DEFAULT_SIZE;
    windowWidth = 50 + size*60;
    windowHeight = 225 + size*60;
    this->setFixedSize(windowWidth, windowHeight);
    initPlayers("Player 1", "Player 2", 1);
    initGameField();
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initButtons()
{
    for (int i =0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            maze_buttons[i][j] = new QPushButton(this);
            maze_buttons[i][j]->setGeometry(QRect(QPoint(30+60*i, 205+60*j), QSize(50, 50)));
            maze_buttons[i][j]->setIconSize(QSize(50,50));
            connect(maze_buttons[i][j], SIGNAL (released()), this, SLOT (handleButton()));
        }
    }
}

void MainWindow::connectSlots()
{
    connect(ui->actionNew, SIGNAL (triggered()), this, SLOT (newGame()));
    connect(ui->actionAbout, SIGNAL (triggered()), this, SLOT (openHelp()));
    connect(ui->actionExit, SIGNAL (triggered()), this, SLOT (exitGame()));
    connect(ui->actionSave, SIGNAL (triggered()), this, SLOT (saveGame()));
    connect(ui->actionLoad, SIGNAL (triggered()), this, SLOT (loadGame()));
    connect(ui->actionUndo, SIGNAL (triggered()), this, SLOT (undoHistory()));
    connect(ui->actionRedo, SIGNAL (triggered()), this, SLOT (redoHistory()));
}

void MainWindow::initGraphics()
{
    /* Positions */
    ui->lblP2Color->setGeometry(QRect(QPoint(windowWidth-50-120, 20), QSize(120, 120)));
    ui->lblP2Score->setGeometry(QRect(QPoint(windowWidth-50-120, 20), QSize(120, 120)));
    /* Black Animation */
    blackAnimation = new QMovie("../graphics/black_120.gif");
    ui->lblP1Color->setMovie(blackAnimation);
    blackAnimation->start();
    /* White animation */

    whiteAnimation = new QMovie("../graphics/white_120.gif");
    ui->lblP2Color->setMovie(whiteAnimation);
    whiteAnimation->start();
    /* Backgrounds */
    ui->centralWidget->setStyleSheet("background-color: rgb(128, 128, 128);");
    ui->lblP1Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
    ui->lblP2Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
}

void MainWindow::init(int size)
{
    game::size = size;
    ui->setupUi(this);
    windowWidth = 50 + game::size*60;
    windowHeight = 225 + game::size*60;
    this->setFixedSize(windowWidth, windowHeight);
    initPlayers("Player 1", "Player 2", 1);

    initGameField();

    initButtons();
    connectSlots();
    initGraphics();
    draw();
}

void MainWindow::draw()
{
    /* Buttons */
    for (int i =0; i < game::size; i++) {
        for (int j =0; j < game::size; j++) {
            switch (gameField[i][j]) {
                case EMPTY:
                    maze_buttons[i][j]->setIcon(QIcon("../graphics/empty_50.bmp"));
                    break;
                case BLACK:
                    maze_buttons[i][j]->setIcon(QIcon("../graphics/black_50.png"));
                    break;
                case WHITE:
                    maze_buttons[i][j]->setIcon(QIcon("../graphics/white_50.png"));
                    break;
            }
        }
    }    
    /* Score and animations */
    ui->lblP1Score->setText(QString::number(player1->getScore()));
    ui->lblP2Score->setText(QString::number(player2->getScore()));
    if (actualPlayer1) {
        blackAnimation->start();
        whiteAnimation->stop();
    } else {
        blackAnimation->stop();
        whiteAnimation->start();
    }
}

void MainWindow::openHelp()
{
    QMessageBox msgBox;

    msgBox.setText("Nápověda");
    msgBox.exec();
}

void MainWindow::undoHistory()
{
    QMessageBox msgBox;

    msgBox.setText("Historie zpět");
    msgBox.exec();
}

void MainWindow::redoHistory()
{
    QMessageBox msgBox;

    msgBox.setText("Historie vpřed");
    msgBox.exec();
}

void MainWindow::clearButtons()
{
    for (int i = 0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            delete maze_buttons[i][j];
        }
    }
}

void MainWindow::newGame()
{
    QString selectedSize;
    QStringList fileNames;
    bool sizeSelected;

    fileNames << "6" << "8" << "10" << "12";
    selectedSize = QInputDialog::getItem(this, tr("Nová hra"), tr("Volba velikosti hrací plochy"), fileNames, 0, false, &sizeSelected);
    if (sizeSelected && !selectedSize.isEmpty()) {
        clearButtons();
        game::size = selectedSize.toInt();
        game::initPlayers("Player 1", "Player 2", 1);
        game::initGameField();
        init(game::size);
        draw();
    }
}

void MainWindow::saveGame()
{
    game::saveGame();
    QMessageBox msgBox;

    msgBox.setWindowTitle("Reversi");
    msgBox.setText("Hra uložena.");
    msgBox.exec();
}

void MainWindow::loadGame()
{
    QStringList fileNames;
    QDir savesDir("./saves");
    QFileInfoList list;
    QString selectedFile;
    bool fileSelected;

    savesDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    list = savesDir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        fileNames << list.at(i).fileName();
    }
    selectedFile = QInputDialog::getItem(this, tr("Nahrát hru"), tr("Volba uložené hry:"), fileNames, 0, false, &fileSelected);
    if (fileSelected && !selectedFile.isEmpty()) {
        /**/
        QMessageBox msgBox;
        msgBox.setText(selectedFile);
        msgBox.exec();
        return;
        /**/
        game::loadGame(selectedFile.toStdString());
        draw();
    }
}

void MainWindow::exitGame()
{
    exit(0);
}

void MainWindow::disableButtons()
{
    for (int i =0; i < game::size; i++) {
        for (int j =0; j < game::size; j++) {
            maze_buttons[i][j]->setEnabled(false);
        }
    }
}

void MainWindow::handleButton()
{    
    QMessageBox msgBox2;
    QMessageBox msgBox;
    QMessageBox msgBox3;

    for(int i = 0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            if (sender() == maze_buttons[i][j]) {
                if (makeMove(WRITE, i, j)) {
                    actualPlayer1 = !actualPlayer1;
                    /* Kontrola následujícího hráče */
                    switch (impossibleMove()) {
                        case 0:
                            break;
                        case 1:
                            draw();
                            actualPlayer1 = !actualPlayer1;
                            msgBox.setText("Nelze provést další tah, hráč bude přeskočen.");
                            msgBox.exec();
                            break;
                        case 2:
                            draw();
                            msgBox2.setText("Hra u konce!!");
                            msgBox2.exec();
                            disableButtons();
                        break;
                    }
                } else {
                    msgBox3.setText("Neplatný tah");
                    msgBox3.exec();
                    ui->label->setText("Neplatný tah!");
                }
                draw();
            }
        }
    }
}

void MainWindow::run()
{

}
