/******************************************
File Name: definitions.h

Author: Francis Zaccharie B. de Leon
Last Update: June 7, 2022

This file contains most of the definitons 
the program needs.
******************************************/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// include libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "array_sizes.h"
#include "../configurations.h"


// type definitions
/* there are 2 extra bytes (STR_MARGIN)
    the first one is for input length checking
    and the second one is for the null byte*/
typedef char stringSName[SHORT_NAME_SIZE + STR_MARGIN];
typedef char stringFName[FULL_NAME_SIZE + STR_MARGIN];
typedef char stringDesc[DESCRIPTION_SIZE + STR_MARGIN];
typedef char stringIn[STR_INPUT_STD + STR_MARGIN];
typedef char stringMsg[WIDTH];                  // message does not need the margin since it does not depend on user input
typedef char stringChoice[STR_CHOICES_SIZE];    // choices do not need the margin since they
                                                // are already predefined in a list (array)


// macro define
#define CLEAR "\e[1;1H\e[2J"    // this string is an escape character 
                                // that clears the screen and puts the cursor at position 1, 1

// struct definition
typedef struct 
{
    stringFName sFull_Name;
    stringSName sShort_Name;
    stringDesc sDescript;
    char cGender;
    short nCaught;
} mon_type;

typedef struct
{
    int nSlot;
    stringSName sShort_Name;
    stringFName sFull_Name;
    int index_Dex;
} box_type;

#endif