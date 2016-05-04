#include "game-cli.h"




gameCli::gameCli()
:game(){
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
    
    
    int tempSize = -1;
    while(true){
        consol.clear();   
        std::cout<<tempSize<<std::endl;
        std::cout<< "Please enter valid size 6, 8, 10, 12. Or press enter or type 0 to set default size"<<std::endl;
        std::cout<<"Enter game field size: ";
        std::getline(std::cin, a);
        tempSize = std::stoi("0"+a);
        
        if((tempSize % 2) == 0 && tempSize > 5 && tempSize < 13 )
            break;
        if(tempSize == 0)
        {
            tempSize = 8;        
            break;
        }
        
    }
    
    size = tempSize;
    initGameField();
    
}

void gameCli::drawScore(){   
    
    std::cout << player1->getName() << ": " << player1->getScore() << " ";
    consol.setFgColor(CSBLACK);
    consol.setBgColor(CSWHITE);
    std::cout<<"O";        
    
    consol.resetToDefault();
    std::cout << "\t" << player2->getName() << ": " << player1->getScore() << " ";
    consol.setFgColor(CSYELLOW);
    consol.setBgColor(CSBLACK);
    std::cout<<"X";
    
    consol.resetToDefault();
    std::cout<<std::endl;
}

void gameCli::draw(){
    
    consol.clear();
    consol.setFgColor(CSBLACK);
    consol.setBgColor(CSWHITE);

    
    std::cout << "  ";
    if(size>9)
        std::cout<<" ";
    for(int firstLine = 0; firstLine < size; firstLine++)
        std::cout << (char)(97 + firstLine) << " ";
    std::cout << std::endl;
    
    
    for (int x = 0; x < size; x++)
    {
        std::cout << (x+1) << " " << ((size>9 && x < 9)?" ":"");
        for (int y = 0; y < size; y++)
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


