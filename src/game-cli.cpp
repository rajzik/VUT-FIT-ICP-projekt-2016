/**
 * @file   console.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */

#include "game-cli.h"



bool fileSort (fileInfo i,fileInfo j) { return std::greater<std::time_t>()(i.time, j.time); }

gameCli::gameCli()
:game(){
    //initialize everything what needs to be
    consol.clear();
    printHelp();
    getGameInfo();
    message = "";
    Emessage = "";
}

gameCli::~gameCli(){
}

void gameCli::getGameInfo(){
    //getting info about game from user
    
    
    int single = -1;
    std::string a;
    clearHistory();
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
    if(single == 1){
        while(true){
            consol.clear();
            std::cout<< "select difficulty"<<std::endl;
            std::cout<<"1) Easy"<<std::endl
            <<"2) Super Uber Hard"<<std::endl
            <<"Please enter game type: ";

            std::getline(std::cin, a);
            single = std::stoi("0"+a);

            if(single == 1 || single == 2)
                break;
        }
		initPlayers(single);    
    }
	else {
		initPlayers(0);
	}
    
    int tempSize = -1;
    while(true){
        consol.clear();
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
//help function to draw score for 2 players
void gameCli::drawScore(){

	consol.setFgColor(CSYELLOW);
	consol.setBgColor(CSBLACK);
	std::cout << "O";
	consol.resetToDefault();

	std::cout << ": " << player1->getScore() << " \t";
    
	consol.setFgColor(CSBLACK);
	consol.setBgColor(CSWHITE);
	std::cout << "O";
	consol.resetToDefault();
    std::cout << ": " << player2->getScore() << " ";

    std::cout<<std::endl;
}
//just drawing to console
//only api made some magic with escape sequnces
void gameCli::draw(){

    consol.clear();
    if(!message.empty())
        std::cout<<message<<std::endl;
    if(!Emessage.empty()){
        consol.setFgColor(CSWHITE);
        consol.setBgColor(CSRED);
        std::cout<<Emessage<<std::endl;
        consol.resetToDefault();
    }
    consol.setFgColor(CSBLACK);
    consol.setBgColor(CSWHITE);


    std::cout << "  ";
    if(size>9)
        std::cout<<" ";
    for(int firstLine = 0; firstLine < size; firstLine++)
        std::cout << (char)(97 + firstLine) << " ";
    std::cout << std::endl;


    for (int y = 0; y < size; y++)
    {
        std::cout << (y+1) << " " << ((size>9 && y < 9)?" ":"");
        for (int x = 0; x < size; x++)
        {
            if(gameField[x][y] == EMPTY)
                std::cout << "_";
            else{
                consol.setFgColor(gameField[x][y] == BLACK? CSYELLOW: CSBLACK);
                consol.setBgColor(gameField[x][y] == BLACK? CSBLACK : CSWHITE);
                std::cout << ("O");
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

    std::cout << "Now Playing: ";
    consol.setFgColor(actualPlayer1? CSYELLOW : CSBLACK );
    consol.setBgColor(actualPlayer1? CSBLACK: CSWHITE );
    std::cout<< "O";
    consol.resetToDefault();
    consol.setCursor(0, size*2+6);
    drawScore();
}
//print end of game, who wins is printed on screen, when its draw says draw
void gameCli::printGameOver(){
    consol.clear();
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    int score1 = player1->getScore(), score2 = player2->getScore();
    if(score1 == score2)
        std::cout<<gStrings[Gdraw];
    else if(score1 > score2){
        consol.setFgColor(CSYELLOW);
        consol.setBgColor(CSBLACK);
        std::cout<<"O";
        consol.resetToDefault();
        std::cout<<gStrings[Gwin];
    }
    else{
        consol.setFgColor(CSBLACK);
        consol.setBgColor(CSWHITE);
        std::cout<<"O";
        consol.resetToDefault();
        std::cout<<gStrings[Gwin];
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Do you wanna play again? (YES/NO): ";
    std::string command;
    std::getline(std::cin, command);
    std::getline(std::cin, command);
    if(command.find("YES") != std::string::npos){
        getGameInfo();
    }
    else{
        exit(0);
    }
}
//printing saved game 
//in order from latest 
void gameCli::printSavedGame(){
    consol.clear();
    boost::filesystem::path dir(SAVEFOLDER);
    boost::filesystem::create_directory(dir);

    std::stringstream filename;

    std::vector<fileInfo> v;
//god bless boost 
    for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(dir), {}))
    {
        std::time_t t = boost::filesystem::last_write_time(entry);
        std::stringstream ss;
        ss << boost::filesystem::basename(entry);
        fileInfo fi;
        fi.time = t;
        fi.basename = ss.str();
        v.insert(v.begin(),fi);
    }
//own sort function by date nothing extra
    std::sort(v.begin(), v.end(), fileSort);

    int i=1;
    for (std::vector<fileInfo>::iterator it=v.begin(); it!=v.end(); ++it, i++){
        char buff[20];
        strftime(buff, 20, "%Y-%m-%d %H:%M", localtime(&(it->time)));
        std::cout<< i <<") "<< it->basename << " " << buff <<std::endl;
    }
    int selected = 0;
    std::string a;
    std::getline(std::cin, a);
    //getting info from user
    while(true){


        std::cout<<"Please enter number of file,"<<std::endl<<"to return write return or press enter to load last game: ";
        std::getline(std::cin, a);


        std::size_t found;
        if((found = a.find("return"))!= std::string::npos){
            return;
        }
        else{
            selected = std::stoi("0" + a);
            if(selected < 0 || selected > i)
                continue;
            if(selected != 0)
                selected--;

            if(loadGame(v[selected].basename + ".sav")){
                message = gStrings[Gload];
            }
            else
                Emessage = eStrings[Eload];
            return;
        }

    }

}


void gameCli::run(){

    while (true)
    {
        if(!actualPlayer1 && player2->computer)
        {
            computerMove();
            draw();
            continue;
        }

        int possible;
        switch(possible = impossibleMove()){
            case 1: //pass 
                actualPlayer1 = !actualPlayer1;
                message = "You were skipped";
            break;
            case 2: //game over 
                printGameOver();
            break;
        }

        if(possible > 0)
            continue;//check if possible was bigger then continue;



        std::string command;

        draw();
        message = "";
        Emessage = "";


        std::cin >> command;
//getting command from user

        std::size_t found;

        if((found = command.find("quit"))!= std::string::npos){
            return;
        }
        else if((found = command.find("back"))!= std::string::npos){
            if(!prevStep())
                Emessage = eStrings[Eback];
            continue;
        }
        else if((found = command.find("forward"))!= std::string::npos){
            if(!nextStep())            
                Emessage = eStrings[Enext];
            continue;
        }
        else if((found = command.find("help"))!= std::string::npos){
            consol.clear();
            printHelp();
            std::cin.get();
        }
        else if((found = command.find("load")) != std::string::npos){
            consol.clear();
            printSavedGame();
        }
        else if((found = command.find("new")) != std::string::npos){
            consol.clear();
            getGameInfo();
        }
        else if((found = command.find("save")) != std::string::npos){
            if(!saveGame())
                Emessage = eStrings[Esave];
            else
                message = gStrings[Gsave];
        }
        else{
            std::size_t i = -1;
            std::string rowNum = "";

            while (isdigit(command[++i]))
            {
                rowNum += command[i];
            }
            int row = std::stoi("0" + rowNum) -1;

            command.erase(0, i);
            int col = (int)(command[0] - 97);

            if(!makeMove(WRITE,col,row))
                Emessage = eStrings[Einvalid];

        }

    }
}
//print help 
void gameCli::printHelp(){
    std::cout << "HRA2016 Help" <<std::endl
    << "To help write help" << std::endl
    << "To quit write quit" << std::endl
    << "to save game type save" << std::endl
    << "to load game type load" << std::endl
    << "to new game type new" << std::endl
    << "To make move just write <row><column>" <<std::endl
    << "to continue to game press enter..." << std::endl;

    std::cin.get();
}


