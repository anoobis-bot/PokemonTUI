/******************************************
File Name: box_imp_proto.h

Author: Francis Zaccharie B. de Leon
Last Update: June 12, 2022

This file contains the function prototypes
of the functions in box_imp.c file
******************************************/

#ifndef BOX_IMP_PROTO_H
#define BOX_IMP_PROTO_H

void 
mainMenu(stringIn sInput, int nInputSize, stringChoice sMainChoices[], int nMainChoicesSize, stringMsg sMessage);

void 
fakedexDatabase(stringIn sInput, int nInputSize, stringChoice sDatabaseChoices[], int nDatabaseChoicesSize, 
                        stringMsg sMessage);

void 
viewMon(stringIn sInput, int nInputSize, stringChoice sChoices[], int nChoicesSize, mon_type *pFakedex, 
                int nMonEntry, int forceView, stringMsg sMessage);

int 
addDex(stringIn sInput, int pInputSizes[], int nInputQty, mon_type *dex_Database, int *pMonCreated, 
            box_type pCaughtMons[], int nCapturedMons, stringMsg sMessage, int nCurrMon);

void 
updateDex(stringIn sInput, int pInputSizes[], int nInputQty, mon_type *pFakedex, int *pMonCreated, 
                box_type pCaughtMons[], int nCapturedMons, stringMsg sMessage);

int 
removeDex(stringIn sInput, int nInputSize, mon_type *pFakedex, int *pMonCreated, 
                box_type pCaughtMons[], int nCapturedMons, stringMsg sMessage);

int 
viewDex(stringIn sInput, int nInputSize, mon_type *pFakedex, int nMonCreated, stringMsg sMessage);

int 
encounter(stringIn sInput, int nInputSize, stringChoice sEncounterChoices[], int nEncounterChoicesSize, 
                mon_type *pFakedex, int nMonCreated, box_type pCaughtMons[], int *pCapturedMons, stringMsg sMessage);

void 
exploration(stringIn sInput, int nInputSize, stringChoice sExploreChoices[], int nExploreChoicesSize, 
                    int *pActiveCell, int nMonCreated, stringMsg sMessage);

void 
viewBox(stringIn sInput, int nInputSize, stringChoice sModeChoices[], int nModeChoicesSize, 
                mon_type *pFakedex, box_type pCaughtMons[], int *pCapturedMons, stringMsg sMessage);

void 
settings(stringIn sInput, int nInputSize, stringChoice sSettingChoices[], int nSettingChoiceSize, 
                        stringMsg sMessage);

void 
save(stringIn sInput, int nInputSize, int nMonCreated, mon_type pFakedex[], box_type pCaughtMons[], 
            int nCapturedMons, stringMsg sMessage);

void load(stringIn sInput, int nInputSize, int *pMonCreated, mon_type pFakedex[], box_type pCaughtMons[], 
            int *pCapturedMons, stringMsg sMessage);

#endif