#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    printf("NumArgs: %d\n", argc);

    FILE* file;
    char filename[200];
    // char *newline;
    // printf("Before");
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        printf("Error");
        return -1; // Input error / EOF
    }

    printf("Content: %s", filename);
    return 0;
}