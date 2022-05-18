#ifndef UTIL_H
#define UTIL_H

// include libraries
#include <stdio.h>
#include <string.h>


// type definitions
typedef char string5[6];
typedef char string11[12];
typedef char string300[301];


// macro define
#define CLEAR "\e[1;1H\e[2J"


// struct definition
typedef struct 
{
    string11 sFull_Name;
    string5 sShort_Name;
    string300 sDescript;
    char cGender;
    short nCaught;
} mon_type;


#endif