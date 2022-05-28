/******************************************
File Name: main.c

Author: Francis Zaccharie B. de Leon
Last Update: May 28, 2022

This is the highest level of source code.
It contains just function calls and simple
return values.
******************************************/

// included header files
#include "../header/definitions.h"
#include "../header/array_sizes.h"
#include "../configurations.h"
#include "../protoypes/box_imp_proto.h"


int main(void)
{
    // choices in the game
    // Main Menu Choices
    stringChoice sMainChoices[MAINCHOICES_SIZE] = {"Fakedex", "Exploration", "Box", "Settings", "Exit"};  // main menu choices
    // Fakedex Database Choices
    stringChoice sDatabaseChoices[DATABASECHOICES_SIZE] = {"Add Dex", "View Dex", "Update Dex", "Remove Dex", "Cancel"};

    
    // initialize dex and make all members equal to 0
    mon_type FakeDex[DEX_MAX] = {{{0}}};

    // number of Fakemon already created
    int nMonCreated = 0;

    // sizes of each member in the FakeDex struct (mon_type)
    int nDatabase_In_Sizes[STRUCT_IN_NUM] = {FULL_NAME_SIZE + STR_MARGIN, SHORT_NAME_SIZE + STR_MARGIN, DESCRIPTION_SIZE + STR_MARGIN, 
                                    1 + STR_MARGIN};

    // sInput is the variable that will hold the user inputt
    stringIn sInput;

    // sMessage is the message feedback that the program will say to the computer
    stringMsg sMessage = "";

    do {
        // main menu screen
        mainMenu(sInput, STR_INPUT_STD + STR_MARGIN, sMainChoices, MAINCHOICES_SIZE, sMessage);

        // Fakedex Database
        if (strcmp(sInput, sMainChoices[0]) == 0)
        {
            do {
                fakedexDatabase(sInput, STR_INPUT_STD + STR_MARGIN, sDatabaseChoices, DATABASECHOICES_SIZE, sMessage);   // Fakedex Database TUI
                // Add Dex
                if (strcmp(sInput, sDatabaseChoices[0]) == 0)
                {
                    addDex(sInput, nDatabase_In_Sizes, STRUCT_IN_NUM, FakeDex, nMonCreated, sMessage);  // Add Dex TUI
                    nMonCreated++;
                }
                // View Dex
                else if (strcmp(sInput, sDatabaseChoices[1]) == 0)
                {
                    viewDex(sInput, STR_INPUT_STD + STR_MARGIN, FakeDex, nMonCreated, sMessage);
                }

            } while (strcmp(sInput, sDatabaseChoices[DATABASECHOICES_SIZE - 1]) != 0); // while the user has not typed "Cancel"
        }

    } while (strcmp(sInput, sMainChoices[MAINCHOICES_SIZE - 1]) != 0);  // while the user has not typed "Exit"

    return 0;
}