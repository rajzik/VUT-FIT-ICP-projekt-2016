/**
 * @file   mainwindow.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  file contains GUI logic, graphics initialization
 */

#include "mainwindow.h"

/**
 * @brief application window constructor, setup ui from mainwindow.iu file
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), game(), ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
}

/**
 * @brief application window destructor, delete ui
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief init buttons matrix, place them, connect to functions
 */
void MainWindow::initButtons()
{
    maze_buttons = new QPushButton**[game::size];

    for (int i =0; i < game::size; i++) {
        maze_buttons[i] = new QPushButton*[game::size];
        for (int j = 0; j < game::size; j++) {
            maze_buttons[i][j] = new QPushButton(this);
            maze_buttons[i][j]->setGeometry(QRect(QPoint(30+60*i, 205+60*j), QSize(50, 50)));
            maze_buttons[i][j]->setIconSize(QSize(50,50));
            maze_buttons[i][j]->setObjectName(QString("btn_") + QString::number(i) + QString("_") + QString::number(j));
            connect(maze_buttons[i][j], SIGNAL (released()), this, SLOT (handleButton()));
            maze_buttons[i][j]->show();
        }
    }
}

/**
 * @brief connects menu bar buttons to functions
 */
void MainWindow::connectSlots()
{
    connect(ui->actionNew, SIGNAL (triggered()), this, SLOT (newGame()), Qt::UniqueConnection);
    connect(ui->actionAbout, SIGNAL (triggered()), this, SLOT (openAbout()), Qt::UniqueConnection);
    connect(ui->actionExit, SIGNAL (triggered()), this, SLOT (exitGame()), Qt::UniqueConnection);
    connect(ui->actionSave, SIGNAL (triggered()), this, SLOT (saveGame()), Qt::UniqueConnection);
    connect(ui->actionLoad, SIGNAL (triggered()), this, SLOT (loadGame()), Qt::UniqueConnection);
    connect(ui->actionUndo, SIGNAL (triggered()), this, SLOT (undoHistory()), Qt::UniqueConnection);
    connect(ui->actionRedo, SIGNAL (triggered()), this, SLOT (redoHistory()), Qt::UniqueConnection);
}

/**
 * @brief
 */
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
    ui->lblCenterAnimation->setGeometry(QRect(QPoint(windowWidth/2-25, 20+35), QSize(50, 50)));
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
    wrongMoveAnimation->setSpeed(500);
    /* Left step animation */
    leftStepAnimation = new QMovie("./graphics/leftStep.gif");
    leftStepAnimation->setSpeed(500);
    /* Right step animation */
    rightStepAnimation = new QMovie("./graphics/rightStep.gif");
    rightStepAnimation->setSpeed(500);
    /* Backgrounds */
    ui->centralWidget->setStyleSheet("background-color: rgb(128, 128, 128);");
    ui->lblP1Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
    ui->lblP2Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
}

/**
 * @brief
 */
void MainWindow::initUi()
{
    initGraphics();
    initButtons();
    connectSlots();
    draw();
}

/**
 * @brief
 */
void MainWindow::init()
{
    game::size = DEFAULT_SIZE;
    initPlayers("Player 1", "Player 2", HUMAN);
    initGameField();
    initUi();
}

/**
 * @brief
 */
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
    /* Score font size */
    ui->lblP1Score->setFont(QFont("Cantarell", (ui->lblP1Score->text().toInt() > 99)?30:40));
    ui->lblP2Score->setFont(QFont("Cantarell", (ui->lblP2Score->text().toInt() > 99)?30:40));
}

/**
 * @brief
 */
void MainWindow::openAbout()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("About");
    msgBox.setText("Reversi - ICP 2016\n"
                   "Jan Šilhan and Pavel Pospíšil\n");
    msgBox.move(appMiddle);
    msgBox.exec();
}

/**
 * @brief
 */
void MainWindow::undoHistory()
{
    if (!game::prevStep()) {
        ui->lblCenterAnimation->setMovie(wrongMoveAnimation);
        wrongMoveAnimation->start();
    } else {
        ui->lblCenterAnimation->setMovie(leftStepAnimation);
        leftStepAnimation->start();
        draw();
        run();
    }
}

/**
 * @brief
 */
void MainWindow::redoHistory()
{
    if (!game::nextStep()) {
        ui->lblCenterAnimation->setMovie(wrongMoveAnimation);
        wrongMoveAnimation->start();
    } else {
        ui->lblCenterAnimation->setMovie(rightStepAnimation);
        rightStepAnimation->start();
        draw();
        run();
    }
}

/**
 * @brief
 */
void MainWindow::clearButtons()
{
    for (int i = 0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            delete maze_buttons[i][j];
        }
    }
    delete maze_buttons;
}

/**
 * @brief
 */
void MainWindow::newGame()
{
    QString selectedSize;
    QString selectedOponent;
    QStringList gameSizes;
    QStringList gameOponents;
    bool sizeSelected;
    bool oponentSelected;

    gameSizes << "6" << "8" << "10" << "12";
    gameOponents << QString::fromStdString(gStrings[Ghuman]) << QString::fromStdString(gStrings[GcomputerEasy]) << QString::fromStdString(gStrings[GcomputerHard]);
    selectedSize = QInputDialog::getItem(this, tr("New game"), tr("Choose playing area size"), gameSizes, 0, false, &sizeSelected);
    if (sizeSelected && !selectedSize.isEmpty()) {
        selectedOponent = QInputDialog::getItem(this, tr("New game"), tr("Choose adversary"), gameOponents, 0, false, &oponentSelected);
        if (oponentSelected && !selectedOponent.isEmpty()) {
            clearButtons();
            game::size = selectedSize.toInt();
            initPlayers("Player1", "Player2", gameOponents.indexOf(selectedOponent));
            initGameField();
            initUi();
            run();
        }
    }
}

/**
 * @brief
 */
void MainWindow::saveGame()
{    
    QMessageBox msgBox;

    msgBox.move(appMiddle);
    msgBox.setWindowTitle("Reversi");
    if (game::saveGame()) {
        msgBox.setText(QString::fromStdString(gStrings[Gsave]));
    } else {
        msgBox.setText(QString::fromStdString(eStrings[Esave]));
    }
    msgBox.exec();
}

/**
 * @brief
 */
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
    selectedFile = QInputDialog::getItem(this, tr("Reversi"), tr("Choose game for load:"), fileNames, 0, false, &fileSelected);
    if (fileSelected && !selectedFile.isEmpty()) {        
        clearButtons();
        if (game::loadGame(selectedFile.toStdString())) {
            initUi();
            draw();
            run();
        } else {
            QMessageBox msgBox;

            msgBox.move(appMiddle);
            msgBox.setWindowTitle("Reversi");
            msgBox.setText(QString::fromStdString(eStrings[Eload]));
            msgBox.exec();
        }
    }
}

/**
 * @brief
 */
void MainWindow::exitGame()
{
    exit(0);
}

/**
 * @brief
 */
void MainWindow::handleButton()
{
    QStringList senderPosition = sender()->objectName().split( "_" );

    if (makeMove(WRITE, senderPosition.at(1).toInt(), senderPosition.at(2).toInt())) {
        draw();
        run();
    } else {
        ui->lblCenterAnimation->setMovie(wrongMoveAnimation);
        wrongMoveAnimation->start();
    }
}

/**
 * @brief
 */
void MainWindow::run()
{
    QMessageBox msgBox;

    switch (impossibleMove()) {
        case 0:
            if (!actualPlayer1 && player2->computer) {
                computerMove();
                draw();
                run();
            }
            break;
        case 1:
            msgBox.setWindowTitle("Reversi");            
            msgBox.setText(QString("There is no possible move.\n") +
                           QString((actualPlayer1)?"Black player":"White player") + QString::fromStdString(gStrings[Gskip]));
            msgBox.move(appMiddle);
            msgBox.exec();
            actualPlayer1 = !actualPlayer1;
            draw();
            run();
            break;
        case 2:
            msgBox.setWindowTitle("Reversi");
            if (player1->getScore() == player2->getScore()) {
                msgBox.setText(QString::fromStdString(gStrings[Gdraw]));
            } else {
                msgBox.setText(QString((player1->getScore() > player2->getScore())?"Black player":"White player") + QString::fromStdString(gStrings[Gwin]));
            }
            msgBox.move(appMiddle);
            msgBox.exec();
            draw();
        break;
    }
}
