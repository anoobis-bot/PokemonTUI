/******************************************
File Name: box_imp.c

Author: Francis Zaccharie B. de Leon
Last Update: May 28, 2022

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
#include "../protoypes/box_imp_proto.h"
#include "../header/art.h"
#include <errno.h>


/* This function creates the GUI for the main menu
    it modifies the sInput to what the user has selected.
    PARAMETERS:
    - sInput is the input thw ould be later modified
    - nInputSize is the size of the char array sInput
    - sMainChoices is the array of strings composed of the main menu choices    */
void mainMenu(stringIn sInput, int nInputSize, stringChoice sMainChoices[], int nMainChoicesSize, stringMsg sMessage)
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
        displayArt(ART_Pokeball, 9,&currRow);    // dipalys the pokeball art
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
        Input_Fail = getInput(sInput, nInputSize, sMainChoices, nMainChoicesSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)
    } while (Input_Fail);
}

void fakedexDatabase(stringIn sInput, int nInputSize, stringChoice sDatabaseChoices[], int nDatabaseChoicesSize, 
                        stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0')   // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Welcome to the Fakedex Database!"); 
        // message that would be sent to the user at the bottom screen
    
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
        Input_Fail = getInput(sInput, nInputSize, sDatabaseChoices, nDatabaseChoicesSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)
    } while (Input_Fail);
}

void viewMon(stringIn sInput, int nInputSize, stringChoice sChoices[], int nChoicesSize, mon_type *Fakedex, 
                int nMonEntry, int forceView, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.


    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "What would you like to do?");   // message that would be sent to the user at the bottom screen.
    
    // buffer that will be printed out in printText function. Max of 500 characters
    char outputBuffer[500] = "";

    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_View_Fakemon);


        // main content
        printText("These are your Fakemon Information", 'c', &currRow);
        printFillerLines(1, &currRow);
        // print full name
        snprintf(outputBuffer, 500, "%s %s", "Full Name:", Fakedex[nMonEntry].sFull_Name);
        printText(outputBuffer, 'j', &currRow);
        printFillerLines(1, &currRow);
        // if the fakemon is caught, disclose all the fakemon's information
        if (Fakedex[nMonEntry].nCaught || forceView)
        {
            // print short name
            snprintf(outputBuffer, 500, "%s %s", "Short Name:", Fakedex[nMonEntry].sShort_Name);
            printText(outputBuffer, 'j', &currRow);
            printFillerLines(1, &currRow);
            // print desciption
            snprintf(outputBuffer, 500, "%s %s", "Description:", Fakedex[nMonEntry].sDescript);
            printText(outputBuffer, 'j', &currRow);
            printFillerLines(1, &currRow);
            // print Gender
            // since cGender member only has char, putting the constant MALE FEMALE or UNKNOWN is necessary
            if (Fakedex[nMonEntry].cGender == 'M')  
                snprintf(outputBuffer, 500, "%s %s", "Gender:", "MALE");
            else if (Fakedex[nMonEntry].cGender == 'F')  
                snprintf(outputBuffer, 500, "%s %s", "Gender:", "FEMALE");
            else if (Fakedex[nMonEntry].cGender == 'U')  
                snprintf(outputBuffer, 500, "%s %s", "Gender:", "UNKNOWN");
            printText(outputBuffer, 'j', &currRow);
            printFillerLines(1, &currRow);
            
        }
        // if not caught, only display ??? for short name, description, and gender
        else
        {
            // print short name
            snprintf(outputBuffer, 500, "%s %s", "Short Name:", "???");
            printText(outputBuffer, 'j', &currRow);
            printFillerLines(1, &currRow);
            // print desciption
            snprintf(outputBuffer, 500, "%s %s", "Description:", "???");
            printText(outputBuffer, 'j', &currRow);
            printFillerLines(1, &currRow);
            // print Gender
            snprintf(outputBuffer, 500, "%s %s", "Gender:", "???");
            printText(outputBuffer, 'j', &currRow);
            printFillerLines(1, &currRow);
        }

        // print caught or uncaught
        // since nCaught member only has short, putting the constant CAUGHT or UNCAUGHT
        if (Fakedex[nMonEntry].nCaught == 0)  
            snprintf(outputBuffer, 500, "%s %s", "Status:", "UNCAUGHT");
        else if (Fakedex[nMonEntry].nCaught == 1)  
            snprintf(outputBuffer, 500, "%s %s", "Status:", "CAUGHT");
        printText(outputBuffer, 'j', &currRow);
        printFillerLines(1, &currRow);

        printChoices(sChoices, nChoicesSize, nChoicesSize, 1, 'c', &currRow);

        printBottomRemain(currRow);


        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

        // getInput returns if the user input is valid or not.
        // refer to getInput implementation (util.c) for the list of possible error msg returns
        // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
        Input_Fail = getInput(sInput, nInputSize, sChoices, nChoicesSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)
    } while (Input_Fail && (strcmp(sInput, sChoices[nChoicesSize - 1]) != 0));

    if (strcmp(sInput, sChoices[nChoicesSize - 1]) == 0)    // if the user typed cancel
    {
        sInput[0] = '\0';   // "Cancel" will be left in the sInput buffer which could cause compplications for
    }    
}

int addDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *dex_Database, int *nMonCreated, 
            box_type caughtMons[], int nCapturedMons, stringMsg sMessage, int nCurrMon)
{
    // this will aslo be used for updateDex function since they have very similar functions, 
    // so putting these would allow which mode the function is currently is
    int isUpdateDex = 0;
    if (nCurrMon < 0)   // if in addDex mode
    {
        // the current created fakemon is the highest index (nMonCreated)
        nCurrMon = *nMonCreated;
    }
    // else if the nCurrMon >= 0, that means this will replace whatever data in the index nCurrMon
    else    // if in updateDex Mode
    {
        isUpdateDex = 1;
    }

    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    // value used in a for loop to check if the name match any of the already stored data 
    int compMon = 0;        // compareMon
    int isDuplicate = 0;   // will turn into 1 once there is a found duplictae
    // this is where the temporary data would be stored if the full name is the same(since it may overwrite data)
    mon_type tempMon = {{0}};
    // choices for viewMon() if there is a duplicate
    stringChoice sDuplicateChoice[2] = {"Yes", "No"};

    // this is what to return, whether a new mon was created. set to yes by default
    int newCreatedMon = 1;

    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "");   // message that would be sent to the user at the bottom screen. set to none at the moment 

    // there are 4 entries (question) that the user needs to fill. 
    // 0 = Full name, 
    // 1 = short name, 
    // 2 = description,
    // 3 = gender.
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

    // used in for loops for the caughtMons[]
    int nCurrCaughtMon;

    while (currQuestion < nInputQty) 
    {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        if (isUpdateDex)
            printHeader(HDR_Update_Dex);
        else
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

        // if the entry is duplicate, the inputted data is stored in a temporary data buffer
        if (isDuplicate || ((*nMonCreated) >= DEX_MAX)) 
        {                   // since the data maybe discarded. so the data to be printed cannot come from dex_Database
            strcat(sOutFName, tempMon.sFull_Name);
            strcat(sOutSName, tempMon.sShort_Name);
            strcat(sOutDesc, tempMon.sDescript);
        }
        else
        {
            // the buffers are based on the available information the user has inputted.
            // because the array was initialized to 0, all other entries are
            // 0 or NULL, so if the user has not yet inputted this, it will not conctenate anything.
            strcat(sOutFName, dex_Database[nCurrMon].sFull_Name);   
            strcat(sOutSName, dex_Database[nCurrMon].sShort_Name);  
            strcat(sOutDesc, dex_Database[nCurrMon].sDescript);
            if (dex_Database[nCurrMon].cGender == 'M')  
                strcat(sOutGender, "MALE");
            else if (dex_Database[nCurrMon].cGender == 'F')
                strcat(sOutGender, "FEMALE");
            else if (dex_Database[nCurrMon].cGender == 'U')
                strcat(sOutGender, "UNKNOWN");
        }
        
        // since cGender member only has char, putting the constant MALE FEMALE or UNKNOWN is necessary
        

        // prints the main content of the TUI. Printing of the output buffers.
        printFillerLines(1, &currRow);

        if (isUpdateDex)
            printText("These are your current Fakemon Information", 'c', &currRow);
        else
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
                strcpy(sMessage, "Input your Fakemon's short name. 5 Letters. Will be capitalized");
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

        // if the input was valid (the size of input is not greater than the alloted size of the member)
        if (!(Input_Fail))
        {
            // since the full name of the fakemon is the basis for overwiting data this is the only question
            // in which the input from that question is compared to every full name in the data base to check if there are
            // duplicates.
            if (currQuestion == 0)
            {
                for (compMon = 0; compMon < (*nMonCreated) && !(isDuplicate); compMon++)
                {
                    // if in the updateDex function, we wouldnt want to trigger a isDuplicate, if the sInput
                    // is its own data (if they do not want to change the contents)
                    if (compMon != nCurrMon)
                    {
                        if (strcasecmp(sInput, dex_Database[compMon].sFull_Name) == 0)
                        {
                            isDuplicate = 1;
                            // compMon is the index where the fakemon to be overwritten resides.
                            // compMon is decremented to balance it out 
                            // since at the end of the for loop, it would be incremeneted.
                            compMon--;
                        }
                    }
                    
                }
            }

            // if it is duplicate or the dex is full, store the contents on a temp buffer.
            // will discard it or not, depending on the choice of the user
            // isDuplicate will never turn again to 0 once set to 1
            if (isDuplicate || ((*nMonCreated) >= DEX_MAX))
            {
                // store the user input to the tempMon struct buffer
                if (currQuestion == 0)
                {
                    // checks if there are only letters in the name
                    // assign it if it is only letters
                    if (onlyLetters(sInput, strlen(sInput)))
                        strcpy(tempMon.sFull_Name, sInput);
                    // if not, get input again
                    else
                    {
                        sInput[0] = '\0';
                        setMessage(sMessage, "Only input letters in the English alphabet");
                        Input_Fail = 9;
                    }
                }
                else if (currQuestion == 1)
                {
                    // checks if the short name input is valid
                    // if it has SHORT_NAME_SIZE characters
                    if (strlen(sInput) == SHORT_NAME_SIZE)
                    {
                        // if there is only letters in the input (no symbols)
                        if (onlyLetters(sInput, SHORT_NAME_SIZE))
                        {
                            // convert it to upper case and assign it
                            toUpperWord(sInput, SHORT_NAME_SIZE);
                            strcpy(tempMon.sShort_Name, sInput);
                        }
                        else
                        {
                            Input_Fail = 9;
                            sInput[0] = '\0';
                            setMessage(sMessage, "Only input letters in the English alphabet");
                        }
                        
                    }
                    else
                    {
                        // this will prompt the user to type a valid input
                        Input_Fail = 9;
                        sInput[0] = '\0';
                        snprintf(sMessage, STR_MSG_SIZE, "Please enter exactly %d Letters. Letters wil be capitalized.", 
                                    SHORT_NAME_SIZE);
                        sMessage[STR_MSG_SIZE - 1] = '\0';
                    }
                }
                else if (currQuestion == 2)
                    strcpy(tempMon.sDescript, sInput);
                
                // for gender's input case, the developer did not modify the getInput command to alter the Input_Fail to 
                // output as 2, it cannot check if the user input is in the choices (M, F, U)since that needs an argument 
                // for the  3rd parameter, which in this case, set to NULL, since the full and short name and 
                // description does not need choices. Since this is the only time that this particular problem will arise, 
                // there is no need to alter the getInput function as this will complicate the getInput function.
                else if (currQuestion == 3)
                {
                    if (sInput[0] == 'M' || sInput[0] == 'F' || sInput[0] == 'U')
                        tempMon.cGender = sInput[0];
                    else // if other letters are inputted
                    {
                        Input_Fail = 2; // user input not in the choices
                        strcpy(sMessage, "Invalid input! You can only enter 'M', 'F', or 'U'" );    
                    }
                }
                
                // procceed to the next question if the input was succesful
                if (!(Input_Fail))  
                    currQuestion++;


                // if all questions have been asked
                if (currQuestion >= nInputQty)
                {
                    // is Duplicate has priority since update first before
                    // replacing
                    if (isDuplicate)
                    {
                        // tell the user that there has been a duplicate
                        setMessage(sMessage, "We found a duplicate, would you like to overide this entry?");
                        // show the original entry and ask if they want to overwrite
                        viewMon(sInput, 3 + STR_MARGIN, sDuplicateChoice, 2, dex_Database, compMon, 1, sMessage);
                        if (strcmp(sInput, sDuplicateChoice[0]) == 0)   // if they entered "Yes"
                        {
                            tempMon.nCaught = dex_Database[compMon].nCaught;
                            dex_Database[compMon] = tempMon;    // update the compMon(index) with its new value
                            setMessage(sMessage, "Fakemon entry updated");

                            // this happens if there are any duplicates, thus prompting for an overwrite. 
                            // an overwrite should affect the names in the box of caughtMons
                            // updates the name and short name of the captured mons 
                            for (nCurrCaughtMon = 0; nCurrCaughtMon < nCapturedMons; nCurrCaughtMon++)
                            {
                                if (caughtMons[nCurrCaughtMon].index_Dex == compMon)
                                {
                                    strcpy(caughtMons[nCurrCaughtMon].sShort_Name, dex_Database[compMon].sShort_Name);
                                    strcpy(caughtMons[nCurrCaughtMon].sFull_Name, dex_Database[compMon].sFull_Name);
                                }
                            }
                        }
                        else    // if they answered no, this function end and the tempMon was not assigned to anything
                            setMessage(sMessage, "Fakemon entry discarded");
                    }
                    else if ((*nMonCreated) >= DEX_MAX)
                    {
                        // tell the user that the dex is full
                        setMessage(sMessage, "Dex is full. Type Cancel or the fakemon's Full name to remove.");
                        // if a fakemon was removed
                        if (removeDex(sInput, nInputSizes[0] + STR_MARGIN, dex_Database, nMonCreated, sMessage))
                        {
                            // adds the fakemon at the end of the fakedex since when removing a fakemon, it is shifted
                            // to the left, leaving the last unoccupied
                            // since nMonCreated is subtracted by 1 by removeDex, there is no need for -1 here
                            dex_Database[(*nMonCreated)] = tempMon;
                            // that is why we need to add 1 again since it was subtracted 1
                            (*nMonCreated)++;
                            setMessage(sMessage, "Freed up space and added new entry!");
                        }
                        else
                        {
                            setMessage(sMessage, "Fakemon entry discarded");
                        }

                    }
                    
                    newCreatedMon = 0;  // no new entry was made, they just updated/discarded/replaced an entry
                }
            }

            else if (!(isDuplicate))    // if the Full Name is not duplicated
            {
                // sInput is assigned to its rightful struct member
                if (currQuestion == 0)
                {
                    // checks if there are only letters in the name
                    // assign it if it is only letters
                    if (onlyLetters(sInput, strlen(sInput)))
                        strcpy(dex_Database[nCurrMon].sFull_Name, sInput);
                    // if not, get input again
                    else
                    {
                        sInput[0] = '\0';
                        setMessage(sMessage, "Only input letters in the English alphabet");
                        Input_Fail = 9;
                    }
                }
                
                else if (currQuestion == 1)
                {
                    // checks if the short name input's format is valid
                    // if it has SHORT_NAME_SIZE characters
                    if (strlen(sInput) == SHORT_NAME_SIZE)
                    {
                        // if there is only letters in the input (no symbols)
                        if (!onlyLetters(sInput, SHORT_NAME_SIZE))
                        {
                            Input_Fail = 9;
                            sInput[0] = '\0';
                            setMessage(sMessage, "Only input letters in the English alphabet");
                        }
                    }
                    // if it does not meet the specified length
                    else
                    {
                        // this will prompt the user to type a valid input
                        Input_Fail = 9;
                        sInput[0] = '\0';
                        snprintf(sMessage, STR_MSG_SIZE, "Please enter exactly %d Letters. Letters wil be capitalized.", 
                                    SHORT_NAME_SIZE);
                        sMessage[STR_MSG_SIZE - 1] = '\0';
                    }
                    
                    // if it did not get an error for format
                    if (!Input_Fail)
                    {
                        // converts the short name into upper case
                        toUpperWord(sInput, SHORT_NAME_SIZE);
                        // checks if there are any duplicates of the Short Name in the database
                        for (compMon = 0; compMon < (*nMonCreated) && !(isDuplicate); compMon++)
                        {
                            // if in the updateDex function, we wouldnt want to trigger a isDuplicate, if the sInput
                            // is its own data (if they do not want to change the contents)
                            if (compMon != nCurrMon)
                            {
                                if (strcmp(sInput, dex_Database[compMon].sShort_Name) == 0)
                                {
                                    Input_Fail = 3;
                                    setMessage(sMessage, 
                                                "Duplicate short name in the database! Enter a unique short name.");
                                }
                            }
                            
                        }
                    }
                    

                    // if there are no other errors, asssign it. 
                    if (!(Input_Fail))
                    {
                        strcpy(dex_Database[nCurrMon].sShort_Name, sInput);
                    }
                }
                
                else if (currQuestion == 2)
                    strcpy(dex_Database[nCurrMon].sDescript, sInput);
                
                // for gender's input case, the developer did not modify the getInput command to alter the Input_Fail to 
                // output as 2, it cannot check if the user input is in the choices (M, F, U)since that needs an argument for the 
                // 3rd parameter, which in this case, set to NULL, since the full and short name and description does not
                // need choices. Since this is the only time that this particular problem will arise, 
                // there is no need to alter the getInput function as this will complicate the getInput function.
                else if (currQuestion == 3)
                {
                    if (sInput[0] == 'M' || sInput[0] == 'F' || sInput[0] == 'U')
                        dex_Database[nCurrMon].cGender = sInput[0];
                    else // if other letters are inputted
                    {
                        Input_Fail = 2; // user input not in the choices
                        strcpy(sMessage, "Invalid input! You can only enter 'M', 'F', or 'U'" );    
                    }
                }

                // if the input was successful, proceed to the next question
                if (!(Input_Fail))
                    currQuestion++;
            }
            
        }
    }

    if (isUpdateDex)
    {
        // this only happens if the input is from updateDex (via updateDex)
        // no need to update what's in the caughtMons if it was a new fakedex entry since to start with
        // it would be impossible to put a new entry in that box without first going to exploration
        // updates the name and short name of the captured mons 
        for (nCurrCaughtMon = 0; nCurrCaughtMon < nCapturedMons; nCurrCaughtMon++)
        {
            if (caughtMons[nCurrCaughtMon].index_Dex == nCurrMon)
            {
                strcpy(caughtMons[nCurrCaughtMon].sShort_Name, dex_Database[nCurrMon].sShort_Name);
                strcpy(caughtMons[nCurrCaughtMon].sFull_Name, dex_Database[nCurrMon].sFull_Name);
            }
        }
    }

    if (newCreatedMon)
        strcpy(sMessage, "Succesfully added a new entry!");

    return newCreatedMon;
}

void updateDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *Fakedex, int *nMonCreated, 
                box_type caughtMons[], int nCapturedMons, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    // variable used to exit the function
    int toCancel = 0;

    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Enter 'Cancel' to go back."); 
        // message that would be sent to the user at the bottom screen.
    

    // there are 2 modes.
    // 1: if in search mode. searching if the name entered matches to any of the fakemon entries
    // 2: edit mode. edits each members of the fakemon struct
    // default to mode 1
    int Mode = 1;

    // variable used to know if the input full name matches to any thing on the data base.
    // default to no;
    int isMatch = 0;
    // variable used to loop through the fakedex, search if there is match
    int currMon;
    
    // for confirmation if they want to update the dex
    stringChoice confirmChoices[2] = {"Yes", "Cancel"};

    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Update_Dex);


        // main content
        // if trying to get fakemon name
        if (Mode == 1)
        {
            printFillerLines(HEIGHT / 2, &currRow);
            printText("Which Fakemon do you want to update? Enter its full name.", 'c', &currRow);

            printBottomRemain(currRow);

            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // getInput returns if the user input is valid or not.
            // refer to getInput implementation (util.c) for the list of possible error msg returns
            // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
            Input_Fail = getInput(sInput, nInputSizes[0], NULL, 0, sMessage);
            // 0 index is for the full name size since the full name is the one being asked
            // if the input fails, it will prompt the user to type an input again
            // only valid inputs will be returned (sInput)

            // if the string length is accepted
            if (!(Input_Fail))
            {   
                // if the user typed cancel
                if (strcmp(sInput, "Cancel") == 0)
                {
                    toCancel = 1;   // end loop and escape function
                    sInput[0] = '\0';
                }

                // if they did not type cancel
                if (!(toCancel))
                {
                    for (currMon = 0; currMon < (*nMonCreated) && !(isMatch); currMon++)
                    {
                        // if the input matches with one of the fakemon
                        if (strcmp(Fakedex[currMon].sFull_Name, sInput) == 0)
                        {
                            isMatch = 1;
                            currMon--;  // since currMon will be incremented at the exit of the for loop
                            Mode = 2;   // change mode to update mode
                        }
                    }

                    if (!isMatch)
                    {
                        setMessage(sMessage, "No fakemon found with that name! type 'Cancel' to go back.");
                        Input_Fail = 2;
                    }
                }
                
            }
        }

        else if (Mode == 2)
        {
            // confirm if they want to update this fakemon
            setMessage(sMessage, "Are you sure you want to update this fakemon's information?");
            viewMon(sInput, nInputSizes[0], confirmChoices, 2, Fakedex, currMon, 1, sMessage);
            // sInputSize[0] is the size since "Yes" and "Cancel" are the only one being asked
            // the STR_FNAME_SIZE is enough for that

            // if they said yes
            if (strcmp(sInput, confirmChoices[0]) == 0) // if they confirmed
            {
                if (addDex(sInput, nInputSizes, nInputQty, Fakedex, nMonCreated, caughtMons, nCapturedMons, 
                            sMessage, currMon))
                {
                    setMessage(sMessage, "Fakemon entry Updated!");
                }
                else
                {
                    // if it were an overwrite proceedure, sMessafe will come from addDex()
                }
            }
            else
            {
                setMessage(sMessage, "Update entry cancelled.");
            }
            // escape the function after Mode 2
            toCancel = 1;
        }
    } while (!(toCancel));
}

int removeDex(stringIn sInput, int nInputSize, mon_type *Fakedex, int *nMonCreated, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    // variable used to exit the function
    int toCancel = 0;

    // variable used to know if a fakemon was removed. default to no
    int isRemoved = 0;

    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Type fakemon's full name or enter 'Cancel' to go back."); 
        // message that would be sent to the user at the bottom screen.
    

    // there are 2 modes.
    // 1: if in search mode. searching if the name entered matches to any of the fakemon entries
    // 2: edit mode. edits each members of the fakemon struct
    // default to mode 1
    int Mode = 1;

    // variable used to know if the input full name matches to any thing on the data base.
    // default to no;
    int isMatch = 0;
    // variable used to loop through the fakedex, search if there is match
    int currMon;
    
    // for confirmation if they want to update the dex
    stringChoice confirmChoices[2] = {"Yes", "Cancel"};

    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Remove_Dex);


        // main content
        // if trying to get fakemon name
        if (Mode == 1)
        {
            printFillerLines(HEIGHT / 2, &currRow);
            printText("Which Fakemon do you want to update? Enter its full name.", 'c', &currRow);

            printBottomRemain(currRow);

            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // getInput returns if the user input is valid or not.
            // refer to getInput implementation (util.c) for the list of possible error msg returns
            // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
            Input_Fail = getInput(sInput, nInputSize, NULL, 0, sMessage);
            // nInputSize is the full name size.
            // if the input fails, it will prompt the user to type an input again
            // only valid inputs will be returned (sInput)

            // if the string length is accepted
            if (!(Input_Fail))
            {   
                // if the user typed cancel
                if (strcmp(sInput, "Cancel") == 0)
                {
                    toCancel = 1;   // end loop and escape function
                    sInput[0] = '\0';
                }

                // if they did not type cancel
                if (!(toCancel))
                {
                    for (currMon = 0; currMon < *(nMonCreated) && !(isMatch); currMon++)
                    {
                        // if the input matches with one of the fakemon
                        if (strcmp(Fakedex[currMon].sFull_Name, sInput) == 0)
                        {
                            isMatch = 1;
                            currMon--;  // since currMon will be incremented at the exit of the for loop
                            Mode = 2;   // change mode to update mode
                        }
                    }
                    
                    // if nothing matched
                    if (!isMatch)
                    {
                        setMessage(sMessage, "No fakemon found with that name! Try again or type 'Cancel'.");
                        Input_Fail = 2;
                    }
                }
                
            }
        }

        // if trying to delete (based on the input fakemon)
        else if (Mode == 2)
        {
            if (Fakedex[currMon].nCaught == 0)  // if the fakemon is not yet caught
            {
                // confirm if they want to update this fakemon
                setMessage(sMessage, "Are you sure you want to delete this fakemon");
                viewMon(sInput, nInputSize, confirmChoices, 2, Fakedex, currMon, 1, sMessage);
                // sInputSize is the size since "Yes" and "Cancel" are the only one being asked
                // the STR_FNAME_SIZE is enough for that
                // that's pretty big already

                // if they said yes
                if (strcmp(sInput, confirmChoices[0]) == 0) // if they confirmed
                {
                    // shifts all entries to the left by one starting from currMon
                    // this essentially deletes the currMon by overwriting it by its next entry
                    // only go up until < nMonCreated - 1 since it's going to have a segmentation fault
                    for (; currMon < (*nMonCreated) - 1; currMon++)
                    {
                        strcpy(Fakedex[currMon].sFull_Name, Fakedex[currMon + 1].sFull_Name);
                        strcpy(Fakedex[currMon].sShort_Name, Fakedex[currMon + 1].sShort_Name);
                        strcpy(Fakedex[currMon].sDescript, Fakedex[currMon + 1].sDescript);
                        Fakedex[currMon].cGender = Fakedex[currMon + 1].cGender;
                        Fakedex[currMon].nCaught = Fakedex[currMon + 1].nCaught;
                    }

                    // delete the last entry since it's already copied(shifted) to the left
                    // nMonCreated starts at index 1
                    (Fakedex[*(nMonCreated) - 1].sFull_Name)[0] = '\0';
                    (Fakedex[*(nMonCreated) - 1].sShort_Name)[0] = '\0';
                    (Fakedex[*(nMonCreated) - 1].sDescript)[0] = '\0';
                    Fakedex[*(nMonCreated) - 1].cGender = 0;
                    Fakedex[*(nMonCreated) - 1].nCaught = 0;
                    (*nMonCreated)--;

                    setMessage(sMessage, "Fakemon deleted.");
                    // set the flag to yes. which means a fakemon was removed.
                    isRemoved = 1;
                }
                else
                {
                    setMessage(sMessage, "Fakemon not deleted.");
                }
                // escape the function after Mode 2
                toCancel = 1;
            }
            else    // if already caught
            {
                toCancel = 0;
                Mode = 1;       // repeat and get full name again
                setMessage(sMessage, "Cannot remove caught Fakemon. Try again or type 'Cancel'");
                sInput[0] = '\0';
            }
            
        }
    } while (!(toCancel));

    return isRemoved;
}

int viewDex(stringIn sInput, int nInputSize, mon_type *Fakedex, int currPopulation, stringMsg sMessage)
{
    int nIntIn;     // since the input that would be used here is integers, this would be the buffer for it

    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT


    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        setMessage(sMessage, "What would you like to do?");   // message that would be sent to the user


    // variables used for page display functions
    int currPage = 0;
    int nMaxPage;
    // used to display the index number of fakemon
    int currMon = 0;

    // initializinf the max page (based on the number of elements that are in Fakedex[] already)
    nMaxPage = currPopulation / MON_PAGE;
    if ((currPopulation % MON_PAGE) != 0)   // ceiling operation. (if there is a decimal in the quotient, round it up always)
        nMaxPage++;
    if (nMaxPage == 0)
        nMaxPage = 1;
    

    // this is the value to be returned. it is the index of the fakemon in Fakedex[]
    int mon_Sel = -1; 

    // 3 modes. 
    // 0 = selecting whether they would like to go back, navigate, or select a fakemon
    // 1 = navigate (change page) ;; 2 = select a fakemon
    int Mode = 0;

    // local array of choices if mode = 0
    stringChoice modeChoices[3] = {"Navigate", "Select", "Cancel"};


    // these variables are used to format the diplay TUI of this page -----

    const int nLeftPad = 3;         // this page (view dex) has a unique left and right padding from the rest
    const int nRightPad = 2;        // it has much larger padding
    const int nSpaceBetween = 3;    // space between the name and description
   
    // max space given to encode the description of the fakemon in one line. the constant 3 here is for "<number>. ", 
    // which has a maximum of 3 chars
    int nDescNumMax = WIDTH - LEFT_PAD - nLeftPad - 3 - FULL_NAME_SIZE - nSpaceBetween - nRightPad  - RIGHT_PAD;

    // used to know the extra number space. since there is a constant '3' for the number, it is possible to have 
    // 2 digits or 3 digit numbers. this is where this comes into place
    int nDeviation;
    
    // since printText function cannot handle variable outputs (i.e. %d place holders and %s)
    // strcat() is used to place the contents of each line to the outputBuffer. After placing all the contents
    // of a singe line to the outputBuffer, it is printf()ed to the output screen. 
    // snprintf could be used, but it would still need to use strcat(). for uniformity, strcat was used to
    // create the single line in a buffer, which is then printed out.
    const int OutputBufMax = WIDTH;
    char outputBuffer[OutputBufMax];
    char sDescBuffer[nDescNumMax];

    // for loops with strcat() is used to concatinate the number of Pad " " that would be printed
    int currPad;

    // used to know the lacking number of spaces to print to reach FULL_NAME_SIZE
    int nNameLack;

    // buffer used to print the current number of the fakemon <number>.
    // this is 6 since the maximum digit is 3 + . + space + null
    char sNumHolder[6];
    
    // these are created to easily change the header text of each column. right now they say: Name      Description
    const int Name_HDR_Len = 5;
    char Name_HDR[Name_HDR_Len];
    strcpy(Name_HDR, "Name");
    const int Desc_HDR_Len = 12;
    char Desc_HDR[Desc_HDR_Len];
    strcpy(Desc_HDR, "Description");

    // up until here -----


    do {    // loop until the user has slected a fakemon or typed "Cancel"

        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_View_Dex); 


        // main content of the TUI
        printFillerLines(1, &currRow);
        printText("Fakemon Entries", 'c', &currRow);
        snprintf(outputBuffer, OutputBufMax, "%d of %d", (currPage + 1), nMaxPage); // putting the page info in buffer
        printText(outputBuffer, 'c', &currRow); // printing the page info

        printFillerLines(1, &currRow);

        outputBuffer[0] = '\0';     // initializing the buffer since strcat will be used
        // putting nLeftPad number of spaces in buffer (to print the left pad)
        for (currPad = 0; currPad < nLeftPad + 3; currPad++)
            strcat(outputBuffer, " ");

        // putting header text
        strcat(outputBuffer, Name_HDR);
        // putting appropriate number of spaces between the 2 text headers
        for (currPad = 0; currPad < nSpaceBetween + (FULL_NAME_SIZE - (Name_HDR_Len - 1)); currPad++)
            strcat(outputBuffer, " ");
        strcat(outputBuffer, Desc_HDR);
        // printing the bufffer containing the header text
        printLeftStart();
        printf("%s", outputBuffer);
        printRightRemain(strlen(outputBuffer));
        currRow++;

        printFillerLines(1, &currRow);


        // printing of fakedex entries
        for (currMon = 0; (currMon < MON_PAGE) && (currMon + (currPage * MON_PAGE)) < currPopulation ; currMon++)
        {
            // strcat will be used in the buffer so in is initialized again
            outputBuffer[0] = '\0'; 

            // sNumHolder is the buffer for the number of the current pokemon entry
            // (currMon + 1) + (currPage * MON_PAGE) displays what index + 1 the fakemon is based on the current page
            // it is put here up front so that nDescMax can be calibrated (it will use strlen(sNumHolder))
            snprintf(sNumHolder, 6, "%d.", (currMon + 1) + (currPage * MON_PAGE));
            
            // since in the nDescNumMax, the constant is 3 (expected digit is only 1)
            // this fixes that.
            nDeviation = strlen(sNumHolder) - 2;

            // prepping the description of the current fakemon entry. if the length of the fakemon's description exceeds 
            // the nDescNumMax - 4 (for the ...\0) it is truncated and replaced with an ellipsis ...
            // nore: snprintf only prints n-1 to buffer
            if (Fakedex[currMon + (currPage * MON_PAGE)].nCaught)
            {
                snprintf(sDescBuffer, nDescNumMax - 3, Fakedex[currMon + (currPage * MON_PAGE)].sDescript);
                // since sDescBuffer is not initialized to all 0, making sure it it has null
                // this only applies if the nDescBuffer is saturated
                sDescBuffer[nDescNumMax - 4] = '\0';    
                if (strlen(Fakedex[currMon + (currPage * MON_PAGE)].sDescript) > nDescNumMax - 4)
                    strcat(sDescBuffer, "..."); // if it is truncated, put ellipsis on it
            }
            // if the fakemon is still uncaught, just display ??? in the description
            else
            {
                snprintf(sDescBuffer, nDescNumMax, "???");
            }
            
            
            // this is where the printing of the line starts.
            // putting the necessary number of pad to the buffer first 
            for (currPad = 0; currPad < nLeftPad; currPad++)
                strcat(outputBuffer, " ");

            strcat(outputBuffer, sNumHolder);   // putting the sNumHolder to the outputBuffer
            // space after the number
            strcat(outputBuffer, " ");

            // putting to the buffer the full name of the current fakemon entry
            strcat(outputBuffer, Fakedex[currMon + (currPage * MON_PAGE)].sFull_Name);

            // putting  the appropriate number of whitespaces after the name so that the description would 
            // have a uniform start position. nNameLack is the number of whitespaces lacking to reach the length
            // FULL NAME SIZE. Full name cannot overflow since in the add dex function, characters more
            // than FULL_NAME_SIZE is rejected
            nNameLack = FULL_NAME_SIZE - strlen(Fakedex[currMon + (currPage * MON_PAGE)].sFull_Name);
            // this is where the nDeviation is used. If there are 2 digits, nDeviation will be 1
            for (currPad = 0; currPad < nSpaceBetween + nNameLack - nDeviation; currPad++)
                strcat(outputBuffer, " ");
            
            // putting the preppared sDescBuffer to the output buffer
            strcat(outputBuffer, sDescBuffer);

            // printing the outputBuffer. one fakemon per line.
            printLeftStart();
            printf("%s", outputBuffer);
            printRightRemain(strlen(outputBuffer));
            currRow++;
            printFillerLines(1, &currRow);
        }   // repeat this line by line until all fakemon entries are exhausted or when MON_PAGE number of fakemon
            // already populates the page

        
        // after printing the fakemon entries, print the choices orlower part of the TUI
        if (Mode == 0)
        {
            // prints the choices of modes
            printChoices(modeChoices, 3, 3, 1, 'c', &currRow);

            printBottomRemain(currRow);
            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.


            getInput(sInput, nInputSize, modeChoices, 3, sMessage);
            if (strcmp(sInput, modeChoices[0]) == 0)    // navigate mode
            {
                Mode = 1;
                setMessage(sMessage, "Which Page woud you like to go? Enter -1 to cancel");
            }
            else if (strcmp(sInput, modeChoices[1]) == 0)   // select mode
            {
                Mode = 2;
                setMessage(sMessage, "Type the Fakemon's number you want to select. Enter -1 to cancel");
            }
            // if cancel is typed, the whole loop is stopped
        }
        else if (Mode == 1) // navigate
        {
            // prints bottom part of the box and the system message too, if there are any.
            printBottomRemain(currRow);
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // since sInput will return a string and the required data is int, sInput is turned into int using strtoll
            getInput(sInput, nInputSize, NULL, 0, sMessage);
            nIntIn = strtoll(sInput, NULL, 10); // strtoll returns 0 if conversion is unsuccesful
            if ((nIntIn < 1 && nIntIn != -1) || nIntIn > nMaxPage)  // if strtoll returned error or the input is not in range
            {                                                       // but excluding -1 (for escape function)
                setMessage(sMessage, "Only input the avaialble page number or -1.");
                sInput[0] = '\0';
            }
            else if (nIntIn == -1)  // escape function. returns to mode 0
            {
                Mode = 0;
                setMessage(sMessage, "What would you like to do?");
            }
            else    // or if the user inputted a valid number, page is set to that and mode returns to 0
            {
                currPage = nIntIn - 1;  // currPage starts at index 0
                Mode = 0;
                setMessage(sMessage, "What would you like to do?");
            }
            
        }
        else if (Mode == 2) // select
        {
            // prints bottom part of the box and the system message too, if there are any.
            printBottomRemain(currRow);
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // since sInput will return a string and the required data is int, sInput is turned into int using strtoll
            getInput(sInput, nInputSize, NULL, 0, sMessage);
            nIntIn = strtoll(sInput, NULL, 10); // strtoll returns 0 if conversion is unsuccesful
            // if the input is unsuccesful, negative (exculdding -1 for escape), not in range of the current fakemon
            // numbers in the page, or greater than the number of fakemon entries
            if ((nIntIn < ((currPage * MON_PAGE) + 1) && nIntIn != -1) || nIntIn > (currPage * MON_PAGE) + MON_PAGE ||
                    nIntIn > currPopulation)
            {
                setMessage(sMessage, "Only input the Fakemon number in this page or -1.");
                sInput[0] = '\0';
            }
            else if (nIntIn == -1)  // escape function. returns to mode 0 
            {
                Mode = 0;
                setMessage(sMessage, "What would you like to do?");
            }
            else    // succesful input. mon_Sel is returned.
            {
                mon_Sel = nIntIn - 1; // mon_Sel starts at 0 index
            }
        }

    } while(strcmp(sInput, modeChoices[2]) != 0 && mon_Sel < 0);    // while sInput != "Cancel" && mon_Sel is negative
                                                                    // (there are no negative in the Fakedex array)
    
    if (strcmp(sInput, modeChoices[2]) == 0)    // if the user typed cancel
    {
        mon_Sel = -1;       // make sure that there were no selected fakemon
        sInput[0] = '\0';   // "Cancel" will be left in the sInput buffer which could cause compplications for
    }                       // other functions. that is why after typing, sInput is cleaned.

    return mon_Sel;
}

int encounter(stringIn sInput, int nInputSize, stringChoice sEncounterChoices[], int nEncounterChoicesSize, 
                mon_type *Fakedex, int nMonCreated, box_type caughtMons[], int *nCapturedMons, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.


    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "What would you like to do?");   // message that would be sent to the user at the bottom screen.
    
    // choices for the viewMon
    stringChoice sViewMonChoices[1] = {"Cancel"};
    
    // buffer that will be printed out in printText function.
    // LIMITATIONS: The text should not be 99
    char outputBuffer[100] = "";

    // the randomly selected fakemon.
    int nChosenMon = rand() % nMonCreated;

    // constant 8 since the longest word is UNKNOWN
    char sGenderBuffer[8];

    // since the chosen mon is already set, we can safely convert the gender character 
    // the gender in the struct only has struct so I have to convert it to string
    if (Fakedex[nChosenMon].cGender == 'M')
        strcpy(sGenderBuffer, "MALE");
    else if (Fakedex[nChosenMon].cGender == 'F')
        strcpy(sGenderBuffer, "FEMALE");
    else if (Fakedex[nChosenMon].cGender == 'U')
        strcpy(sGenderBuffer, "UNKNOWN");

    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Encounter);

        printFillerLines(HEIGHT / 4, &currRow);
        snprintf(outputBuffer, 100, "A wild %s (%s) has appeared!", Fakedex[nChosenMon].sFull_Name, 
                    sGenderBuffer);
        printText(outputBuffer, 'c', &currRow);
        printFillerLines(1, &currRow);
        displayArt(ART_Mon_Sprite, 7, &currRow);
        printFillerLines(2, &currRow);
        printChoices(sEncounterChoices, nEncounterChoicesSize, nEncounterChoicesSize, 1, 'c', &currRow);

        printBottomRemain(currRow);

        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

        // getInput returns if the user input is valid or not.
        // refer to getInput implementation (util.c) for the list of possible error msg returns
        // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
        Input_Fail = getInput(sInput, nInputSize, sEncounterChoices, nEncounterChoicesSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)
    } while (Input_Fail);

    // if they decided to catch
    if (strcmp(sInput, sEncounterChoices[0]) == 0)
    {
        // CATCH_RATE% chance to catch
        if ((rand() % 100) < CATCH_RATE)
        {
            setMessage(sMessage, "Fakemon Caught!");
            // assignin appropriate data to each member of the element in captured mons
            caughtMons[*nCapturedMons].nSlot = *nCapturedMons;
            strcpy(caughtMons[*nCapturedMons].sShort_Name, Fakedex[nChosenMon].sShort_Name);
            strcpy(caughtMons[*nCapturedMons].sFull_Name, Fakedex[nChosenMon].sFull_Name);
            caughtMons[*nCapturedMons].index_Dex = nChosenMon;

            (*nCapturedMons)++;

            // if not yet caught, make the caught field caught
            if (!(Fakedex[nChosenMon].nCaught))
            {
                // makes the fakedex entry as captured
                Fakedex[nChosenMon].nCaught = 1;

                viewMon(sInput, nInputSize, sViewMonChoices, 1, Fakedex, nChosenMon, 1, sMessage);
                // since "Cancel" will be typed, the input buffer needs to be cleaned since it might unintentionally
                // break/exit a loop.
                sInput[0] = '\0';
            }

            return nChosenMon;
        }
        else
        {
            setMessage(sMessage, "Fakemon got away!");
            return -1;
        }
    }
    else 
    {
        setMessage(sMessage, "Succesfully ran away");
        return -1;
    }
}

void exploration(stringIn sInput, int nInputSize, stringChoice sExploreChoices[], int nExploreChoicesSize, 
                    int *ActiveCell, int nMonCreated, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0')   // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Type out instructions and explore all you want!"); 
        // message that would be sent to the user at the bottom screen

    // used to know if an encounter is possible. default to no since it should be impossible to get an 
    // encounter on the first appearance
    int toEncounter = 0;

    // used to know if the trainer has encountered a fakemon
    int Encountered = 0;

    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_EXPLORATION);

        // displays the tree art
        displayArt(ART_Tree, 10, &currRow);
        // prints the grass tiles based in the ActiveCell(position)
        printGrass(*ActiveCell, &currRow);
        // this will only trigger if the user has succesfully issued a FORWARD or BACHWARD command
        if (toEncounter)
        {
            // rand() % 100 generates a pseudo-random number with a range of [0, 99]
            // generating a number that is less than 40 (meaning [0, 39]) means that 40 of the 100
            // numbers would return true. that is a 40% chance to be true.
            if ((rand() % 100) < ENCOUNTER_RATE)
                Encountered = 1;

            // resets it back to 0 to make sure that this if statement will only trigger
            // on a succesful FORWARD or BACKWARD command 
            toEncounter = 0;
        }
        printFillerLines(1, &currRow);
        // FORWARD, BACKWARD, CANCEL
        printChoices(sExploreChoices, nExploreChoicesSize, nExploreChoicesSize, 1, 'c', &currRow);

        printBottomRemain(currRow);


        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

        // if the user has already encountered a fakemon, there is no need to get input once again
        if (!Encountered)
        {
            // getInput returns if the user input is valid or not.
            // refer to getInput implementation (util.c) for the list of possible error msg returns
            // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
            Input_Fail = getInput(sInput, nInputSize, sExploreChoices, nExploreChoicesSize, sMessage);
            // if the input fails, it will prompt the user to type an input again
            // only valid inputs will be returned (sInput)


            // FORWARD
            if (strcmp(sInput, sExploreChoices[0]) == 0)
            {
                // if not at the boundary
                if (*(ActiveCell) < EXPLORE_COLUMN - 1)
                {
                    (*ActiveCell)++;
                    sInput[0] = '\0';
                    snprintf(sMessage, STR_MSG_SIZE, "Moved %s", sExploreChoices[0]);
                    sMessage[STR_MSG_SIZE - 1] = '\0';
                    // an encounter is only possible if there are any fakemon in the fakedex
                    if (nMonCreated)
                        toEncounter = 1;
                }
            }
            // BACKWARD
            else if (strcmp(sInput, sExploreChoices[1]) == 0)
            {
                // if not at the boundary
                if (ActiveCell > 0)
                {
                    (*ActiveCell)--;
                    sInput[0] = '\0';
                    snprintf(sMessage, STR_MSG_SIZE, "Moved %s", sExploreChoices[1]);
                    sMessage[STR_MSG_SIZE - 1] = '\0';
                    // an encounter is only possible if there are any fakemon in the fakedex
                    if (nMonCreated)
                        toEncounter = 1;
                }
            }
        }

    } while ((Input_Fail || (strcmp(sInput, sExploreChoices[nExploreChoicesSize - 1] ) != 0)) && !(Encountered));
    // loop if there are input errors, if the input is not cancel, and the user has not encountered any fakemon
    
}

void viewBox(stringIn sInput, int nInputSize, stringChoice sModeChoices[], int nModeChoicesSize, 
                mon_type *Fakedex, box_type caughtMons[], int *nCapturedMons, stringMsg sMessage)
{
    int nIntIn = 0;     // since the input that would be used here is integers, this would be the buffer for it

    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        setMessage(sMessage, "What would you like to do?");   // message that would be sent to the user


    // variables used for page display functions
    int currPage = 0;
    int nMaxPage;

    // initializinf the max page (based on the number of elements that are in Fakedex[] already)
    nMaxPage = *nCapturedMons / BOX_MON_PAGE;
    // ceiling operation. (if there is a decimal in the quotient, round it up always)
    if ((*nCapturedMons % BOX_MON_PAGE) != 0)  
        nMaxPage++;
    if (nMaxPage == 0)
        nMaxPage = 1;
    
    // temporary max page for when searching algorithms comes into place. 
    // nMax page will change if search algorithm is done
    // initialized to nMaxPage since at loadup, it is not yes on search mode
    int nTempMaxPage = nMaxPage;

    // number of cells per page
    int cellPerPage = NUM_BOX_COLUMN * NUM_BOX_ROW;

    // it is the index of the fakemon in Fakedex[]
    int mon_Sel = -1; 

    // used in select mode to know if a fakemon is found
    int isFound = 0;

    // 3 modes. 
    // 0 = selecting whether they would like to go back, navigate, or select a fakemon
    // 1 = navigate (change page)
    // 2 = select a fakemon
    // 3 = Search by full name
    // 4 = search by short name
    // 5 = sort
    // 6 = fakemon has been selected. 
    // 7 = release mode. confirm if they want to release
    int Mode = 0;

    // for mode = 6
    stringChoice selectedChoices[3] = {"View Entry", "Release", "Cancel"};

    // choices for viewMon
    stringChoice viewMonChoice[1] = {"Cancel"};

    // choices for release
    stringChoice releaseConfirmChoices[2] = {"Yes", "No"};

    // choices for sort mode
    stringChoice sSortChoices[3] = {"Ascending", "Descending", "Cancel"};

    // choices when in search mode and selecting mode (Mode = 0)
    // Navigate, Select, and Cancel
    stringChoice sRestrictModeChoices[3] = {"Navigate", "Select", "Cancel"};

    // variable used to determine if in search opeartion
    // 3 if search mode for full name
    // 4 if search mode for short name
    int isSearchMode = 0;

    // arrays that store which fakemons are searched
    box_type searchedCaughtMons[BOX_MAX] = {{0}};

    // how many vaelements in searchedCaughtMons
    int searchedQty = 0;

    // indicates what type of sort mode to use
    // 0 = none selected yed
    // 1 = Ascending
    // 2 = Descending
    int nSortMode = 0;

    // variable used in a for loop to seek out the other arrays (selection sort)
    int nSeeker;
    // used to know which value is the lowest/highest
    int nSwap_Slot;
    // used as a place holder for swaping
    box_type tempMon;

    // used in for loops for checking if input is valid / is in the page
    int currMon;
    
    // since printText function cannot handle variable outputs (i.e. %d place holders and %s)
    // strcat() is used to place the contents of each line to the outputBuffer. After placing all the contents
    // of a singe line to the outputBuffer, it is printf()ed to the output screen. 
    // snprintf could be used, but it would still need to use strcat(). for uniformity, strcat was used to
    // create the single line in a buffer, which is then printed out.
    const int OutputBufMax = WIDTH;
    char outputBuffer[OutputBufMax];

    
    do
    {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Box); 

        // main content
        printText("Welcome to your box! Here lies your caught Fakemons.", 'c', &currRow);
        snprintf(outputBuffer, OutputBufMax, "%d of %d", (currPage + 1), nTempMaxPage);
        printText(outputBuffer, 'c', &currRow);
        printFillerLines(1, &currRow);
        
        // if in search mode, print the only searched fakemons
        if (isSearchMode)
            printCaughtMons(searchedCaughtMons, searchedQty, currPage, &currRow);
        else if (!isSearchMode)
            printCaughtMons(caughtMons, *nCapturedMons, currPage, &currRow);

        // Picking type mode
        if (Mode == 0)
        {
            if (!isSearchMode)
            {
                printChoices(sModeChoices, nModeChoicesSize, nModeChoicesSize / 2, 2, 'c', &currRow);
                printBottomRemain(currRow);

                // prints bottom part of the box and the system message too, if there are any.
                printRemark(sMessage);
                sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

                Input_Fail = getInput(sInput, nInputSize, sModeChoices, nModeChoicesSize, sMessage);
            }
            // serach mode has restricted choices. only navigate, select, and cancel
            else if (isSearchMode)
            {
                printChoices(sRestrictModeChoices, 3, 3, 1, 'c', &currRow);
                printBottomRemain(currRow);
                // prints bottom part of the box and the system message too, if there are any.
                printRemark(sMessage);
                sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

                Input_Fail = getInput(sInput, nInputSize, sRestrictModeChoices, 3, sMessage);
            }
            
            

            // if the user input is valid
            if (!(Input_Fail))
            {
                // Navigate
                if (strcmp(sInput, sModeChoices[0]) == 0)
                {
                    Mode = 1;
                    setMessage(sMessage, "What page would you like to go? Type -1 to Cancel");
                }
                // Select
                else if (strcmp(sInput, sModeChoices[1]) == 0)
                {
                    Mode = 2;
                    setMessage(sMessage, "Which fakemon would you like to pick?");
                }
                // Full Name Search
                else if (strcmp(sInput, sModeChoices[2]) == 0)
                {
                    Mode = 3;
                    setMessage(sMessage, "Enter your fakemon's full name or type Cancel");
                }
                // Short Name Search
                else if (strcmp(sInput, sModeChoices[3]) == 0)
                {
                    Mode = 4;
                    setMessage(sMessage, "Enter your fakemon's short name or type Cancel");
                }
                // Sort
                else if (strcmp(sInput, sModeChoices[4]) == 0)
                {
                    Mode = 5;
                    setMessage(sMessage, "Short Name Sort. Which sort mode would you like to do?");
                }
                // user typed cancel while in search mode. will returnj to mode select
                // but not in search mode anymore
                else if (strcmp(sInput, sModeChoices[5]) == 0 && isSearchMode)
                {
                    Mode = 0;
                    isSearchMode = 0;
                    // since the sInput still has "Cancel" it will stop the loop
                    // that is why it is necessary to clean it
                    sInput[0] = '\0';
                    setMessage(sMessage, "What would you like to do?");

                    // since it might be used again, the searchedCaughtMons is reseted
                    for (currMon = 0; currMon < searchedQty; currMon++)
                    {
                        searchedCaughtMons[currMon].nSlot = 0;
                        searchedCaughtMons[currPage].index_Dex = 0;
                        searchedCaughtMons[currMon].sShort_Name[0] = '\0';
                        searchedCaughtMons[currMon].sFull_Name[0] = '\0';
                    }
                    searchedQty = 0;

                    // reset the number of page to original
                    nTempMaxPage = nMaxPage;
                }
            }
        }
        
        // Navigate mode
        else if (Mode == 1)
        {            
            // prints bottom part of the box and the system message too, if there are any.
            printBottomRemain(currRow);
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // since sInput will return a string and the required data is int, sInput is turned into int using strtoll
            getInput(sInput, nInputSize, NULL, 0, sMessage);
            nIntIn = strtoll(sInput, NULL, 10); // strtoll returns 0 if conversion is unsuccesful
            if ((nIntIn < 1 && nIntIn != -1) || nIntIn > nTempMaxPage)  // if strtoll returned error or the input is not in range
            {                                                       // but excluding -1 (for escape function)
                setMessage(sMessage, "Only input the avaialble page number or -1.");
                sInput[0] = '\0';
            }
            else if (nIntIn == -1)  // escape function. returns to mode 0
            {
                Mode = 0;
                setMessage(sMessage, "What would you like to do?");
            }
            else    // or if the user inputted a valid number, page is set to that and mode returns to 0
            {
                currPage = nIntIn - 1;  // currPage starts at index 0
                Mode = 0;
                setMessage(sMessage, "What would you like to do?");
            }
        }

        // Select Mode
        else if (Mode == 2)
        {
            // prints bottom part of the box and the system message too, if there are any.
            printBottomRemain(currRow);
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // since sInput will return a string and the required data is int, sInput is turned into int using strtoll
            getInput(sInput, nInputSize, NULL, 0, sMessage);
            nIntIn = strtoll(sInput, NULL, 10); // strtoll returns 0 if conversion is unsuccesful

            if (nIntIn == 0)
            {
                setMessage(sMessage, "Only input the Fakemon number in this page or -1.");
                sInput[0] = '\0';
            }
            else
            {
                if (isSearchMode)
                {
                    // if the user decided not to select a fakemon
                    if (nIntIn == -1)
                    {
                        // turns back to mod e select, but searchMode is still active
                        Mode = 0;
                        setMessage(sMessage, "What would you like to do?");
                    }
                    // if the user typed the short name
                    else
                    {
                        // search every fakemon's short name only in the current page in searchedCaughtMons
                        for (currMon = currPage * cellPerPage; 
                            currMon < (currPage * cellPerPage) + cellPerPage && currMon < searchedQty; 
                            currMon++)
                        {
                            // if found
                            if (searchedCaughtMons[currMon].nSlot == (nIntIn - 1))
                            {
                                mon_Sel = searchedCaughtMons[currMon].nSlot;
                                isFound = 1;
                                Mode = 6;
                                snprintf(sMessage, STR_MSG_SIZE, "What would you like to do with SLOT: %d?", 
                                            caughtMons[mon_Sel].nSlot + 1);
                                sMessage[STR_MSG_SIZE - 1] = '\0';
                            }
                        }
                        // if not found
                        if (!isFound)
                        {
                            setMessage(sMessage, "Only input the Fakemon number in this page or -1.");
                            sInput[0] = '\0';
                        }
                    }
                    

                }
                else if (!isSearchMode)
                {
                    if (nIntIn == -1)
                    {
                        Mode = 0;
                        setMessage(sMessage, "What would you like to do?");
                    }
                    else
                    {
                        // search every fakemon's short name only in the current page
                        for (currMon = currPage * cellPerPage; 
                            currMon < (currPage * cellPerPage) + cellPerPage && currMon < *nCapturedMons; 
                            currMon++)
                        {
                            // if found
                            if (caughtMons[currMon].nSlot == (nIntIn - 1))
                            {
                                mon_Sel = caughtMons[currMon].nSlot;
                                isFound = 1;
                                Mode = 6;
                                snprintf(sMessage, STR_MSG_SIZE, "What would you like to do with SLOT: %d?", 
                                            caughtMons[mon_Sel].nSlot + 1);
                                sMessage[STR_MSG_SIZE - 1] = '\0';
                            }
                        }
                        // if not found
                        if (!isFound)
                        {
                            setMessage(sMessage, "Only input the Fakemon number in this page or -1.");
                            sInput[0] = '\0';
                        }
                    }
                    
                }
            }
        }
        
        // search by full name
        else if (Mode == 3)
        {
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(sInput, nInputSize, NULL, 0, sMessage);

            // if the user input is valid (the number of chars is accepted)
            if (!(Input_Fail))
            {
                // if the user typed cancel, go back to mode select
                if (strcmp(sInput, "Cancel") == 0)
                {
                    sInput[0] = '\0';
                    Mode = 0;
                    setMessage(sMessage, "What would you like to do?");
                }
                // if the user did not type cancel, loop through every fakemon in your box and 
                // see if it matches to any of the name
                else
                {
                    // since the slot number is the same as the index, currMon can be used
                    // as the variable to acces each element in the caughtMons array
                    // search the whole caughtMons array
                    for (currMon = 0; currMon < *nCapturedMons; currMon++)
                    {
                        // if it matches, appeand the member's contents to the searchCaughtMon's 
                        if (strcmp(caughtMons[currMon].sFull_Name, sInput) == 0)
                        {
                            isSearchMode = 3;
                            searchedCaughtMons[searchedQty].nSlot = caughtMons[currMon].nSlot;
                            searchedCaughtMons[searchedQty].index_Dex = caughtMons[currMon].index_Dex;
                            strcpy(searchedCaughtMons[searchedQty].sShort_Name, caughtMons[currMon].sShort_Name);
                            strcpy(searchedCaughtMons[searchedQty].sFull_Name, caughtMons[currMon].sFull_Name);
                            searchedQty++;
                        }
                    }

                    // if a fakemon was searched
                    if (isSearchMode)
                    {
                        // setting the right page number since the fakemon searched
                        // is lower than the whole box population
                        nTempMaxPage = searchedQty / (NUM_BOX_COLUMN * NUM_BOX_ROW);
                        if ((searchedQty % (NUM_BOX_COLUMN * NUM_BOX_ROW)) != 0)
                            nTempMaxPage++;
                        
                        setMessage(sMessage, "Found some fakemon!");
                    }
                    // if no fakemon was found
                    else if (!isSearchMode)
                    {
                        setMessage(sMessage, "No Fakemon found.");
                    }
                    // either way go back to mode select choices
                    Mode = 0;
                    sInput[0] = '\0';
                }
            }
        }

        // search by short name
        else if (Mode == 4)
        {
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(sInput, nInputSize, NULL, 0, sMessage);

            // if the user input is valid
            if (!(Input_Fail))
            {
                // if the user typed cancel, go back to mode select
                if (strcmp(sInput, "Cancel") == 0)
                {
                    sInput[0] = '\0';
                    Mode = 0;
                    setMessage(sMessage, "What would you like to do?");
                }
                // if the user did not type cancel, loop through every fakemon in your box and 
                // see if it matches to any of the name
                else
                {
                    // since the slot number is the same as the index, currMon can be used
                    // as the variable to acces each element in the caughtMons array
                    for (currMon = 0; currMon < *nCapturedMons; currMon++)
                    {
                        // if it matches, appeand the member's contents to the searchCaughtMon's 
                        if (strcmp(caughtMons[currMon].sShort_Name, sInput) == 0)
                        {
                            isSearchMode = 4;
                            searchedCaughtMons[searchedQty].nSlot = caughtMons[currMon].nSlot;
                            searchedCaughtMons[searchedQty].index_Dex = caughtMons[currMon].index_Dex;
                            strcpy(searchedCaughtMons[searchedQty].sShort_Name, caughtMons[currMon].sShort_Name);
                            strcpy(searchedCaughtMons[searchedQty].sFull_Name, caughtMons[currMon].sFull_Name);
                            searchedQty++;
                        }
                    }

                    // if a fakemon was searched
                    if (isSearchMode)
                    {
                        // setting the right page number since the fakemon searched
                        // is lower than the whole box population
                        nTempMaxPage = searchedQty / (NUM_BOX_COLUMN * NUM_BOX_ROW);
                        if ((searchedQty % (NUM_BOX_COLUMN * NUM_BOX_ROW)) != 0)
                            nTempMaxPage++;
                        
                        setMessage(sMessage, "Found some fakemon!");
                    }
                    // if no fakemon was found
                    else if (!isSearchMode)
                    {
                        setMessage(sMessage, "No Fakemon found.");
                    }
                    // either way go back to mode select choices
                    Mode = 0;
                    sInput[0] = '\0';
                }
            }
        }

        // sort by short name
        else if (Mode == 5)
        {

            printChoices(sSortChoices, 3, 3, 1, 'c', &currRow);
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(sInput, nInputSize, sSortChoices, 3, sMessage);

            // if the user input is valid
            if (!(Input_Fail))
            {
                // if the user typed cancel, go back to mode select
                if (strcmp(sInput, "Cancel") == 0)
                {
                    sInput[0] = '\0';
                    Mode = 0;
                    nSortMode = 0;
                    setMessage(sMessage, "What would you like to do?");
                }
                // check what sort mode the user has selected
                // Ascending
                else if (strcmp(sInput, sSortChoices[0]) == 0)
                    nSortMode = 1;
                // Descending
                else if (strcmp(sInput, sSortChoices[1]) == 0)
                    nSortMode = 2;

                // if the user has already selected a sort mode
                // Ascending
                if (nSortMode == 1)
                {
                    // Selection Sort
                    for (currMon = 0; currMon < (*nCapturedMons) - 1; currMon++)
                    {
                        // initializing the slot to be swapped
                        nSwap_Slot = currMon;
                        // checks each short name value after the currmon
                        for (nSeeker = currMon + 1; nSeeker < *nCapturedMons; nSeeker++)
                        {
                            // it records which slot has the firstest letter in the alphabet
                            if (strcmp(caughtMons[nSwap_Slot].sShort_Name, caughtMons[nSeeker].sShort_Name) > 0)
                            {
                                nSwap_Slot = nSeeker;
                            }
                        }
                        // if it found a firster letter in the alphabe, swap it.
                        if (nSwap_Slot > currMon)
                        {
                            // swap algo
                            tempMon = caughtMons[currMon];
                            caughtMons[currMon] = caughtMons[nSwap_Slot];
                            caughtMons[nSwap_Slot] = tempMon;

                            // retain the slot number. only swap the short name, full name, and dex index
                            caughtMons[nSwap_Slot].nSlot = caughtMons[currMon].nSlot;
                            caughtMons[currMon].nSlot = tempMon.nSlot;
                        }

                    }

                    setMessage(sMessage, "Sorted Short Name by Ascending Order");
                }
                // descending
                else if (nSortMode == 2)
                {
                    // Selection Sort
                    for (currMon = 0; currMon < (*nCapturedMons) - 1; currMon++)
                    {
                        // initializing the slot to be swapped
                        nSwap_Slot = currMon;
                        // checks each short name value after the currmon
                        for (nSeeker = currMon + 1; nSeeker < *nCapturedMons; nSeeker++)
                        {
                            // it records which slot has the lastest letter in the alphabet
                            if (strcmp(caughtMons[nSwap_Slot].sShort_Name, caughtMons[nSeeker].sShort_Name) < 0)
                            {
                                nSwap_Slot = nSeeker;
                            }
                        }
                        // if it found a lastest letter in the alphabe, swap it.
                        if (nSwap_Slot > currMon)
                        {
                            // swap algo
                            tempMon = caughtMons[currMon];
                            caughtMons[currMon] = caughtMons[nSwap_Slot];
                            caughtMons[nSwap_Slot] = tempMon;

                            // retain the slot number. only swap the short name, full name, and dex index
                            caughtMons[nSwap_Slot].nSlot = caughtMons[currMon].nSlot;
                            caughtMons[currMon].nSlot = tempMon.nSlot;
                        }

                    }

                    setMessage(sMessage, "Sorted Short Name by Descending Order");
                }
                    
                // resetting the values because it might be used again
                sInput[0] = '\0';
                Mode = 0;
                nSortMode = 0;
            }
        }

        // what to do with the selected fakemon
        else if (Mode == 6)
        {
            // NOTE: mon_Sel is already defined in Mode = 2
            // the only way to get here is if the user succesfully selected a fakemon
            // mon_Sel is the slot number of the fakemon in box struct array

            // resetting the value for future use
            isFound = 0;

            printChoices(selectedChoices, 3, 3, 1, 'c', &currRow);
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(sInput, nInputSize, selectedChoices, 3, sMessage);

            if (!Input_Fail)
            {
                // mon_Sel has already been defined

                // Cancel
                if (strcmp(sInput, selectedChoices[2]) == 0)
                {
                    sInput[0] = '\0';
                    Mode = 0;
                    mon_Sel = -1;
                    setMessage(sMessage, "What would you like to do?");
                }
                // View Entry
                else if (strcmp(sInput, selectedChoices[0]) == 0)
                {
                    // makes sure that input buffer is clear
                    sInput[0] = '\0';
                    // index_Dex is uused in this case
                    viewMon(sInput, nInputSize, viewMonChoice, 1, Fakedex, caughtMons[mon_Sel].index_Dex, 1, 
                            sMessage);
                    // since Cancel will be typed in the viewMon, it needs to be cleaned or else, this loop
                    // will end
                    sInput[0] = '\0';
                    // since it will loop back to the same fakemon, it is repeated.
                    snprintf(sMessage, STR_MSG_SIZE, "What would you like to do with SLOT: %d?", 
                        caughtMons[mon_Sel].nSlot + 1);
                    sMessage[STR_MSG_SIZE - 1] = '\0';
                }
                // Release
                else if (strcmp(sInput, selectedChoices[1]) == 0)
                {
                    Mode = 7;
                    sInput[0] = '\0';
                    snprintf(sMessage, STR_MSG_SIZE, "Are you sure you want to release SLOT: %d?", 
                        caughtMons[mon_Sel].nSlot + 1);
                    sMessage[STR_MSG_SIZE - 1] = '\0';
                }
            }
        }

        // release mode (confirmation)
        else if (Mode == 7)
        {
            // NOTE: mon_Sel has already been defined

            printChoices(releaseConfirmChoices, 2, 2, 1, 'c', &currRow);
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(sInput, nInputSize, releaseConfirmChoices, 2, sMessage);

            if (!Input_Fail)
            {
                // if no
                if (strcmp(sInput, releaseConfirmChoices[1]) == 0)
                {
                    setMessage(sMessage, "Release Cancelled");
                    sInput[0] = '\0';
                    // go back to the choices on what to do.
                    Mode = 6;
                }
                // if yes. release fakemon and adjust the caughtMons array
                else if (strcmp(sInput, releaseConfirmChoices[0]) == 0)
                {
                    // currMon represents the slot in the caughtMons array
                    // since the index of the caughtMons is = its nSlot, we can have this operation
                    for (currMon = caughtMons[mon_Sel].nSlot; currMon < (*nCapturedMons) - 1; currMon++)
                    {
                        // shifting to the left
                        // only the names and the indexDex will move, not the slot.
                        strcpy(caughtMons[currMon].sShort_Name, caughtMons[currMon + 1].sShort_Name);
                        strcpy(caughtMons[currMon].sFull_Name, caughtMons[currMon + 1].sFull_Name);
                        caughtMons[currMon].index_Dex = caughtMons[currMon + 1].index_Dex;
                    }
                    // cleaning the last content of caughtMons, since it would be redundant 
                    // (plus, it will not be counted)
                    caughtMons[(*nCapturedMons) - 1].nSlot = 0;
                    (caughtMons[(*nCapturedMons) - 1].sShort_Name)[0] = '\0';
                    (caughtMons[(*nCapturedMons) - 1].sFull_Name)[0] = '\0';
                    caughtMons[(*nCapturedMons) - 1].index_Dex = 0;

                    // decrementing captured mons counter
                    (*nCapturedMons)--;

                    // since search set of fakemons have a different array, it needs to be updated too
                    if (isSearchMode)
                    {
                        // finding the fakemon to be deleted in the searchedCaughtMons array
                        currMon = 0;
                        while (searchedCaughtMons[currMon].nSlot != caughtMons[mon_Sel].nSlot)
                        {
                            currMon++;
                        }
                        for (; currMon < searchedQty - 1; currMon++)
                        {
                            // this time, every member will be shifted
                            searchedCaughtMons[currMon].nSlot = searchedCaughtMons[currMon + 1].nSlot;
                            searchedCaughtMons[currMon].index_Dex = searchedCaughtMons[currMon + 1].index_Dex;
                            strcpy(searchedCaughtMons[currMon].sShort_Name, searchedCaughtMons[currMon + 1].sShort_Name);
                            strcpy(searchedCaughtMons[currMon].sFull_Name, searchedCaughtMons[currMon + 1].sFull_Name);
                        }
                    }
                    // cleaning the last content of searcgedCaughtMons, since it would be redundant 
                    // (plus, it will not be counted)
                    searchedCaughtMons[searchedQty - 1].nSlot = 0;
                    (searchedCaughtMons[searchedQty - 1].sShort_Name)[0] = '\0';
                    (searchedCaughtMons[searchedQty - 1].sFull_Name)[0] = '\0';
                    searchedCaughtMons[searchedQty - 1].index_Dex = 0;

                    // decrementing searchedMon counter (searched Qty)
                    searchedQty--;

                    setMessage(sMessage, "Released Fakemon.");
                    sInput[0] = '\0';
                    // go back to main menu
                    Mode = 0;
                    mon_Sel = -1;

                    // recalculate nMaxPage since number of fakemon has been subtracted
                    nMaxPage = *nCapturedMons / BOX_MON_PAGE;
                    // ceiling operation. (if there is a decimal in the quotient, round it up always)
                    if ((*nCapturedMons % BOX_MON_PAGE) != 0)   
                        nMaxPage++;
                    if (nMaxPage == 0)
                        nMaxPage = 1;

                    nTempMaxPage = nMaxPage;
                }
            }
        }

    } while (Input_Fail || strcmp(sInput, sModeChoices[nModeChoicesSize - 1]) != 0);
}

void settings(stringIn sInput, int nInputSize, stringChoice sSettingChoices[], int nSettingChoiceSize, 
                        stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0')   // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "What would you like to do?"); // message that would be sent to the user at the bottom screen

    
    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Settings); 


        // prints the main content of the TUI
        printFillerLines(HEIGHT / 5, &currRow);
        printText("Save Slots:", 'c', &currRow);
        printFillerLines(2, &currRow);
        printFileNames("sav", &currRow);
        printFillerLines(2, &currRow);
        printChoices(sSettingChoices, nSettingChoiceSize, nSettingChoiceSize, 1, 'c', &currRow);

        printBottomRemain(currRow);


        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

        // getInput returns if the user input is valid or not.
        // refer to getInput implementation (util.c) for the list of possible error msg returns
        // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
        Input_Fail = getInput(sInput, nInputSize, sSettingChoices, nSettingChoiceSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)

    } while (Input_Fail);
}

void save(stringIn sInput, int nInputSize, int nMonCreated, mon_type Fakedex[], box_type caughtMons[], 
            int nCapturedMons, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0')   // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Enter a name for your file. Put .txt at the end. You can 'Cancel'");
        // message that would be sent to the user at the bottom screen


    // file name has the maximum input of FILE_NAME_LEN characters (including .txt), so this space would 
    // not be a problem
    // the constant 6 is used for the additional "sav\\" path
    char pathBuffer[nInputSize + 6];
    pathBuffer[0] = '\0';   // making sure that the buffer has no string
    // used as a buffer for the accepted file name, since sInput will also be used for yes or no (confirmation)
    char fileNameBuffer[nInputSize];
    // this is used since when deleting a file, the user is prompted to input the file name that they want 
    // to delete. This buffer holds that file name to be deleted
    char deleteNameBuffer[nInputSize];  
    fileNameBuffer[0] = '\0';
    deleteNameBuffer[0] = '\0';

    // tells if the file opening was succesful. default to yes
    int isOpened = 1;

    // variables used when deleting or overwriting the file
    int isOverwriting = 0;
    int toOverwrite = 0;
    int isDeleting = 0;
    int availDeleteName = 0;
    int toDelete = 0;

    stringChoice confirmChoices[2] = {"Yes", "No"};

    // used to know how many save slots are populated
    int nNumSav = 0;

    // used in for loops when looping thorgh every fakemon entry
    int currMon;

    // variable used to know if the user wanted to cancel save operation. 
    int toCancel = 0;
    
    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Save);

        // prints the main content of the TUI
        printFillerLines(HEIGHT / 5, &currRow);
        printText("Save Slots:", 'c', &currRow);
        printFillerLines(2, &currRow);
        nNumSav = printFileNames("sav", &currRow);  // updates how many save files
        printFillerLines(2, &currRow);
        
        // if not asking for confirmation (not asking for the file name input)
        if (isOverwriting || (isDeleting && !(availDeleteName)))
        {
            printChoices(confirmChoices, 2, 2, 1, 'c', &currRow);

            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(sInput, nInputSize, confirmChoices, 2, sMessage);

            if (!(Input_Fail))
            {
                if (strcmp(sInput, "Yes") == 0)
                {
                    toDelete = 1;
                    toOverwrite = 1;
                }
            }

        }
        // if in delete mode and asking which file to delete
        else if (isDeleting && availDeleteName)
        {
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(deleteNameBuffer, nInputSize, NULL, 0, sMessage);
        }
        // if not any one those, ask for the file name
        else
        {
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            Input_Fail = getInput(sInput, nInputSize, NULL, 0, sMessage);
        }


        // if the specified file name length is accepted
        if (!(Input_Fail))
        {
            // if the file name is the input
            if (!(isOverwriting || isDeleting))
            {
                // check if the user typed cancel
                if (strcmp(sInput, "Cancel") == 0)
                {
                    toCancel = 1;
                    sInput[0] = '\0';
                }
                // or check if the file name is valid
                else if (strcmp(&(sInput[strlen(sInput) - 4]), ".txt") != 0) // if the file extension is not .txt
                {
                    Input_Fail = 5;
                    setMessage(sMessage, "Type .txt at the end of the file name. Try again or type 'Cancel'");
                    sInput[0] = '\0';
                }
                else if (strcmp(sInput, ".txt") == 0)   // if the file name is empty (only .txt)
                {
                    Input_Fail = 4;
                    setMessage(sMessage, "Type a file name followed by a .txt. Try again or type 'Cancel'");
                    sInput[0] = '\0';
                }
                
                else // if there are no more problems, accept the file name
                {
                    // put the accepted file name in the fileNameBuffer
                    strcpy(fileNameBuffer, sInput);
                }
            }


            // if there were no problems in the file name and the user has not typed cancel
            if (!(Input_Fail) && !(toCancel))
            {
                // if Overwriting mode
                if (isOverwriting)
                {
                    // if confirmed to overwrite, delete the same file name
                    if (toOverwrite)
                    {
                        deleteSav(fileNameBuffer);
                        nNumSav--;  // update the number of files
                    }
                    // if they do not want to overwrite
                    else
                    {
                        // turning these variables to 0 exits the loop and the function
                        Input_Fail = 0;
                        isDeleting = 0;
                        isOverwriting = 0;
                        setMessage(sMessage, "Save Cancelled");
                    }
                }
                // if in delete mode
                else if (isDeleting)
                {
                    // if they want to delete
                    if (toDelete)
                    {
                        // if they already have a file name they entered to delete
                        if (availDeleteName)
                        {
                            // if the file to be deleted exists (based on the file name)
                            if (fileExists(deleteNameBuffer))
                            {
                                deleteSav(deleteNameBuffer);
                                nNumSav--;  // update the number of files
                            }
                            // if the file does not exist, exit the function
                            else
                            {
                                // turning these variables to 0 exits the loop and the function
                                Input_Fail = 0;
                                isDeleting = 0;
                                isOverwriting = 0;
                                setMessage(sMessage, "That file does not exist. Save operation cancelled.");
                            }
                        }
                        else
                        {
                            availDeleteName = 1;
                            setMessage(sMessage, "Type the name of the file you want to delete");
                        }
                    }
                    // if if they do not want to delete
                    else
                    {
                        // turning these variables to 0 exits the loop and the function
                        Input_Fail = 0;
                        isDeleting = 0;
                        isOverwriting = 0;
                        setMessage(sMessage, "Save Cancelled");
                    }
                }

                else if (fileExists(fileNameBuffer))    // if the entered file name already exist
                {
                    // set the mode to isOverwriting
                    Input_Fail = 6;
                    setMessage(sMessage, 
                        "The file name is already in the slot. Do you want to Overwrite?");
                    sInput[0] = '\0';
                    isOverwriting = 1;
                }
                else if (nNumSav >= MAX_SAV_FILES) // if there are too many save files
                {
                    // set the mode to isDeleting
                    Input_Fail = 7;
                    snprintf(sMessage, STR_MSG_SIZE, 
                        "Maximum of %d save slots. Do you want to delete a save slot?", MAX_SAV_FILES);
                    sMessage[STR_MSG_SIZE - 1] = '\0';
                    sInput[0] = '\0';
                    isDeleting = 1;
                }

                
                // if there are no other possible errors. save the file with the filename
                // if there are too many save files, it is handeled by now since 
                // a save file is already deleted. if they said no to the confirmation, no
                // file will be deleted and thus, no new file will be created because of the
                // expression !(nNumSav >= MAX_SAV_FILES).
                // !(fileExists(fileNameBuffer)) is also a safeguard, so that no new file will be created
                // if the input file name is a duplicate.
                if (!(nNumSav >= MAX_SAV_FILES) && !(fileExists(fileNameBuffer)))    
                {
                    // put the file path to the pathBuffer
                    snprintf(pathBuffer, nInputSize + 6, "sav\\%s", fileNameBuffer);
                    FILE *fptr;
                    fptr = fopen(pathBuffer, "w");  // write file

                    if (fptr == NULL)   // if unable to open file. just another precaution
                    {
                        snprintf(sMessage, STR_MSG_SIZE, "%s", strerror(errno));
                        isOpened = 0;
                    }
                    
                    if (isOpened)   // if succesfully opened
                    {
                        // write the current data to a save file
                        fprintf(fptr, "NUMBER OF ENTRIES: %d\n", nMonCreated);
                        fprintf(fptr, "\n");
                        for (currMon = 0; currMon < nMonCreated; currMon++)
                        {
                            fprintf(fptr, "FULL NAME: %s\n", Fakedex[currMon].sFull_Name);
                            fprintf(fptr, "SHORT NAME: %s\n", Fakedex[currMon].sShort_Name);
                            fprintf(fptr, "DESCRIPTION: %s\n", Fakedex[currMon].sDescript);
                            // since cGender is only a character data type, 
                            // literal constants such as MALE must be printed
                            if (Fakedex[currMon].cGender == 'M')  
                                fprintf(fptr, "GENDER: MALE\n");
                            else if (Fakedex[currMon].cGender == 'F')  
                                fprintf(fptr, "GENDER: FEMALE\n");
                            else if (Fakedex[currMon].cGender == 'U')  
                                fprintf(fptr, "GENDER: UNKNOWN\n");
                            
                            // since nCaught is only a short data type,
                            // literal constants such as YES must be printed
                            if (Fakedex[currMon].nCaught == 1)  
                                fprintf(fptr, "CAUGHT: YES\n");
                            if (Fakedex[currMon].nCaught == 0)  
                                fprintf(fptr, "CAUGHT: NO\n");

                            fprintf(fptr, "\n");
                        }
                        fprintf(fptr, "--------- DEX END ---------\n");
                        fprintf(fptr, "NUMBER OF CAUGHT: %d\n", nCapturedMons);
                        fprintf(fptr, "\n");
                        for (currMon = 0; currMon < nCapturedMons; currMon++)
                        {
                            fprintf(fptr, "SLOT: %d\n", caughtMons[currMon].nSlot);
                            fprintf(fptr, "SHORT NAME: %s\n", caughtMons[currMon].sShort_Name);
                            fprintf(fptr, "FULL NAME: %s\n", caughtMons[currMon].sFull_Name);
                            fprintf(fptr, "INDEX FROM DEX: %d\n", caughtMons[currMon].index_Dex);

                            fprintf(fptr, "\n");
                        }
                        fprintf(fptr, "--------- BOX END ---------\n");

                        fclose(fptr);

                        // makes sure that the loop breaks and that the function exits
                        Input_Fail = 0;
                        isDeleting = 0;
                        isOverwriting = 0;
                        setMessage(sMessage, "File saved!");
                    }
                }
            }
            
        }

    } while ((Input_Fail || isDeleting || isOverwriting) && !(toCancel));

}

void load(stringIn sInput, int nInputSize, int *nMonCreated, mon_type Fakedex[], box_type caughtMons[], 
            int *nCapturedMons, stringMsg sMessage)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    if (sMessage[0] == '\0')   // if the sMessage is empty (no message from other functions)
        strcpy(sMessage, "Enter a name for your file. Put .txt at the end. You can 'Cancel'");
        // message that would be sent to the user at the bottom screen

    // used to know if file opening is succesful. default to no
    int isOpened = 0;

    // file name has the maximum input of FILE_NAME_LEN characters (including .txt), so this space 
    // would not be a problem
    // The literal 6 is used for the "sav\\"
    char pathBuffer[nInputSize + 6];

    // variable used to know if the user confirmed to overwrite the file. deafult to no
    int isConfirmed = 0;
    int isConfimring = 0;   // is confirming is the state in which the program asks for a sure overwrite
    // choices for confirming
    stringChoice confirmChoices[2] = {"Yes", "No"};

    // used in for loops when looping thorgh every fakemon entry
    int currMon;

    // file pointer used for file operations
    FILE *fptr;  

    // for the strings used in cGender, since the data stored in a text file is a string
    // a buffer is needed to convert that data into the right data type
    // 10 should be a big enough size since the largest word is UNKNOWN
    const int stringBuffer_Size = 10;
    char stringBuffer[stringBuffer_Size];
    
    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_Load);

        // prints the main content of the TUI
        printFillerLines(HEIGHT / 5, &currRow);
        printText("Save Slots:", 'c', &currRow);
        printFillerLines(2, &currRow);
        printFileNames("sav", &currRow);
        printFillerLines(2, &currRow);
        
        if (!(isConfimring))    // if not confirmiing for an overwrite (getting file name)
        {
            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // get the file name
            Input_Fail = getInput(sInput, nInputSize, NULL, 0, sMessage);
        }
        else if (isConfimring)  // if confirming for an overwrite
        {
            printChoices(confirmChoices, 2, 2, 1, 'c', &currRow);

            printBottomRemain(currRow);

            // prints bottom part of the box and the system message too, if there are any.
            printRemark(sMessage);
            sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.

            // get the confimation for overwrite
            Input_Fail = getInput(sInput, nInputSize, confirmChoices, 2, sMessage);

            if (!(Input_Fail))
            {
                if (strcmp(sInput, "Yes") == 0)
                    isConfirmed = 1;
                else if (strcmp(sInput, "No") == 0)
                    isConfirmed = 0;
            }
        }

        // if the specified string length is accepted
        if (!(Input_Fail))
        {
            // if not confirming for an overwrite (the file name is the input)
            if (!(isConfimring))
            {
                // if they typed cancel
                if (strcmp(sInput, "Cancel") == 0)
                {
                    Input_Fail = 0;
                    sInput[0] = '\0';   // cleans the input buffer

                    if (isOpened)
                        fclose(fptr);
                }
                // if they did not typed cancel
                // open the file with the inputted file name
                else
                {
                    // put the file name to the pathBuffer
                    snprintf(pathBuffer, nInputSize + 6, "sav\\%s", sInput);
                    fptr = fopen(pathBuffer, "r");  // open file in read mode
                    isOpened = 1;   // set to yes. 

                    if (fptr == NULL)   // if the entered file name does not exist in the sav directory
                    {
                        Input_Fail = 8;
                        sInput[0] = '\0';
                        isOpened = 0;       // set to no if file opening was unsuccesful
                        setMessage(sMessage, "That file name does not exist! Try again or type 'Cancel'");
                    }
                    
                    if (isOpened)
                    {
                        // set the question state to confirm if the user wants to overwrite
                        // will loop to the start
                        isConfimring = 1;
                        setMessage(sMessage, "Loading this file will delete all your current data. Proceed?");
                    }
                }
                
            }
            
            // if the overwrite question has been asked
            // (which will only happen if file opening was succesful)
            else if (isConfimring)
            {
                // if they said yes, overwrite the data and load the file
                if (isConfirmed)
                {
                    // deletes all the current data
                    for (currMon = 0; currMon < *nMonCreated; currMon++)
                    {
                        (Fakedex[currMon].sFull_Name)[0] = '\0';
                        (Fakedex[currMon].sShort_Name)[0] = '\0';
                        (Fakedex[currMon].sDescript)[0] = '\0';
                        Fakedex[currMon].cGender = 0;
                        Fakedex[currMon].nCaught = 0;
                    }
                    for (currMon = 0; currMon < *nCapturedMons; currMon++)
                    {
                        caughtMons[currMon].nSlot = 0;
                        (caughtMons[currMon].sShort_Name)[0] = '\0';
                        (caughtMons[currMon].sFull_Name)[0] = '\0';
                        caughtMons[currMon].index_Dex = 0;
                    }

                    // PRELIMINARY INFO
                    // asterisk (*) is used to discard information that are not needed.
                    // such as, FULL NAME:, SHORT NAME:, etc. only the important data are gathered 
                    fscanf(fptr, " %*s %*s %*s %d", nMonCreated);   // sets created fakemon

                    // loops through every fakemon entry
                    for (currMon = 0; currMon < *nMonCreated; currMon++)
                    {
                        //FULL NAME
                        // META information discarded
                        fscanf(fptr, " %*s %*s ");
                        // since there may be spaces in the entries, fgets is used
                        fgets(Fakedex[currMon].sFull_Name, FULL_NAME_SIZE + STR_MARGIN, fptr);
                        // removes the new line characterin the string
                        Fakedex[currMon].sFull_Name[strcspn(Fakedex[currMon].sFull_Name, "\n")] = 0;

                        // SHORT NAME
                        fscanf(fptr, " %*s %*s ");
                        fgets(Fakedex[currMon].sShort_Name, SHORT_NAME_SIZE + STR_MARGIN, fptr);
                        Fakedex[currMon].sShort_Name[strcspn(Fakedex[currMon].sShort_Name, "\n")] = 0;

                        // DESCRIPTION
                        fscanf(fptr, " %*s ");
                        fgets(Fakedex[currMon].sDescript, DESCRIPTION_SIZE + STR_MARGIN, fptr);
                        Fakedex[currMon].sDescript[strcspn(Fakedex[currMon].sDescript, "\n")] = 0;

                        // GENDER
                        // since the data in the save text file has the literal MALE, FEMALE, or UNKNOWN
                        // in it, it is necessary to convert those literals into characters
                        fscanf(fptr, " %*s ");
                        fgets(stringBuffer, stringBuffer_Size, fptr);
                        stringBuffer[strcspn(stringBuffer, "\n")] = 0;
                        if (strcmp(stringBuffer, "MALE") == 0)
                            Fakedex[currMon].cGender = 'M';
                        else if (strcmp(stringBuffer, "FEMALE") == 0)
                            Fakedex[currMon].cGender = 'F';
                        else if (strcmp(stringBuffer, "UNKNOWN") == 0)
                            Fakedex[currMon].cGender = 'U';
                        
                        // CAUGHT
                        // same case with gender
                        fscanf(fptr, " %*s ");
                        fgets(stringBuffer, stringBuffer_Size, fptr);
                        stringBuffer[strcspn(stringBuffer, "\n")] = 0;
                        if (strcmp(stringBuffer, "YES") == 0)
                            Fakedex[currMon].nCaught = 1;
                        else if (strcmp(stringBuffer, "NO") == 0)
                            Fakedex[currMon].nCaught = 0;
                        
                    }

                    // BOX PART
                    // discarding the header
                    fscanf(fptr, " %*s %*s %*s %*s");  

                    // PRELIMINARY INFO
                    // such as, FULL NAME:, SHORT NAME:, etc. only the important data are gathered 
                    fscanf(fptr, " %*s %*s %*s %d", nCapturedMons);   // sets how many capture fakemon fakemon

                    for (currMon = 0; currMon < *(nCapturedMons); currMon++)
                    {
                        // SLOT NUMBER
                        fscanf(fptr, " %*s %d", &(caughtMons[currMon].nSlot));

                        // SHORT NAME
                        fscanf(fptr, " %*s %*s ");
                        fgets(caughtMons[currMon].sShort_Name, SHORT_NAME_SIZE + STR_MARGIN, fptr);
                        // removes new line character
                        caughtMons[currMon].sShort_Name[strcspn(caughtMons[currMon].sShort_Name, "\n")] = 0;

                        // FULL NAME
                        fscanf(fptr, " %*s %*s ");
                        fgets(caughtMons[currMon].sFull_Name, FULL_NAME_SIZE + STR_MARGIN, fptr);
                        // removes new line character
                        caughtMons[currMon].sFull_Name[strcspn(caughtMons[currMon].sFull_Name, "\n")] = 0;

                        // INDEX FROM DEX
                        fscanf(fptr, " %*s %*s %*s %d", &(caughtMons[currMon].index_Dex));
                    }
                    

                    setMessage(sMessage, "File succesfully loaded!");
                }
                // if they do not want to overwrite and load anymore
                else if (!(isConfirmed))
                {
                    setMessage(sMessage, "Loading File Cancelled");
                }

                // either way, close the file and exit the function (will go back to settings menu)
                fclose(fptr);
                isConfimring = 0;   // to end the function
                sInput[0] = '\0';   // cleaning input buffer
                
            }
        }

    } while (Input_Fail || isConfimring);
}