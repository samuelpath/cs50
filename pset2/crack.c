#define _XOPEN_SOURCE
#define POSSIBLE_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define MAX_CHARS_IN_PWD 5
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

string getSaltFromHash(string hash);
void strev(char *str);
char* fromDeci(char res[], int base, int inputNum);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    string hash = argv[1];
    string salt = getSaltFromHash(hash);

    int nbPossibleChars = strlen(POSSIBLE_CHARS);

    int currOptionNum;
    for (currOptionNum = 0; currOptionNum < pow(nbPossibleChars, MAX_CHARS_IN_PWD); currOptionNum++)
    {
        printf("\tcurrent option number: %i", currOptionNum);

        char res[MAX_CHARS_IN_PWD];
        string currOption = fromDeci(res, nbPossibleChars, currOptionNum);

        printf("\tcurrOption: %s", currOption);

        string currOptionEncrypted = crypt(currOption, salt);

        printf("\tcurrOptionEncrypted: %s", currOptionEncrypted);

        if (strncmp(currOptionEncrypted, hash, 13) == 0)
        {
            printf("\nYEEAH, result: %s", currOption);
            return 0;
        }
        printf("\n");
    }
    return 0;
}

string getSaltFromHash(string hash)
{
    char *salt = (char*) malloc(3);
    strncpy(salt, hash, 2);
    return salt;
}

// Utility function to reverse a string
void strev(char *str)
{
    int len = strlen(str);
    int i;
    for (i = 0; i < len/2; i++)
    {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

// Function to convert a given decimal number to a base 'base'
char* fromDeci(char res[], int base, int inputNum)
{
    int index = 0;  // Initialize index of result

    // Convert input number is given base by repeatedly
    // dividing it by base and taking remainder
    if (inputNum == 0)
    {
        res[index++] = POSSIBLE_CHARS[0];
    }

    while (inputNum > 0)
    {
        res[index++] = POSSIBLE_CHARS[inputNum % base];
        inputNum /= base;
    }

    res[index] = '\0';

    // Reverse the result
    strev(res);

    return res;
}