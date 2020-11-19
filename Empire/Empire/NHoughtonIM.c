#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    printf("NumArgs: %d\n", argc);

    char* line = NULL;
    size_t len = 0;
    size_t lineSize = 0;

    char name[10];
    while (fgets(name, 10, stdin))
    {
        printf("Hello %s", name);
    }

    return 0;
}