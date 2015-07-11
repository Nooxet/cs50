#ifndef HASHMAP_H
#define HASHMAP_H

/* the linked list */
typedef struct node_t
{
	char *key;
	char *value;
	struct node_t *next;
} node_t;

typedef struct hm_t
{
	int size;
	node_t **array; // array of node_t pointers
} hm_t;

typedef hm_t* hashmap_t;

int hinsert(hashmap_t, char *, char *);
char *hget(hashmap_t, char *);
void hprint(hashmap_t);
void hfree(hashmap_t);

#endif
