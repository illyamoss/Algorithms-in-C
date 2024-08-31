#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"


int main(void)
{
    Hashtable *h = createHashtable();

    // printf("hello: %lu\n", hash("qello") % 100);
    // printf("Key: %lu\n", hash("Key") % 100);
    // printf("Illya: %lu\n", hash("Illya") % 100);
    // printf("Moss: %lu\n", hash("Moss") % 100);

    printf("Initial size of the Hashtable: %zu\n", h->size);

    const char *key = "Illya";
    const char *value = "Succesful entrepreneur and founder of Imminent";

    insert(h, key, value);

    insert(h, "Yurii", "Crypto investor");
    insert(h, "Sasha", "Don't know");    
    insert(h, "Vlad", "Vice President");
    insert(h, "Leonid", "Founder of Virage");

    const char *nValue = get(h, "Vlad");

    printf("Key: %s; Value: %s\n", key, nValue);

    printf("Size of the Hashtable: %zu\n", h->size);

    printTable(h);

    delete(h, "Illya");

    printf("Deleted\n");

    printTable(h);

    // char *value = get(h, "key");

    // printf("Value: %s", value);

    freeHashtable(h);

    return 1;
}
