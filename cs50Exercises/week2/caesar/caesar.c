#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// gcc -o out caesar.c -lcs50

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int argLength = strlen(argv[1]);

    for (int i = 0; i < argLength; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // determine key
    int key = atoi(argv[1]) % 26;

    // get inputs
    string plainText = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(plainText); i++)
    {
        char character = plainText[i];

        if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
        {
            // encrypt and print upper case character
            if (character >= 65 && character <= 90)
            {
                char encryptedChar = character + key;
                if (encryptedChar > 90)
                    encryptedChar -= 26;
                printf("%c", encryptedChar);
            }

            // encrypt and print lower case character
            if (character >= 97 && character <= 122)
            {
                char encryptedChar;
                if (character + key > 122)
                    encryptedChar = character + key - 26;
                else
                    encryptedChar = character + key;
                printf("%c", encryptedChar);
            }
        }
        else
        {
            // print character unaltered
            printf("%c", character);
        }
    }

    printf("\n");

    return 0;
}