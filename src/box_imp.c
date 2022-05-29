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
#include "../header/art.h"


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
        strcpy(sMessage, "Welcome to the Fakedex Database!"); // message that would be sent to the user at the bottom screen
    
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

void viewMon(stringIn sInput, int nInputSize, stringChoice sChoices[], int nChoicesSize, mon_type *Fakedex, int nMonEntry, 
                stringMsg sMessage)
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
        // print short name
        snprintf(outputBuffer, 500, "%s %s", "Short Name:", Fakedex[nMonEntry].sShort_Name);
        printText(outputBuffer, 'j', &currRow);
        printFillerLines(1, &currRow);
        // print desciption
        snprintf(outputBuffer, 500, "%s %s", "Description:", Fakedex[nMonEntry].sDescript);
        printText(outputBuffer, 'j', &currRow);
        printFillerLines(1, &currRow);
        // print Gender
        if (Fakedex[nMonEntry].cGender == 'M')  // since cGender member only has char, putting the constant MALE FEMALE or UNKNOWN is necessary
            snprintf(outputBuffer, 500, "%s %s", "Gender:", "MALE");
        else if (Fakedex[nMonEntry].cGender == 'F')  
            snprintf(outputBuffer, 500, "%s %s", "Gender:", "FEMALE");
        else if (Fakedex[nMonEntry].cGender == 'U')  
            snprintf(outputBuffer, 500, "%s %s", "Gender:", "UNKNOWN");
        printText(outputBuffer, 'j', &currRow);
        printFillerLines(1, &currRow);
        // print caught or uncaught
        if (Fakedex[nMonEntry].nCaught == 0)  // since nCaught member only has short, putting the constant CAUGHT or UNCAUGHT
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

int addDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *dex_Database, int nCurrMon, stringMsg sMessage)
{
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

        if (isDuplicate)    // if the entry is duplicate, the inputted data is stored in a temporary data buffer
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
        }
        
        // since cGender member only has char, putting the constant MALE FEMALE or UNKNOWN is necessary
        if (dex_Database[nCurrMon].cGender == 'M')  
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

        // if the input was valid (the size of input is not greater than the alloted size of the member)
        if (!(Input_Fail))
        {
            // since the full name of the fakemon is the basis for overwiting data this is the only question
            // in which the input from that question is compared to every full name in the data base to check if there are
            // duplicates.
            if (currQuestion == 0)
            {
                for (compMon = 0; compMon < nCurrMon && !(isDuplicate); compMon++)
                {
                    if (strcmp(sInput, dex_Database[compMon].sFull_Name) == 0)
                    {
                        isDuplicate = 1;
                        // compMon is the index where the fakemon to be overwritten resides.
                        // compMon is decremented to balance it out 
                        // since at the end of the for loop, it would be incremeneted.
                        compMon--;
                    }
                }
            }

            if (isDuplicate)    // isDuplicate will never turn again to 0 once set to 1
            {
                // store the user input to the tempMon struct buffer
                if (currQuestion == 0)
                    strcpy(tempMon.sFull_Name, sInput);
                else if (currQuestion == 1)
                    strcpy(tempMon.sShort_Name, sInput);
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
                    // tell the user that there has been a duplicate
                    snprintf(sMessage, STR_MSG_SIZE, "We found a duplicate, would you like to overide this entry?");
                    // show the original entry and ask if they want to overwrite
                    viewMon(sInput, 3 + STR_MARGIN, sDuplicateChoice, 2, dex_Database, compMon, sMessage);
                    if (strcmp(sInput, sDuplicateChoice[0]) == 0)   // if they entered "Yes"
                    {
                        dex_Database[compMon] = tempMon;    // update the compMon(index) with its new value
                        snprintf(sMessage, STR_MSG_SIZE, "Fakemon entry updated");
                    }
                    else    // if they answered no, this function end and the tempMon was not assigned to anything
                        snprintf(sMessage, STR_MSG_SIZE, "Fakemon entry discarded");
                    
                    newCreatedMon = 0;  // no new entry was made, they just updated/discarded an entry
                }
            }

            else if (!(isDuplicate))    // if the Full Name is not duplicated
            {
                // sInput is assigned to its rightful struct member
                if (currQuestion == 0)
                    strcpy(dex_Database[nCurrMon].sFull_Name, sInput);
                
                else if (currQuestion == 1)
                {
                    // checks if there are any duplicates of the Short Name in the database
                    for (compMon = 0; compMon < nCurrMon && !(isDuplicate); compMon++)
                    {
                        if (strcmp(sInput, dex_Database[compMon].sShort_Name) == 0)
                        {
                            Input_Fail = 3;
                            snprintf(sMessage, STR_MSG_SIZE, 
                                        "Duplicate short name in the database! Enter a unique short name.");
                        }
                    }

                    // if there are no duplicates, assign the short name
                    if (!(Input_Fail))
                        strcpy(dex_Database[nCurrMon].sShort_Name, sInput);
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

    if (newCreatedMon)
        strcpy(sMessage, "Succesfully added a new entry!");

    return newCreatedMon;
}

int viewDex(stringIn sInput, int nInputSize, mon_type *Fakedex, int currPopulation, stringMsg sMessage)
{
    int nIntIn;     // since the input that would be used here is integers, this would be the buffer for it

    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT


    if (sMessage[0] == '\0')    // if the sMessage is empty (no message from other functions)
        snprintf(sMessage, STR_MSG_SIZE, "What would you like to do?");   // message that would be sent to the user


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
    // which is 3 chars
    const int nDescNumMax = WIDTH - LEFT_PAD - nLeftPad - 3 - FULL_NAME_SIZE - nSpaceBetween - nRightPad  - RIGHT_PAD;
    
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
    char sNumHolder[3];
    
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

            // prepping the description of the current fakemon entry. if the length of the fakemon's description exceeds 
            // the nDescNumMax - 4 (for the ...\0) it is truncated and replaced with an ellipsis ...
            // nore: snprintf only prints n-1 to buffer
            snprintf(sDescBuffer, nDescNumMax - 3, Fakedex[currMon + (currPage * MON_PAGE)].sDescript);
            sDescBuffer[nDescNumMax - 4] = '\0';    // since sDescBuffer is not initialized to all 0, making sure it it has null
            if (strlen(Fakedex[currMon + (currPage * MON_PAGE)].sDescript) > nDescNumMax - 4)
                strcat(sDescBuffer, "..."); // if it is truncated, put ellipsis on it
            
            // this is where the printing of the line starts.
            // putting the necessary number of pad to the buffer first 
            for (currPad = 0; currPad < nLeftPad; currPad++)
                strcat(outputBuffer, " ");

            // sNumHolder is the buffer for the number of the current pokemon entry
            // (currMon + 1) + (currPage * MON_PAGE) displays what index + 1 the fakemon is based on the current page
            snprintf(sNumHolder, 3, "%d.", (currMon + 1) + (currPage * MON_PAGE));
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
            for (currPad = 0; currPad < nSpaceBetween + nNameLack; currPad++)
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
                snprintf(sMessage, STR_MSG_SIZE, "Which Page woud you like to go? Enter -1 to cancel");
            }
            else if (strcmp(sInput, modeChoices[1]) == 0)   // select mode
            {
                Mode = 2;
                snprintf(sMessage, STR_MSG_SIZE, "Type the Fakemon's number you want to select. Enter -1 to cancel");
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
                snprintf(sMessage, STR_MSG_SIZE, "Only input the avaialble page number or -1.");
                sInput[0] = '\0';
            }
            else if (nIntIn == -1)  // escape function. returns to mode 0
            {
                Mode = 0;
                snprintf(sMessage, STR_MSG_SIZE, "What would you like to do?");
            }
            else    // or if the user inputted a valid number, page is set to that and mode returns to 0
            {
                currPage = nIntIn - 1;  // currPage starts at index 0
                Mode = 0;
                snprintf(sMessage, STR_MSG_SIZE, "What would you like to do?");
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
                snprintf(sMessage, STR_MSG_SIZE, "Only input the Fakemon number in this page or -1.");
                sInput[0] = '\0';
            }
            else if (nIntIn == -1)  // escape function. returns to mode 0 
            {
                Mode = 0;
                snprintf(sMessage, STR_MSG_SIZE, "What would you like to do?");
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