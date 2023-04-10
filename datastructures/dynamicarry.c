#include "dynamicarry.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 10

Dynamicarray default_alloc() { return alloc_arr(INITIAL_SIZE); }

Dynamicarray alloc_arr(unsigned int capacity) {
  if (!capacity) {
    capacity = INITIAL_SIZE;
  }

  Dynamicarray arr;

  arr.list = malloc(sizeof(void *) * capacity);
  arr.size = 0;
  arr.capacity = arr.list ? capacity : 0;
  return arr;
}

void realloc_arr(Dynamicarray *list, unsigned int extra_capacity) {
  unsigned int new_capacity = list->capacity + extra_capacity;

  if(new_capacity >list->capacity) {
    unsigned int capacity = list->capacity;
    if(!capacity) {
      capacity = INITIAL_SIZE;
    }

    while(capacity < new_capacity) {
          capacity <<= 2;
    }

    void **old_list = list->list;
    list->list = realloc(list->list, sizeof(void *) * capacity);
    if(!list->list){
          //allocate in new location
          list->list = malloc(sizeof(void *) * capacity);
          memcpy(list->list, old_list, sizeof(void *) * list->capacity);
          free(old_list);
    }

  }

}

void add_index(Dynamicarray *list, void *item, unsigned int index) {
        if (index > list->size) {
        fprintf(stderr, "Boundary Error: Can't add item to index %d, list size is %d.\n", index, list->size);
        return;
        }
        // Check if we need to realloc
        realloc_arr(list, 1);

        // Move items to the right
        memmove(list->list + index + 1, list->list + index, sizeof(void *) * (list->size - index));

        // Check if memmove failed
        if (!list->list) {
          fprintf(stderr, "Error: Can't memmove memory.\n");
          return;
        }

        // Add item at index
        list->list[index] = item;
        list->size++;
}

void *remove_index(Dynamicarray *list, unsigned int index) {
  if (index >= list->size) {
    fprintf(stderr, "Boundary Error: Can't remove item from index %d, list size is %d.\n", index, list->size);
    return NULL;
  }

  // get the item to be removed
  void *item = list->list[index];

  // Move items to the left
  memmove(list->list + index, list->list + index + 1, sizeof(void *) * (list->size - index - 1));

  // Check if memmove failed
  if (!list->list) {
    fprintf(stderr, "Error: Can't memmove memory.\n");
    return NULL;
  }

  list->size--;
  return item;
}

void push(Dynamicarray *list, void *item) { add_index(list, item, list->size); }

void *pop(Dynamicarray *list) { return remove_index(list, list->size - 1); }

void *shift(Dynamicarray *list) { return remove_index(list, 0); }

void unshift(Dynamicarray *list, void *item) { add_index(list, item, 0); }

void set_index(Dynamicarray *list, void *item, unsigned int index) {
  if (index >= list->size) {
    fprintf(stderr, "Boundary Error: Can't set item to index %d, list size is %d.\n", index, list->size);
    return;
  }

  list->list[index] = item;
}

void *get_index(Dynamicarray *list, unsigned int index) {
  if (index >= list->size) {
    fprintf(stderr, "Boundary Error: Can't get item from index %d, list size is %d.\n", index, list->size);
    return NULL;
  }

  return list->list[index];
}

void iterate(Dynamicarray *list, void (*visit)(void *element)) {
  for (unsigned int i = 0; i < list->size; i++) {
    visit(list->list[i]);
  }
}

Dynamicarray map(Dynamicarray *list, void *(*visit)(void *element)) {
  Dynamicarray new_list = alloc_arr(list->size);
  for (unsigned int i = 0; i < list->size; i++) {
    void *item = visit(list->list[i]);
    push(&new_list, item);
  }
  return new_list;
}

void clear(Dynamicarray *list) {
  for (unsigned int i = 0; i < list->size; i++) {
    free(list->list[i]);
  }
  list->size = 0;
}

void free_arr(Dynamicarray *list) {
  free(list->list);
}

void free_arr_deep(Dynamicarray *list) {
  for(unsigned int i = 0; i < list->size; i++) {
    free(list->list[i]);
  }
}

Dynarr_iterator *create_iterator(Dynamicarray *list) {
  Dynarr_iterator *iter = malloc(sizeof(Dynarr_iterator));
  iter->list = list;
  iter->cur_idx = 0;
  return iter;
}

void *next(Dynarr_iterator *iter) {
  if (iter->cur_idx >= iter->list->size) {
    return NULL;
  }
  return iter->list->list[iter->cur_idx++];
}



unsigned int length(Dynamicarray *list) { return list->size; }
