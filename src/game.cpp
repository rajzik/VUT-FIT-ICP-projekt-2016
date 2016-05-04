
#include "game.h"
#include "player.h"

game::game(bool computer, int size)
{
    history = new std::stack<std::string>();
    future = new std::stack<std::string>();
    std::string name = "player";
    if(size == 6 || size == 8 || size == 10 || size == 12 ) {
        game::size = size;
        game::initGameField();
    } else {
        exit(1);
    }
    
    int firstX = size/2;
    
    gameField[firstX-1][firstX-1] = BLACK;
    gameField[firstX-1][firstX] = WHITE;
    gameField[firstX][firstX-1] = WHITE;
    gameField[firstX][firstX] = BLACK;
    
    
    // checkMove(true, 5, 3);
    // checkMove(false,5, 2);
    // checkMove(false,5, 4);
    // gameField[5][3] = BLACK;
    // changeField(true, 5, 3);
    std::cout<<std::endl;
    
    
}

void game::initPlayers(std::string nameOne, std::string nameTwo, bool computer){
    player1 = new player(nameOne, false, computer);
    player2 = new player(nameTwo, true, false); 
}


game::~game()
{
    
}

void game::initGameField() {
    gameField = new int*[size];

    for(int i = 0; i < size; i++)
        gameField[i] = new int[size];
}


bool game::makeMove(bool black, int x, int y) {
    if(x < 0 || y < 0 || x >= size || y >= size)
        return false;
    if(gameField[x][y] != EMPTY)
        return false;

    checkMove(black, x, y);
    return true;
}
bool game::checkMove(bool black, int x, int y){

    int score = 0;
    // std::cout<<"leva"<<std::endl;    
    if(x > 0)
        score += checkDirection(black, x,y, 0,y);
    
    // std::cout<<"prava"<<std::endl;
    if(x < size-1)
        score += checkDirection(black, x,y, size-1,y);
        
    // std::cout<<"nahoru"<<std::endl;
    if(y > 0)
        score += checkDirection(black, x,y, x,0);
        
    // std::cout<<"dolu"<<std::endl;
    if(y < size-1)
        score += checkDirection(black, x,y, x,size-1);
        
    // std::cout<<"leva nahoru"<<std::endl;
    if(x > 0 && y > 0){
        int minimum = std::min(x,y);
        score += checkDirection(black, x, y, x-minimum, y-minimum);
    }
    
    // std::cout<<"leva dolu"<<std::endl;
    if(x > 0 && y < size-1){
        int minimum = std::min(x,size-1-y);
        score += checkDirection(black, x, y, x-minimum, y+minimum);
    }
    
    // std::cout<<"prava dolu"<<std::endl;
    if(x<size-1 && y < size-1){
        int minimum = std::min(size-1-x, size-1-y);
        score += checkDirection(black, x, y, x + minimum, y+minimum);
    }
    
    // std::cout<<"prava nahoru"<<std::endl;
    if(x<size-1 && y > 0){
        int minimum = std::min(size-1-x, y);
        score += checkDirection(black,x,y,x+minimum, y-minimum);
    }
    
    changeScore(black, score);
    if(score != 0)
        changeScore(!black, - (score - 1));
    
    return score != 0;
}

int game::checkDirection(bool black, int x, int y, int endX, int endY){
    // std::cout<<"x:"<<x<<" y: "<<y<<" endX: "<<endX<< " endY: "<<endY<<std::endl;
    
    int color = black?BLACK:WHITE, score = 0;
    int revColor = black?WHITE:BLACK;
    bool oposite = false, bro = false;
    
    
    int stepCount = std::max(abs(x-endX),abs(y-endY));
    int xStep = (endX-x)/stepCount;
    int yStep = (endY-y)/stepCount;
    
    
    for(int i = 1; i <= stepCount; i++){
        int dataField = gameField[x+i*xStep][y+i*yStep];
        if(dataField == revColor)
        { 
            oposite =true;
            continue;
        }
        if(oposite && dataField == color){
            score++;
            colorPath(black, x,y, x+i*xStep, y+i*yStep);
            break;
        }
        if(dataField == EMPTY)
            break;
    }
    
    
    return score;
     
}

void game::colorPath(bool color, int x, int y, int endX, int endY){  
    
    int stepCount = std::max(abs(x-endX),abs(y-endY));
    int xStep = (endX-x)/stepCount;
    int yStep = (endY-y)/stepCount;
    
    
    for(int i = 0; i <= stepCount; i++){
        changeField(color, x+i*xStep, y+i*yStep);
        //gameField[][] = color;
    }
}

bool game::saveGame() {
    return true;
}

bool game::loadGame() {
    return true;
}

void game::changeField(bool black, int x, int y) {
    std::cout<<"obarvuji: "<< x << y<<std::endl;
    gameField[x][y] = black? BLACK : WHITE;
}

void game::nextStep() {
    if(future->empty())
        return; // ??

    history->push(future->top());
    future->pop();
}

void game::prevStep() {
    if(history->empty())
        return; // ??

    future->push(history->top());
    history->pop();
}


void game::changeScore(bool black, int scoreDiff){
    if(black)
        player1->setScore(player1->getScore() + scoreDiff);
    else
        player2->setScore(player2->getScore() + scoreDiff);
}



void game::draw(){}
void game::run(){}