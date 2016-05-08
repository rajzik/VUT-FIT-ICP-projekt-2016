/**
 * @file   console.cpp
 * @Author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */


#include "console.h"



console::console(){
    fgColor = CSWHITE;
    bgColor = CSDEFAULT;

    
    if(ISWINDOWS){
       colorsNumber[0] = 0;
       colorsNumber[1] = 0;
       colorsNumber[2] = 7;
       colorsNumber[3] = 4;
       colorsNumber[4] = 6;
       colorsNumber[5] = 2;
       colorsNumber[6] = 4;
       colorsNumber[7] = 5;
       colorsNumber[8] = 6;
    }
    else{
       colorsNumber[0] = 0;
       colorsNumber[1] = 0;
       colorsNumber[2] = 7;
       colorsNumber[3] = 1;
       colorsNumber[4] = 3;
       colorsNumber[5] = 2;
       colorsNumber[6] = 4;
       colorsNumber[7] = 5;
       colorsNumber[8] = 6;
    }
}

console::~console(){
    if (ISWINDOWS)
    {
        
    }
    else
    {
        std::cout<< "\033c";
    }
}

void console::setBgColor(int color){
    bgColor = color;
    setConsoleColor();
}

void console::setFgColor(int color){
    fgColor = color;
    setConsoleColor();
}
void console::setConsoleColor(){
    if (ISWINDOWS)
    {
		std::stringstream ss;
		ss << "color " << colorsNumber[bgColor] << colorsNumber[fgColor];	
        system(ss.str().c_str());
    }
    else
    {
        std::cout << "\033[3" << colorsNumber[fgColor] << ";4" << colorsNumber[bgColor] << "m";
    }
    
    
}

void console::setCursor(int x, int y){
    y = y/2;
    if (ISWINDOWS)
    {
        
    }
    else
    {
        std::cout << "\033[" << y << ";" <<x <<"H";
    }
}
void console::clear(){
	if (ISWINDOWS)
	{
		system("cls");
	}
    else
    {
        std::cout << "\033[2J\033c";
    }
}


void console::resetToDefault(){
    if (ISWINDOWS)
    {
        
    }
    else
    {
        std::cout << "\033[0m";
    }
}