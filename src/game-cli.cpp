#include "game-cli.h"



     gameCli::gameCli(bool computer, int size)
    :game(computer, size){}
     
    gameCli::~gameCli(){
        
    }


void gameCli::draw(){
    
    gameField[2][2] = WHITE;
    gameField[3][3] = BLACK;
     
    
    
    
    std::cout << "  a b c d e f g h" <<std::endl;
    for (int x = 0; x < size; x++)
    {
        std::cout << (x+1) << " ";
        for (int y = 0; y < size; y++)
        {
            if(gameField[x][y] == EMPTY)
                std::cout << "_";
                
            else
            {
                // system(gameField[x][y] == BLACK? "Color 1A": "Color 2B");
                std::cout << (gameField[x][y] == BLACK?"X":"O");   
            }        
            std::cout << "|";
            
        }
        std::cout << std::endl;
    }
    
    
    
    
    
}