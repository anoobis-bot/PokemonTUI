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
#include <string.h>

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

void printLeftStart()
{
    printSpace(LEFT_MARGIN);
    printf(H_LINE);
    printSpace(LEFT_PAD);
}

void printRightRemain(int nContentLen)
{
    int nSpaceRemain = WIDTH - LEFT_PAD - nContentLen;
    printSpace(nSpaceRemain);
    printf(H_LINE);
    printf("\n");
}

void printHeader(char sArtText[][WIDTH])
{
    int currCol;
    int rowArt;
    int nArtLen;

    printSpace(LEFT_MARGIN);

    printf("%c", UP_RIGHT_CORNER);
    for (currCol = 0; currCol < WIDTH; currCol++)
    {
        printf("-");
    }
    printf("%c", UP_LEFT_CORNER); 

    printf("\n");
    
    nArtLen = strlen(sArtText[0]);
    for (rowArt = 0; rowArt < ART_TEXT_HEIGHT; rowArt++)
    {
        printLeftStart();
        printf("%s", sArtText[rowArt]);
        printRightRemain(nArtLen);
    }

    printSpace(LEFT_MARGIN);
    printf("%c", DOWN_LEFT_CORNER); 
    for (currCol = 0; currCol < WIDTH; currCol++)
    {
        printf("-");
    }
    printf("%c", DOWN_RIGHT_CORNER); 
}