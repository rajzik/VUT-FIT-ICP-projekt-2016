#include "game-cli.h"



gameCli::gameCli(bool computer, int size)
:game(computer, size){
    dummyPlayer = "Silhan";
    dummyScore = 0;
    consol.clear();
    printHelp();
}
     
gameCli::~gameCli(){
    
}


void gameCli::drawScore(){
    
    std::cout << dummyPlayer << ": " << dummyScore << "\t" << dummyPlayer << ": " << dummyScore << std::endl;
}

void gameCli::draw(){
    
    consol.clear();
    consol.setFgColor(CSBLACK);
    consol.setBgColor(CSWHITE);

    std::cout << "  ";
    for(int firstLine = 0; firstLine < size; firstLine++)
        std::cout << (char)(97 + firstLine) << " ";
    std::cout << std::endl;
    
    
    for (int y = 0; y < size; y++)
    {
        std::cout << (y+1) << " ";
        for (int x = 0; x < size; x++)
        {
            if(gameField[x][y] == EMPTY)
                std::cout << "_";
            else{
                consol.setFgColor(gameField[x][y] == BLACK? CSYELLOW: CSBLACK);
                consol.setBgColor(gameField[x][y] == BLACK? CSBLACK : CSWHITE);
            
                std::cout << (gameField[x][y] == BLACK?"X":"O");        
                consol.setFgColor(CSBLACK);
                consol.setBgColor(CSWHITE);
            }
            std::cout << "|";
        }
        std::cout << std::endl;
    }
    
    consol.resetToDefault();
    
    std::cout << std::endl;
    consol.setCursor(size*2 + 5, 5);
    std::cout << "Now Playing: "<< dummyPlayer << std::endl;
    consol.setCursor(0, size*2+4);
    
    drawScore();    
}


void gameCli::run(){
    
    
    while (true)
    {
        std::string command;
        draw();
      
        
        std::cin >> command;
        if(command.compare("quit") >= 0 || command.compare("q") >= 0)
            return;
            
        if(command.compare("help") >= 0 || command.compare("h") >= 0)
            printHelp();
    }
}

void gameCli::printHelp(){
    std::cout << "HRA2016 Help" <<std::endl
    
    << "To help write help/h" << std::endl
    << "to continue to game press any key" << std::endl;
    
    std::cin.get();
    
}


