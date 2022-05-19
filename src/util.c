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

/* This function handles the input of the user.*/
int getInput(char *sInput, int nInputArrSize, char *sErrorFeedBack, int nMsgArrSize)
{
    int nErrorMsg = 0;

    printSpace(LEFT_MARGIN + LEFT_PAD + 1);
    printf("[INPUT]: ");
    fgets(sInput, nInputArrSize, stdin);
    sInput[strcspn(sInput, "\n")] = 0;

    if (strlen(sInput) == nInputArrSize - 1)
    {
        snprintf(sErrorFeedBack, nMsgArrSize, "Invalid input! You may only enter a maximum of %d characters", 
                    nInputArrSize - STR_MARGIN);
        nErrorMsg = 1;
    }

    return nErrorMsg;
}