/**
 * @file   mainwindow.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief  file contains GUI logic, graphics initialization
 */

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

void MainWindow::initGraphics()
{
    /* Window size */
    windowWidth = 50 + game::size*60;
    windowHeight = 225 + game::size*60;
    this->setFixedSize(windowWidth, windowHeight);
    /* Positions */
    ui->lblP2Color->setGeometry(QRect(QPoint(windowWidth-50-120, 20), QSize(120, 120)));
    ui->lblP2Score->setGeometry(QRect(QPoint(windowWidth-50-120, 20), QSize(120, 120)));
    ui->lblCenterAnimation->setGeometry(QRect(QPoint(windowWidth/2-25, 20+35), QSize(50, 50)));
    /* Animations */
    blackAnimation = new QMovie("./graphics/blackPlayer.gif");
    whiteAnimation = new QMovie("./graphics/whitePlayer.gif");
    wrongMoveAnimation = new QMovie("./graphics/wrongMove.gif");    
    wrongMoveAnimation->setSpeed(500);
    warningAnimatrion = new QMovie("./graphics/warning.gif");    
    wheelAnimation = new QMovie("./graphics/wheel.png");
    leftStepAnimation = new QMovie("./graphics/leftStep.gif");
    leftStepAnimation->setSpeed(500);    
    rightStepAnimation = new QMovie("./graphics/rightStep.gif");
    rightStepAnimation->setSpeed(500);
    /* Backgrounds */
    ui->lblP1Color->setMovie(blackAnimation);
    blackAnimation->start();
    ui->lblP2Color->setMovie(whiteAnimation);
    whiteAnimation->start();
    ui->centralWidget->setStyleSheet("background-color: rgb(128, 128, 128);");
    ui->lblP1Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
    ui->lblP2Score->setStyleSheet("background-color: rgba(0, 0, 0, 0%);");
}

void MainWindow::initUi()
{
    initGraphics();
    initButtons();
    connectSlots();
    draw();
}

void MainWindow::init()
{
    sleeper = false;
    game::size = DEFAULT_SIZE;
    initPlayers("Player 1", "Player 2", HUMAN);
    initGameField();
    initUi();
}

void MainWindow::draw()
{
    /* Buttons icons */
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

void MainWindow::centerAppMiddle()
{
    appMiddle.setX(this->geometry().x());
    appMiddle.setY(this->geometry().y());
    appMiddle.setX(appMiddle.x() + windowWidth/2 - 140);
    appMiddle.setY(appMiddle.y() + windowHeight/2);
}

void MainWindow::openAbout()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("About");
    msgBox.setText(QString("Reversi - ICP 2016\n"
                   "Jan Šilhan and Pavel Pospíšil\n"
                    + MSGBOXSPACER));
    centerAppMiddle();
    msgBox.move(appMiddle);

    msgBox.exec();
}

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

void MainWindow::clearButtons()
{
    for (int i = 0; i < game::size; i++) {
        for (int j = 0; j < game::size; j++) {
            delete maze_buttons[i][j];
        }
    }
    delete maze_buttons;
}

void MainWindow::newGame()
{
    QString selectedSize;
    QString selectedOponent;
    QStringList gameSizes;
    QStringList gameOponents;
    QInputDialog gameSizeDialog;
    QInputDialog oponentDialog;

    gameSizeDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    centerAppMiddle();
    gameSizeDialog.move(appMiddle);
    gameSizeDialog.resize(150, 200);
    oponentDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    centerAppMiddle();
    oponentDialog.move(appMiddle);
    oponentDialog.resize(150, 200);

    gameOponents << QString::fromStdString(gStrings[Ghuman]) << QString::fromStdString(gStrings[GcomputerEasy]) << QString::fromStdString(gStrings[GcomputerHard]);
    gameSizes << "6" << "8" << "10" << "12";

    gameSizeDialog.setComboBoxItems(gameSizes);
    gameSizeDialog.setWindowTitle("New game");
    gameSizeDialog.setLabelText("Playing area size" + MSGBOXSPACER);
    if (gameSizeDialog.exec()) {
            selectedSize = gameSizeDialog.textValue();
            oponentDialog.setComboBoxItems(gameOponents);
            oponentDialog.setWindowTitle("New game");
            oponentDialog.setLabelText("Choose oponent" + MSGBOXSPACER);
            if (oponentDialog.exec()) {
                selectedOponent = oponentDialog.textValue();
                clearButtons();
                game::size = selectedSize.toInt();
                clearHistory();
                initPlayers("Player1", "Player2", gameOponents.indexOf(selectedOponent));
                initGameField();
                initUi();
                run();
            }
    }
}

void MainWindow::saveGame()
{    
    QMessageBox msgBox;

    centerAppMiddle();
    msgBox.move(appMiddle);
    msgBox.setWindowTitle("Reversi");
    if (game::saveGame()) {
        msgBox.setText(QString::fromStdString(gStrings[Gsave]) + MSGBOXSPACER);
    } else {
        msgBox.setText(QString::fromStdString(eStrings[Esave]) + MSGBOXSPACER);
    }
    msgBox.exec();
}

void MainWindow::loadGame()
{
    QStringList fileNames;
    QDir savesDir("./saves");
    QFileInfoList list;
    QString selectedFile;
    QInputDialog loadDialog;

    savesDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    list = savesDir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        fileNames << list.at(i).fileName();
    }
    loadDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    centerAppMiddle();
    loadDialog.move(appMiddle);
    loadDialog.resize(150, 200);
    loadDialog.setComboBoxItems(fileNames);
    loadDialog.setWindowTitle("Reversi");
    loadDialog.setLabelText("Choose game for load" + MSGBOXSPACER);
    if (loadDialog.exec()) {
        selectedFile = loadDialog.textValue();
        clearButtons();
        if (game::loadGame(selectedFile.toStdString())) {
            initUi();
            draw();
            run();
        } else {
            QMessageBox msgBox;

            centerAppMiddle();
            msgBox.move(appMiddle);
            msgBox.setWindowTitle("Reversi");
            msgBox.setText(QString::fromStdString(eStrings[Eload]) + MSGBOXSPACER);
            msgBox.exec();
        }
    }
}

void MainWindow::exitGame()
{
    exit(0);
}

void MainWindow::handleButton()
{
    QStringList senderPosition = sender()->objectName().split( "_" );

    if (sleeper)
        return;

    if (makeMove(WRITE, senderPosition.at(1).toInt(), senderPosition.at(2).toInt())) {
        draw();
        run();
    } else {
        ui->lblCenterAnimation->setMovie(wrongMoveAnimation);
        wrongMoveAnimation->start();
    }
}

void MainWindow::computerMovePause()
{
    sleeper = true;    
    QTimer::singleShot(COMPUTERDELAY, this, SLOT(computerMoveContinue()));
}

void MainWindow::computerMoveContinue()
{
    sleeper = false;    
    draw();
    run();
}

void MainWindow::run()
{    

    switch (impossibleMove()) {
        case 0:
            if (!actualPlayer1 && player2->computer) {                
                computerMove();
                computerMovePause();
            }
            break;
        case 1:            
            ui->lblCenterAnimation->setMovie(warningAnimatrion);
            warningAnimatrion->start();
            actualPlayer1 = !actualPlayer1;
            draw();
            run();
            break;
        case 2:
            QMessageBox msgBox;
            msgBox.setWindowTitle("Reversi");
            if (player1->getScore() == player2->getScore()) {
                msgBox.setText(QString::fromStdString(gStrings[Gdraw]));
            } else {
                msgBox.setText(QString((player1->getScore() > player2->getScore())?"Black player":"White player") + QString::fromStdString(gStrings[Gwin]) + MSGBOXSPACER);
            }
            centerAppMiddle();
            msgBox.move(appMiddle);
            msgBox.exec();
            draw();
        break;
    }
}
