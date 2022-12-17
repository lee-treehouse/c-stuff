// gcc -o out credit.c -lcs50 
// https://cs50.harvard.edu/college/2022/fall/psets/1/credit/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// not ascii number but actual integer value 
int getIntFromChar(char value)
{
    return (int)(value) - 48;
}

// string getStringFromInt(int value)
// {
//     char result[20];
//     sprintf(result, "%d", value);
//     return result;
// }

int getSumOfEachDigitsInInteger(int value)
{
        //string valueAsString = getStringFromInt(value);

    char valueAsString[20];
    sprintf(valueAsString, "%d", value);

        //printf ("string value from %d is %s \n", value, valueAsString);
        int sum = 0;
        for (int i = 0; i < strlen(valueAsString); i++)
        {
            sum += getIntFromChar(valueAsString[i]);
        }
        return sum;
}

bool isValidNumber(string creditCardNumber)
{
    int cardNumberLength = strlen(creditCardNumber);

    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    int sumStep1 = 0;
    for (int i=cardNumberLength-2; i >= 0; i-= 2)
    {
        int value = getIntFromChar(creditCardNumber[i]);

        int doubleValue = value * 2;        
        
        sumStep1 += getSumOfEachDigitsInInteger(doubleValue);
        //printf("%d \n", value);
    }


    // sum the digits that weren’t multiplied by 2.
    int sumStep2 = 0;
    for (int i=cardNumberLength-1; i >= 0; i-= 2)
    {
        int value = getIntFromChar(creditCardNumber[i]);
        sumStep2 += value;
        //printf("%d \n", value);
    }

    // sum the results of step 1 and the results of step 2
    int finalSum = sumStep1 + sumStep2;

    if (finalSum % 10 == 0)
    {
        //printf("%s is Valid \n", creditCardNumber);
        return true;
    }

    //printf("%s is not Valid \n", creditCardNumber);
    return false;    
}

string getCardType(string creditCardNumber)
{
    
    int numberLength = strlen(creditCardNumber);

    char firstNumber = creditCardNumber[0];
    char secondNumber = creditCardNumber[1];

    int oneInASCII = 49;
    int threeInASCII = 51;
    int fourInASCII = 52;
    int sevenInASCII = 55;
    int fiveInASCII = 53;

    // AMEX: 15 digits; first two digits are 34 or 37
    if (numberLength == 15 && firstNumber == threeInASCII && (secondNumber == fourInASCII || secondNumber == sevenInASCII))
    {
        //printf("%s is Amex \n", creditCardNumber);
        return "AMEX";
    }

    // Mastercard: 16 digits; first two digits are 51, 52, 53, 54, 55 
    if (numberLength == 16 && firstNumber == fiveInASCII)
    {
        int secondNumberAsInt = (int)secondNumber;
        if (secondNumberAsInt >= oneInASCII && secondNumberAsInt <= fiveInASCII)
        {
        //printf("%s is Mastercard \n", creditCardNumber);
            return "MASTERCARD";
        }
    }

    // Visa: 13 or 16 digits; first digit is 4 (52 in ASCII)
    if ((numberLength == 13 || numberLength == 16) && firstNumber == fourInASCII)
    {
       // printf("%s is VISA \n", creditCardNumber);
        return "VISA";
    }

    //printf("%s is invalid cardtype \n", creditCardNumber);
    return "";
}

int main(void) 
{

 string creditCardNumber = get_string("Number: ");
 string cardType = getCardType(creditCardNumber);
 
 if (strcmp(cardType, "") == 0)
 {
    printf("INVALID\n");
 } else 
 {
    bool isValid = isValidNumber(creditCardNumber);
    if (!isValid)
    {
        printf("INVALID\n");
    } else 
    {
        printf("%s\n", cardType);
    }
 }
 
}