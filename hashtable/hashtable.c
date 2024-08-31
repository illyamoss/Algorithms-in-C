#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define INIT_SIZE 5
#define MULTIPLIER 37


Hashtable *createHashtable()
{
    const char **keysList = calloc(INIT_SIZE, sizeof(const char *));
    if (keysList == NULL) {
        fprintf(stderr, "Allocation fault\n");
        exit(EXIT_FAILURE);
    }

    const char **valuesList = malloc(sizeof(const char *) * INIT_SIZE);
    if (valuesList == NULL) {
        free(keysList);
        fprintf(stderr, "Allocation fault\n");
        exit(EXIT_FAILURE);           
    }

    Hashtable *h = malloc(sizeof(Hashtable));
    if (h == NULL) {
        free(keysList);
        free(valuesList); 
        fprintf(stderr, "Allocation fault\n");
        exit(EXIT_FAILURE);
    }

    h->keys = keysList;
    h->values = valuesList;
    h->numberOfElements = 0;
    h->size = INIT_SIZE;

    return h;
}


static unsigned long hash(const char *s)
{
    unsigned long h;
    unsigned const char *us;

    // cast s to unsigned const char
    // this ensures that elements of s will be treated as having values >= 0
    us = (unsigned const char *)s;

    h = 0;
    while (*us != '\0') {
        h = h * MULTIPLIER + *us;
        us++;
    }

    return h;
}


static void expandSize(Hashtable *h, size_t newSize)
{
    h->keys = (const char **)realloc(h->keys, newSize * sizeof(const char *));
    h->values = (const char **)realloc(h->values, newSize * sizeof(const char *));

    if (h->keys == NULL || h->values == NULL) {
        freeHashtable(h);
        fprintf(stderr, "Allocation fault\n");
        exit(EXIT_FAILURE);
    }
}


void insert(Hashtable *h, const char *k, const char *v) 
{
    h->numberOfElements++;
    if (h->numberOfElements > h->size / 1.5) {
        h->size = h->size * 2;
        expandSize(h, h->size);
    }

    unsigned long h_ = hash(k) % h->size;
    printf("---Key: %s, hash: %lu\n", k, h_);

    if (h->keys[h_] != NULL && strcmp(h->keys[h_], k) == 0) {
        h->values[h_] = v;
        return;
    } else if (h->keys[h_] != NULL && (strcmp(h->keys[h_], k) != 0)) {
        for (int i = h_; i < h->size + h_; ++i) {
            int index = i % h->size;
            
            if (h->keys[index] == 0) {
                h->keys[index] = k;
                h->values[index] = v;
                return;
            }
        }
    }

    h->keys[h_] = k;
    h->values[h_] = v;
}


const char *get(Hashtable *h, const char *k)
{
    unsigned long h_ = hash(k) % h->size;
    if (h->keys[h_] != NULL && strcmp(h->keys[h_], k) == 0) {
        return h->values[h_];
    } else if (h->keys[h_] != NULL && (strcmp(h->keys[h_], k) != 0)) {
        for (int i = h_; i < h->size + h_; ++i) {
            int index = i % h->size;

            if (h->keys[index] != NULL && strcmp(h->keys[index], k) == 0) {
                return h->values[index];
            }
        }
    }
    return NULL;
}


void delete(Hashtable *h, const char *k)
{
    unsigned long h_ = hash(k) % h->size;
    if (h->keys[h_] != NULL && strcmp(h->keys[h_], k) != 0)
        return;

    h->values[h_] = NULL;
    h->keys[h_] = NULL;
}


void printTable(Hashtable *h)
{
    for (int i = 0; i < h->size; ++i) {
        if (h->keys[i] != NULL)
            printf("Key %s; value: %s.\n", h->keys[i], h->values[i]);
    }
}


void freeHashtable(Hashtable *h)
{
    free(h->keys);
    free(h->values);
    free(h);
}
