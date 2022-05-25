/******************************************
File Name: box_imp.c

Author: Francis Zaccharie B. de Leon
Last Update: May 18, 2022

This file constains the function 
implementations for the GUI of the 
different modes the dex has
******************************************/

// include files
#include "../configurations.h"
#include "../header/definitions.h"
#include "../header/array_sizes.h"
#include "../protoypes/util_proto.h"
#include "../protoypes/art_proto.h"
#include "../header/art.h"


/* This function creates the GUI for the main menu
    it modifies the sInput to what the user has selected.
    PARAMETERS:
    - sInput is the input thw ould be later modified
    - sInputSize is the size of the char array sInput
    - sMainChoices is the array of strings composed of the main menu choices    */
void mainMenu(stringIn sInput, int sInputSize, stringChoice sMainChoices[], int nMainChoicesSize, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0') // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Choose the choices in the menu"); // message that would be sent to the user at the bottom screen
                                                            // initialized to "Choose the choices in the menu"

    
    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_FakeDex); 

        
        // prints the main content of the TUI
        printFillerLines(HEIGHT / 10, &currRow);
        printText("Welcome to the Fakedex game, trainer!", 'c', &currRow);
        printFillerLines(1, &currRow);              // prints lines 1/8 of the HEIGHT
        displayPokeball(ART_Pokeball, &currRow);    // dipalys the pokeball art
        printFillerLines(1, &currRow);
        printChoices(sMainChoices, nMainChoicesSize, 3, 2, 'c', &currRow); // prints the possible choices fot main menu
        
        printBottomRemain(currRow); // prints the remaining row so that it would be HEIGHT 
                                    // number of content rows


        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.


        // getInput returns if the user input is valid or not.
        // refer to getInput implementation (util.c) for the list of possible error msg returns
        // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
        Input_Fail = getInput(sInput, sInputSize, sMainChoices, nMainChoicesSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)
    } while (Input_Fail);
}

void fakedexDatabase(stringIn sInput, int sInputSize, stringChoice sDatabaseChoices[], int nDatabaseChoicesSize, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0')   // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Welcome to the Fakedex Database!");        // message that would be sent to the user at the bottom screen
                                                           
    
    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Database); 


        // prints the main content of the TUI
        printFillerLines(HEIGHT / 2, &currRow);
        printText("Welcome to the Fakedex Database, Trainer! What would you like to do?", 'c', &currRow);
        printFillerLines(1, &currRow);
        printChoices(sDatabaseChoices, nDatabaseChoicesSize, nDatabaseChoicesSize, 1, 'c', &currRow);

        printBottomRemain(currRow);


        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

        // getInput returns if the user input is valid or not.
        // refer to getInput implementation (util.c) for the list of possible error msg returns
        // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
        Input_Fail = getInput(sInput, sInputSize, sDatabaseChoices, nDatabaseChoicesSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)
    } while (Input_Fail);
}

void addDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *dex_Database, int nCurrMon, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.


    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "");   // message that would be sent to the user at the bottom screen. set to none at the moment 

    // there are 4 entries (question) that the user needs to fill. Full name, short name, description and gender.
    // this variable lets the function know what kind of entry the program currently needs from the user
    int currQuestion = 0;

    // since this function's contents type out the user's input, printing the contents of this function 
    // requires a dynamic approach. number of spaces varies line by line to connect the right vertical bar (box TUI)
    // the printText function that the developer implemented cannot handle %s place holders that is why strcat
    // functions are used. to make sure that strcat has enought room to concatinate the destination string, and to avoid
    // segmentation errors, the sizes of each members of the struct are assigned to the output buffers(destinations of strcat)
    // nExtra is for headroom, and also for the "Name: ", "Description: " etc...
    int nExtra = 20;
    char sOutFName[nInputSizes[0] + nExtra];
    char sOutSName[nInputSizes[1] + nExtra];
    char sOutDesc[nInputSizes[2] + nExtra];
    char sOutGender[nInputSizes[3] + nExtra];

    while (currQuestion < nInputQty) 
    {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Add_Dex);


        // setup for main content
        sOutFName[0] = '\0';    // since this loops, the developer is just making sure that the strings start at 0
        sOutSName[0] = '\0';    // to avoid segmentation faults. since strcat has a tendency to be dangerous.
        sOutDesc[0] = '\0';
        sOutGender[0] = '\0';
        strcpy(sOutFName, "Name: ");    // these are what the nExtra is used for
        strcpy(sOutSName, "Short Name: ");
        strcpy(sOutDesc, "Description: ");
        strcpy(sOutGender, "Gender: ");
        strcat(sOutFName, dex_Database[nCurrMon].sFull_Name);   // based on the available information the user has inputted
        strcat(sOutSName, dex_Database[nCurrMon].sShort_Name);  // because the array was initialized to 0, all other entries are
        strcat(sOutDesc, dex_Database[nCurrMon].sDescript);     // 0 or NULL, so if the user has not yet inputted this, it will not conctenate anything.
        if (dex_Database[nCurrMon].cGender == 'M')  // since cGender member only has char, putting the constant MALE FEMALE or UNKNOWN is necessary
            strcat(sOutGender, "MALE");
        else if (dex_Database[nCurrMon].cGender == 'F')
            strcat(sOutGender, "FEMALE");
        else if (dex_Database[nCurrMon].cGender == 'U')
            strcat(sOutGender, "UNKNOWN");

        // prints the main content of the TUI. Printing of the output buffers.
        printFillerLines(1, &currRow);
        printText("These are your new Fakemon Information", 'c', &currRow);
        printFillerLines(1, &currRow);
        printText(sOutFName, 'j', &currRow);
        printFillerLines(1, &currRow);
        printText(sOutSName, 'j', &currRow);
        printFillerLines(1, &currRow);
        printText(sOutDesc, 'j', &currRow);
        printFillerLines(1, &currRow);
        printText(sOutGender, 'j', &currRow);
        printFillerLines(1, &currRow);

        printBottomRemain(currRow);


        // preparing the right message, since each question requires different prompt from the program.
        if (!(Input_Fail))
        {
            if (currQuestion == 0)
                strcpy(sMessage, "Input your Fakemon's full name.");
            else if (currQuestion == 1)
                strcpy(sMessage, "Input your Fakemon's short name. Capital Letters only.");
            else if (currQuestion == 2)
                strcpy(sMessage, "Input your Fakemon's description.");
            else if (currQuestion == 3)
                strcpy(sMessage, "Input your Fakemon's gender. 'F', 'M', 'U' only. U is Unknown.");
        }
        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

        // getInput returns if the user input is valid or not.
        // refer to getInput implementation (util.c) for the list of possible error msg returns
        // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
        Input_Fail = getInput(sInput, nInputSizes[currQuestion], NULL, 0, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)

        // sInput is assigned to its rightful struct member
        if (currQuestion == 0)
            strcpy(dex_Database[nCurrMon].sFull_Name, sInput);
        else if (currQuestion == 1)
            strcpy(dex_Database[nCurrMon].sShort_Name, sInput);
        else if (currQuestion == 2)
            strcpy(dex_Database[nCurrMon].sDescript, sInput);
        
        // for gender's input case, the developer did not modify the getInput command to alter the Input_Fail to output as 2, 
        // it cannot check if the user input is in the choices since that needs an argument for the 3rd parameter,
        // which in this case, set to NULL. since this is the only time that this particular problem will arise, 
        // there is no need to alter the getInput function as this will complicate the getInput function.
        else if (currQuestion == 3)
        {
            if (sInput[0] == 'M' || sInput[0] == 'F' || sInput[0] == 'U')
                dex_Database[nCurrMon].cGender = sInput[0];
            else if (Input_Fail != 1)   // if there are just the right amount of Input (no errors in that part)
            {
                Input_Fail = 2; // user input not in the choices
                strcpy(sMessage, "Invalid input! You can only enter 'M', 'F', or 'U'" );    // this overides the message if the input is too long
            }
        }

        if (!(Input_Fail))
        {
            currQuestion++;
        }
    }

    strcpy(sMessage, "Succesfully added a new entry!");
}