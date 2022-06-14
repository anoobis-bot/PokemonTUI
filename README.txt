Hello esteemed professors and programmers!

Thank you for taking reviewing my code. I worked hard to accomplish this fairly large project.

This file contains the discriptions and what to expect in each directories. Pasted below will also be the input for 
the terminal to compile all the source codes.

COMPILATION
Go inside the "src" directory and open Powershell (preferably) or CMD. Then paste this command:
gcc main.c box_imp.c util.c art.c -Wall -std=c99 -o "..\\Fakemon.exe"

If without warnings (which, there shouldn't be) enter in the command line "cd ..\\" which will bring you back to the 
root folder. type ls (or dir if using cmd) to make sure that Fakemon.exe exists.

Lastly type ./Fakemon and have fun!


DIRECTORIES
- src
    This directory contains all the c source code that I used in making the program. The details of each c file is already
    in their header comments.

- prototypes
    This directory has the header files containing the function prototypes of each c file. Naming convention
    is "<c file name>_proto.h" every function in that particular c file has a prototype in the specified
    proto header file.

- header
    This file contains most of the declaration and definitions that the source files rely on. It contains struct
    definitions, text art and macro definitions for array.


configurations.h
    This file contains confirgurable in-game mechanics such as catch rate, max number of fakemons to be caught,
    the height and width of the TUI, the borders used, etc...
 
