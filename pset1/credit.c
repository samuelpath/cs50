#include <stdio.h>
#include <cs50.h>
#include <string.h>

int isCardLegit(long long creditCardNumber);
int getSumOfEveryOtherDigitDoubled(long long creditCardNumber);
int getSumOfRemainingDigits(long long creditCardNumber);
string getCreditCardType(long long creditCardNumber);
bool isVisa(string creditCardString);
bool isAmex(string creditCardString);
bool isMastercard(string creditCardString);
bool firstCharIsNumberFive(string creditCardString);
bool secondCharIsNumberBetweenOneAndFive(string creditCardString);

int main(void)
{
    long long creditCardNumber = get_long_long("Number: ");

    if (isCardLegit(creditCardNumber))
    {
        printf("%s\n", getCreditCardType(creditCardNumber));
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

int isCardLegit(long long creditCardNumber)
{
    int sumOfEveryOtherDigitDoubled = getSumOfEveryOtherDigitDoubled(creditCardNumber);
    int sumOfRemainingDigits = getSumOfRemainingDigits(creditCardNumber);
    int aggregatedSums = sumOfEveryOtherDigitDoubled + sumOfRemainingDigits;
    return (aggregatedSums % 10) == 0;
}

int getSumOfEveryOtherDigitDoubled(long long creditCardNumber)
{
    int sum = 0;
    int idxDigit = 0;
    while (creditCardNumber)
    {
        int currentDigit = creditCardNumber % 10;
        if (idxDigit % 2 == 1)
        {
            int currentDigitDoubled = currentDigit * 2;
            if (currentDigitDoubled >= 10)
            {
                sum += 1 + (currentDigitDoubled % 10);
            }
            else
            {
                sum += currentDigitDoubled;
            }
        }
        idxDigit++;
        creditCardNumber /= 10;
    }
    return sum;
}

int getSumOfRemainingDigits(long long creditCardNumber)
{
    int sum = 0;
    int idxDigit = 0;
    while (creditCardNumber)
    {
        int currentDigit = creditCardNumber % 10;
        if (idxDigit % 2 == 0)
        {
            sum += currentDigit;
        }
        idxDigit++;
        creditCardNumber /= 10;
    }
    return sum;
}

string getCreditCardType(long long creditCardNumber)
{
    char creditCardString[21];
    sprintf(creditCardString, "%lld", creditCardNumber);

    if (isVisa(creditCardString))
    {
        return "VISA";
    }

    if (isAmex(creditCardString))
    {
        return "AMEX";
    }

    if (isMastercard(creditCardString))
    {
        return "MASTERCARD";
    }

    return "INVALID";
}

bool isVisa(string creditCardString)
{
    return (strlen(creditCardString) == 13 || strlen(creditCardString) == 16) && creditCardString[0] == '4';
}

bool isAmex(string creditCardString)
{
    return strlen(creditCardString) == 15 && creditCardString[0] == '3' && (creditCardString[1] == '4' || creditCardString[1] == '7');
}

bool isMastercard(string creditCardString)
{
    return strlen(creditCardString) == 16 && firstCharIsNumberFive(creditCardString)
           && secondCharIsNumberBetweenOneAndFive(creditCardString);
}

bool firstCharIsNumberFive(string creditCardString)
{
    return creditCardString[0] == '5';
}

bool secondCharIsNumberBetweenOneAndFive(string creditCardString)
{
    return creditCardString[1] >= '1' && creditCardString[1] <= '5';
}