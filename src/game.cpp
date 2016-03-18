
#include "game.h"
#include "player.h"
game::game(bool computer, int size)
{
    history = new std::stack<std::string>();
    future = new std::stack<std::string>();
    std::string name = "player";
    // player1 = new player(name+"1", false, computer);
    // player2 = new player(name+"2", true, false);
    if(size == 6 || size == 8 || size == 10 || size == 12 ) {
        game::size = size;
        game::initGameField();
    } else {
        exit(1);
    }
    
    int firstX = size/2;
    int firstY = size/2;
    
    gameField[firstX-1][firstY-1] = BLACK;
    gameField[firstX-1][firstY] = WHITE;
    gameField[firstX][firstY-1] = WHITE;
    gameField[firstX][firstY] = BLACK;
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

    game::changeField(black, x, y);
    return true;
}


bool game::saveGame() {
    return true;
}

bool game::loadGame() {
    return true;
}

void game::changeField(bool black, int x, int y) {
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


void game::draw(){}
void game::run(){}