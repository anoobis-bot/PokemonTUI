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

void printCaughtMons(box_type IndexMonsDisplay[], int nIndexMonsDisplay_Size, int currPage, int *currRow)
{
    // dimensions of a cell
    const int cellWidth = 7;
    const int cellHeight = 5;
    // the space between the cells
    const int spaceBetween = 1;

    // the length if every width of the cell is added, plus the spaces between them.
    // the literal 2 is because of the corner characters. they are not included in the cellWidth
    const int boxRowWidthLen = (cellWidth * NUM_BOX_COLUMN) + (2 * NUM_BOX_COLUMN) + (spaceBetween * (NUM_BOX_COLUMN));
    // which position to start printing the grass tiles if they were to be printed at the middle
    const int centerStartPosPrint = (WIDTH / 2) - (boxRowWidthLen / 2);

    // row of the cell in which the sprite is to be printed (center of the cell)
    int rowPrintSprite = cellHeight / 2;
    if (cellHeight % 2 == 0)    // if the cell height is even, print sprite at a higher-middle position
        rowPrintSprite--;

    // column of center of the cell
    int columnCenter = cellWidth / 2;
    if (cellWidth % 2 == 0)     // if the cell width is even, print sprite at a left-middle position
        columnCenter--;

    // variables used in for loops
    int printRowCell;
    int printColumnCell;
    int currCellRow;
    int currCellColumn;

    // tracks to which index of the IndexMonDisplay will be used
    int currMonIndex;

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
    int currPad;


    for (currCellRow = 0; currCellRow < NUM_BOX_ROW; currCellRow++)
    {
        for (printRowCell = 0; printRowCell < cellHeight; printRowCell++)
        {
            // at the start of the row, print these
            printLeftStart();
            printSpace(centerStartPosPrint);

            // in cell, print the specifics of it in the current printRow
            for (currCellColumn = 0; currCellColumn < NUM_BOX_COLUMN; currCellColumn++)
            {
                currMonIndex = currCellColumn + (currCellRow * NUM_BOX_COLUMN) + 
                                (currPage * NUM_BOX_COLUMN * NUM_BOX_ROW);

                // if there are still fakemons to print
                if (currMonIndex < nIndexMonsDisplay_Size)
                {
                    // if printing the first row of the cell
                    if (printRowCell == 0)
                    {
                        // print the upper left corner
                        printf("%c", BOX_TILE_UP_LEFT);

                        for (printColumnCell = 0; printColumnCell < cellWidth; printColumnCell++)
                        {
                            // - 1 since there are 3 digits. it shifts the starting position of the printing
                            // of the digits 1 unit to the left
                            if (printColumnCell == (columnCenter - 1))
                            {
                                // print the formatted number
                                printFormatNum(IndexMonsDisplay[currMonIndex].nSlot + 1);
                                // += 2 since the formatted number, 000 takes 3 character spaces. + 1 will 
                                // be incremented at every iteration of for loop
                                printColumnCell += 2;
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
                    else if (printRowCell == rowPrintSprite)
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (printColumnCell = 0; printColumnCell < cellWidth; printColumnCell++)
                        {
                            // if at the column in which the name starts to be printed
                            if (printColumnCell == (columnCenter - (nNamePadding)))
                            {
                                // strcat will be used
                                sNameBuffer[0] = '\0'; // making sure the the buffer is clean

                                // print the short name of the fakemon
                                nNameSpaceRemain = SHORT_NAME_SIZE - 
                                                    strlen(IndexMonsDisplay[currMonIndex].sShort_Name);

                                // printing the necessary spaces
                                if (nNameSpaceRemain > 0)
                                {
                                    if (nNameSpaceRemain % 2 == 0)
                                    {
                                        for (currPad = 0; currPad < nNameSpaceRemain / 2; currPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                    else if (nNameSpaceRemain % 2 != 0)
                                    {
                                        for (currPad = 0; currPad < (nNameSpaceRemain - 1) / 2; currPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                }
                                
                                // putting the name to the buffer
                                strcat(sNameBuffer, IndexMonsDisplay[currMonIndex].sShort_Name);

                                // printing the necessary spaces
                                if (nNameSpaceRemain % 2 == 0)
                                    {
                                        for (currPad = 0; currPad < nNameSpaceRemain / 2; currPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                    else if (nNameSpaceRemain % 2 != 0)
                                    {
                                        for (currPad = 0; currPad < (nNameSpaceRemain / 2) + 1; currPad++)
                                            strcat(sNameBuffer, " ");
                                    }
                                
                                printf("%s", sNameBuffer);

                                // updating the cursor to which to printing head is
                                // - 1 since it will be incremeneted by the end
                                printColumnCell += (SHORT_NAME_SIZE - 1);
                            }
                            else
                                printf("%c", BOX_TILE_OCCUPY);
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }

                    // just print the tile occupy sprite in any other rows
                    else if (!(printRowCell == cellHeight - 1))
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (printColumnCell = 0; printColumnCell < cellWidth; printColumnCell++)
                        {
                            printf("%c", BOX_TILE_OCCUPY);
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }
                }
                
                // if there aren't anymore fakemons to print (just print empty in the cell)
                else if (currMonIndex >= nIndexMonsDisplay_Size)
                {
                    // if printing the first row of the cell
                    if (printRowCell == 0)
                    {
                        // print the upper left corner
                        printf("%c", BOX_TILE_UP_LEFT);

                        // print the horizontal bars all the way. no digits needed
                        for (printColumnCell = 0; printColumnCell < cellWidth; printColumnCell++)
                        {
                            printf("%c", BOX_TILE_H_LINE);
                        }

                        // and print the right border of the cell
                        printf("%c", BOX_TILE_UP_RIGHT);
                    }

                    // if printing at the row where the names are being printed
                    else if (printRowCell == rowPrintSprite)
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (printColumnCell = 0; printColumnCell < cellWidth; printColumnCell++)
                        {
                            // if at the column in which the name starts to be printed
                            if (printColumnCell == (columnCenter - (nNamePadding)))
                            {
                                printf("EMPTY");

                                // updating the cursor to which to printing head is
                                // - 1 since it will be incremeneted by the end
                                printColumnCell += (strlen("EMPTY") - 1);
                            }
                            else
                                printf(" ");
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }

                    // just print the tile occupy sprite in any other rows
                    else if (!(printRowCell == cellHeight - 1))
                    {
                        // print the left boarder
                        printf("%c", BOX_TILE_V_LINE);
                        for (printColumnCell = 0; printColumnCell < cellWidth; printColumnCell++)
                        {
                            printf(" ");
                        }
                        // and print the right border of the cell
                        printf("%c", BOX_TILE_V_LINE);
                    }
                }

                // if printing the lower border of the cell. since all of them, either empty or occupied
                // have the same bottom border
                if (printRowCell == cellHeight - 1)
                {
                    // print the border
                    printf("%c", BOX_TILE_DOWN_LEFT);
                    for (printColumnCell = 0; printColumnCell < cellWidth; printColumnCell++)
                    {
                        printf("%c", BOX_TILE_H_LINE);
                    }
                    printf("%c", BOX_TILE_DOWN_RIGHT);
                }

                // psace between columns of cells
                printSpace(spaceBetween);

            }
            printRightRemain(centerStartPosPrint + boxRowWidthLen);

            
        }
        // incrementes currRow to be updated in the box_imp
        (*currRow) += cellHeight;

        // prints the number of space between rows of cells
        printFillerLines(spaceBetween, currRow);
    }


}