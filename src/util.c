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

/* This function acts as a prep for the main contents 
    in the box. It prints spaces based on LEFT_MARGIN
    and LEFT_PAD. It also puts the Horizontal Boarder
    after this function.                                */
void printLeftStart()
{
    printSpace(LEFT_MARGIN);
    printf(V_LINE);
    printSpace(LEFT_PAD);
}

/* This function prints the remaining spaces so that
    the box would be completed in a singe line.
    It accepts the input nContentLen
        - this input is the length (width) of a content
            in a single line
    With this information, this function would know how
    many spaces to print. It also closes it off with the
    horizontal line bar                                 */
void printRightRemain(int nContentLen)
{
    int nSpaceRemain = WIDTH - LEFT_PAD - nContentLen;
    printSpace(nSpaceRemain);
    printf(V_LINE);
    printf("\n");
}

void printBottomRemain(int currRow)
{
    while (currRow < HEIGHT)
    {
            printLeftStart();
            printRightRemain(0);
            currRow++;
    }
}

void printFillerLines(int nQuantity, int *currRow)
{
    int i;
    for (i = 0; i < nQuantity; i++)
    {
        printLeftStart(); 
        printRightRemain(0); 
        (*currRow)++;
    }
}

/* This function prints the top bar of the TUI. It accepts
    the text art (in art.h) as it would be printed as the 
    title of the current page of the TUI.                   */
void printHeader(char sArtText[][WIDTH])
{
    int currCol;
    int rowArt;
    int nArtLen = strlen(sArtText[0]);  // assigns the width of the art to nArtLen

    printSpace(LEFT_MARGIN);
    
    // prints the topmost horizontal bar
    printf("%c", UP_LEFT_CORNER);
    for (currCol = 0; currCol < WIDTH; currCol++)
    {
        printf(H_LINE);
    }
    printf("%c", UP_RIGHT_CORNER); 

    printf("\n");
    
    // prints the art: HDR_<text name> (refer to art.h)
    for (rowArt = 0; rowArt < ART_TEXT_HEIGHT; rowArt++)
    {
        printLeftStart();
        printf("%s", sArtText[rowArt]);
        printRightRemain(nArtLen);
    }

    // prints the middle bar
    printSpace(LEFT_MARGIN);
    printf("%c", MID_LEFT_CORNER); 
    for (currCol = 0; currCol < WIDTH; currCol++)
    {
        printf(H_LINE);
    }
    printf("%c", MID_RIGHT_CORNER); 
    
    
    printf("\n");
}

/* This function prints out the bottom part of the
    TUI. It contains whatever message the system
    has for the user e.g. invalid or succesful input    */
void printRemark(char *sMessage)
{
    int currCol;
    int nMsgLen = strlen(sMessage);

    // prints the top part of the lower TUI
    printSpace(LEFT_MARGIN);
    printf("%c", MID_LEFT_CORNER);
    for (currCol = 0; currCol < WIDTH; currCol++)
    {
        printf(H_LINE);
    }
    printf("%c", MID_RIGHT_CORNER); 
    printf("\n");

    // prints the message to the TUI
    printLeftStart();
    printf("%s", sMessage);
    printRightRemain(nMsgLen);

    // prints the bottom most part of the TUI
    printSpace(LEFT_MARGIN);
    printf("%c", DOWN_LEFT_CORNER);
    for (currCol = 0; currCol < WIDTH; currCol++)
    {
        printf(H_LINE);
    }
    printf("%c", DOWN_RIGHT_CORNER); 
    printf("\n");

}

/* This function handles the input of the user.
    the macro STR_MSG_SIZE is the size of the array sMessage
    I put it that way so the parameters would be fewer
        this function accepts the sInput pointer and alters it based on user input
    error codes:
        0 - succeful input
        1 - the input is too long than the specified input*/
int getInput(char *sInput, int nInputSize, char *sErrorFeedBack)
{
    int nErrorMsg = 0;

    char buffer;        // used for flushing the stdin file stream

    printSpace(LEFT_MARGIN + LEFT_PAD + 1);
    printf("[INPUT]: ");
    fgets(sInput, nInputSize, stdin);       // used fgets to limit the characters. it only get upto nInputSize - 1 char in stdin
    sInput[strcspn(sInput, "\n")] = 0;      // replaces the \n with null character. if the buffer doesn't have it (has more than nInputSize - 1),
                                            // it replaces the last element in the array (margin) with null

    if (strlen(sInput) == nInputSize - 1)   // if the characters are too many for the array size
    {
        snprintf(sErrorFeedBack, STR_MSG_SIZE, "Invalid input! You may only enter a maximum of %d characters", 
                    nInputSize - STR_MARGIN);
        while ( (buffer = getchar()) != '\n' && buffer != EOF );    // flushes stdin filestream 

        nErrorMsg = 1;
    }


    return nErrorMsg;
}

void printChoices(char sChoices[][STR_CHOICES_SIZE], int numElem, int column, int row, char format, int *boxHeight)
{
    int currRow;
    int currCol;
    int printedElem = 0;
    
    int maxLenCol[10] = {};
    int currElem = 0;
    
    int lenCurWord = 0;

    int nNumSpacesBetween = 3;
    int nCursorLen = 2;

    int rowWidth;
    
    // counting the highest length in each column
    for (currRow = 0; currRow < row; currRow++)
    {
        for (currCol = 0; currCol < column && 
            currElem < numElem; currCol++)
            {
                lenCurWord = strlen(sChoices[currElem]);
                if (maxLenCol[currCol] < lenCurWord)
                    maxLenCol[currCol] = lenCurWord;
                currElem++;
            }
    }

    int i;
    int words_row_width = 0;
    for (i = 0; i < 10; i++)
    {
        words_row_width += maxLenCol[i];
    }
    int half_start = (WIDTH / 2) - ((words_row_width + (nCursorLen * column) + ((column - 1) * nNumSpacesBetween)) / 2);
    if (half_start % 2 == 1)
        half_start--;


	if (format != 'c' && format != 'j')
        printf("Tabulation not specified");
    
    for (currRow = 0; currRow < row; currRow++)
    {
        rowWidth = 0;
        if (format == 'c')
        {
    	    printLeftStart();
            printSpace(half_start);
            rowWidth += half_start;
        }
        else if (format == 'j')		                                    
            printLeftStart();

        for (currCol = 0; currCol < column && printedElem < numElem; currCol++)
            {
                printf("> ");
                rowWidth += nCursorLen;

                printf("%s", sChoices[printedElem]);
                lenCurWord = strlen(sChoices[printedElem]);
                rowWidth += lenCurWord;
                
                if (currCol + 1 < column)
                {
                	if (lenCurWord < maxLenCol[currCol])
                	{
                		printSpace(maxLenCol[currCol] - lenCurWord);
                        rowWidth += maxLenCol[currCol] - lenCurWord;
					}
                    printSpace(nNumSpacesBetween);
                    rowWidth += nNumSpacesBetween;
                }
                
                printedElem++;
                
            }
        if (format == 'c')
        {
    	    printRightRemain(rowWidth);
        }
        else if (format == 'j')		                                    
            printRightRemain(rowWidth);
    }

    (*boxHeight) += row;
    
}

void printText(char *sTempText, int *currRow)
{
    char sText[500];
    char *sTemp;

    int nRowPrintedElem = 0;
    int nWordLen;

    strcpy(sText, sTempText);

    printLeftStart();
    sTemp = strtok(sText, " ");
    nWordLen = strlen(sTemp) + 1;
    while (sTemp != NULL)
    {
        if (nRowPrintedElem + (nWordLen - 1) < WIDTH - (LEFT_PAD + RIGHT_PAD))
        {
            nRowPrintedElem += nWordLen;
            printf("%s ", sTemp);
        }
        else
        {
            printRightRemain(nRowPrintedElem);
            (*currRow)++;
            nRowPrintedElem = 0;
            printLeftStart();
        }

        sTemp = strtok(NULL, " ");
        if (sTemp != NULL)
            nWordLen = (strlen(sTemp)) + 1;
    }
    printRightRemain(nRowPrintedElem);
    (*currRow)++;
}