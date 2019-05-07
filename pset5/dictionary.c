// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

node *hashtable[HASHTABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char* wordLowercase = stringToLowercase(word);
    int hashIdx = hash_it(wordLowercase);
    free(wordLowercase);

    node *cursor = hashtable[hashIdx];
    while (cursor != NULL)
    {
        int wordsAreEqual = (strcasecmp(word, cursor->word) == 0);
        if (wordsAreEqual)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }

    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = malloc(sizeof(node));
        strcpy(hashtable[i]->word, "");
        hashtable[i]->next = NULL;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);

        int hashIdx = hash_it(word);

        new_node->next = hashtable[hashIdx];
        hashtable[hashIdx] = new_node;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;

    int i = 0;
    node *cursor = NULL;
    for (i = 0; i < HASHTABLE_SIZE; i++)
    {
        cursor = hashtable[i];
        while (cursor->next != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int i = 0;
    node *cursor = NULL;
    node *temp = NULL;
    for (i = 0; i < HASHTABLE_SIZE; i++)
    {
        cursor = hashtable[i];
        while (cursor->next != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        free(cursor);
        cursor = NULL;
    }

    return true;
}

int hash_it(const char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i < n; i++)
    {
        hash = (hash << 2) ^ needs_hashing[i];
    }
    return hash % HASHTABLE_SIZE;
}

char* stringToLowercase(const char *str)
{
  char *strCpy = malloc((strlen(str) + 1) * sizeof(char));
  strcpy(strCpy, str);

  char *s;

  for(s = strCpy; *s; s++)
  {
    *s = tolower((unsigned char)*s);
  }
  return strCpy;
}