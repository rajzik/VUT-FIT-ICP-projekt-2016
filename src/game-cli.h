/**
 * @file   console.cpp
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   may 2016
 * @brief  work with console in both systems
 *
 * sometimes i believe compiler ignores all my comments, but doxygen don't
 */

#pragma once

#include "game.h"
#include "console.h"



/**
 * @brief definition of files with just time and basename
 */
typedef struct fileLoad{

/**
* @brief time var
*/
    std::time_t time;
    
/**
* @brief time var
*/
    std::string basename;
} fileInfo;


/**
 * @brief Child of game with extension for command line input
 */
class gameCli : public game
{
private: 
    /**
    * @brief own basic API for linux CLI
    */
    console consol;    
    /**
    * @brief informational message showed on top of gamefield
    */
    std::string message;
/**
* @brief error message showed on top of gamefield
*/
    std::string Emessage;
/**
* @brief Print saved game on screen
*/
    void printSavedGame();
/**
* @brief print game over and select new game or end
*/
    void printGameOver();
    
public:
        /**
         * @brief constructor
         */
    gameCli();
            /**
         * @brief destructor
         */
    ~gameCli();
    /**
    * @brief gets game info and set it from user
    */
    void getGameInfo();
    /**
    * @brief prints help
    */
    void printHelp();
    /**
    * @brief draw made for command line
    */
    void draw();
    /**
    * @brief draw score for both players
    */
    void drawScore();
    /**
    * @brief infinite loop for runing game
    */
    void run();
};
