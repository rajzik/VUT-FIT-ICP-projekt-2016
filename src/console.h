#pragma once


#include <iostream>
#include <cstdlib>

#define ISWINDOWS false
#ifdef WINDOWS
    #include <windows.h>
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
    void resetToDefault();

private: 
    int colorsNumber[5];
    int fgColor;
    int bgColor;
    
};

