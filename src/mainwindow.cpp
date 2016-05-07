#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), game(), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
            maze_buttons[i][j]->show();
        }
    }
}

void MainWindow::connectSlots()
{
    connect(ui->actionNew, SIGNAL (triggered()), this, SLOT (newGame()));
    connect(ui->actionAbout, SIGNAL (triggered()), this, SLOT (openAbout()));
    connect(ui->actionExit, SIGNAL (triggered()), this, SLOT (exitGame()));
    connect(ui->actionSave, SIGNAL (triggered()), this, SLOT (saveGame()));
    connect(ui->actionLoad, SIGNAL (triggered()), this, SLOT (loadGame()));
    connect(ui->actionUndo, SIGNAL (triggered()), this, SLOT (undoHistory()));
    connect(ui->actionRedo, SIGNAL (triggered()), this, SLOT (redoHistory()));
}

void MainWindow::initGraphics()
{
    /* Window size */
    windowWidth = 50 + game::size*60;
    windowHeight = 225 + game::size*60;
    this->setFixedSize(windowWidth, windowHeight);
    appMiddle = ui->centralWidget->mapToGlobal(ui->centralWidget->pos());
    appMiddle.setX(appMiddle.x() + windowWidth/2);
    appMiddle.setY(appMiddle.y() + windowHeight/2);
    /* Positions */
    ui->lblP2Color->setGeometry(QRect(QPoint(windowWidth-50-120, 20), QSize(120, 120)));
    ui->lblP2Score->setGeometry(QRect(QPoint(windowWidth-50-120, 20), QSize(120, 120)));
    ui->lblWrongMove->setGeometry(QRect(QPoint(windowWidth/2-25, 20+35), QSize(50, 50)));
    /* Black Animation */
    blackAnimation = new QMovie("./graphics/blackPlayer.gif");
    ui->lblP1Color->setMovie(blackAnimation);
    blackAnimation->start();
    /* White animation */
    whiteAnimation = new QMovie("./graphics/whitePlayer.gif");
    ui->lblP2Color->setMovie(whiteAnimation);
    whiteAnimation->start();
    /* Wrong animation */
    wrongMoveAnimation = new QMovie("./graphics/wrongMove.gif");
    ui->lblWrongMove->setMovie(wrongMoveAnimation);
    wrongMoveAnimation->setSpeed(500);
    /* Backgrounds */
    ui->centralWidget->setStyleSheet("background-color: rgb(128, 128, 128);");
    ui->lblP1Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
    ui->lblP2Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
}

void MainWindow::init(int size)
{
    game::size = size;

    initPlayers("Player 1", "Player 2", 1);
    initGameField();
    initGraphics();
    initButtons();
    connectSlots();
    draw();
}

void MainWindow::draw()
{
    /* Buttons */
    for (int i =0; i < game::size; i++) {
        for (int j =0; j < game::size; j++) {
            switch (gameField[i][j]) {
                case EMPTY:
                    maze_buttons[i][j]->setIcon(QIcon("./graphics/emptyStone.png"));
                    break;
                case BLACK:
                    maze_buttons[i][j]->setIcon(QIcon("./graphics/blackStone.png"));
                    break;
                case WHITE:
                    maze_buttons[i][j]->setIcon(QIcon("./graphics/whiteStone.png"));
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
        whiteAnimation->jumpToFrame(1);
    } else {        
        blackAnimation->stop();
        whiteAnimation->start();
        blackAnimation->jumpToFrame(1);
    }
}

void MainWindow::openAbout()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("About");
    msgBox.setText("Reversi - ICP 2016\n"
                   "Jan Šilhan and Pavel Pospíšil\n");
    msgBox.move(appMiddle);
    msgBox.exec();
}

void MainWindow::undoHistory()
{
    QMessageBox msgBox;

    game::prevStep();
    msgBox.setText("Step back ");
    msgBox.move(appMiddle);
    msgBox.exec();
}

void MainWindow::redoHistory()
{
    QMessageBox msgBox;

    game::nextStep();
    msgBox.setText("Krok vpřed proveden.");
    msgBox.move(appMiddle);
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
    QString selectedOponent;
    QStringList gameSizes;
    QStringList gameOponents;
    bool sizeSelected;
    bool oponentSelected;

    gameSizes << "6" << "8" << "10" << "12";
    gameOponents << "Člověk" << "Počítač - lehčí" << "Počítač - těžší";
    selectedSize = QInputDialog::getItem(this, tr("Nová hra"), tr("Volba velikosti hrací plochy"), gameSizes, 0, false, &sizeSelected);
    if (sizeSelected && !selectedSize.isEmpty()) {
        selectedOponent = QInputDialog::getItem(this, tr("Nová hra"), tr("Volba protihráče"), gameOponents, 0, false, &oponentSelected);
        if (oponentSelected && !selectedOponent.isEmpty()) {
            clearButtons();
            init(selectedSize.toInt());
        }
    }
}

void MainWindow::saveGame()
{    
    QMessageBox msgBox;

    game::saveGame();
    msgBox.move(appMiddle);
    msgBox.setWindowTitle("Uložit hru");
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
        game::loadGame(selectedFile.toStdString());
        QMessageBox msgBox;
        msgBox.move(appMiddle);
        msgBox.setText("Hra " + selectedFile + "nahrána.");
        msgBox.exec();
        draw();
    }
}

void MainWindow::exitGame()
{
    exit(0);
}

void MainWindow::handleButton()
{    
    QMessageBox msgBox2;
    QMessageBox msgBox;    

    for(int i = 0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            if (sender() == maze_buttons[i][j]) {
                if (makeMove(WRITE, i, j)) {
                    draw();
                    actualPlayer1 = !actualPlayer1;
                    /* Kontrola následujícího hráče */
                    switch (impossibleMove()) {
                        case 0:
                            break;
                        case 1:                            
                            actualPlayer1 = !actualPlayer1;
                            draw();
                            msgBox.setText("Nelze provést další tah, hráč bude přeskočen.");
                            msgBox.move(appMiddle);
                            msgBox.exec();
                            break;
                        case 2:                            
                            msgBox2.setText("Hra u konce!!");
                            msgBox2.move(appMiddle);
                            msgBox2.exec();                            
                        break;
                    }
                } else {
                    wrongMoveAnimation->start();                    
                }
                draw();
            }
        }
    }
}

void MainWindow::run()
{

}

void MainWindow::makeComputerMove()
{

}
