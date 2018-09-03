#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#define NB_LETTERS_IN_ALPHABET 26
#define LOWERCASE_ASCII_LIMIT 122
#define UPPERCASE_ASCII_LIMIT 90

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    int k = atoi(argv[1]) % NB_LETTERS_IN_ALPHABET;

    string p = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(p); i < n; i++)
    {
        char plain_letter = p[i];
        char cipher_letter;

        if (!isalpha(plain_letter))
        {
            cipher_letter = plain_letter;
        }
        else if (islower(plain_letter))
        {
            cipher_letter = (plain_letter + k > LOWERCASE_ASCII_LIMIT)
                ? plain_letter - NB_LETTERS_IN_ALPHABET + k
                : plain_letter + k;
        }
        else if (isupper(plain_letter))
        {
            cipher_letter = (plain_letter + k > UPPERCASE_ASCII_LIMIT)
                ? plain_letter - NB_LETTERS_IN_ALPHABET + k
                : plain_letter + k;
        }

        printf("%c", cipher_letter);
    };

    printf("\n");
}