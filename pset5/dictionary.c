/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "dictionary.h"
#include "hashmap.h"

// the dictionary
dict_t dict;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char w[LENGTH + 1] = { 0 };
    
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            w[i] = (char) tolower(word[i]);
        }
        else
        {
            w[i] = word[i];
        }
    }

    return dcontains(dict, w);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    dict = new_dict();

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: could not open %s\n", dictionary);
        return false;
    }

    // buffer for the words in dictionary
    // make room for the newline char as well
    char buffer[LENGTH + 2];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // remove trailing newline character
        buffer[strlen(buffer) - 1] = '\0';
        dinsert(dict, buffer);
    }

    fclose(file);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dict->size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    dfree(dict);
    return true;
}
