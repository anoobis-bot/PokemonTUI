/******************************************
File Name: box_imp_proto.h

Author: Francis Zaccharie B. de Leon
Last Update: May 22, 2022

This file contains the function prototypes
of the functions in box_imp.c file
******************************************/

#ifndef BOX_IMP_PROTO_H
#define BOX_IMP_PROTO_H

void mainMenu(stringIn sInput, int nInputSize, stringChoice sMainChoices[], int sMainChoicesSize , stringMsg sMessage);
void fakedexDatabase(stringIn sInput, int nInputSize, stringChoice sDatabaseChoices[], int nDatabaseChoicesSize, 
                        stringMsg sMessage);
void viewMon(stringIn sInput, int nInputSize, stringChoice sChoices[], int nChoicesSize, mon_type *Fakedex, 
                int nMonEntry, stringMsg sMessage);
void addDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *dex_Database, int nMonCreated, stringMsg sMessage);
int viewDex(stringIn sInput, int nInputSize, mon_type *Fakedex, int currPopulation, stringMsg sMessage);

#endif