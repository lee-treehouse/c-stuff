// compile with `gcc food-lines.c` or `gcc -o outputFilename food-lines.c`

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

void solve(int numberOfLines, int numberOfArrivals, int peopleInEachLine[])
{

    for (int i=0; i<numberOfArrivals; i++)
    {
        int shortestLineIndex = getShortestLineIndex(peopleInEachLine, numberOfLines);
        peopleInEachLine[shortestLineIndex]++;
    }

    for (int i=0; i < numberOfLines; i++)
    {
        printf("%d\n", peopleInEachLine[i]);
    }

}

int main()
{
    int lines[3] = {3,2,5};
    solve(3,4, lines);
    return 0;
}