/******************************************
File Name: art_proto.h

Author: Francis Zaccharie B. de Leon
Last Update: May 22, 2022

This file contains the function prototypes
of the functions in art.c file
******************************************/

#ifndef ART_PROTO_H
#define ART_PROTO_H

#include "../configurations.h"

void colorReset();
void forgroundGreen();
void foregroundRed();
void foregroundBrown();

void displayArt(char sArt[][WIDTH], int nArtHeight,int *currRow);
void printGrass(int ActiveCell, int *currRow);

#endif