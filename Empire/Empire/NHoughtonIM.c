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
    // Allocate an array of the size of the row the matrix
    int* ret = (int*)malloc(size * sizeof(int));
    char* str = strtok(input, " ");
    int i = 0;
    while (str != NULL)
    {
        int value = readNumber(str);
        ret[i] = value;
        str = strtok(NULL, " ");
        ++i;
    }
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
        matrix[i] = readLine(line, i);
        ++i;
    }

    return 0;
}