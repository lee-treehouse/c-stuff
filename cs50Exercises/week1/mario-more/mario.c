//gcc -o out mario.c -lcs50
// https://cs50.harvard.edu/college/2022/fall/psets/1/mario/more/
#include <cs50.h>
#include <stdio.h>

int printPyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {

        // print spaces before left hand side of pyramid
        for ( int j = height - i; j >= 1; j-- )
        {
            printf(" ");
        }

        // print hashes that make up left hand side of pyramid
        for ( int j = 1; j <= i; j++ )
        {
            printf("#");
        }

        // print spaces that are the middle column of the pyramid
        printf("  ");

        // print hashes that make up right hand side of pyramid
        for ( int j = 1; j <= i; j++ )
        {
            printf("#");
        }

        printf("\n");
    }
    return 0;
}

int askForHeight()
{
    return get_int("Height: ");
}


int main(void) 
{
    int height;

    while (!height || height < 1 || height > 8)
    {
        height = askForHeight();
    }

    printPyramid(height);
}

