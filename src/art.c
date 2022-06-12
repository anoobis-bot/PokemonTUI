/******************************************
File Name: art.c

Author: Francis Zaccharie B. de Leon
Last Update: May 21, 2022

This file contains most of the implmentation 
for printing the 2d array art in art.h 
******************************************/

#include "../configurations.h"
#include "../protoypes/util_proto.h"
#include "../header/definitions.h"
#include <stdio.h>
#include <string.h>

/* This function resets any text modifications 
*/
void 
colorReset()
{
    if (COLOR_ENABLE)
        printf("\x1b[0m");
}


/* This function sets the foreground color to Green 
*/
void 
forgroundGreen()
{
    if (COLOR_ENABLE)
        printf("\x1b[38;5;40m");
}


/* This function sets the foreground color to Red 
*/
void 
foregroundRed()
{
    if (COLOR_ENABLE)
        printf("\x1b[38;5;124m");
}


/* This function sets the foreground color to Brown 
*/
void 
foregroundBrown()
{
    if (COLOR_ENABLE)
        printf("\x1b[38;5;94m");
}


/* This function prints the ART arrays in art.h it prints it at the middle of the TUI.          
    @param sArt: the ART_<art name> in art.h
    @param nArtHeight: How many elements does sArt have
    @param *nCurrRow: the address for the current row in box_imp.c it would be incremented based on the 
                    number of row this art has.
    PRE-CONDITION:The number of characters of each element in the 2d array is uniform  
*/
void 
displayArt(char sArt[][WIDTH], int nArtHeight,int *nCurrRow)
{
    int nArtWidth = strlen(sArt[0]);           // how long the art is

    int nCenterStart = (WIDTH / 2) - (nArtWidth / 2);  // WIDTH / 2 is the center of the TUI. shift it to the left
                                                            // by half of the width of the image. nCenterStart would be
                                                            // the x coordinate on where the image would start printing
    
    int nArtRow;                                             // used in loops to know which row of the art is being printed                                       


    if (*nCurrRow + nArtHeight < HEIGHT)    // if there is still height space in the TUI
    {
        for (nArtRow = 0; nArtRow < nArtHeight; nArtRow++)    
        {
            printLeftStart();
            printSpace(nCenterStart);
            printf("%s", sArt[nArtRow]);
            printRightRemain(nArtWidth + nCenterStart);
        }
        (*nCurrRow) += nArtHeight;  // inrementing nCurrRow so that after printing the art, the nCurrRow in box_imp.c
                                        // would be updated to the right value.
    }
    else
        printf("not enough height!"); 
}


/* This function prints the grass tiles on the screen and the position of the player
    based on the ActiveCell        
    @param nActiveCell: What position the player is
    @param *nCurrRow: Put nCurrRow here, it is incremented to update the number of rows already consumed    
*/
void 
printGrass(int nActiveCell, int *nCurrRow)
{
    // dimensions of a cell
    const int nCellWidth = 7;
    const int nCellHeight = 5;
    // the space between the cells
    const int nSpaceBetween = 1;

    // the length if every width of the cell is added, plus the spaces between them.
    // the literal 2 is because of the corner characters. they are not included in the nCellWidth
    const int nBoxRowWidthLen = (nCellWidth * EXPLORE_COLUMN) + (2 * EXPLORE_COLUMN) + (nSpaceBetween * (EXPLORE_COLUMN));
    // which position to start printing the grass tiles if they were to be printed at the middle
    const int nCenterStartPosPrint = (WIDTH / 2) - (nBoxRowWidthLen / 2);

    // row of the cell in which the sprite is to be printed (center of the cell)
    int nRowPrintSprite = nCellHeight / 2;
    if (nCellHeight % 2 == 0)    // if the cell height is even, print sprite at a higher-middle position
        nRowPrintSprite--;

    // column of the cell in which the sprite is to be printed (center of the cell)
    int nColumnPrintSprite = nCellWidth / 2;
    if (nCellWidth % 2 == 0)     // if the cell width is even, print sprite at a left-middle position
        nColumnPrintSprite--;

    // variables used in for loops
    int nPrintRow;
    int nPrintColumn;
    int nCurrCell;

    // iterates through every row
    for (nPrintRow = 0 ; nPrintRow < nCellHeight; nPrintRow++)
    {
        // at the start of the row, print these
        printLeftStart();
        printSpace(nCenterStartPosPrint);

        // in cell, print the specifics of it in the current nPrintRow
        for (nCurrCell = 0; nCurrCell < EXPLORE_COLUMN; nCurrCell++)
        {
            // if printing the first row of the cell
            if (nPrintRow == 0)
            {
                // print the upper borders
                printf("%c", GRASS_UP_LEFT);
                for (nPrintColumn = 0; nPrintColumn < nCellWidth; nPrintColumn++)
                {
                    // if at the center of the cell, print the tile number
                    if (nPrintColumn == nColumnPrintSprite)
                        printf("%d", nCurrCell);
                    else
                        printf(H_LINE);
                }
                printf("%c", GRASS_UP_RIGHT);
            }
            // if printing the lower border of the cell
            else if (nPrintRow == nCellHeight - 1)
            {
                // print the border
                printf("%c", GRASS_DOWN_LEFT);
                for (nPrintColumn = 0; nPrintColumn < nCellWidth; nPrintColumn++)
                {
                    printf(H_LINE);
                }
                printf("%c", GRASS_DOWN_RIGHT);
            }
            // if printing the row in which the sprite is populated and if the current cell to be printed
            // is the ActiveCell
            else if ((nPrintRow == nRowPrintSprite) && (nCurrCell == nActiveCell))
            {
                // print the left boarder
                printf("%c", D_V_LINE);
                // set the foreground to be green (green tiles)
                forgroundGreen();
                for (nPrintColumn = 0; nPrintColumn < nCellWidth; nPrintColumn++)
                {
                    // if at the column in which the sprite is to be printed
                    if (nPrintColumn == nColumnPrintSprite)
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
                for (nPrintColumn = 0; nPrintColumn < nCellWidth; nPrintColumn++)
                {
                    printf("%c", GRASS_TILE);
                }
                colorReset();
                printf("%c", D_V_LINE);
            }
            
            // after printing the row of the specific cell, put the space between them.
            printSpace(nSpaceBetween);
        }
        
        // after printing the whole row of every cell, print the number of spaces required and close it off
        // with the vertical border
        printRightRemain(nCenterStartPosPrint + nBoxRowWidthLen);
    }

    // update the nCurrRow
    (*nCurrRow) += nCellHeight;
}


/* This function prints the fakemon in the box in the current page
    based on the ActiveCell        
    @param pIndexMonsDisplay[]: the box_type array that would be printed on the screen
    @param nIndexMonsDisplay_Size: how many elements in pIndexMonsDisplay
    @param nCurrPage: put the nCurrPage variable here as it would only print the fakemon in the current page
    @param *nCurrRow: Put nCurrRow here, it is incremented to update the number of rows already consumed    
*/
void 
printCaughtMons(box_type pIndexMonsDisplay[], int nIndexMonsDisplay_Size, int nCurrPage, int *nCurrRow)
{
    // dimensions of a cell
    const int nCellWidth = 7;
    const int cellHeight = 5;
    // the space between the cells
    const int nSpaceBetween = 1;

    // the length if every width of the cell is added, plus the spaces between them.
    // the literal 2 is because of the corner characters. they are not included in the nCellWidth
    const int nBoxRowWidthLen = (nCellWidth * NUM_BOX_COLUMN) + (2 * NUM_BOX_COLUMN) + (nSpaceBetween * (NUM_BOX_COLUMN));
    // which position to start printing the grass tiles if they were to be printed at the middle
    const int nCenterStartPosPrint = (WIDTH / 2) - (nBoxRowWidthLen / 2);

    // row of the cell in which the sprite is to be printed (center of the cell)
    int nRowPrintSprite = cellHeight / 2;
    if (cellHeight % 2 == 0)    // if the cell height is even, print sprite at a higher-middle position
        nRowPrintSprite--;

    // column of center of the cell
    int nColumnCenter = nCellWidth / 2;
    if (nCellWidth % 2 == 0)     // if the cell width is even, print sprite at a left-middle position
        nColumnCenter--;

    // variables used in for loops
    int nPrintRowCell;
    int nPrintColumnCell;
    int nCurrCellRow;
    int nCurrCellColumn;

    // tracks to which index of the IndexMonDisplay will be used
    int nCurrMonIndex;

    // padding needed for the name
    int nNamePadding = SHORT_NAME_SIZE / 2;
    if (SHORT_NAME_SIZE % 2 == 0)   // to make it center only make the paddings odd number
        nNamePadding--;

    // buffer used for printing the fakemon names
    // plus 1 is for the NULL Byte
    char sNameBuffer[SHORT_NAME_SIZE + 1] = "";

    // variable used to determine the number of spaces to be printed while displaying the short name
    int nNameSpaceRemain;

    // used in for loops
    int nCurrPad;


    for (nCurrCellRow = 0; nCurrCellRow < NUM_BOX_ROW; nCurrCellRow++)
    {
        for (nPrintRowCell = 0; nPrintRowCell < cellHeight; nPrintRowCell++)
        {
            // at the start of the row, print these
            printLeftStart();
            printSpace(nCenterStartPosPrint);

            // in cell, print the specifics of it in the current nPrintRow
            for (nCurrCellColumn = 0; nCurrCellColumn < NUM_BOX_COLUMN; nCurrCellColumn++)
            {
                nCurrMonIndex = nCurrCellColumn + (nCurrCellRow * NUM_BOX_COLUMN) + 
                                (nCurrPage * NUM_BOX_COLUMN * NUM_BOX_ROW);

                // if there are still fakemons to print
                if (nCurrMonIndex < nIndexMonsDisplay_Size)
                {
                    // if printing the first row of the cell
                    if (nPrintRowCell == 0)
                    {
                        // print the upper left corner
                        printf("%c", BOX_TILE_UP_LEFT);

                        for (nPrintColumnCell = 0; nPrintColumnCell < nCellWidth; nPrintColumnCell++)
                        {
                            // - 1 since there are 3 digits. it shifts the starting position of the printing
                            // of the digits 1 unit to the left
                            if (nPrintColumnCell == (nColumnCenter - 1))
                            {
                                // print the formatted number
                                printFormatNum(pIndexMonsDisplay[nCurrMonIndex].nSlot + 1);
                                // += 2 since the formatted number, 000 takes 3 character spaces. + 1 will 
                                // be incremented at every iteration of for loop
                                nPrintColumnCell += 2;
                            }
                            else 
                            {
                                printf("%c", BOX_TILE_H_LINE);
                            }
                        }
                        // print the upper right corner
                        printf("%c", BOX_TILE_UP_RIGHT);

                    }

                    // if printing at the row where the names are being printed
                    else if (nPrintRowCell == nRowPrintSprite)
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (nPrintColumnCell = 0; nPrintColumnCell < nCellWidth; nPrintColumnCell++)
                        {
                            // if at the column in which the name starts to be printed
                            if (nPrintColumnCell == (nColumnCenter - (nNamePadding)))
                            {
                                // strcat will be used
                                sNameBuffer[0] = '\0'; // making sure the the buffer is clean

                                // print the short name of the fakemon
                                nNameSpaceRemain = SHORT_NAME_SIZE - 
                                                    strlen(pIndexMonsDisplay[nCurrMonIndex].sShort_Name);

                                // printing the necessary spaces
                                if (nNameSpaceRemain > 0)
                                {
                                    if (nNameSpaceRemain % 2 == 0)
                                    {
                                        for (nCurrPad = 0; nCurrPad < nNameSpaceRemain / 2; nCurrPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                    else if (nNameSpaceRemain % 2 != 0)
                                    {
                                        for (nCurrPad = 0; nCurrPad < (nNameSpaceRemain - 1) / 2; nCurrPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                }
                                
                                // putting the name to the buffer
                                strcat(sNameBuffer, pIndexMonsDisplay[nCurrMonIndex].sShort_Name);

                                // printing the necessary spaces
                                if (nNameSpaceRemain % 2 == 0)
                                    {
                                        for (nCurrPad = 0; nCurrPad < nNameSpaceRemain / 2; nCurrPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                    else if (nNameSpaceRemain % 2 != 0)
                                    {
                                        for (nCurrPad = 0; nCurrPad < (nNameSpaceRemain / 2) + 1; nCurrPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                
                                printf("%s", sNameBuffer);

                                // updating the cursor to which to printing head is
                                // - 1 since it will be incremeneted by the end
                                nPrintColumnCell += (SHORT_NAME_SIZE - 1);
                            }
                            else
                                printf("%c", BOX_TILE_OCCUPY);
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }

                    // just print the tile occupy sprite in any other rows
                    else if (!(nPrintRowCell == cellHeight - 1))
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (nPrintColumnCell = 0; nPrintColumnCell < nCellWidth; nPrintColumnCell++)
                        {
                            printf("%c", BOX_TILE_OCCUPY);
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }
                }
                
                // if there aren't anymore fakemons to print (just print empty in the cell)
                else if (nCurrMonIndex >= nIndexMonsDisplay_Size)
                {
                    // if printing the first row of the cell
                    if (nPrintRowCell == 0)
                    {
                        // print the upper left corner
                        printf("%c", BOX_TILE_UP_LEFT);

                        // print the horizontal bars all the way. no digits needed
                        for (nPrintColumnCell = 0; nPrintColumnCell < nCellWidth; nPrintColumnCell++)
                        {
                            printf("%c", BOX_TILE_H_LINE);
                        }

                        // and print the right border of the cell
                        printf("%c", BOX_TILE_UP_RIGHT);
                    }

                    // if printing at the row where the names are being printed
                    else if (nPrintRowCell == nRowPrintSprite)
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (nPrintColumnCell = 0; nPrintColumnCell < nCellWidth; nPrintColumnCell++)
                        {
                            // if at the column in which the name starts to be printed
                            if (nPrintColumnCell == (nColumnCenter - (nNamePadding)))
                            {
                                printf("EMPTY");

                                // updating the cursor to which to printing head is
                                // - 1 since it will be incremeneted by the end
                                nPrintColumnCell += (strlen("EMPTY") - 1);
                            }
                            else
                                printf(" ");
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }

                    // just print the tile occupy sprite in any other rows
                    else if (!(nPrintRowCell == cellHeight - 1))
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (nPrintColumnCell = 0; nPrintColumnCell < nCellWidth; nPrintColumnCell++)
                        {
                            printf(" ");
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }
                }

                // if printing the lower border of the cell. since all of them, either empty or occupied
                // have the same bottom border
                if (nPrintRowCell == cellHeight - 1)
                {
                    // print the border
                    printf("%c", BOX_TILE_DOWN_LEFT);
                    for (nPrintColumnCell = 0; nPrintColumnCell < nCellWidth; nPrintColumnCell++)
                    {
                        printf("%c", BOX_TILE_H_LINE);
                    }
                    printf("%c", BOX_TILE_DOWN_RIGHT);
                }

                // psace between columns of cells
                printSpace(nSpaceBetween);

            }
            printRightRemain(nCenterStartPosPrint + nBoxRowWidthLen);

            
        }
        // incrementes nCurrRow to be updated in the box_imp
        (*nCurrRow) += cellHeight;

        // prints the number of space between rows of cells
        printFillerLines(nSpaceBetween, nCurrRow);
    }


}