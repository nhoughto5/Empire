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

int* readLine(char* input, int* row, int size)
{
    char* str = strtok(input, " ");
    int i = 0;
    while (str != NULL)
    {
        int value = readNumber(str);
        row[i] = value;
        str = strtok(NULL, " ");
        ++i;
    }
    return row;
}

void testMatrix(int** matrix, int size)
{
    printf("Test\n");
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    char line[LINE_SIZE];
    int N = 0;

    // Get the N value
    fgets(line, LINE_SIZE, stdin);

    N = readNumber(line);

    // Create an array of arrays size N
    int** matrix = (int**)malloc((N - 1) * sizeof(int));
    for (int i = 0; i < (N - 1); i++)
    {
        matrix[i] = (int*)malloc((i + 1) * sizeof(int));
    }
        
    int i = 0;
    while (fgets(line, LINE_SIZE, stdin))
    {
        matrix[i] = readLine(line, matrix[i], i);
        ++i;
    }

    testMatrix(matrix, N - 1);

    return 0;
}