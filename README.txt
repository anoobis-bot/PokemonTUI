FRANCIS ZACCHARIE DE LEON | S17

Hello esteemed professors and programmers!

Thank you for taking the time on reviewing my code. I worked hard to accomplish this fairly large project.

This file contains the discriptions and what to expect in each directories. Pasted below will also be the input for 
the terminal to compile all the source codes.

COMPILATION
Go inside the "src" directory and open Powershell (preferably) or CMD. Then paste this command:
gcc main.c box_imp.c util.c art.c -Wall -std=c99 -o "..\\Fakemon.exe"

If without warnings (which, there shouldn't be) enter in the command line "cd ..\\" which will bring you back to the 
root folder. type ls (or dir if using cmd) to make sure that Fakemon.exe exists.

Lastly type ./Fakemon and have fun!

SYSTEM
- This was made in a Windows environment, although, I have not used any windows specific libraries. It may work
	using Unix based OS

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
 

KNOWN ISSUES
Apparently, the snprintf() implementation used in my MinGw compiler is different.
The size parameter is different comparing to the man pages online
the function DOES NOT take n - 1 characters. It takes n characters
Furthormore, itdoesn't automatically put a null character at n - 1th element
Meaning, if I have a size n, and have a buffer sized 3
If I were to put snprintf(outputBuffer, 3, "Hello!");
Instead of putting inside outputBuffer the elements {'H', 'e','\0'} as what the man pages has told
My compiler would put {'H', 'e','l'} instead! This caused me some worries as it could produce undefined behaviors.
That is why, in the setMessage function, I would always put a '\0' at the end of the array

The issue here is if you were to compile this using a different compiler, edge cases may occur where your
c compiler version uses the n - 1 in printfs instead of the n size in my program, which could cut off some words