#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct
{
  unsigned int size;
  unsigned int capacity;
  void **list;
} Dynamicarray;

typedef struct
{
  Dynamicarray *list;
  unsigned int cur_idx;
} Dynarr_iterator;

Dynamicarray default_alloc();
Dynamicarray alloc_arr(unsigned int capacity);
void realloc_arr(Dynamicarray *list, unsigned int extra_capacity);
void add_index(Dynamicarray *list, void *item, unsigned int index);
void *get_index(Dynamicarray *list, unsigned int index);
void *pop(Dynamicarray *list);
void push(Dynamicarray *list, void *item);
void *shift(Dynamicarray *list);
void unshift(Dynamicarray *list, void *item);
void set_index(Dynamicarray *list, void *item, unsigned int index);
void iterate(Dynamicarray *list, void (*func)(void *));
void clear(Dynamicarray *list);
void free_arr(Dynamicarray *list);
void free_arr_deep(Dynamicarray *list);
Dynarr_iterator *create_iterator(Dynamicarray *list);
Dynamicarray map(Dynamicarray *list, void *(*func)(void *));
void *next(Dynarr_iterator *iter);
unsigned int length(Dynamicarray *list);

#endif // DATASTRUCTURES_H
