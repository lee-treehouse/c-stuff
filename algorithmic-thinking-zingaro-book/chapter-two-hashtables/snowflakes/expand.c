#include <stdio.h>
// compile with `gcc start.c` or `gcc -o out start.c`
// pipe in start.txt instead of command line params entry like this ./out < start.txt
// could also cat start.txt | ./out


int EachItemInArrayIsSameGivenOffset(int firstIntegerArray[], int secondIntegerArray[], int integerArrayLength, int offset)
{
        
    for (int i=0; i < integerArrayLength; i++)
    {

    int adjustedOffset = offset + i;

    if (adjustedOffset >= integerArrayLength)
    {
        adjustedOffset = adjustedOffset % integerArrayLength;
        // if adjustedOffset was 5 and length is 5, offset becomes 0
        // if adjustedOffset was 6 and length is 5, offset becomes 1
    }

        // printf("comparing item %d and item %d \n", i, adjustedOffset);
        if (firstIntegerArray[i] != secondIntegerArray[adjustedOffset])
        {
           // printf("%d - %d items do not match \n\n", firstIntegerArray[i], secondIntegerArray[adjustedOffset]);
            return 0;
        }
    }
    return 1;
}

int EachItemInArrayIsSameForAtLeastOnePossibleOffset(int firstIntegerArray[], int secondIntegerArray[], int integerArrayLength)
{
        
    for (int i=0; i < integerArrayLength; i++)
    {
        int result = EachItemInArrayIsSameGivenOffset(firstIntegerArray, secondIntegerArray, integerArrayLength, i);
        if (result == 1)
        {
            return 1;
        }
    }
    return 0;
}




int EachItemInArrayIsSame(int firstIntegerArray[], int secondIntegerArray[], int integerArrayLength)
{
    for (int i=0; i < integerArrayLength; i++)
    {
        if (firstIntegerArray[i] != secondIntegerArray[i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{

    int TestArray1[5] = {1,2,3,4,5};
    int TestArray2[5] = {1,2,3,4,5};
    
    int result = EachItemInArrayIsSameForAtLeastOnePossibleOffset(TestArray1, TestArray2, 5);
    printf("result from EachItemInArrayIsSameForAllPossibleOffsets with testArray one and two is %d \n", result);

    int TestArray3[5] = {1,2,3,4,5};
    int TestArray4[5] = {5,1,2,3,4};
    
    int result2 = EachItemInArrayIsSameForAtLeastOnePossibleOffset(TestArray3, TestArray4, 5);
    printf("result from EachItemInArrayIsSameForAllPossibleOffsets with testArray three and four is %d \n", result2);


   int TestArray5[5] = {1,2,3,4,5};
    int TestArray6[5] = {4,5,1,2,3};
    
    int result3 = EachItemInArrayIsSameForAtLeastOnePossibleOffset(TestArray5, TestArray6, 5);
    printf("result from EachItemInArrayIsSameForAllPossibleOffsets with testArray five and six is %d \n", result3);

    int TestArray7[5] = {1,2,3,4,5};
    int TestArray8[5] = {1,2,3,4,0};
    
    int result4 = EachItemInArrayIsSameForAtLeastOnePossibleOffset(TestArray7, TestArray8, 5);
    printf("result from EachItemInArrayIsSameForAllPossibleOffsets with testArray seven and eight is %d \n", result4);


    int TestArray9[5] = {1,2,3,4,5};
    int TestArray10[5] = {2,3,4,5,1};
    
    int result5 = EachItemInArrayIsSameForAtLeastOnePossibleOffset(TestArray9, TestArray10, 5);
    printf("result from EachItemInArrayIsSameForAllPossibleOffsets with testArray nine and ten is %d \n", result5);


    return 0;
}