
#include "game.h"
#include "player.h"

game::game()
{
    history = new std::stack<move>();
    future = new std::stack<move>();
}
void game::initPlayers(std::string nameOne, std::string nameTwo, bool computer){
    player1 = new player(nameOne, false, computer);
    player2 = new player(nameTwo, true, false); 
}
game::~game()
{
    delete player1;
    delete player2;
}

void game::initGameField() {
    if(!(size == 6 || size == 8 || size == 10 || size == 12 ))
        return;   
    gameField = new int*[size];

    for(int i = 0; i < size; i++)
        gameField[i] = new int[size];
        
    for(int x = 0; x < size; x++)
        for(int y = 0; y < size; y++)
            gameField[x][y] = 0;    
        
    int center = size/2;
    
    gameField[center-1][center-1] = WHITE;
    gameField[center-1][center] = BLACK;
    gameField[center][center-1] = BLACK;
    gameField[center][center] = WHITE;    
    
}


bool game::makeMove(bool black, int x, int y) {
    if(x < 0 || y < 0 || x >= size || y >= size)
        return false;
    if(gameField[x][y] != EMPTY)
        return false;
    bool validMove = checkMove(black, x, y);
    move mv = {black,x,y};
    if(validMove){
        history->push(mv);
        
        std::stack<move> * empty = new std::stack<move>();
        swap(future, empty);
    
    }
    return validMove;
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
    }
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
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
            savFile << gameField[x][y];
        savFile<<std::endl;
    }
    
    savFile << "fse"<<std::endl;
    move a = {true, 0,1};
    history->push(a);
    std::stack<move> * tempStack = new std::stack<move>(); 

    if(!history->empty())
    {
        savFile << "hs"<<std::endl;
        savFile << history->size()<<std::endl;
        while(!history->empty()){
            move m = history->top();
            tempStack->push(m);
            savFile << m.player <<";"<<m.x<<";"<<m.y<<";"<<std::endl;
            history->pop(); 
        }
        savFile << "hse"<<std::endl;
    }
    while(!tempStack->empty()){
        history->push(tempStack->top());
        tempStack->pop();        
    }
    
    future->push(a);
    if(!future->empty())
    {
        savFile << "fs"<<std::endl;
        savFile << future->size()<<std::endl;
        while(!future->empty()){
            move m = future->top();
            tempStack->push(m);
            savFile << m.player <<";"<<m.x<<";"<<m.y<<";"<<std::endl;
            future->pop(); 
        }
        savFile << "fse"<<std::endl;
    }
    while(!tempStack->empty()){
        future->push(tempStack->top());
        tempStack->pop();        
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
    
    if((pos = content.find("fs")) == std::string::npos)
        return false;
    
    content.erase(0, 3);
    
    if((pos = content.find("\n")) == std::string::npos)
        return false;
    
    int tempSize = std::stoi("0" + content.substr(0, pos));
    if(!((tempSize % 2) == 0 && tempSize < 6  && tempSize > 12) )
        return false;
    content.erase(0, pos+1);
    
    
    size = tempSize;
    initGameField();
    
    
    
    
    for(int x = 0; x < size; x++){
        for(int y = 0; y < size; y++){
            int tempColor = std::stoi("0"+ content.substr(0,1));
            if(tempColor > 2 || tempColor < 0)
                return false;
            gameField[x][y] = tempColor;
            content.erase(0,1); 
        }
        content.erase(0,1);
    }
    
    
    if((pos = content.find("fse")) == std::string::npos)
        return false;
    
    content.erase(0, pos+4);
    
    if((pos = content.find("hse")) != std::string::npos)
    {
        content.erase(0, pos + 4);
        
        
        
    }
    
    
    
    return true;
}

void game::changeField(bool black, int x, int y) {
    // std::cout<<"obarvuji: "<< x << y<<std::endl;
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