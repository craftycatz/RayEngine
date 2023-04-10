#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10
#define MAX_LOAD_FACTOR 0.75

Hashmap alloc_map(int (*hash)(const void *key, int len),
                  int (*compare)(const void *key1, const void *key2)) {
  return alloc_num_buckets(hash, compare, INITIAL_SIZE);
}

Hashmap alloc_num_buckets(int (*hash)(const void *key, int len),
                          int (*compare)(const void *key1, const void *key2),
                          unsigned int capacity) {
  if (capacity < 1) {
    capacity = INITIAL_SIZE;
  }

  Hashmap map;
  map.num_buckets = capacity;
  map.num_entries = 0;
  map.buckets = calloc(capacity, sizeof(HashmapEntry *));
  map.hash = hash;
  map.compare = compare;

  // set all buckets to null
  for (int i = 0; i < capacity; i++) {
    map.buckets[i] = NULL;
  }

  return map;
}

Hashmap alloc_num_entries(unsigned int num_entries,
                          int (*hash)(const void *key, int len),
                          int (*compare)(const void *key1, const void *key2)) {

  double num_buckets = INITIAL_SIZE;
  double num_entries_f = (double)num_entries;
  while (num_entries / num_buckets > MAX_LOAD_FACTOR) {
    num_buckets *= 2.0;
  }

  return alloc_num_buckets(hash, compare, (unsigned int)num_buckets);
}

void realloc_map(Hashmap *map) {
  Hashmap new_map = alloc_num_buckets(map->hash, map->compare, map->num_buckets * 2);

  for (int i = 0; i < map->num_buckets; i++) {
    HashmapEntry *entry = map->buckets[i];
    while (entry != NULL) {
      HashmapEntry *next = entry->next;
      int bucket = entry->hash % new_map.num_buckets;
      entry->next = new_map.buckets[bucket];
      new_map.buckets[bucket] = entry;
      entry = next;
    }
  }

  free(map->buckets);
  map->buckets = new_map.buckets;
  map->num_buckets = new_map.num_buckets;
}

uint32_t hash(const void *key, size_t len) {
  uint32_t hash = 0;
  const uint8_t *data = (const uint8_t *)key;
  for (size_t i = 0; i < len; ++i) {
    hash += data[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}