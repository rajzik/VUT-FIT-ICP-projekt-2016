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
    }
    else{
       colorsNumber[0] = 0;
       colorsNumber[1] = 0;
       colorsNumber[2] = 7;
       colorsNumber[3] = 1;
       colorsNumber[4] = 3;
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
        std::string toCharArr = "color "+ std::to_string(colorsNumber[bgColor]) + std::to_string(colorsNumber[fgColor]);
        // std::string toCharArr = "color "+ std::to_string(0) + std::to_string(0);
        
        system(toCharArr.c_str());
    }
    else
    {
        std::cout << "\033[3"+std::to_string(colorsNumber[fgColor])+";4"+std::to_string(colorsNumber[bgColor]) + "m";
        // std::cout << "\e[3"+std::to_string(0)+";4"+std::to_string(0);   
    }
    
    
}

void console::setCursor(int x, int y){
    y = y/2;
    std::string a;
    if (ISWINDOWS)
    {
        
    }
    else
    {
        a = "\033["+std::to_string(y)+";"+std::to_string(x)+"H";
        std::cout << a;
    }
}
void console::clear(){
    if (ISWINDOWS)
    {
        
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
        std::cout << "\033[0m ";
    }
}