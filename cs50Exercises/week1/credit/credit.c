// gcc -o out credit.c -lcs50 
// https://cs50.harvard.edu/college/2022/fall/psets/1/credit/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool isValidNumber(string creditCardNumber)
{
    // TODO 
    return true;    
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
        return "AMEX";
    }

    // Mastercard: 16 digits; first two digits are 51, 52, 53, 54, 55 
    if (numberLength == 16 && firstNumber == fiveInASCII)
    {
        int secondNumberAsInt = (int)secondNumber;
        if (secondNumberAsInt >= oneInASCII && secondNumberAsInt <= fiveInASCII)
        {
            return "MASTERCARD";
        }
    }

    // Visa: 13 or 16 digits; first digit is 4 (52 in ASCII)
    if ((numberLength == 13 || numberLength == 16) && firstNumber == fourInASCII)
    {
        return "VISA";
    }

    return "";
}

int main(void) 
{

 string creditCardNumber = get_string("Number: ");
 string cardType = getCardType(creditCardNumber);
 
 if (strcmp(cardType, "") == 0)
 {
    printf("INVALID");
 } else 
 {
    bool isValid = isValidNumber(creditCardNumber);
    if (!isValid)
    {
        printf("INVALID");
    } else 
    {
        printf("%s", cardType);
    }
 }
 
}