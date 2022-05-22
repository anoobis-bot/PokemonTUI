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
#include "../protoypes/util_proto.h"
#include "../protoypes/art_proto.h"
#include "../header/art.h"


/* This functioncreates the GUI for the main menu
    it returns what the user selected
        - it can be fakedex database
        - Explore
        - Box
        - Settings                                 */
void main_menu(stringIn sInput, int sInputSize)
{
    int currRow = 0;

    // Input validation
    int Input_Fail = 0;

    // message that would be sent to the user at the bottom screen
    stringMsg sMessage = "";

    
    do {
        printf(CLEAR);
        printf("\n");

        // prints top part of the box
        printHeader(HDR_FakeDex);

        
        // main content
        printFillerLines(HEIGHT / 8, &currRow);
        displayPokeball(ART_Pokeball, &currRow);
        printBottomRemain(currRow);


        // prints bottom part of the box and the system message too, if there are any.
        printRemark(sMessage);
        sMessage[0] = '\0';     // cleaning the sMessage array because it will be reused.


        // getInput returns if the user input is valid or not.
        // refer to getInput implementation (util.c) for the list of possible error msg returns
        // it also alters the sMessage to be printed if it found an error or if it has a feedback to be printed again
        Input_Fail = getInput(sInput, sInputSize, sMessage);
        // if the input fails, it will prompt the user to type an input again
        // only valid inputs will be returned (sInput)
    } while (Input_Fail);
}