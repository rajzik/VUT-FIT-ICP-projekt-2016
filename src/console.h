#pragma once


#include <iostream>
#include <cstdlib>

#define ISWINDOWS false
#ifdef WINDOWS
    #define ISWINDOWS true
#endif


enum consoleColor
{
    CSDEFAULT,
    CSBLACK,
    CSWHITE,
    CSRED,
    CSYELLOW  
};


class console
{
public:
    console();
    ~console();

    void setFgColor(int color);
    void setBgColor(int color);
    void setConsoleColor();
    void setCursor(int x, int y);
    void clear();
    
    char *colors;
private: 

    int fgColor;
    int bgColor;
    
};

