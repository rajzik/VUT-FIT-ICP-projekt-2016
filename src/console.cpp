#include "console.h"



console::console(){
    fgColor = CSWHITE;
    bgColor = CSDEFAULT;
    console::colors = new char[5];
    
    // if(ISWINDOWS)
    //    console::colors[] = {'0','0','7','4','6'};
    // else
    //     console::colors[] = {'0','0','7','1','3'};
}

console::~console(){}

void console::setBgColor(int color){
    bgColor = color;
}

void console::setFgColor(int color){
    fgColor = color;
}
void console::setConsoleColor(){
    if (ISWINDOWS)
    {
        // std::string toCharArr = "color "+ std::to_string(colors[bgColor]) + std::to_string(colors[fgColor]);
        std::string toCharArr = "color "+ std::to_string(0) + std::to_string(0);
        
        system(toCharArr.c_str());
    }
    else
    {
        // std::cout << "\e[3"+std::to_string(colors[fgColor])+";4"+std::to_string(colors[bgColor]);
        std::cout << "\e[3"+std::to_string(0)+";4"+std::to_string(0);
        
    }
    
    
}

void console::setCursor(int x, int y){
    std::string a;
    if (ISWINDOWS)
    {
        
    }
    else
    {
        a = "\e["+std::to_string(y)+";"+std::to_string(x)+"H";
        std::cout << a;
    }
}
void console::clear(){
    if (ISWINDOWS)
    {
           
    }
    else
    {
        std::cout << "\e[2J\ec";
    }
    setConsoleColor();
    
}