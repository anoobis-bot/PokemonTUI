/******************************************
File Name: definitions.h

Author: Francis Zaccharie B. de Leon
Last Update: May 19, 2022

This file contains most of the definitons 
the program needs
******************************************/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// include libraries
#include <stdio.h>
#include <string.h>
#include "../configurations.h"


// type definitions
/* there are 2 extra bytes
    the first one is for input length checking
    and the second one is for the null byte*/
typedef char string5[5 + STR_MARGIN];
typedef char string11[11 + STR_MARGIN];
typedef char string300[300 + STR_MARGIN];
typedef char stringIO[STR_IO_SIZE + STR_MARGIN];


// macro define
#define CLEAR "\e[1;1H\e[2J"    // this string is an escape character 
                                // that clears the screen and puts the cursor at position 1, 1

// struct definition
typedef struct 
{
    string11 sFull_Name;
    string5 sShort_Name;
    string300 sDescript;
    char cGender;
    short nCaught;
} mon_type;


#endif