#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 20



int main(int argc, char** argv)
{
    char line[LINE_SIZE];
    int i = 0, n = 0;
    while (fgets(line, LINE_SIZE, stdin))
    {
        if (i == 0)
        {
            sscanf_s(line, "%d", &n);
            printf("N %d\n", n);
        }
        else
        {
            printf("Line %s", line);
        }
        i++;
    }

    return 0;
}