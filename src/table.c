#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table* mk_table(int size, long (*hash)(int)) {
  struct table *t = malloc(sizeof(struct table));
  t->size = 0;
  t->entries = NULL;
  t->hash = hash;

  set_table_size(t, size);

  return t;
}

void set_table_size(struct table *t, unsigned int size) {
  int chunk_size = sizeof(struct table_entry) * size;

  t->size = size;
  t->entries = malloc(chunk_size);
  memset(t->entries, '\0', chunk_size);
}

struct table_entry* mk_entry() {
  struct table_entry *te = malloc(sizeof(struct table_entry));
  te->entry = NULL;
  te->next = NULL;

  return te;
}

void add_to_table(struct table *t, struct table_entry *te, unsigned int location) {
  if (location >= t->size) {
    fprintf(stderr, "Location %d too large for table of size %d", location, t->size);
    exit(1);
  }

  struct table_entry* te_current = t->entries[location];

  if (!te_current) {
    t->entries[location] = te;
    return;
  }

  fprintf(stderr, "Collision detected. Not adding element to table.");
}

