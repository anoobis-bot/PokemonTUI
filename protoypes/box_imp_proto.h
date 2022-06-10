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
                int nMonEntry, int forceView, stringMsg sMessage);
int addDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *dex_Database, int *nMonCreated, 
            box_type caughtMons[], int nCapturedMons, stringMsg sMessage, int nCurrMon);
void updateDex(stringIn sInput, int nInputSizes[], int nInputQty, mon_type *Fakedex, int *nMonCreated, 
                box_type caughtMons[], int nCapturedMons, stringMsg sMessage);
int removeDex(stringIn sInput, int nInputSize, mon_type *Fakedex, int *nMonCreated, 
                box_type caughtMons[], int nCapturedMons, stringMsg sMessage);
int viewDex(stringIn sInput, int nInputSize, mon_type *Fakedex, int currPopulation, stringMsg sMessage);
int encounter(stringIn sInput, int nInputSize, stringChoice sEncounterChoices[], int nEncounterChoicesSize, 
                mon_type *Fakedex, int nMonCreated, box_type caughtMons[], int *nCapturedMons, stringMsg sMessage);
void exploration(stringIn sInput, int nInputSize, stringChoice sExploreChoices[], int nExploreChoicesSize, 
                    int *ActiveCell, int nMonCreated, stringMsg sMessage);
void viewBox(stringIn sInput, int nInputSize, stringChoice sModeChoices[], int nModeChoicesSize, 
                mon_type *Fakedex, box_type caughtMons[], int *nCapturedMons, stringMsg sMessage);
void settings(stringIn sInput, int nInputSize, stringChoice sSettingChoices[], int nSettingChoiceSize, 
                        stringMsg sMessage);
void save(stringIn sInput, int nInputSize, int nMonCreated, mon_type Fakedex[], box_type caughtMons[], 
            int nCapturedMons, stringMsg sMessage);
void load(stringIn sInput, int nInputSize, int *nMonCreated, mon_type Fakedex[], box_type caughtMons[], 
            int *nCapturedMons, stringMsg sMessage);

#endif