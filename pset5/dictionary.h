// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define HASHTABLE_SIZE 65536 // 2^16

// type definitions
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Standard Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

// Custom Prototypes
int hash_it(const char* needs_hashing);
char* stringToLowercase(const char *str);

#endif // DICTIONARY_H
