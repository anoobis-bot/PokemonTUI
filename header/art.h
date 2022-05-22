/******************************************
File Name: art.h

Author: Francis Zaccharie B. de Leon
Last Update: May 19, 2022

This file contains the art that would
be printed in the console
Each line would be a row in a 2d array.
This is implemented this way so that 
the program could be flexible when 
printing art and text together in the
same line.
The prefix of a text art is HDR_ follwed
by the text.
******************************************/

#ifndef ART_H
#define ART_H

#include "../configurations.h"

char HDR_FakeDex[ART_TEXT_HEIGHT][WIDTH] = 
{
    {" ____   __    _     ____  ___   ____  _    "},
    {"| |_   / /\\  | |_/ | |_  | | \\ | |_  \\ \\_/ "},
    {"|_|   /_/--\\ |_| \\ |_|__ |_|_/ |_|__ /_/ \\ "},
};


char ART_Pokeball[9][WIDTH] = 
{
    {"+------------------------------+"},
    {"|                              |"},
    {"|                              |"},
    {"|            ------            |"},
    {"+------------|    |------------+"},
    {"|            ------            |"},
    {"|                              |"},
    {"|                              |"},
    {"+------------------------------+"},
};

#endif