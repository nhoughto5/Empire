#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 20

inline int readNumber(char* input)
{
    int ret;
    //sscanf should fill a single variable (i.e. N), if not something has gone wrong 
    if (sscanf(input, "%d", &ret) != 1) return -1;
    return ret;
}

int* readLine(char* input, int size)
{
    int* ret = (int*)malloc(size * sizeof(int));
    printf("Line:");
    char* str = strtok(input, " ");
    while (str != NULL)
    {
        //printf(" %s", str);
        printf(" %d", readNumber(str));
        str = strtok(NULL, " ");
    }

    printf("\n");
    return ret;
}

int main(int argc, char** argv)
{
    char line[LINE_SIZE];
    int N = 0;

    // Get the N value
    fgets(line, LINE_SIZE, stdin);

    N = readNumber(line);

    // Create an array of arrays size N
    int** matrix = (int**)malloc(N * sizeof(int));
    int i = 1;
    while (fgets(line, LINE_SIZE, stdin))
    {
        //printf("Line %s\n", line);
        matrix[i] = readLine(line, i);
        //char* tokens = strtok(line, " "); // seperate by spaces
        //while (tokens != NULL)
        //{
        //    //printf("Number: %s", tokens);
        //    tokens = strtok(NULL, " ");
        //    if (tokens != NULL) printf("A Number: %d", readNumber(tokens));
        //}
        ++i;
    }

    return 0;
}