
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hashmap.h"

void *xmalloc(int size)
{
	void *data = malloc(size);
	if (data == NULL) {
		printf("Error allocating!\n");
		exit(1);
	}

	return data;
}

hashmap_t new_hashmap(int size)
{
	// create a new hashmap and allocate space for it
	hashmap_t hm = xmalloc(sizeof(hm_t));
	hm->array = xmalloc(size * sizeof(node_t *));

	// init the lists to NULL
	for (int i = 0; i < size; i++) {
		hm->array[i] = NULL;
	}

	// update the size accordingly
	hm->size = size;

	return hm;
}

unsigned int hashvalue(char *key)
{
	return toupper(key[0]) - 'A';
}

// TODO: add last, checking if key is not already in the HM
int hinsert(hashmap_t hashmap, char *key, char *value)
{
	int idx = hashvalue(key) % hashmap->size;

	// create a new node
	node_t *new = xmalloc(sizeof(node_t));
	new->key = xmalloc(strlen(key) + 1);
	new->value = xmalloc(strlen(value) + 1);

	// update the information
	strcpy(new->key, key);
	strcpy(new->value, value);
	new->next = NULL;

	if (hashmap->array[idx] == NULL) {
		hashmap->array[idx] = new;
	} else {
		// insert first
		node_t *tmp = hashmap->array[idx];
		hashmap->array[idx] = new;
		new->next = tmp;
	}

	return 0;
}

char *hget(hashmap_t hashmap, char *key)
{
	int idx = hashvalue(key) % hashmap->size;

	if (hashmap->array[idx] == NULL)
		return NULL;

	// search for the key
	node_t *tmp = hashmap->array[idx];
	while (tmp != NULL) {
		// key found
		if (strcmp(tmp->key, key) == 0) {
			return tmp->value;
		}
		tmp = tmp->next;
	}

	// key not found
	return NULL;
}

void listfree(node_t *node)
{
	node_t *curr, *pred;
	curr = pred = node;

	while (curr != NULL) {
		curr = curr->next;
		free(pred->key);
		free(pred->value);
		free(pred);
		pred = curr;
	}
}

void hfree(hashmap_t hashmap)
{
	for (int i = 0; i < hashmap->size; i++)
	{
		listfree(hashmap->array[i]);
	}
	
	free(hashmap->array);
	free(hashmap);
}

void hprint(hashmap_t hashmap)
{
	node_t *tmp;
	for (int i = 0; i < hashmap->size; i++) {
		printf("[%d] :", i);
		tmp = hashmap->array[i];
		while (tmp != NULL) {
			printf(" %s", tmp->value);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

int main()
{
	hashmap_t hm = new_hashmap(26);
	hinsert(hm, "a", "noxet");
	hinsert(hm, "ab", "bajs");
	hinsert(hm, "abc", "Liina");
	hinsert(hm, "bb", "Liina");
	hinsert(hm, "gg", "Loona");
	hinsert(hm, "hy", "Felle");
	hinsert(hm, "sr", "bajsi");
	hinsert(hm, "qr", "H4xx0r");

	hprint(hm);

	hfree(hm);
	return 0;
}
