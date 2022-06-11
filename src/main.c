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
    // View fakemon entry choices
    stringChoice sViewMonDexChoices[VIEWMONDEXCHOICES_SIZE] = {"OK"};
    // Settings choice
    stringChoice sSettingChoices[SETTINGCHOICES_SIZE] = {"Save", "Load", "Cancel"};
    // Exploration Choices
    stringChoice sExplorationChoices[EXPLORATIONCHOICES_SIZE] = {"FORWARD", "BACKWARD", "EXIT"};
    // Encounter Fakemon choices
    stringChoice sEncounterChoices[ENCOUNTERCHOICES_SIZE] = {"CATCH", "RUN"}; 
    // mode choices for the viewBox
    stringChoice sBoxChoices[BOXCHOICES_SIZE] = {"Navigate", "Select", "Full Name Search", "Short Name Search", 
                                                    "Sort", "Exit"};

    
    // initialize dex and make all members equal to 0
    mon_type FakeDex[DEX_MAX] = {{{0}}};

    // sizes of each member in the FakeDex struct (mon_type)
    int nDatabase_In_Sizes[STRUCT_IN_NUM] = {FULL_NAME_SIZE + STR_MARGIN, SHORT_NAME_SIZE + STR_MARGIN, DESCRIPTION_SIZE + STR_MARGIN, 
                                    1 + STR_MARGIN};

    // number of Fakemon already created
    int nMonCreated = 0;

    // array of box_type that tell which fakemon are already caught. the number of each element identifies to
    // which fakemon it is based on the index number of the fakemon in Fakedex[].
    // if caughtMons[0] = 1. then that means that the trainer has the fakemon of fakedex's index 1.
    box_type caughtMons[BOX_MAX] = {{0}};

    // number of mons already in the box (caught mons)
    int nCapturedMons = 0;

    // selected fakemon in the Fakdex database
    int mon_Sel = -1;

    // variable used to keep track of the position of the player (Exploration Mode)
    int ActiveCell = 0;

    // sInput is the variable that will hold the user inputt
    stringIn sInput;

    // sMessage is the message feedback that the program will say to the computer
    stringMsg sMessage = "";

    // used to catch the return value of functions whether the operation was succesful or not. default to no
    int isSucces = 0;



    // seeding the rand() function
    srand(time(0));

    do {
        // main menu screen
        mainMenu(sInput, STR_INPUT_STD + STR_MARGIN, sMainChoices, MAINCHOICES_SIZE, sMessage);

        // Fakedex Database
        if (strcmp(sInput, sMainChoices[0]) == 0)
        {
            do {
                fakedexDatabase(sInput, STR_INPUT_STD + STR_MARGIN, sDatabaseChoices,       // Fakedex Database TUI
                                    DATABASECHOICES_SIZE, sMessage);   
                // Add Dex
                if (strcmp(sInput, sDatabaseChoices[0]) == 0)
                {
                    
                    isSucces = addDex(sInput, nDatabase_In_Sizes, STRUCT_IN_NUM, FakeDex,   // Add Dex TUI
                                        &nMonCreated, caughtMons, nCapturedMons, sMessage, -1);  
                    if (isSucces)   // addDex returns 1 if new fakemon populated the Fakedex (excluding update entries)
                        nMonCreated++;
                }
                // View Dex
                else if (strcmp(sInput, sDatabaseChoices[1]) == 0)
                {
                    do {
                        mon_Sel = viewDex(sInput, STR_INPUT_STD + STR_MARGIN, FakeDex,      // View Dex TUI
                                            nMonCreated, sMessage);
                        // mon_Sel is -1 if no fakemon in the fakedex is selected (if the user typed cancel)
                        // there are no -1 in the index of the array Fakemon[]
                        if (mon_Sel != -1)  
                            viewMon(sInput, STR_INPUT_STD + STR_MARGIN, sViewMonDexChoices, VIEWMONDEXCHOICES_SIZE, 
                                        FakeDex, mon_Sel, 0,sMessage);
                    } while (mon_Sel != -1);
                }
                // Update Dex
                else if (strcmp(sInput, sDatabaseChoices[2]) == 0)
                {
                    updateDex(sInput, nDatabase_In_Sizes, STRUCT_IN_NUM, FakeDex,   // Update Dex TUI
                        &nMonCreated, caughtMons, nCapturedMons, sMessage);
                }
                // Remove Dex
                else if (strcmp(sInput, sDatabaseChoices[3]) == 0)
                {
                    removeDex(sInput, FULL_NAME_SIZE + STR_MARGIN, FakeDex, &nMonCreated, caughtMons, 
                                nCapturedMons, sMessage);
                }

            } while (strcmp(sInput, sDatabaseChoices[DATABASECHOICES_SIZE - 1]) != 0); 
            // while the user has not typed "Cancel"
        }
        
        // Exploration
        else if (strcmp(sInput, sMainChoices[1]) == 0)
        {
            // if there is still room in the box, the user can do exploration 
            if (nCapturedMons < BOX_MAX)
            {
                do 
                {
                    exploration(sInput, STR_INPUT_STD + STR_MARGIN, sExplorationChoices, EXPLORATIONCHOICES_SIZE, 
                                    &ActiveCell, nMonCreated, sMessage);

                    // if the user has not typed "Cancel"
                    if (strcmp(sInput, sExplorationChoices[EXPLORATIONCHOICES_SIZE - 1]) != 0)
                    {
                        // encounter a fakemon. randomized fakemon is handled inside the function
                        encounter(sInput, STR_INPUT_STD + STR_MARGIN, sEncounterChoices, ENCOUNTERCHOICES_SIZE, 
                                    FakeDex, nMonCreated, caughtMons, &nCapturedMons, sMessage);
                    }   
                                    

                } while ((strcmp(sInput, sExplorationChoices[EXPLORATIONCHOICES_SIZE - 1]) != 0) && 
                            nCapturedMons < BOX_MAX);
                // while the user has not typed EXIT or still have room in the box

                // if the loop stopped because the box is full, print this
                if (nCapturedMons >= BOX_MAX)
                {
                    sInput[0] = '\0';
                    sprintf(sMessage, "You have been kicked out. Your box is full. Maximum of %d", BOX_MAX);
                }
                // if the user typed exit
                else if (strcmp(sInput, sExplorationChoices[EXPLORATIONCHOICES_SIZE - 1]) == 0)
                {
                    // just in case no loop would accidentally stop, the sInput buffer is cleaned from the word
                    // exit
                    sInput[0] = '\0';
                }

                // either way, if the user exited the exploration, his position will repeat to index 0
                ActiveCell = 0;
            }
            // if there is no more room
            else
            {
                sInput[0] = '\0';
                sprintf(sMessage, "You need to own less than %d fakemons to explore.", BOX_MAX);
            }
        }

        // Box
        else if (strcmp(sInput, sMainChoices[2]) == 0)
        {
            do
            {
                viewBox(sInput, STR_INPUT_STD + STR_MARGIN, sBoxChoices, BOXCHOICES_SIZE, FakeDex, 
                            caughtMons, &nCapturedMons, sMessage);
            } while (strcmp(sInput, sBoxChoices[BOXCHOICES_SIZE - 1]) != 0);
            // while the user has not typed cancel

            // if the user typed exit
            if (strcmp(sInput, sBoxChoices[BOXCHOICES_SIZE - 1]) == 0)
            {
                // just in case no loop would accidentally stop, the sInput buffer is cleaned from the word
                // exit
                sInput[0] = '\0';
            }
        }

        // Settings
        else if (strcmp(sInput, sMainChoices[3]) == 0)
        {
            do {
                settings(sInput, STR_INPUT_STD + STR_MARGIN, sSettingChoices,   // settings TUI
                    SETTINGCHOICES_SIZE, sMessage);
                
                // save
                if (strcmp(sInput, sSettingChoices[0]) == 0)
                {
                    save(sInput, FILE_NAME_LEN + STR_MARGIN, nMonCreated, FakeDex, caughtMons, 
                            nCapturedMons, sMessage); // save TUI
                }
                // load
                else if (strcmp(sInput, sSettingChoices[1]) == 0)
                {
                    load(sInput, FILE_NAME_LEN + STR_MARGIN, &nMonCreated, FakeDex, caughtMons, 
                            &nCapturedMons, sMessage);
                }

            } while (strcmp(sInput, sSettingChoices[SETTINGCHOICES_SIZE - 1]) != 0); 
            // while the user has not typed "Cancel"
        }
    } while (strcmp(sInput, sMainChoices[MAINCHOICES_SIZE - 1]) != 0);  // while the user has not typed "Exit"

    return 0;
}