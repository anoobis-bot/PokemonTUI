/******************************************
File Name: util.c

Author: Francis Zaccharie B. de Leon
Last Update: May 18, 2022

This file contains the common utility 
functions that the developer may use
******************************************/

// include files
#include "../configurations.h"
#include "../header/array_sizes.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h> 

/* This function prints n number of spaces 
    PARAMETERS:
    - int nNumSpace is how many spaces would be printed */
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
    and LEFT_PAD. It also prints the Vertical line boarder */
void printLeftStart()
{
    printSpace(LEFT_MARGIN);
    printf(V_LINE);
    printSpace(LEFT_PAD);
}

/* This function prints the remaining spaces so that
    the box would be completed in a singe line.
    PARAMETERS: 
    - nContentLen: this input is the length (width) of a 
        content in a single line
    With this information, this function would know how
    many spaces to print. It also closes it off with the
    horizontal line bar                                     */
void printRightRemain(int nContentLen)
{
    int nSpaceRemain = WIDTH - LEFT_PAD - nContentLen;
    printSpace(nSpaceRemain);
    printf(V_LINE);
    printf("\n");
}

/* This function prints the remaining line so that
    the box would be have the number of rows of HEIGHT
    PARAMETERS: 
    - currRow: this input is how many rows that have been 
        printed already
    With this information, this function would know how
    many rows are elft to print to get HEIGHT amount of rows    */
void printBottomRemain(int currRow)
{
    while (currRow < HEIGHT)
    {
        printLeftStart();
        printRightRemain(0);    // prints blanks only
        currRow++;
    }
}

/* This function prints a quantity of empty lines
    PARAMETERS:
    - nQuantity: how much lines would be printed
    - adds to currRow how many lines are printed    */
void printFillerLines(int nQuantity, int *currRow)
{
    int i;
    for (i = 0; i < nQuantity; i++)
    {
        printLeftStart(); 
        printRightRemain(0); 
    }
    (*currRow) += nQuantity;
}

/* This function prints the top bar or header of the TUI. 
    PARAMETERS:
    - sArtText: art text from art.h to be printed as the 
        title of the current page of the TUI.               */
void printHeader(char sArtText[][WIDTH])
{
    int currCol;    // for the loops. so that this function would know which column it is printing
    int rowArt;     // for the loops. so that this function would know which row it is printing
    int nArtLen = strlen(sArtText[0]);  // assigns the width of the art to nArtLen

    printSpace(LEFT_MARGIN);    // prints margin
    
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

    // prints the middle bar (before content)
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
    TUI. It also prints whatever message the system
    has for the user e.g. invalid or succesful input    
    PARAMETERS:
    - sMessage: this is the string to be printed at
        the bottom bar.                                 */
void printRemark(char *sMessage)
{
    int currCol;   // used in for loops when printing horizontal bars
    int nMsgLen = strlen(sMessage); // used for printRightRemain()

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
    PARAMETERS:
    - sErrorFeedBack: this is the sMessage in box_imp.c. It is to be
        altered based on the feedback (e.g. error or succesfuly input!)
    - sInput: variable that holds the input of the user. it is to 
        be altered in this function
    - sInputSize: size of the sInputArray
    - nChoices: the list of choices the sInput is to be compared to. (checks if it matches to any of it)
    - nChoiceSize: size of the array nChoices
    - sErrorFeedback: put sMessage here.
    ERROR CODES:
    0: succesful input
    1: The input is too long and exceeds sInputSize
    2: The input entered is not in the list of input                     
    3: Duplicate input from the database
    4: Input is empty                                                                                       
    5: Invalid file type
    6: File name taken
    7: Too many save files
    8: file name does not exist                                                                                 */
int getInput(char *sInput, int nInputSize, char sChoices[][STR_CHOICES_SIZE], int nChoicesSize, char *sErrorFeedBack)
{
    int nErrorMsg = 0;  // error code

    char buffer;        // used for flushing the stdin file stream

    int currChoice;     // used in loops for checking each element in the sChoices array
    int isMatch = 0;    // used to check if the user has entered an input identical to one of the elements in the list

    // prints and setup the [INPUT] prompt
    printSpace(LEFT_MARGIN + LEFT_PAD + 1);
    printf("[INPUT]: ");
    fgets(sInput, nInputSize, stdin);       // used fgets to limit the characters. it only get upto nInputSize - 1 char in stdin
    sInput[strcspn(sInput, "\n")] = 0;      // replaces the \n with null character. if the buffer doesn't have it (the string input has more than nInputSize - 1),
                                            // it replaces the last element in the array (margin) with null (0)

    if (strlen(sInput) == nInputSize - 1)   // if the characters are too many for the array size 
    {
        snprintf(sErrorFeedBack, WIDTH - STR_MARGIN, "Invalid input! You may only enter a maximum of %d characters", 
                    nInputSize - STR_MARGIN);
        while ( (buffer = getchar()) != '\n' && buffer != EOF );    // flushes stdin filestream 

        sInput[0] = '\0';   // cleans input buffer if the input was invalid.

        nErrorMsg = 1;
    }
    else if (strlen(sInput) == 0)   // if there are no inputs
    {
        snprintf(sErrorFeedBack, WIDTH - STR_MARGIN, "You must have an input!");

        nErrorMsg = 4;
    }

    // checks if the input is one of the elements in sChoices array. Case-sensitive (strcmp)
    for (currChoice = 0; (currChoice < nChoicesSize) && (isMatch == 0); currChoice++)
    {
        if (strcmp(sChoices[currChoice], sInput) == 0)
            isMatch = 1;
    }

    // catch case. if there are no choices to pick (e.g. input a name) catch it with this if statement
    if (sChoices == NULL)
    {
        // empty. just return the input. nErrorMsg would still be 0 (provided strlen is in range)
    }

    // if there are choices in the game, start from here
    else if ((!isMatch) && (nErrorMsg == 0)) // if strcnmp did not return 0 and input is not larger that nInputSize
    {
        snprintf(sErrorFeedBack, WIDTH - STR_MARGIN, "Your input is not in the choices. Inputs are case-sensitive.");

        sInput[0] = '\0';   // cleans the input buffer if the input was invalid

        nErrorMsg = 2;
    }

    return nErrorMsg;
}

/* This function prints out words (choices) in a rectangular form (e.g. 2x2, 2x3, etc..): word box
    PARAMETERS:
    - sChoices: array of words (strings)\
    - numElem: number of words(elements) in the array sChoices
    - column: how many columns in the rectangle
    - row: how many row in the rectangle
    - *currRow: used to incremenet currRow in box_imp.c, based on the hiehgt of the word box       */
void printChoices(char sChoices[][STR_CHOICES_SIZE], int numElem, int column, int row, char format, int *currRow)
{
    int tabRow;            // current element row in the box
    int tabCol;            // current element column in the box
    int printedElem = 0;    // how many elements are printed
    
    int maxLenCol[10] = {}; // max length of words in a column. used for lining up columns
    int currElem = 0;       // variable used to getting inputs for maxLenCol
    
    int lenCurWord = 0;     // length of current word(element) in sChoices

    int nNumSpacesBetween = 3;  // define variable. number of spaces between columns
    int nCursorLen = 2;         // define variable. number of elements in the cursor: "> " = 2

    int rowWidth;   // variable that will be used to know how many (width) were printed 
                    // in a single row of the rectangle
    

    // counting the highest width in each column and storing it in maxLenCol[]
    for (tabRow = 0; tabRow < row; tabRow++)
    {
        for (tabCol = 0; tabCol < column && 
            currElem < numElem; tabCol++)
            {
                lenCurWord = strlen(sChoices[currElem]);
                if (maxLenCol[tabCol] < lenCurWord)
                    maxLenCol[tabCol] = lenCurWord;
                currElem++;
            }
    }

    // if the format is 'c' (center), this calculates on which x position should it start prinitng, based on the
    // max width of the rectangle
    int i = 0;
    int words_row_width_max = 0;
    int half_start = 0;
    if (format == 'c')
    {
        for (i = 0; i < 10; i++)
        {
            words_row_width_max += maxLenCol[i];
        }
        // divide width by 2 and shift it to the left by (how much elements (including spaces) are in a box width) divided by 2
        int max_width_all = ((WIDTH / 2) - ((words_row_width_max + (nCursorLen * column) + ((column - 1) * nNumSpacesBetween)) / 2));
        half_start =  max_width_all;
    }

    // 'c' and 'j' would be the only ones accepted. this serves as a warning only
	if (format != 'c' && format != 'j')
        printf("Tabulation not specified");
    

    for (tabRow = 0; tabRow < row; tabRow++)
    {
        rowWidth = 0;   // resets to 0 if it reaches a new row.
        // prints the left part
        if (format == 'c')
        {
    	    printLeftStart();
            printSpace(half_start);
            rowWidth += half_start; // rowWidth accounts for spaces too. (for printRightRemain). 
        }                           // recall: LEFT_PAD is not included in printRightRemain contents to count
        else if (format == 'j')		                                    
            printLeftStart();

        // print of contents of the rectangle word box
        for (tabCol = 0; tabCol < column && printedElem < numElem; tabCol++)
        {
            printf("> ");           // prints cursor
            rowWidth += nCursorLen; // updates rowWidth

            printf("%s", sChoices[printedElem]);        // prints the word in the current sChoices element
            lenCurWord = strlen(sChoices[printedElem]); // for the rowWidth update
            rowWidth += lenCurWord;
                
            if (tabCol + 1 < column)   // if there is supposed to be a next word in the word box. (e.g. 2x3, if currCol is only 1)
            {
                if (lenCurWord < maxLenCol[tabCol])    
                {
                	printSpace(maxLenCol[tabCol] - lenCurWord);    // prints the pagkukulang of word if mas konti yung letters ng word sa 
                    rowWidth += maxLenCol[tabCol] - lenCurWord;    // max len ng column na yon
				}
                printSpace(nNumSpacesBetween);  // prints the space between columns
                rowWidth += nNumSpacesBetween;
            }
                
            printedElem++;
                
        }

        printRightRemain(rowWidth); // prints the remaining spaces of the row and closes it off with the vertical bar
    }

    (*currRow) += row; // updates the currRow for box_imp.c
    
}

/* This function prints out the inputted string to the TUI. It handles all new lines (if the string is too long for WIDTH)
    and prints it out justified or centered
    PARAMETERS:
    - sTempText: The text to be displayed
    - fomat: you can input 'c' for center or 'j' for justified
    - *currRow: for updating the currRow in box_imp.c based on how many rows the text consumed
    LIMITATIONS
    - can only input 500 characters of sTempText                                                                               */
void printText(char *sTempText, char format, int *currRow)
{
    char sText[500];    // strcpy from sTempText since sTempText is only a pointer (cant do string manipulations)
    char *sTemp;        // storage of word in the sText
    int nWordLen;       // length of that word
    char sLineTextHolder[WIDTH];    // this is a buffer that will hold all the words in a single line
    sLineTextHolder[0] = '\0';      // since strcat() would be used. This clean is a safe guard so that strcat is sure to start at the 0th element

    int nLeftExtraSpace = 0;        // used if it is centered. used in printSpace to print the appropriate number of spaces when format is centered

    int nRowPrintedElem = 0;    // used fto know how many characters were already printed in a row (new line if it exceeds WIDTH)

    strcpy(sText, sTempText);

    // initializes while loop
    printLeftStart();
    sTemp = strtok(sText, " ");     // strtok splits a string based on the 2nd param. the splitted word(string segment) is returned
    nWordLen = strlen(sTemp) + 1;   // +1 to count the whitespace after each word
    while (sTemp != NULL)
    {
        if (nRowPrintedElem + (nWordLen - 1) < WIDTH - (LEFT_PAD + RIGHT_PAD))  // if kasya pa yung word sa row
        {
            strcat(sLineTextHolder, sTemp); // adds the word to the sLineTextHolder buffer
            strcat(sLineTextHolder, " ");   // adds space since strtok does not include the space
            nRowPrintedElem += nWordLen;    // update the number of characters in the row since new words are added
        }
        else    // if di na kasya yung word, then print the sLineTextHolder buffer. after that, clean the buffer
        {
            if (format == 'c')  // if the format is centered
            {
                nLeftExtraSpace = (WIDTH / 2) - ((int)strlen(sLineTextHolder) / 2); // number of spaces required to center text
                printSpace(nLeftExtraSpace);
            }

            printf("%s", sLineTextHolder);  // print the buffer
            sLineTextHolder[0] = '\0';      // clean the buffer
            printRightRemain(nRowPrintedElem + nLeftExtraSpace);  // print number of spaces na meron pa and close it off
            (*currRow)++;                       // update the currRow
            nRowPrintedElem = 0;                // reset the number of elements in a row
            printLeftStart();
            
            strcat(sLineTextHolder, sTemp);     // since sTemp still holds the next word, it is stored as the next line already
            strcat(sLineTextHolder, " ");
            nRowPrintedElem += nWordLen;    // update the number of characters in the row (next row in this case)

            nLeftExtraSpace = 0;            // the row has different number of words so the space required to center is different
        }

        sTemp = strtok(NULL, " ");              // proceed to the next word
        if (sTemp != NULL)  // if it reaches the end of the string, sTemp might be NULL. segmenetaion fault guard
            nWordLen = (strlen(sTemp)) + 1;     // + 1 for the space
    }
    // printing the final row
    if (format == 'c') 
    {
        nLeftExtraSpace = (WIDTH / 2) - ((int)strlen(sLineTextHolder) / 2);
        printSpace(nLeftExtraSpace);
    }
    printf("%s", sLineTextHolder);
    sLineTextHolder[0] = '\0';
    printRightRemain(nRowPrintedElem + nLeftExtraSpace);  // print the rest of the space after reaching the last word
    (*currRow)++;                       // updates the currRow for box_imp.c
}

/* This function prints all the file names inside the *path directory
    PARAMETERS:
    - *path: directory you want the filenames to be printed
    - *currRow: for updating the currRow in box_imp.c based on how many rows the text consumed
    RETURN
    - Number of files in the directory  */
int printFileNames(char *path, int *currRow)
{
    int numSavs = 0;    // keeps track how many files are in the directory

    int isOpened = 1;   // used to know if opening the directory is succesful

    char outputBuffer[WIDTH] = "";  // buffer where filenames are stored, which is then printed

    char displayNum[3]; // concatinated in outputBuffer. used to store the number.

    const int nLeftPad = WIDTH / 3; // left pad
    int currPad;    // used in for loops for printing the pad 

    DIR * dpath = opendir(path);    // opens the specified path
    if (dpath == NULL)              // if the directory was not opened succesfully
        isOpened = 0; 

    if (isOpened)
    {
        struct dirent * dir;            // creates a struct that can handle dir operations

        while ((dir = readdir(dpath)) != NULL)  // if there are still files in the directory
        {
            // every directory has "." and ".." exclude them in the list
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                numSavs++;  // increment to keep track the number of files
                
                printLeftStart();

                outputBuffer[0] = '\0'; // resets the output buffer since strcat() will be used
                // puts the necessary space based on nLeftPad
                for (currPad = 0; currPad < nLeftPad; currPad++)
                    strcat(outputBuffer, " ");

                // puts the current number of the file to the buffer
                snprintf(displayNum, 3, "%d.", numSavs);
                strcat(outputBuffer, displayNum);
                // space after number
                strcat(outputBuffer, " ");

                // puts the name of the file to the buffer
                strcat(outputBuffer, dir->d_name);

                // prints the buffer
                printf("%s", outputBuffer);
                printRightRemain(strlen(outputBuffer));
                (*currRow)++;

                printFillerLines(1, currRow);
            }
        }
        closedir(dpath); // finally close the directory

        // if no files are in the directory
        if (numSavs == 0)
            printText("No save files yet...", 'c', currRow);
    }

    else
        printText("Can't open directory!", 'c', currRow);
    
    return numSavs;
}

/* This function returns 1 if the input file name exists in the directory "sav", otherwise, return 0
    PARAMETERS:
    - *fname: name of the file  */
int fileExists(const char *fname)
{
    char path[5 + FILE_NAME_LEN + STR_MARGIN] = "sav\\";
    strcat(path, fname);

    FILE *file;
    if ((file = fopen(path, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

/* This function returns 1 if the file deletion was succesful
    PARAMETERS:
    - *fname: name of the file  */
int deleteSav(char *fname)
{
    char pathBuffer[FILE_NAME_LEN + 6] = "";
    snprintf(pathBuffer, FILE_NAME_LEN + 6, "sav\\%s", fname);
    
    return remove(pathBuffer);
}