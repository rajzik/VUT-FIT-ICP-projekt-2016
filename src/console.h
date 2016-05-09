/**
 * @file   console.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 * All about escape Sequnces
 */

#pragma once


#include <iostream>
#include <cstdlib>
#include <sstream>


/**
* @brief Colors enum for console, all about escape sequneces
*/
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


/**
* @brief Basic API for console
*/
class console
{
public:
    /**
    * @brief Constructor sets color array
    */
    console();
    /**
    * @brief Clears everything
    */
    ~console();
    /**
    * @brief Setter for foreground color
    * @param color
    */
    void setFgColor(int color);
    /**
    * @brief Setter for background color 
    * @param color
    */
    void setBgColor(int color);
    /**
    * @brief Help function for console color
    */
    void setConsoleColor();
    /**
    * @brief Set cursor on linux console visually
    * @param x 
    * @param y
    */
    void setCursor(int x, int y);
    /**
    * @brief Clear everything on console screen
    */
    void clear();
    /**
    * @brief Check fields in specified direction
    */
    void resetToDefault();

private: 
    /**
    * @brief Static colors numbers for console
    */
    int colorsNumber[9];
    /**
    * @brief global variable for foreground color
    */
    int fgColor;
    /**
    * @brief global variable for background color
    */
    int bgColor;
    
};

