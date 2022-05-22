/******************************************
File Name: art.c

Author: Francis Zaccharie B. de Leon
Last Update: May 21, 2022

This file contains most of the implmentation 
for printing the art in art.h
******************************************/

#include "../configurations.h"
#include "../protoypes/util_proto.h"
#include <stdio.h>
#include <string.h>


void displayPokeball(char sPokeBallArt[][WIDTH], int *currRow)
{
    int nPokeballHeight = 9;
    int nPokeballWidth = strlen(sPokeBallArt[0]);
    int nCenterStart = (WIDTH / 2) - (nPokeballWidth / 2);
    int artRow;

    if (*currRow + nPokeballHeight < HEIGHT)
    {
        for (artRow = 0; artRow < nPokeballHeight; artRow++)
        {
            printLeftStart();
            printSpace(nCenterStart);
            printf("%s", sPokeBallArt[artRow]);
            printRightRemain(nPokeballWidth + nCenterStart);
        }
        (*currRow) += nPokeballHeight;
    }
    else
        printf("not enough height!");

}
