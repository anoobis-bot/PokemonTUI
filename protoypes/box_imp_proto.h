/******************************************
File Name: box_imp_proto.h

Author: Francis Zaccharie B. de Leon
Last Update: May 22, 2022

This file contains the function prototypes
of the functions in box_imp.c file
******************************************/

#ifndef BOX_IMP_PROTO_H
#define BOX_IMP_PROTO_H

void mainMenu(stringIn sInput, int sInputSize, stringChoice sMainChoices[], int sMainChoicesSize , stringMsg sMessage);
void fakedexDatabase(stringIn sInput, int sInputSize, stringChoice sDatabaseChoices[], int nDatabaseChoicesSize, stringMsg sMessage);
void addDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *dex_Database, int nMonCreated, stringMsg sMessage);

#endif