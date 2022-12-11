// get cs50.h from here https://github.com/cs50/libcs50
// when compiling I need to link cs50 like this 
// gcc -o out hello.c -lcs50
#include <stdio.h>
#include <cs50.h>

int main()
{
    string name = get_string("Howdy! What is your name, friend? \n");
    printf("hello, %s\n", name);
    return 0;
}