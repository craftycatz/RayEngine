//
// Created by Robin Denker on 10.04.23.
//

#ifndef CENGINE_HASHMAP_H
#define CENGINE_HASHMAP_H

typedef struct {
    void *key;
    int hash;
    void *value;
    struct HashmapEntry *next;
} HashmapEntry;

typedef struct {
    int num_buckets;
    int num_entries;
    HashmapEntry **buckets;

        int (*hash)(const void *key, int len);
        int (*compare)(const void *key1, const void *key2);
} Hashmap;

Hashmap alloc_map(int (*hash)(const void *key, int len),
                  int (*compare)(const void *key1, const void *key2));

Hashmap alloc_num_buckets(int (*hash)(const void *key, int len),
                          int (*compare)(const void *key1, const void *key2),
                          unsigned int capacity);

Hashmap alloc_num_entries(unsigned int num_entries, int (*hash)(const void *key, int len),
                                int (*compare)(const void *key1, const void *key2));

#endif // CENGINE_HASHMAP_H
