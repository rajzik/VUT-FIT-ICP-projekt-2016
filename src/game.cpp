/**
 * @file   game.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
 *
 */

#include "game.h"
#include "player.h"

game::game()
{
    history = new std::vector<move>();
    future = new std::vector<move>();
}

void game::initPlayers(std::string nameOne, std::string nameTwo, int oppositePlayer)
{
    game::easyComputer = oppositePlayer % 2;
    actualPlayer1 = true;
    player1 = new player(nameOne, true, false);
    player2 = new player(nameTwo, false, oppositePlayer);
}

game::~game()
{
    delete player1;
    delete player2;
}

void game::computerMove()
{
    if (game::easyComputer) {
        /* Random move */
        int randomX;
        int randomY;
        std::srand(std::time(0));
        do {
            randomX = std::rand() % game::size;
            randomY = std::rand() % game::size;
        } while (!makeMove(WRITE, randomX, randomY));
    } else {
        /* Find maximal moves + random select */
        int maxScore = 0, actScore, randomPos;
        std::vector<int> xVals, yVals;
        /* Find maximal value */
        for (int i = 0; i < game::size; i++) {
            for (int j = 0; j < game::size; j++) {
                actScore = makeMove(READ, i, j);
                if (actScore == maxScore) {
                    xVals.push_back(i);
                    yVals.push_back(j);
                }
                if (actScore > maxScore) {
                    maxScore = actScore;
                    xVals.clear();
                    yVals.clear();
                    xVals.push_back(i);
                    yVals.push_back(j);
                }
            }
        }
        /* Random select from max */
        std::srand(std::time(0));
        randomPos = std::rand() % xVals.size();
        makeMove(WRITE, xVals.at(randomPos), yVals.at(randomPos));
    }
}

void game::initGameField() {
    if(!(size == 6 || size == 8 || size == 10 || size == 12 ))
        return;   
    gameField = new int*[size];

    for(int i = 0; i < size; i++)
        gameField[i] = new int[size];    
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
            gameField[x][y] = EMPTY;

    int center = size/2;
    
    gameField[center-1][center-1] = WHITE;
    gameField[center-1][center] = BLACK;
    gameField[center][center-1] = BLACK;
    gameField[center][center] = WHITE;        
}


int game::makeMove(bool write, int x, int y, bool clearHistory) {
    if(x < 0 || y < 0 || x >= size || y >= size)
        return false;
    if(gameField[x][y] != EMPTY)
        return false;
    bool validMove = checkMove(write, x, y);
    move mv = {actualPlayer1,x,y};
    if(validMove && write == WRITE){
        changeScore();

        history->push_back(mv);
        if(clearHistory && write == WRITE)
            future->clear();
        actualPlayer1 = !actualPlayer1;
    }
    return validMove;
}

int game::impossibleMove()
{
    bool blackCan = false;
    bool whiteCan = false;
    bool actualPlayerBackup;

    actualPlayerBackup = actualPlayer1;
    for (int i = 0; i < game::size; i++) {
        for (int j =0; j < game::size; j++) {
            /* Check black player */
            actualPlayer1 = 1;
            if (game::makeMove(READ, i, j))
                blackCan = true;
            /* Check white player */
            actualPlayer1 = 0;
            if (game::makeMove(READ, i, j))
                whiteCan = true;
        }
    }
    actualPlayer1 = actualPlayerBackup;
    /* Nobody can move - return 2 */
    if (!blackCan && !whiteCan) {
        return 2;
    }
    /* Actual can move - return 0 || Skip actual player - return 1 */
    if (actualPlayer1) {
        if (blackCan) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if (whiteCan) {
            return 0;
        } else {
            return 1;
        }
    }
}

int game::checkMove(bool write, int x, int y){

    int score = 0;
    // std::cout<<"leva"<<std::endl;    
    if(x > 0)
        score += checkDirection(write, x,y, 0,y);
    
    // std::cout<<"prava"<<std::endl;
    if(x < size-1)
        score += checkDirection(write, x,y, size-1,y);
        
    // std::cout<<"nahoru"<<std::endl;
    if(y > 0)
        score += checkDirection(write, x,y, x,0);
        
    // std::cout<<"dolu"<<std::endl;
    if(y < size-1)
        score += checkDirection(write, x,y, x,size-1);
        
    // std::cout<<"leva nahoru"<<std::endl;
    if(x > 0 && y > 0){
        int minimum = std::min(x,y);
        score += checkDirection(write, x, y, x-minimum, y-minimum);
    }
    
    // std::cout<<"leva dolu"<<std::endl;
    if(x > 0 && y < size-1){
        int minimum = std::min(x,size-1-y);
        score += checkDirection(write, x, y, x-minimum, y+minimum);
    }
    
    // std::cout<<"prava dolu"<<std::endl;
    if(x<size-1 && y < size-1){
        int minimum = std::min(size-1-x, size-1-y);
        score += checkDirection(write, x, y, x + minimum, y+minimum);
    }
    
    // std::cout<<"prava nahoru"<<std::endl;
    if(x<size-1 && y > 0){
        int minimum = std::min(size-1-x, y);
        score += checkDirection(write,x,y,x+minimum, y-minimum);
    }
    
    if(score == 1)
    {
        score--;
        gameField[x][y] = EMPTY;
    }
    
    return score;
}

void game::timeTravel(){
    actualPlayer1 = true;
    initGameField();
    
    std::vector<move> * tempVector = new std::vector<move>();
    
    swap(tempVector, history);
    
    for(int i = 0, a = tempVector->size(); i < a; i++){
        move m = tempVector->at(i);
        makeMove(WRITE, m.x, m.y, false);
    }
    changeScore();
    
}
int game::checkDirection(bool write, int x, int y, int endX, int endY){
    // std::cout<<"x:"<<x<<" y: "<<y<<" endX: "<<endX<< " endY: "<<endY<<std::endl;
    
    int revColor = actualPlayer1?WHITE:BLACK;
    int color = actualPlayer1?BLACK:WHITE;
    
    
    int stepCount = std::max(abs(x-endX),abs(y-endY));
    int xStep = (endX-x)/stepCount;
    int yStep = (endY-y)/stepCount;
    
    int dataField = gameField[x+1*xStep][y+1*yStep];
    if(dataField != revColor)
    { 
        return 0;
    }


    
    for(int i = 2; i <= stepCount; i++){
        dataField = gameField[x+i*xStep][y+i*yStep];
        if(dataField == color){
            return colorPath(write, x,y, x+i*xStep, y+i*yStep);
        }
        if(dataField == EMPTY)
            break;
    }
    
    return 0;
}

int game::colorPath(bool write, int x, int y, int endX, int endY){
    
    int stepCount = std::max(abs(x-endX),abs(y-endY));
    int xStep = (endX-x)/stepCount;
    int yStep = (endY-y)/stepCount;

    if (write == READ)
        return stepCount;
    int i;
    for(i = 0; i <= stepCount; i++){
        changeField(x+i*xStep, y+i*yStep);
    }
    return i;
}

void game::changeField(int x, int y) {
    // std::cout<<"obarvuji: "<< x << y<<std::endl;
    gameField[x][y] = actualPlayer1 ? BLACK : WHITE;
}

bool game::saveGame() {
    
    boost::filesystem::path dir("saves");
    
    boost::filesystem::create_directory(dir);
    
    std::stringstream filename; 
    int biggest = -1;
    for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(dir), {}))
    {
        std::stringstream ss;
        ss << boost::filesystem::basename(entry);
        int actualNum = std::stoi("0" + ss.str());
        if(actualNum > biggest)
            biggest = actualNum;
    }
    filename << (++biggest) << "a.sav";
    
    std::ofstream savFile;
    savFile.open(("saves/"+ filename.str()), std::ios::out | std::ios::binary);
    if(!savFile.is_open())
        return false;
    savFile << "fs" << std::endl;
    savFile << size << std::endl;
    savFile << "fse"<<std::endl;
    
    if(player2->computer){
        savFile << "pc"<<std::endl;
        savFile << easyComputer << ";"<<std::endl;
        savFile << "pce"<<std::endl;
    }
    
    
    

    if(!history->empty())
    {
        savFile << "hs"<<std::endl;
        savFile << history->size()<<std::endl;
        for(int a = 0, si =history->size(); a < si; a++){
            move m = history->at(a);
            savFile << m.player <<";"<<m.x<<";"<<m.y<<";"<<std::endl;
        }
        for(int a = future->size()-1; a > 0; a--){
            move m = future->at(a);
            savFile << m.player <<";"<<m.x<<";"<<m.y<<";"<<std::endl;
        }
        savFile << "hse"<<std::endl;
    }
    
    if(!future->empty())
    {
        savFile << "ft"<<std::endl;
        savFile << future->size()<<std::endl;
        savFile << "fte"<<std::endl;
    }
    

    
    
    savFile.close();
    return true;
}

bool game::loadGame(std::string filename) {
    boost::filesystem::path dir("saves");
    boost::filesystem::create_directory(dir);
    
    if(!boost::filesystem::exists( "saves/"+filename ))
        return false;
    
    
    std::ifstream savFile;
    savFile.open("saves/"+filename);
    std::stringstream ss;
    ss << savFile.rdbuf();
    std::string content = ss.str();
    std::size_t pos;
    savFile.close();
    std::string a;

    
    if((pos = content.find("fs")) == std::string::npos)
        return false;
    
    content.erase(0, 3);
    
    if((pos = content.find("\n")) == std::string::npos)
        return false;
    
    
    int tempSize = std::stoi("0" + content.substr(0, pos));

    if(!((tempSize % 2) == 0 && tempSize >= 6  && tempSize <= 12) )
        return false;
        
    content.erase(0, pos+1);
    size = tempSize;
    initGameField();

    if((pos = content.find("fse")) == std::string::npos)
        return false;
    
    content.erase(0, pos+4);
        
    if((pos = content.find("pc")) != std::string::npos)
    {
        
        content.erase(0, pos+3);
        if((pos = content.find(";")) == std::string::npos)
            return false;    
        int tempComputer = std::stoi("0" + content.substr(0,pos));
        if(tempComputer < 0 || tempComputer > 2)
            return false;
                    
        initPlayers("Player 1", "Player2", tempComputer);
        player2->computer =true;
        content.erase(0, pos+2);
        
        if((pos = content.find("pce")) == std::string::npos)
            return false;    
        content.erase(0, pos+4);
    }
    else
    {
        initPlayers("Player 1", "Player2", 0);
    }
    
    
    if((pos = content.find("hs")) != std::string::npos)
    {
        content.erase(0, pos + 3);
        if((pos = content.find("\n")) == std::string::npos)
            return false;
        tempSize = std::stoi("0" + content.substr(0, pos));
        content.erase(0, pos+1);
        if(tempSize <= 0)
            return false;
        
        // actualPlayer1 = true;
        
        for(int i = 0; i < tempSize; i++){
            move m;
            if((pos = content.find(";")) == std::string::npos)
                return false;
            actualPlayer1 = m.player = std::stoi("0" + content.substr(0, pos)) == 1;
            
            content.erase(0, pos+1);
            if((pos = content.find(";")) == std::string::npos)
                return false;
            m.x = std::stoi("0" + content.substr(0, pos));
            content.erase(0, pos+1);
            
            if((pos = content.find(";")) == std::string::npos)
                return false;
            m.y = std::stoi("0" + content.substr(0, pos));
            content.erase(0, pos+2);
            
            makeMove(WRITE, m.x, m.y);            
        }
        
        
    
        if((pos = content.find("hse")) == std::string::npos)
            return false;
        
        content.erase(0, pos + 4);
    
    }
    
    if((pos = content.find("ft")) != std::string::npos)
    {
        content.erase(0, pos + 3);
        if((pos = content.find("\n")) == std::string::npos)
            return false;
        tempSize = std::stoi("0" + content.substr(0, pos));
        content.erase(0, pos+1);
        if(tempSize <= 0)
            return false;
        
        for(int i = 0; i < tempSize; i++){
            prevStep();
        }
        
        if((pos = content.find("fte")) != std::string::npos)
            content.erase(0, pos + 3);
    }
    
    
    return true;
}

bool game::nextStep() {
    if(future->empty())
        return false;

    history->push_back(future->back());
    future->pop_back();
    
    timeTravel();
    return true;
}

bool game::prevStep() {
    if(history->empty())
        return false;
    future->push_back(history->back());
    history->pop_back();
    if(player2->computer)
    {
        future->push_back(history->back());
        history->pop_back();  
    }
    timeTravel();
    return true;
}


void game::changeScore(){
    int black = 0, white = 0;
    for(int x = 0; x < size;x ++)
    {
        for(int y = 0; y < size; y++)
            if(gameField[x][y] == BLACK)
                black++;
            else if(gameField[x][y] == WHITE)
                white++;
    }
    player1->setScore(black);
    player2->setScore(white);    
}



void game::draw(){}
void game::run(){}
