
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "hashmap.h"

/* a nice way of error checking malloc with debug prints */
#define xmalloc(size) (xmalloc(__FILE__, __LINE__, size))

void *(xmalloc)(char *file, unsigned long line, int size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        fprintf(stderr, "Error allocating at line %lu in file %s\n", line, file);
        exit(1);
    }

    return ptr;
}

/* a hash function based on djb2 */
unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + (unsigned char) c;
    }

    return hash;
}

/**
 * creates and returns a new empty dictionary
 */
dict_t new_dict()
{
    dict_t hm = xmalloc(sizeof(hm_t));

    for (int i = 0; i < HASHSIZE; i++)
    {
        hm->array[i] = NULL;
    }

    hm->size = 0;

    return hm;
}

/**
 * insert a new word in to the dictionary
 */
void dinsert(dict_t hm, char *word)
{
    unsigned long idx = hash(word) % HASHSIZE;

    // create a new node and initialize it
    node_t *node = xmalloc(sizeof(node_t));
    // make sure we do not overflow buffer
    strncpy(node->word, word, sizeof(node->word));
    node->next = NULL;

    if (hm->array[idx] == NULL)
    {
        // first and only node in list
        hm->array[idx] = node;
    }
    else
    {
        // insert first
        node->next = hm->array[idx];
        hm->array[idx] = node;
    }

    hm->size++;
}

bool dcontains(dict_t hm, const char *word)
{
    unsigned long idx = hash(word) % HASHSIZE;

    node_t *tmp = hm->array[idx];

    while (tmp != NULL)
    {
        // word found
        if (strncmp(tmp->word, word, sizeof(tmp->word)) == 0)
            return true;

        tmp = tmp->next;
    }

    // word not found
    return false;
}

/**
 * "private" function for freeing a list in 
 * the hashmap
 */
void free_list(node_t *list)
{
    node_t *tmp = list;
    while (list != NULL)
    {
        list = list->next;
        free(tmp);
        tmp = list;
    }
}

/**
 * frees the allocated memory in the hashmap
 */
void dfree(dict_t hm)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        free_list(hm->array[i]);
    }

    free(hm);
}

/**
 * "private" function for printing each
 * list in the hashmap
 */
void print_list(node_t *list)
{
    while (list != NULL)
    {
        printf(" %s", list->word);
        list = list->next;
    }
}

/**
 * prints the contents of a dictionary
 */
void dprint(dict_t hm)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        printf("[%d] - ", i);
        print_list(hm->array[i]);
        printf("\n");
    }
}
