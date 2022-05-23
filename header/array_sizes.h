#ifndef LISTS_SIZE_H
#define LISTS_SIZE_H

#define MAINCHOICES_SIZE 5


// sizes for char array for strings
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


// for art sizes
#define ART_TEXT_HEIGHT 3   // height of the text art (art.h)

#endif