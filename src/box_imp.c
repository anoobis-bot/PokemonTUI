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
void main_menu(stringIn sInput, int sInputSize, stringChoice sMainChoices[], int nMainChoicesSize)
{
    int currRow;    // indicates to functions on how many rows are already printed in the content area.
                    // this so that the height of the content is consistent to the macro HEIGHT

    int Input_Fail = 0; // used for input validation. will loop for user input if the input is invalid.

    
    stringMsg sMessage = "Choose the choices in the menu";  // message that would be sent to the user at the bottom screen
                                                            // initialized to "Choose the choices in the menu"

    
    do {
        printf(CLEAR);  // clears the screen
        printf("\n");   // and creates new line for the margin
        currRow = 0;    // sets row to 0 again

        // prints the header of the TUI
        printHeader(HDR_FakeDex); 

        
        // prints the main content of the TUI
        printFillerLines(HEIGHT / 10, &currRow);
        printText("Welcome to the Fakedex game trainer!", 'c', &currRow);
        printFillerLines(1, &currRow);              // prints lines 1/8 of the HEIGHT
        displayPokeball(ART_Pokeball, &currRow);    // dipalys the pokeball art
        printFillerLines(1, &currRow);
        printChoices(sMainChoices, nMainChoicesSize, 2, 2, 'c', &currRow); // prints the possible choices fot main menu
        
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