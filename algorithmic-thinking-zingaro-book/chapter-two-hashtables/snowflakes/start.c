#include <stdio.h>
// compile with `gcc start.c` or `gcc -o out start.c`
// pipe in start.txt instead of command line params entry like this ./out < start.txt
// could also cat start.txt | ./out

int hasRepeatIntegers(int integerArray[], int integerArrayLength)
{

    for (int i=0; i < integerArrayLength; i++)
    {
        for (int j=i+1; j < integerArrayLength; j++)
        {
            printf("i is %d and j is %d, comparing values %d and %d \n", i, j, integerArray[i], integerArray[j]);
            if (integerArray[i]==integerArray[j])
            {
                printf("match found for %d and %d \n", integerArray[i], integerArray[j]);
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    int testData[5] = {1,2,3,1,5};
    int result = hasRepeatIntegers(testData, 5);
    printf("result from hasRepeatIntegers with dataset one is %d \n", result);

    int testData2[5] = {1,2,3,4,5};
    int result2 = hasRepeatIntegers(testData2, 5);
    printf("result from hasRepeatIntegers with dataset two is %d \n", result2);

    return 0;
}