#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
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

// ====================================== //
// Dijkstra's
// ====================================== //


int findClosestNonVisitedCity(int numCities, int* weights, bool* visited)
{
    int smallest = INT_MAX;
    int index = -1;
    for (int i = 1; i < numCities; ++i)
    {
        if (!visited[i] && weights[i] < smallest && weights[i] > -1)
        {
            smallest = weights[i];
            index = i;
        }
    }

    if (index == -1)
    {
        for (int i = 1; i < numCities; ++i)
        {
            if (!visited[i] && weights[i] < smallest)
            {
                smallest = weights[i];
                index = i;
            }
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

int inline largestDistance(int numCities, int* distances)
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

int inline getDistance(int** graph, int currentCity, int lookAt)
{
    if (currentCity == lookAt)
    {
        return -1;
    }
    else if (currentCity >= lookAt)
    {
        //return graph[currentCity][lookAt -1];
        return graph[currentCity - 1][lookAt];
    }

    return graph[lookAt - 1][currentCity];
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
            shortest[i] = INT_MAX;
        }
        visited[i] = false;
    }

    // We can immediately populate the shortest path
    // From the source city
    for (int i = 0; i < numCities-1; ++i)
    {
        if (graph[i][0] > -1)
        {
            shortest[i + 1] = graph[i][0];
        }
    }

    int currentCity = 0;
    visited[currentCity] = true;
    while (true)
    {
        //currentCity = findClosestNonVisitedCity(graph, currentCity, numCities, shortest, visited);
        currentCity = findClosestNonVisitedCity(numCities, shortest, visited);
        visited[currentCity] = true;

        // For the new city we are looking at, lets look at all adjacent cities.
        for (int currentlyLookingAt = 0; currentlyLookingAt < numCities; ++currentlyLookingAt)
        {
            int g = getDistance(graph, currentCity, currentlyLookingAt);

            // If we have not visited this city and its new distance is shorter then our current record, update the record
            if (!visited[currentlyLookingAt] && g > -1 && ((shortest[currentCity] + g) < shortest[currentlyLookingAt]))
            {
                // Do not want to sum the old record if we have not recorded a previous record
                if (shortest[currentCity] != INT_MAX)
                {
                    shortest[currentlyLookingAt] = g + shortest[currentCity];
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
* NOTES
============================================================================================================================
Began this problem by reacquainting myself with C99 as it has been a long time since I have used it.
It took a little while to figure out the best dev environment but I went with visual studio even though its implementation of C99 is missing some features.

I then proceeded to tackle some basics, reading standard input, parsing the input and storing it into a usable matrix format.
I then spent some time converting that matrix into a more useable format by using C99�s struct features.
This in the end didn't prove to be useful so I removed that.

I then attempted to use Kruskals�s minimum spanning tree algorithm to attempt to
find the shortest path from the �capital� to each city but it quickly became apparent that this was not the correct solution.

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

    // Create an array of arrays size N
    int** matrix = (int**)malloc((N - 1) * sizeof(int));
    for (int i = 0; i < (N - 1); ++i) {
        matrix[i] = (int*)malloc((i + 1) * sizeof(int));
    }

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

    printf("%d", disjkstras(N, matrix));

    return 0;
}