// compile with `gcc food-lines.c` or `gcc -o outputFilename food-lines.c`
// pipe in food-lines.txt instead of command line params entry like this ./out < food-lines.txt
// could also cat food-lines.txt | ./out
#define MAX_LINES 100 
#include <stdio.h>


// parameters 
// n number of lines
// m amount of people arrive and each goes to the shortest line 

// what don't we know
// how many poeple are in each line

// worked example
// 3 lines as follows
// line 1 has 3 people
// line 2 has 2 people
// line 3 has 5 people
// four new people arrive 
// the first person will join line 2 which will now have 3 people 
// the next two people will join line 1 and line 2 respsectively which now both have 4 people 
// the next person can join either line 1 or line 2

int getShortestLineIndex(int lines[], int numberOfLines)
{
    int shortestIndex = 0;
    for (int i=0; i < numberOfLines; i++)
    {
        if (lines[i] < lines[shortestIndex])
        {
            shortestIndex = i;
        }
    }
    return shortestIndex;
}

// we actually need to print the length of the line that gets joined
// not the final lengths of all the lines
void solve(int numberOfLines, int numberOfArrivals, int peopleInEachLine[])
{

    for (int i=0; i<numberOfArrivals; i++)
    {
        int shortestLineIndex = getShortestLineIndex(peopleInEachLine, numberOfLines);
        printf("%d\n", peopleInEachLine[shortestLineIndex]);
        peopleInEachLine[shortestLineIndex]++;
    }
}

int main()
{
 //   int lines[3] = {3,2,5};
 //   solve(3,4, lines);
 //   return 0;
    int lines[MAX_LINES];
    int n, m, i;
    scanf("%d%d", &n, &m);
    for (int i=0; i<n; i++)
    {
        scanf("%d", &lines[i]);
    }
    solve(n, m, lines);
    return 0;
}