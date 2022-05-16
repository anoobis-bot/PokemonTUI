#include <stdio.h>

int main(void)
{
    printf("\x1b[4m");
    printf("> Hello World!\n");

    printf("\x1b[0m");
    printf("%c---------------------------------%c\n", 218, 1022);

    return 0;
}