/******************************************
File Name: util.c

Author: Francis Zaccharie B. de Leon
Last Update: May 18, 2022

This file contains the common utility 
functions that the developer may use
******************************************/

// include files
#include "../configurations.h"
#include <stdio.h>

/* This function prints n number of spaces 
    int nNumSpace is how many spaces would
    be printed                              */
void printSpace(int nNumSpace)
{
    int i = 0;
    for(i = 0; i < nNumSpace; i++)
    {
        printf(" ");
    }
}

void printArt(char sArtChoice[][WIDTH])
{
    
}