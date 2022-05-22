/******************************************
File Name: art.c

Author: Francis Zaccharie B. de Leon
Last Update: May 21, 2022

This file contains most of the implmentation 
for printing the 2d array art in art.h 
******************************************/

#include "../configurations.h"
#include "../protoypes/util_proto.h"
#include <stdio.h>
#include <string.h>

/* This function prints the ART_Pokeball in art.h
    it prints it at the middle of the TUI           
    PARAMETERS:
    - sPokeballArt is the ART_Pokeball in art,h
    - *currRow is the address for the current row in box_imp.c 
        it would be incremented based on the number of row this art has*/
void displayPokeball(char sPokeBallArt[][WIDTH], int *currRow)
{
    int nPokeballHeight = 9;                                // how many rows the art has
    int nPokeballWidth = strlen(sPokeBallArt[0]);           // how long the art is

    int nCenterStart = (WIDTH / 2) - (nPokeballWidth / 2);  // WIDTH / 2 is the center of the TUI. shift it to the left
                                                            // by half of the width of the image. nCenterStart would be
                                                            // the x coordinate on where the image would start printing
    
    int artRow;                                             // used in loops to know which row of the art is being printed                                       


    if (*currRow + nPokeballHeight < HEIGHT)    // if there is still height space in the TUI
    {
        for (artRow = 0; artRow < nPokeballHeight; artRow++)    
        {
            printLeftStart();
            printSpace(nCenterStart);
            printf("%s", sPokeBallArt[artRow]);
            printRightRemain(nPokeballWidth + nCenterStart);
        }
        (*currRow) += nPokeballHeight;  // inrementing currRow so that after printing the art, the currRow in box_imp.c
                                        // would be updated to the right value.
    }
    else
        printf("not enough height!");

}
