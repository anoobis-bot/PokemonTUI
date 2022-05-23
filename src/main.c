/******************************************
File Name: main.c

Author: Francis Zaccharie B. de Leon
Last Update: May 18, 2022

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
    stringChoice sMainChoices[MAINCHOICES_SIZE] = {"Fakedex", "Exploration", "Box", "Settings", "Exit"};  // main menu choices


    // initialize dex and make all members equal to 0
    mon_type FakeDex[DEX_MAX] = {{{0}}};

    // sInput is the variable that will hold the user inputt
    stringIn sInput;

    // main menu screen
    main_menu(sInput, STR_INPUT_STD + STR_MARGIN, sMainChoices, MAINCHOICES_SIZE);

    return 0;
}