#ifndef UTIL
#define UTIL

// include libraries
#include <stdio.h>


// type definitions
typedef char string5[6];
typedef char string11[12];
typedef char string300[301];


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