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
#include "../header/art.h"


/* This functioncreates the GUI for the main menu
    it returns what the user selected
        - it can be fakedex database
        - Explore
        - Box
        - Settings                                 */
char *main_menu()
{

    printf(CLEAR);
    printf("\n");

    printHeader(HDR_FakeDex);

}