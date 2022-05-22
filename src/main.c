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
#include "../configurations.h"
#include "../protoypes/box_imp_proto.h"


int main(void)
{
    // choices in the game
    stringChoice main_menu_choices[5] = {"Fakedex", "Exploration", "Box", "Settings", "Exit"};

    // initialize dex with 0s
    mon_type FakeDex[DEX_MAX] = {{{0}}};

    stringIn sInput;

    // main menu screen
    main_menu(sInput, STR_INPUT_STD + STR_MARGIN, main_menu_choices);

    return 0;
}