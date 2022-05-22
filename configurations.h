#ifndef CONFIGURATION
#define CONFIGURATION

#define HEIGHT 17
#define WIDTH 75        // content width

#define LEFT_MARGIN 2   // margin on the left side of TUI

#define RIGHT_PAD 1     // padding on the right side of TUI
#define LEFT_PAD 1      // padding on the left side of TUI

#define ART_TEXT_HEIGHT 3   // height of the text art (art.h)

#define UP_LEFT_CORNER 218      // "┌"
#define UP_RIGHT_CORNER 191     // "┐"
#define MID_LEFT_CORNER 195     // ├
#define MID_RIGHT_CORNER 180    // ┤
#define DOWN_LEFT_CORNER 192    // "└"
#define DOWN_RIGHT_CORNER 217   // "┘"
#define V_LINE "|"
#define H_LINE "-"

#define DEX_MAX 150             // maximuim number of entities in the fakedex database

// refer to definitions.h, this is the size of the strings          
#define STR_MSG_SIZE 65
#define STR_CHOICES_SIZE 15
#define STR_INPUT_STD 65
#define STR5_ARR_SIZE 5
#define STR11_ARR_SIZE 11
#define STR300_ARR_SIZE 300

// this margin is used for error checking. the first one is for checking if the input has 
// exeeded the maximum number of elements. (e.g. is string can only handle 5 elements, if the 6th element
// is populated, then the user has exeeded the maximum input. This is so it makes sure the other
// memory values remain safe / untouched that might caused undefined behavior. 
// the second one is for the null byte.
#define STR_MARGIN 2   

#endif