/**
 * @file   console.cpp
 * @authors Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */

#pragma once


#include <iostream>
#include <cstdlib>
#include <sstream>

enum consoleColor
{
    CSDEFAULT,
    CSBLACK,
    CSWHITE,
    CSRED,
    CSYELLOW,
    CSGREEN,
    CSBLUE,
    CSMAGENTA,
    CSCYAN
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
    int colorsNumber[9];
    int fgColor;
    int bgColor;
    
};

