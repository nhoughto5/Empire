#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define LINE_SIZE 20

// ====================================== //
// Utilities
// ====================================== //

int readNumber(char* input) {
    int ret;
    //sscanf should fill a single variable (i.e. N), if not something has gone wrong
    if (sscanf(input, "%d", &ret) != 1) return -1;
    return ret;
}

void printArray(int* arr, int n, bool newLine)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d:%d ", i, arr[i]);
    }

    if (newLine) printf("\n");
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

int getDistance(int numCities, int graph[][numCities], int x, int y)
{
    int ret1 = graph[x][y];
    if (ret1 > -1) return ret1;
    int ret2 = graph[y][x];
    if (ret2 > -1) return ret2;
    return -1;
}

int disjkstras(int numCities, int graph[][numCities])
{
    int shortest[numCities];
    bool visited[numCities];

    // Init trackers
    
    for (int i = 0; i < numCities; ++i)
    {
        if (i > 0)
        {
            shortest[i] = INT_MAX;
        }
        visited[i] = false;
    }

    // We can immediately populate the shortest path
    // From the source city
    for (int i = 0; i < numCities; ++i)
    {
        if (graph[0][i] > -1)
        {
            shortest[i] = graph[0][i];
        }
    }

    int currentCity = 0;
    visited[currentCity] = true;
    shortest[0] = 0;
    while (true)
    {
        currentCity = findClosestNonVisitedCity(numCities, shortest, visited);
        visited[currentCity] = true;

        // For the new city we are looking at, lets look at all adjacent cities.
        for (int currentlyLookingAt = 0; currentlyLookingAt < numCities; ++currentlyLookingAt)
        {
            int g = getDistance(numCities, graph,currentCity,currentlyLookingAt);

            // If we have not visited this city and its new distance is shorter then our current record, update the record
            if (!visited[currentlyLookingAt] && g > -1 && (shortest[currentCity] + g < shortest[currentlyLookingAt]))
            {
                // Do not want to sum the old record if we have not recorded a previous record
                shortest[currentlyLookingAt] = g + ((shortest[currentCity] != INT_MAX) ? shortest[currentCity] : 0);
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
* NOTES
============================================================================================================================
Began this problem by reacquainting myself with C99 as it has been a long time since I have used it.
It took a little while to figure out the best dev environment but I went with visual studio even though its implementation of C99 is missing some features.
I then proceeded to tackle some basics, reading standard input, parsing the input and storing it into a usable matrix format.
I then spent some time converting that matrix into a more useable format by using C99’s struct features.
This in the end didn't prove to be useful so I removed that. 
I then attempted to use Kruskals’s minimum spanning tree algorithm to attempt to
find the shortest path from the “capital” to each city but it quickly became apparent that this was not the correct solution.
I then rememberd that Dijkstra's was a fairly standard way to visit every node so I tried that next.
I found working with the lower half of the adjacency matrix tricky while implementing Dijkstra so I created a transpose
matrix and filled in any missing cells.
This allowed me to succesfully implement a working solution. However if I had more time I would focus on removing the need
for it and accessing distances from the input matrix directly. 
Time Log:
    11/20/2020: About 45 minutes reading and understanding the problem
    11/21/2020: ~ 4.5 hours to get a basic working solution
    11/22/2020: ~ 2.5 hours of dev time debugging and optimizing. Another 1hr to come up with a second test sample and testing. 
Additional sample input tested:
9
4
x 8
x x 7
x x x 9
x x 4 14 10
x x x x x 2
8 11 x x x x 1
x x 2 x x x 6 7
============================================================================================================================
~~~~~~~~~~~~
PLEASE NOTE:
~~~~~~~~~~~~
    I "inlined" a few helper functions to boost performance. I had no issues with this in Visual Studio or with a CLANG compliler. 
    My locally installed MinGW compiler however, did not like the inline for some reason. If I had more time I would add some precompiler 
    statements to ensure portability with the inline command.
    If you have any compile issues with it when you run your test please let me know and I will send you a new version without them.
*/
int main(int argc, char** argv) {
    char line[LINE_SIZE];
    int N = 0;

    // Get the N value
    fgets(line, LINE_SIZE, stdin);
    N = readNumber(line);
    int matrix[N][N];

    int ii = 0;
    while (fgets(line, LINE_SIZE, stdin)) {
        char* str = strtok(line, " ");
        int i = 0;
        while (str != NULL) {
            int value = readNumber(str);
            matrix[ii][i] = value;
            str = strtok(NULL, " ");
            ++i;
        }
        ii++;
    }

    // Invert the matrix to make working with indices slightly easier
    int transposedMatrix[N][N];

    // Populate the transpose matrix
    // TODO: Find way to not need this
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

    printf("%d\n", disjkstras(N, transposedMatrix));
    return 0;
}
