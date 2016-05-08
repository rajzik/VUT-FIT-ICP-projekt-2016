/**
 * @file   enums.h
 * @author Jan Silhan (xsilha10@stud.fit.vutbr.cz), Pavel Pospisil (xpospi88@stud.fit.vutbr.cz)
 * @date   May 2016
 * @brief
 */

#pragma once
#include <string>


enum field_color
{
    EMPTY,
    BLACK,
    WHITE
};

enum write_perms
{
    READ,
    WRITE
};

enum opposite_player
{
    HUMAN,
    COMPUTEREASY,
    COMPUTERHARD
};

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
enum EmessagesGame{
    Esave,
    Eload,
    Enext,
    Eback,
    Einvalid
};


#ifndef ESTR
#define ESTR
std::string const eStrings[] = {
    "Save failed!",
    "Load failed!",
	"No forward moves!",
	"No back moves!",
	"Invalid move."
};
#endif

