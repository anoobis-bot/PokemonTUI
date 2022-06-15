/******************************************
File Name: art_proto.h

Author: Francis Zaccharie B. de Leon
Last Update: June 12, 2022

This file contains the function prototypes
of the functions in util.c file
******************************************/

#ifndef UTIL_PROTO_H
#define UTIL_PROTO_H

#include "../header/array_sizes.h"
#include "../configurations.h"

void 
printSpace(int nNumSpace);

void 
printLeftStart();

void 
printRightRemain(int nContentLen);

void 
printBottomRemain(int nCurrRow);

void 
printFillerLines(int nQuantity, int *nCurrRow);

void 
setMessage(char *sMessage, char *sText);

void 
printHeader(char sArtText[][WIDTH]);

void 
printRemark(char *sMessage);

int 
getInput(char *sInput, int nInputSize, char sChoices[][STR_CHOICES_SIZE], int nChoicesSize, char *sErrorFeedBack);

void 
printChoices(char sChoices[][STR_CHOICES_SIZE], int nNumElem, int nColumn, int nRow, char cFormat, int *nCurrRow);

void 
printText(char *sTempText, char cFormat, int *nCurrRow);

int 
printFileNames(char *sPath, int *nCurrRow);

int 
fileExists(const char *sFname);

int 
deleteSav(char *sFname);

void 
printFormatNum(int nNum);

int 
onlyLetters(const char *sWord, const int nWordLen);

void 
toUpperWord(char sWord[], const int nWordLen);

#endif