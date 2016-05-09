/**
 * @file   enums.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
 */

#pragma once
#include <string>

/**
 * @brief Folder for game savess
 */
#define SAVEFOLDER "examples"

/**
 * @brief Move enumerate, contains owner and position
 */
typedef struct move{
    /**
    * @brief True when it's black player move
    */
    bool player;
    /**
    * @brief Move coordinate x
    */
    int x;
    /**
    * @brief Move coordinate y
    */
    int y;
} move;

/**
 * @brief Enumerate for game field colors
 */
enum field_color
{
    EMPTY,
    BLACK,
    WHITE
};

/**
 * @brief Enumerate for game field permissions
 */
enum write_perms
{
    READ,
    WRITE
};

/**
 * @brief Enumarate for indetfy second player
 */
enum opposite_player
{
    HUMAN,
    COMPUTEREASY,
    COMPUTERHARD
};

/**
 * @brief Application messages enumerate
 */
enum messagesGame
{
    Gwin, 
    Gdraw,
    Gload,
    Gsave,
    Gskip,
    Gplayer1,
    Gplayer2,
    Ghuman,
    GcomputerEasy,
    GcomputerHard
};


#ifndef GSTR
#define GSTR

/**
 * @brief Array of application messages
 */
std::string const gStrings[] = {
    " WIN!",
    "It's a draw!",
	"Load successful.",
	"Save successful.",
    " skipped.",
	"Player 1",
    "Player 2",
    "Human",
    "Computer - easy",
    "Computer - hard"
};

#endif

/**
 * @brief Application error messages enumerate
 */
enum EmessagesGame{
    Esave,
    Eload,
    Enext,
    Eback,
    Einvalid
};

#ifndef ESTR
#define ESTR
/**
 * @brief Array of aplication error messages
 */
std::string const eStrings[] = {
    "Save failed!",
    "Load failed!",
	"No forward moves!",
	"No back moves!",
	"Invalid move."
};
#endif


