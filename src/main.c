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
    // initialize dex with 0s
    mon_type FakeDex[DEX_MAX] = {{{0}}};

    stringIO sInput;

    main_menu(sInput);

    return 0;
}