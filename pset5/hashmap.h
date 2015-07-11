#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

#include "dictionary.h"

// size of hashmap array
#define HASHSIZE 10000

typedef struct node_t
{
    char word[LENGTH + 1];
    struct node_t *next;
} node_t;

typedef struct hm_t
{
    unsigned int size;
    node_t *array[HASHSIZE];
} hm_t;

typedef hm_t* dict_t;

// prototypes
dict_t new_dict();
void dinsert(dict_t, char *);
bool dcontains(dict_t hm, const char *word);
void dfree(dict_t);
void dprint(dict_t);

#endif
