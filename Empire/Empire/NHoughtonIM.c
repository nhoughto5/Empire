#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LINE_SIZE 20

// ====================================== //
// Utilities
// ====================================== //
inline int readNumber(char* input) {
    int ret;
    //sscanf should fill a single variable (i.e. N), if not something has gone wrong 
    if (sscanf(input, "%d", &ret) != 1) return -1;
    return ret;
}

int* readLine(char* input, int* row, int size) {
    char* str = strtok(input, " ");
    int i = 0;
    while (str != NULL) {
        int value = readNumber(str);
        row[i] = value;
        str = strtok(NULL, " ");
        ++i;
    }
    return row;
}

void testMatrix(int** matrix, int size) {
    printf("Test\n");
    for (int i = 0; i < size-1; ++i) {
        for (int j = 0; j <= i; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int findSmallestInArray(int* arr, int n)
{
    int smallest = INT_MAX, index = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] < n)
        {
            smallest = arr[i];
            index = i;
        }
    }
    return index;
}

// ====================================== //
// Dijkstra's
// ====================================== //

int disjkstras(int numCities, int** graph)
{
    int* previous = (int*)malloc((numCities) * sizeof(int));
    int* shortest = (int*)malloc((numCities) * sizeof(int));
    bool* visited = (bool*)malloc((numCities) * sizeof(bool));
    bool* unvisted = (bool*)malloc((numCities) * sizeof(bool));

    // Init trackers
    shortest[0] = 0;
    for (int i = 0; i < numCities; ++i)
    {
        if (i > 0) shortest = INT_MAX;
        visited[i] = false;
        unvisted[i] = true;
    }

    int currentCity = 0;


    return 0;
}

/*
Began this problem by reacquainting myself with C99 as it has been a long time since I have used it.
It took a little while to figure out the best dev environment but I went with visual studio even though its implementation of C99 is missing some features.

I then proceeded to tackle some basics, reading standard input, parsing the input and storing it into a usable matrix format.
I then spent some time converting that matrix into a more useable format by using C99�s struct features.

I then attempted to use Kruskals�s minimum spanning tree algorithm to attempt to
find the shortest path from the �capital� to each city but it quickly became apparent that this was not the correct solution.

I then rememberd that Dijkstra's was a fairly standrad way to visit every node so I tried that next.
*/
int main(int argc, char** argv) {
    char line[LINE_SIZE];
    int N = 0;

    // Get the N value
    fgets(line, LINE_SIZE, stdin);

    N = readNumber(line);

    // Create an array of arrays size N
    // Invert the matrix to make dijkstra easier
    int** matrix = (int**)malloc((N - 1) * sizeof(int));
    for (int i = 0; i < (N - 1); i++) {
        matrix[i] = (int*)malloc((i+1) * sizeof(int));
    }



    int ii = 0;
    while (fgets(line, LINE_SIZE, stdin)) {
        matrix[ii] = readLine(line, matrix[ii], ii);
        ++ii;
    }

    int** transposedMatrix = (int**)malloc((N - 1) * sizeof(int));
    for (int i = 0; i < (N - 1); i++) {
        transposedMatrix[i] = (int*)malloc((N - 1 - i) * sizeof(int));
        for (int j = i; j < N - 1; ++j)
        {
            int t = matrix[j][i];
            transposedMatrix[i][j] = matrix[j][i];
            printf("%d ", t);
        }
        printf("\n");
    }

    testMatrix(matrix, N);

    printf("%d", disjkstras(N, matrix));
    free(matrix);
    return 0;
}