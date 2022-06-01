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

/* This function resets any text modifications */
void colorReset()
{
    if (COLOR_ENABLE)
        printf("\x1b[0m");
}

/* This function sets the foreground color to Green */
void forgroundGreen()
{
    if (COLOR_ENABLE)
        printf("\x1b[38;5;40m");
}

/* This function sets the foreground color to Red */
void foregroundRed()
{
    if (COLOR_ENABLE)
        printf("\x1b[38;5;124m");
}

/* This function sets the foreground color to Brown */
void foregroundBrown()
{
    if (COLOR_ENABLE)
        printf("\x1b[38;5;94m");
}

/* This function prints the ART arrays in art.h
    it prints it at the middle of the TUI. 
    ASSUMPTION
    - The number of characters of each element is uniform           
    PARAMETERS:
    - sArt: the ART_<art name> in art.h
    - nArtHeight: How many elements does sArt have
    - *currRow: the address for the current row in box_imp.c 
        it would be incremented based on the number of row this art has*/
void displayArt(char sArt[][WIDTH], int nArtHeight,int *currRow)
{
    int nArtWidth = strlen(sArt[0]);           // how long the art is

    int nCenterStart = (WIDTH / 2) - (nArtWidth / 2);  // WIDTH / 2 is the center of the TUI. shift it to the left
                                                            // by half of the width of the image. nCenterStart would be
                                                            // the x coordinate on where the image would start printing
    
    int artRow;                                             // used in loops to know which row of the art is being printed                                       


    if (*currRow + nArtHeight < HEIGHT)    // if there is still height space in the TUI
    {
        for (artRow = 0; artRow < nArtHeight; artRow++)    
        {
            printLeftStart();
            printSpace(nCenterStart);
            printf("%s", sArt[artRow]);
            printRightRemain(nArtWidth + nCenterStart);
        }
        (*currRow) += nArtHeight;  // inrementing currRow so that after printing the art, the currRow in box_imp.c
                                        // would be updated to the right value.
    }
    else
        printf("not enough height!"); 
}

/* This function prints the grass tiles on the screen and the position of the player
    based on the ActiveCell        
    PARAMETERS:
    -  ActiveCell: What position the player is
    - *currRow: Put currRow here, it is incremented to update the number of rows already
        consumed    */
void printGrass(int ActiveCell, int *currRow)
{
    // dimensions of a cell
    const int cellWidth = 7;
    const int cellHeight = 5;
    // the space between the cells
    const int spaceBetween = 1;

    // the length if every width of the cell is added, plus the spaces between them.
    // the literal 2 is because of the corner characters. they are not included in the cellWidth
    const int boxRowWidthLen = (cellWidth * EXPLORE_COLUMN) + (2 * EXPLORE_COLUMN) + (spaceBetween * (EXPLORE_COLUMN));
    // which position to start printing the grass tiles if they were to be printed at the middle
    const int centerStartPosPrint = (WIDTH / 2) - (boxRowWidthLen / 2);

    // row of the cell in which the sprite is to be printed (center of the cell)
    int rowPrintSprite = cellHeight / 2;
    if (cellHeight % 2 == 0)    // if the cell height is even, print sprite at a higher-middle position
        rowPrintSprite--;

    // column of the cell in which the sprite is to be printed (center of the cell)
    int columnPrintSprite = cellWidth / 2;
    if (cellWidth % 2 == 0)     // if the cell width is even, print sprite at a left-middle position
        columnPrintSprite--;

    // variables used in for loops
    int printRow;
    int printColumn;
    int currCell;

    // iterates through every row
    for (printRow = 0 ; printRow < cellHeight; printRow++)
    {
        // at the start of the row, print these
        printLeftStart();
        printSpace(centerStartPosPrint);

        // in cell, print the specifics of it in the current printRow
        for (currCell = 0; currCell < EXPLORE_COLUMN; currCell++)
        {
            // if printing the first row of the cell
            if (printRow == 0)
            {
                // print the upper borders
                printf("%c", GRASS_UP_LEFT);
                for (printColumn = 0; printColumn < cellWidth; printColumn++)
                {
                    // if at the center of the cell, print the tile number
                    if (printColumn == columnPrintSprite)
                        printf("%d", currCell);
                    else
                        printf(H_LINE);
                }
                printf("%c", GRASS_UP_RIGHT);
            }
            // if printing the lower border of the cell
            else if (printRow == cellHeight - 1)
            {
                // print the border
                printf("%c", GRASS_DOWN_LEFT);
                for (printColumn = 0; printColumn < cellWidth; printColumn++)
                {
                    printf(H_LINE);
                }
                printf("%c", GRASS_DOWN_RIGHT);
            }
            // if printing the row in which the sprite is populated and if the current cell to be printed
            // is the ActiveCell
            else if ((printRow == rowPrintSprite) && (currCell == ActiveCell))
            {
                // print the left boarder
                printf("%c", D_V_LINE);
                // set the foreground to be green (green tiles)
                forgroundGreen();
                for (printColumn = 0; printColumn < cellWidth; printColumn++)
                {
                    // if at the column in which the sprite is to be printed
                    if (printColumn == columnPrintSprite)
                    {
                        // turn the foreground brown (brown sprite)
                        foregroundBrown();
                        printf("%c", TRAINER_SPRITE);
                        // turn it back to green
                        forgroundGreen();
                    }
                    else
                        printf("%c", GRASS_TILE);
                }
                // after printing the grass tiles, set the color back to original
                colorReset();
                // and print the right border of the cell
                printf("%c", D_V_LINE);
            }

            // if printing a regular row
            else 
            {
                // print the border and the grass tiles
                printf("%c", D_V_LINE);
                forgroundGreen();
                for (printColumn = 0; printColumn < cellWidth; printColumn++)
                {
                    printf("%c", GRASS_TILE);
                }
                colorReset();
                printf("%c", D_V_LINE);
            }
            
            // after printing the row of the specific cell, put the space between them.
            printSpace(spaceBetween);
        }
        
        // after printing the whole row of every cell, print the number of spaces required and close it off
        // with the vertical border
        printRightRemain(centerStartPosPrint + boxRowWidthLen);
    }

    // update the currRow
    (*currRow) += cellHeight;
}