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
    @param nNumSpace is how many spaces would be printed 
*/
void 
printSpace(int nNumSpace)
{
    int i = 0;
    for(i = 0; i < nNumSpace; i++)
    {
        printf(" ");
    }
}


/* This function acts as a prep for the main contents 
    in the box. It prints spaces based on LEFT_MARGIN
    and LEFT_PAD. It also prints the Vertical line boarder 
*/
void 
printLeftStart()
{
    printSpace(LEFT_MARGIN);
    printf(V_LINE);
    printSpace(LEFT_PAD);
}


/* This function prints the remaining spaces so that
    the box would be completed in a singe line. It also closes it off 
    with the horizontal line bar  
    @param nContentLen: this input is the length (width) of a 
        content in a single line
    With this information, this function would know how
    many spaces to print.                                    
*/
void 
printRightRemain(int nContentLen)
{
    int nSpaceRemain = WIDTH - LEFT_PAD - nContentLen;
    printSpace(nSpaceRemain);
    printf(V_LINE);
    printf("\n");
}


/* This function prints the remaining line so that
    the box would be have the number of rows of HEIGHT
    @param nCurrRow: this input is how many rows that have been 
        printed already
    With this information, this function would know how
    many rows are elft to print to get HEIGHT amount of rows    
*/
void 
printBottomRemain(int nCurrRow)
{
    while (nCurrRow < HEIGHT)
    {
        printLeftStart();
        printRightRemain(0);    // prints blanks only
        nCurrRow++;
    }
}


/* This function prints a quantity of empty lines
    @param nQuantity: how much lines would be printed
    @param nCurrRow: adds to nCurrRow how many lines are printed    
*/
void 
printFillerLines(int nQuantity, int *nCurrRow)
{
    int i;
    for (i = 0; i < nQuantity; i++)
    {
        printLeftStart(); 
        printRightRemain(0); 
    }
    (*nCurrRow) += nQuantity;
}


/* This function prints replaces the text in sMessage. it makes sure that
    sMessage has a maximum of STR_MSG_SIZE - 1 characters to give space for
    the null character.
    @param sMessage: put sMessage string here
    @param sText: the string that you want to put in sMessage    
*/
void 
setMessage(char *sMessage, char *sText)
{
    snprintf(sMessage, STR_MSG_SIZE - 1, sText);
    sMessage[STR_MSG_SIZE - 1] = '\0';
}


/* This function prints the top bar or header of the TUI. 
    @param sArtText: art text from art.h to be printed as the 
        title of the current page of the TUI.               
*/
void 
printHeader(char sArtText[][WIDTH])
{
    int nCurrCol;    // for the loops. so that this function would know which nColumn it is printing
    int nRowArt;     // for the loops. so that this function would know which nRow it is printing
    int nArtLen = strlen(sArtText[0]);  // assigns the width of the art to nArtLen

    printSpace(LEFT_MARGIN);    // prints margin
    
    // prints the topmost horizontal bar
    printf("%c", UP_LEFT_CORNER);
    for (nCurrCol = 0; nCurrCol < WIDTH; nCurrCol++)
    {
        printf(H_LINE);
    }
    printf("%c", UP_RIGHT_CORNER); 

    printf("\n");
    
    // prints the art: HDR_<text name> (refer to art.h)
    for (nRowArt = 0; nRowArt < ART_TEXT_HEIGHT; nRowArt++)
    {
        printLeftStart();
        printf("%s", sArtText[nRowArt]);
        printRightRemain(nArtLen);
    }

    // prints the middle bar (before content)
    printSpace(LEFT_MARGIN);
    printf("%c", MID_LEFT_CORNER); 
    for (nCurrCol = 0; nCurrCol < WIDTH; nCurrCol++)
    {
        printf(H_LINE);
    }
    printf("%c", MID_RIGHT_CORNER); 
    
    
    printf("\n");
}


/* This function prints out the bottom part of the
    TUI. It also prints whatever message the system
    has for the user e.g. invalid or succesful input    
    @param sMessage: this is the string to be printed at
        the bottom bar.                                 
*/
void 
printRemark(char *sMessage)
{
    int nCurrCol;   // used in for loops when printing horizontal bars
    int nMsgLen = strlen(sMessage); // used for printRightRemain()

    // prints the top part of the lower TUI
    printSpace(LEFT_MARGIN);
    printf("%c", MID_LEFT_CORNER);
    for (nCurrCol = 0; nCurrCol < WIDTH; nCurrCol++)
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
    for (nCurrCol = 0; nCurrCol < WIDTH; nCurrCol++)
    {
        printf(H_LINE);
    }
    printf("%c", DOWN_RIGHT_CORNER); 


    printf("\n");
}


/* This function handles the input of the user.
    @param sInput: variable that holds the input of the user. it is to 
        be altered in this function
    @param sInputSize: size of the sInputArray
    @param nChoices: the list of choices the sInput is to be compared to. (checks if it matches to any of it)
    @param nChoiceSize: size of the array nChoices
    @param sErrorFeedback: this is the sMessage in box_imp.c. It is to be
        altered based on the feedback (e.g. error or succesfuly input!) 

    @return ERROR CODES:
    0: succesful input
    1: The input is too long and exceeds nInputSize
    2: The input entered is not in the list of input                     
    3: Duplicate input from the database
    4: Input is empty                                                                                       
    5: Invalid file type
    6: File name taken
    7: Too many save files
    8: file name does not exist
    9: input format not followed                                                                           
*/
int 
getInput(char *sInput, int nInputSize, char sChoices[][STR_CHOICES_SIZE], int nChoicesSize, char *sErrorFeedBack)
{
    int nErrorMsg = 0;  // error code

    char cBuffer;        // used for flushing the stdin file stream

    int nCurrChoice;     // used in loops for checking each element in the sChoices array
    
    int isMatch = 0;    // used to check if the user has entered an input identical to one of the elements in the list

    // prints and setup the [INPUT] prompt
    printSpace(LEFT_MARGIN + LEFT_PAD + 1);
    printf("[INPUT]: ");
    fgets(sInput, nInputSize, stdin);       // used fgets to limit the characters. it only get upto nInputSize - 1 char in stdin
    sInput[strcspn(sInput, "\n")] = 0;      // replaces the \n with null character. if the cBuffer doesn't have it 
                                            // (the string input has more than nInputSize - 1),
                                            // it replaces the last element in the array (margin) with null (0)

    if (strlen(sInput) == nInputSize - 1)   // if the characters are too many for the array size 
    {
        snprintf(sErrorFeedBack, STR_MSG_SIZE, "Invalid input! You may only enter a maximum of %d characters", 
                    nInputSize - STR_MARGIN);
        sErrorFeedBack[STR_MSG_SIZE - 1] = '\0';
        while ( (cBuffer = getchar()) != '\n' && cBuffer != EOF );    // flushes stdin filestream 

        sInput[0] = '\0';   // cleans input cBuffer if the input was invalid.

        nErrorMsg = 1;
    }
    else if (strlen(sInput) == 0)   // if there are no inputs
    {
        setMessage(sErrorFeedBack, "You must have an input!");

        nErrorMsg = 4;
    }

    // checks if the input is one of the elements in sChoices array. Case-sensitive (strcmp)
    for (nCurrChoice = 0; (nCurrChoice < nChoicesSize) && (isMatch == 0); nCurrChoice++)
    {
        if (strcmp(sChoices[nCurrChoice], sInput) == 0)
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
        setMessage(sErrorFeedBack, "Your input is not in the choices. Inputs are case-sensitive.");

        sInput[0] = '\0';   // cleans the input cBuffer if the input was invalid

        nErrorMsg = 2;
    }

    return nErrorMsg;
}


/* This function prints out words (choices) in a rectangular form (e.g. 2x2, 2x3, etc..): word box
    @param sChoices: array of words to be printed (strings)
    @param nNumElem: number of words(elements) in the array sChoices
    @param nColumn: how many columns in the rectangle
    @param nRow: how many nRow in the rectangle
    @param *nCurrRow: used to incremenet nCurrRow in box_imp.c, based on the hiehgt of the word box       */
void 
printChoices(char sChoices[][STR_CHOICES_SIZE], int nNumElem, int nColumn, int nRow, char cFormat, int *nCurrRow)
{
    int nTabRow;            // current element nRow in the box
    int nTabCol;            // current element nColumn in the box
    int nPrintedElem = 0;    // how many elements are printed
    
    int pMaxLenCol[10] = {}; // max length of words in a nColumn. used for lining up columns
    int nCurrElem = 0;       // variable used to getting inputs for pMaxLenCol
    
    int nLenCurWord = 0;     // length of current word(element) in sChoices

    int nNumSpacesBetween = 3;  // define variable. number of spaces between columns
    int nCursorLen = 2;         // define variable. number of elements in the cursor: "> " = 2

    int nRowWidth;   // variable that will be used to know how many (width) were printed 
                    // in a single nRow of the rectangle
    
    int i = 0;
    // used in centering the text
    int nWords_row_width_max = 0;
    int nHalf_start = 0;


    // counting the highest width in each nColumn and storing it in pMaxLenCol[]
    for (nTabRow = 0; nTabRow < nRow; nTabRow++)
    {
        for (nTabCol = 0; nTabCol < nColumn && 
            nCurrElem < nNumElem; nTabCol++)
            {
                nLenCurWord = strlen(sChoices[nCurrElem]);
                if (pMaxLenCol[nTabCol] < nLenCurWord)
                    pMaxLenCol[nTabCol] = nLenCurWord;
                nCurrElem++;
            }
    }

    // if the cFormat is 'c' (center), this calculates on which x position should it start prinitng, based on the
    // max width of the rectangle
    if (cFormat == 'c')
    {
        for (i = 0; i < 10; i++)
        {
            nWords_row_width_max += pMaxLenCol[i];
        }
        // divide width by 2 and shift it to the left by (how much elements (including spaces) are in a box width) divided by 2
        int max_width_all = ((WIDTH / 2) - ((nWords_row_width_max + (nCursorLen * nColumn) + ((nColumn - 1) * nNumSpacesBetween)) / 2));
        nHalf_start =  max_width_all;
    }

    // 'c' and 'j' would be the only ones accepted. this serves as a warning only
	if (cFormat != 'c' && cFormat != 'j')
        printf("Tabulation not specified");
    

    for (nTabRow = 0; nTabRow < nRow; nTabRow++)
    {
        nRowWidth = 0;   // resets to 0 if it reaches a new nRow.
        // prints the left part
        if (cFormat == 'c')
        {
    	    printLeftStart();
            printSpace(nHalf_start);
            nRowWidth += nHalf_start; // nRowWidth accounts for spaces too. (for printRightRemain). 
        }                           // recall: LEFT_PAD is not included in printRightRemain contents to count
        else if (cFormat == 'j')		                                    
            printLeftStart();

        // print of contents of the rectangle word box
        for (nTabCol = 0; nTabCol < nColumn && nPrintedElem < nNumElem; nTabCol++)
        {
            printf("> ");           // prints cursor
            nRowWidth += nCursorLen; // updates nRowWidth

            printf("%s", sChoices[nPrintedElem]);        // prints the word in the current sChoices element
            nLenCurWord = strlen(sChoices[nPrintedElem]); // for the nRowWidth update
            nRowWidth += nLenCurWord;
                
            if (nTabCol + 1 < nColumn)   // if there is supposed to be a next word in the word box. (e.g. 2x3, if nCurrCol is only 1)
            {
                if (nLenCurWord < pMaxLenCol[nTabCol])    
                {
                	printSpace(pMaxLenCol[nTabCol] - nLenCurWord);    // prints the pagkukulang of word if mas konti yung letters ng word sa 
                    nRowWidth += pMaxLenCol[nTabCol] - nLenCurWord;    // max len ng nColumn na yon
				}
                printSpace(nNumSpacesBetween);  // prints the space between columns
                nRowWidth += nNumSpacesBetween;
            }
                
            nPrintedElem++;
                
        }

        printRightRemain(nRowWidth); // prints the remaining spaces of the nRow and closes it off with the vertical bar
    }

    (*nCurrRow) += nRow; // updates the nCurrRow for box_imp.c
    
}


/* This function prints out the inputted string to the TUI. It handles all new lines (if the string is too long for WIDTH)
    and prints it out justified or centered
    @param sTempText: The text to be displayed
    @param cFormat: you can input 'c' for center or 'j' for justified
    @param *nCurrRow: for updating the nCurrRow in box_imp.c based on how many rows the text consumed
    PRE-CONDITION: can only input 500 characters of sTempText
*/
void 
printText(char *sTempText, char cFormat, int *nCurrRow)
{
    char sText[500];    // strcpy from sTempText since sTempText is only a pointer (cant do string manipulations)
    char *sTemp;        // storage of word in the sText
    int nWordLen;       // length of that word
    char sLineTextHolder[WIDTH];    // this is a buffer that will hold all the words in a single line
    sLineTextHolder[0] = '\0';      // since strcat() would be used. This clean is a safe guard so that strcat is sure to start at the 0th element

    int nLeftExtraSpace = 0;        // used if it is centered. used in printSpace to print the appropriate number of spaces when cFormat is centered

    int nRowPrintedElem = 0;    // used fto know how many characters were already printed in a nRow (new line if it exceeds WIDTH)


    strcpy(sText, sTempText);

    // initializes while loop
    printLeftStart();
    sTemp = strtok(sText, " ");     // strtok splits a string based on the 2nd param. the splitted word(string segment) is returned
    nWordLen = strlen(sTemp) + 1;   // +1 to count the whitespace after each word
    while (sTemp != NULL)
    {
        if (nRowPrintedElem + (nWordLen - 1) < WIDTH - (LEFT_PAD + RIGHT_PAD))  // if kasya pa yung word sa nRow
        {
            strcat(sLineTextHolder, sTemp); // adds the word to the sLineTextHolder buffer
            strcat(sLineTextHolder, " ");   // adds space since strtok does not include the space
            nRowPrintedElem += nWordLen;    // update the number of characters in the nRow since new words are added
        }
        else    // if di na kasya yung word, then print the sLineTextHolder buffer. after that, clean the buffer
        {
            if (cFormat == 'c')  // if the cFormat is centered
            {
                nLeftExtraSpace = (WIDTH / 2) - ((int)strlen(sLineTextHolder) / 2); // number of spaces required to center text
                printSpace(nLeftExtraSpace);
            }

            printf("%s", sLineTextHolder);  // print the buffer
            sLineTextHolder[0] = '\0';      // clean the buffer
            printRightRemain(nRowPrintedElem + nLeftExtraSpace);  // print number of spaces na meron pa and close it off
            (*nCurrRow)++;                       // update the nCurrRow
            nRowPrintedElem = 0;                // reset the number of elements in a nRow
            printLeftStart();
            
            strcat(sLineTextHolder, sTemp);     // since sTemp still holds the next word, it is stored as the next line already
            strcat(sLineTextHolder, " ");
            nRowPrintedElem += nWordLen;    // update the number of characters in the nRow (next nRow in this case)

            nLeftExtraSpace = 0;            // the nRow has different number of words so the space required to center is different
        }

        sTemp = strtok(NULL, " ");              // proceed to the next word
        if (sTemp != NULL)  // if it reaches the end of the string, sTemp might be NULL. segmenetaion fault guard
            nWordLen = (strlen(sTemp)) + 1;     // + 1 for the space
    }
    // printing the final nRow
    if (cFormat == 'c') 
    {
        nLeftExtraSpace = (WIDTH / 2) - ((int)strlen(sLineTextHolder) / 2);
        printSpace(nLeftExtraSpace);
    }
    printf("%s", sLineTextHolder);
    sLineTextHolder[0] = '\0';
    printRightRemain(nRowPrintedElem + nLeftExtraSpace);  // print the rest of the space after reaching the last word
    (*nCurrRow)++;                       // updates the nCurrRow for box_imp.c
}


/* This function prints all the file names inside the *sPath directory
    @param *sPath: directory you want the filenames to be printed
    @param *nCurrRow: for updating the nCurrRow in box_imp.c based on how many rows the text consumed
    
    @return Number of files in the directory  
*/
int 
printFileNames(char *sPath, int *nCurrRow)
{
    int numSavs = 0;    // keeps track how many files are in the directory

    int isOpened = 1;   // used to know if opening the directory is succesful

    char outputBuffer[WIDTH] = "";  // buffer where filenames are stored, which is then printed

    char displayNum[3]; // concatinated in outputBuffer. used to store the number.

    const int nLeftPad = WIDTH / 3; // left pad
    int currPad;    // used in for loops for printing the pad 

    DIR * dpath = opendir(sPath);    // opens the specified sPath
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
                (*nCurrRow)++;

                printFillerLines(1, nCurrRow);
            }
        }
        closedir(dpath); // finally close the directory

        // if no files are in the directory
        if (numSavs == 0)
            printText("No save files yet...", 'c', nCurrRow);
    }

    else
        printText("Can't open directory!", 'c', nCurrRow);
    
    return numSavs;
}


/* Checks if file exists in sav directory
    @param *sFname: name of the file

    @return returns 1 if the input file name exists in the directory "sav", otherwise, return 0   
*/
int 
fileExists(const char *sFname)
{
    FILE *pFile;

    char sPath[5 + FILE_NAME_LEN + STR_MARGIN] = "sav\\";
    strcat(sPath, sFname);

    if ((pFile = fopen(sPath, "r")))
    {
        fclose(pFile);
        return 1;
    }
    return 0;
}


/* This dunction deletes a file named sFname in the sav directory
    @param *sFname: name of the file  

    @return returns 1 if the file deletion was succesful
*/
int 
deleteSav(char *sFname)
{
    char sPathBuffer[FILE_NAME_LEN + 6] = "";
    snprintf(sPathBuffer, FILE_NAME_LEN + 6, "sav\\%s", sFname);
    
    return remove(sPathBuffer);
}


/* Formats level to 000 format
    @param nNum: input number to be formatter  
*/
void 
printFormatNum(int nNum) 
{
    if (nNum < 10) 
    {
		printf("00%d", nNum);
	}
    else if (nNum < 100)
    {
        printf("0%d", nNum);
    }
	else 
    {
		printf("%d", nNum);
	}
}


/* This function checks if the word only has letters in it 
    @param sWord: string input
    @param nWordLen: length of the string
    
    @return 1 if it is only letters. 0 if it encountered a character that is not a letter
*/
int 
onlyLetters(const char *sWord, const int nWordLen)
{
    int isOnlyLetter = 1;
    int nCurrLetter;
    for (nCurrLetter = 0; nCurrLetter < nWordLen && isOnlyLetter; nCurrLetter++)
    {
        if ((sWord[nCurrLetter] < 'A' || sWord[nCurrLetter] > 'Z') &&
            (sWord[nCurrLetter] < 'a' || sWord[nCurrLetter] > 'z'))
                isOnlyLetter = 0;
    }

    return isOnlyLetter;
}


/* This function converts all letters in a word into uppercase.
    if a character is not a lower case letter (symbol), it will not do anything to that character
    @param sWord: string input. make sure it is an array, not a constant literal
    @param nWordLen: length of the string 
*/
void 
toUpperWord(char sWord[], const int nWordLen)
{
    int nCurrLetter;
    for (nCurrLetter = 0; nCurrLetter < nWordLen; nCurrLetter++)
    {
        if (sWord[nCurrLetter] >= 'a' && sWord[nCurrLetter] <= 'z')
        {
            // based on the ascii table, to turn a letter to uppercase, shift the value
            // by 32 to the left
            sWord[nCurrLetter] -= 32;
        }
    }
}