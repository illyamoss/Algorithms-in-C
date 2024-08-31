#ifndef HASHTABLE_IMP_
#define HASHTABLE_IMP_

typedef const char **keysList;
typedef const char **valuesList;

typedef struct Hashtable {
    keysList keys;
    valuesList values;
    int numberOfElements;
    size_t size;
} Hashtable;

Hashtable *createHashtable();

void insert(Hashtable *h, const char *k, const char *v);
const char *get(Hashtable *h, const char *k);
void delete(Hashtable *h, const char *k);

void freeHashtable(Hashtable *h);
void printTable(Hashtable *h);

#endif