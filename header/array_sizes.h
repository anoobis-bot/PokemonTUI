/******************************************
File Name: array_sizes.h

Author: Francis Zaccharie B. de Leon
Last Update: June 3, 2022

This file contains most of the macros for
declaring the sizes of arrays.
Whether char arrays, art arrays or 
list arrays
******************************************/
#ifndef LISTS_SIZE_H
#define LISTS_SIZE_H

// list arrays
#define MAINCHOICES_SIZE 5
#define DATABASECHOICES_SIZE 5
#define VIEWMONDEXCHOICES_SIZE 1
#define SETTINGCHOICES_SIZE 3
#define EXPLORATIONCHOICES_SIZE 3
#define ENCOUNTERCHOICES_SIZE 2
#define BOXCHOICES_SIZE 6


// sizes for char array for strings
// refer to definitions.h, this is the size of the strings          
#define STR_MSG_SIZE 65
#define STR_CHOICES_SIZE 20
#define STR_INPUT_STD 400

// this margin is used for error checking. the first one is for checking if the input has 
// exeeded the maximum number of elements. (e.g. is string can only handle 5 elements, if the 6th element
// is populated, then the user has exeeded the maximum input. This is so it makes sure the other
// memory values remain safe / untouched that might caused undefined behavior. 
// the second one is for the null byte.
#define STR_MARGIN 2

// array sizes for the Full name, short name, description, gender, and caught
#define FULL_NAME_SIZE 11
#define SHORT_NAME_SIZE 5
#define DESCRIPTION_SIZE 300

// how many user inputs for the mon_type struct
#define STRUCT_IN_NUM 4

// for art sizes
#define ART_TEXT_HEIGHT 3   // height of the text art (art.h)


#endif