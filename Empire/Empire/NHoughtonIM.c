#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

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
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++)
        {
            printf("%d:%d=%d ", i, j, matrix[i][j]);
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

void printArray(int* arr, int n, bool newLine)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d:%d ", i, arr[i]);
    }

    if (newLine) printf("\n");
}

void printBoolArray(bool* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        bool v = arr[i];
        printf("%s ", v ? "true" : "false");
    }
    printf("\n");
}

// ====================================== //
// Dijkstra's
// ====================================== //

int findClosestNonVisitedCity(int numCities, int* weights, bool* visited)
{
    int smallest = INT_MAX;
    int index = -1;

    for (int i = 1; i < numCities; ++i)
    {
        int w = weights[i];
        bool v = visited[i];
        if (!visited[i] && weights[i] < smallest)
        {
            smallest = weights[i];
            index = i;
        }
    }

    return index;
}

bool visitedAllCities(bool* visited, int numCities)
{
    for (int i = 0; i < numCities; ++i)
    {
        if (!visited[i])
        {
            return false;
        }
    }
    return true;
}

int largestDistance(int numCities, int* distances)
{
    int largest = 0;
    for (int i = 0; i < numCities; ++i)
    {
        if (distances[i] > largest)
        {
            largest = distances[i];
        }
    }

    return largest;
}

int inline getDistance(int** graph, int x, int y)
{
    int ret1 = graph[x][y];
    if (ret1 > -1) return ret1;
    int ret2 = graph[y][x];
    if (ret2 > -1) return ret2;
    return -1;
}

int disjkstras(int numCities, int** graph)
{
    int* shortest = (int*)malloc((numCities) * sizeof(int));
    bool* visited = (bool*)malloc((numCities) * sizeof(bool));

    // Init trackers
    shortest[0] = 0;
    for (int i = 0; i < numCities; ++i)
    {
        if (i > 0)
        {
            shortest[i] = INT_MAX - 1;
        }
        visited[i] = false;
    }

    for (int i = 0; i < numCities; ++i)
    {
        if (graph[0][i] > -1)
        {
            shortest[i] = graph[0][i];
        }
    }

    int currentCity = 0;
    visited[0] = true;
    while (true)
    {
        currentCity = findClosestNonVisitedCity(numCities, shortest, visited);
        visited[currentCity] = true;

        for (int currentlyLookingAt = 0; currentlyLookingAt < numCities; ++currentlyLookingAt)
        {
            int g = getDistance(graph,currentCity,currentlyLookingAt);
            
            if (!visited[currentlyLookingAt] && g > -1 && (shortest[currentCity] + g < shortest[currentlyLookingAt]))
            {
                // First time inspecting this city
                if (shortest[currentCity] != (INT_MAX - 1))
                {
                    shortest[currentlyLookingAt] = shortest[currentCity] + g;
                }
                else
                {
                    shortest[currentlyLookingAt] = g;
                }
            }
        }
        if (visitedAllCities(visited, numCities))
        {
            break; // Disjkstra complete
        }
    }

    return largestDistance(numCities, shortest);
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
    int** matrix = (int**)malloc((N - 1) * sizeof(int));
    for (int i = 0; i < (N - 1); i++) {
        matrix[i] = (int*)malloc((i + 1) * sizeof(int));
    }

    int ii = 0;
    while (fgets(line, LINE_SIZE, stdin)) {
        matrix[ii] = readLine(line, matrix[ii], ii);
        ++ii;
    }

    // Invert the matrix to make working with indices slightly easier
    int** transposedMatrix = (int**)malloc((N) * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        transposedMatrix[i] = (int*)malloc((N - 1) * sizeof(int));
    }

    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N - 1; j++)
        {
            int t;

            if (j < i || i >= (N - 1) || j >= (N - 1))
            {
                t = -1;
            }
            else
            {
                t = matrix[j][i];
            }
            transposedMatrix[i][j + 1] = t;
        }
    }

    free(matrix);
    int result = disjkstras(N, transposedMatrix);
    assert(result == 35);
    printf("%d", result);
    free(transposedMatrix);
    return 0;
}