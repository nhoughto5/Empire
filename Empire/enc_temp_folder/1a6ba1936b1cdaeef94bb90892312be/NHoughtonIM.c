#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 20

// ====================================== //
// Utilities
// ====================================== //
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

// ====================================== //
// Minimum Spanning Tree
// ====================================== //

struct Route {
    int cityA, cityB, time;
};

int routeSort(const void* a, const void* b)
{
    struct Route* routeA = (struct Route*)a;
    struct Route* routeB = (struct Route*)b;
    int ret = 0;

    if (routeA->time > routeB->time) {
        ret = 1;
    }
    else {
        ret = -1;
    }

    return ret;
}

void createAndSortRoutes(struct Route* routes, int** matrix, int numCities, int numRoutes)
{
    int routeNum = 0;
    for (int i = 1; i <= (numCities - 1); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            struct Route* route = malloc(sizeof(struct Route));
            if (route != NULL)
            {
                //printf("Route: %d -> %d   = %d\n", j,i, matrix[i-1][j]);
                route->cityA = j;
                route->cityB = i;
                route->time = matrix[i-1][j];
                printf("Route: %d -> %d   = %d\n", route->cityA, route->cityB, route->time);
                routes[routeNum] = *route;
                ++routeNum;
            }
            else
            {
                fprintf(stderr, "Failed to create Route on heap");
                exit(-1);
            }
        }
    }

    qsort(routes, numRoutes, sizeof(struct Route), routeSort);
}

int findMinimumTime(int** matrix, int numCities)
{
    int numberOfRoutes = (numCities * (numCities - 1)) / 2; // EQ for lower half of matrix
    struct Route* routes = (struct Route*)malloc(numberOfRoutes * sizeof(struct Route));

    createAndSortRoutes(routes, matrix, numCities, numberOfRoutes);

    printf("\n\n Sorted \n");
    for (int i = 0; i < numberOfRoutes; ++i)
    {
        printf("Route: %d -> %d   = %d\n", routes[i].cityA, routes[i].cityB, routes[i].time);
    }

    free(routes);
    return 0;
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

    //testMatrix(matrix, N - 1);
    printf("%d", findMinimumTime(matrix, N));
    free(matrix);
    return 0;
}