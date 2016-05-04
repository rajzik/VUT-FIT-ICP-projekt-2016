#include "game-cli.h"


constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}


gameCli::gameCli(bool computer, int size)
:game(computer, size){
    consol.clear();
    printHelp();
    getGameInfo();
    actualPlayer = true;
}
     
gameCli::~gameCli(){
    
}

void gameCli::getGameInfo(){
    
    int single = -1;
    std::string a;
    while(true){
        consol.clear();        
        if(single != -1)
            std::cout<< "Please enter valid game type 1 or 2"<<std::endl;
                
        std::cout<<"1) Single Player"<<std::endl
        <<"2) Multiplayer"<<std::endl
        <<"Please enter game type: ";
        

        std::getline(std::cin, a);
        single = std::stoi("0"+a);
        
        if(single == 1 || single == 2)
            break;
        
    }
    initPlayers("Player 1", "Player 2", single == 1);
    
}

void gameCli::drawScore(){   
    std::cout << player1->getName() << ": " << player1->getScore() << "\t" << player2->getName() << ": " << player1->getScore() << std::endl;
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
    
    std::cout << "Now Playing: "<< (actualPlayer? player1->getName():player2->getName()) << std::endl;
    consol.setCursor(0, size*2+4);
    
    drawScore();    
}


void gameCli::run(){
    
    
    while (true)
    {
        std::string command;
        draw();
      
        
        std::cin >> command;
        
        
        std::size_t found;
        
        if((found = command.find("quit"))!= std::string::npos){
            return;
        }
        else if((found = command.find("help"))!= std::string::npos){
            consol.clear();
            printHelp();    
            std::cin.get();
        }
        else{
            //make move to be filed later
            actualPlayer = !actualPlayer;
        }
        
    }
}

void gameCli::printHelp(){
    std::cout << "HRA2016 Help" <<std::endl
    << "To help write help" << std::endl
    << "To quit write quit" << std::endl
    << "to save game type save" << std::endl
    << "to load game type load" << std::endl
    << "To make move just write <column><row>" <<std::endl
    << "to continue to game press enter..." << std::endl;
    
    std::cin.get();
}


