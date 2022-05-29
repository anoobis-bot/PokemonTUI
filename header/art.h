/******************************************
File Name: art.h

Author: Francis Zaccharie B. de Leon
Last Update: May 28, 2022

This file contains the declaration of 2d 
array variables for the art that would
be printed in the console
Each line would be a row in a 2d array.
This is implemented this way so that 
the program could be flexible when 
printing art and text together in the
same line.
The prefix of a text art is HDR_ follwed
by the text.
The prefix of an image are is ART_ followed
by the image
******************************************/

#ifndef ART_H
#define ART_H

#include "../configurations.h"  // added this so that the WIDTH macro could be imported
                                // this serves as a limiter so that the compiler would warn the developer if the image
                                // is too big for the width of the TUI.
#include "../header/array_sizes.h"  // ART_TEXT_HEIGHT

char HDR_FakeDex[ART_TEXT_HEIGHT][WIDTH] = 
{
    {" ____   __    _     ____  ___   ____  _    "},
    {"| |_   / /\\  | |_/ | |_  | | \\ | |_  \\ \\_/ "},
    {"|_|   /_/--\\ |_| \\ |_|__ |_|_/ |_|__ /_/ \\ "},
};

char HDR_Database[ART_TEXT_HEIGHT][WIDTH] =
{
    {" ___    __   _____   __    ___    __    __   ____"}, 
    {"| | \\  / /\\   | |   / /\\  | |_)  / /\\  ( (` | |_ "}, 
    {"|_|_/ /_/--\\  |_|  /_/--\\ |_|_) /_/--\\ _)_) |_|__"}, 
};

char HDR_Add_Dex[ART_TEXT_HEIGHT][WIDTH] = 
{
    {"  __    ___   ___       ___   ____  _   "}, 
    {" / /\\  | | \\ | | \\     | | \\ | |_  \\ \\_/"}, 
    {"/_/--\\ |_|_/ |_|_/     |_|_/ |_|__ /_/ \\"}, 
};

char HDR_View_Dex[ART_TEXT_HEIGHT][WIDTH] = 
{
    {" _      _   ____  _           ___   ____  _    "},
    {"\\ \\  / | | | |_  \\ \\    /    | | \\ | |_  \\ \\_/ "},
    {" \\_\\/  |_| |_|__  \\_\\/\\/     |_|_/ |_|__ /_/ \\ "},
};

char HDR_View_Fakemon[ART_TEXT_HEIGHT][WIDTH] = 
{
    {" _      _   ____  _           ____   __    _     ____  _      ___   _    "}, 
    {"\\ \\  / | | | |_  \\ \\    /    | |_   / /\\  | |_/ | |_  | |\\/| / / \\ | |\\ |"}, 
    {" \\_\\/  |_| |_|__  \\_\\/\\/     |_|   /_/--\\ |_| \\ |_|__ |_|  | \\_\\_/ |_| \\|"},  
};



char ART_Pokeball[9][WIDTH] = 
{
    {"+----------------------------+"},
    {"|                            |"},
    {"|                            |"},
    {"|           ------           |"},
    {"+-----------|    |-----------+"},
    {"|           ------           |"},
    {"|                            |"},
    {"|                            |"},
    {"+----------------------------+"},
};

#endif