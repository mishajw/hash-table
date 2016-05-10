#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private functions */
void set_table_size(struct table *t, unsigned int size);
void add_entry_at_location(struct table *t, struct table_entry *te, unsigned int location);
void append_entry(struct table_entry *base, struct table_entry *te);

struct table_entry {
  void* entry;
  struct table_entry* next;
};

struct table* mk_table(int size, long (*hash)(void*)) {
  struct table *t = malloc(sizeof(struct table));
  t->size = 0;
  t->entries = NULL;
  t->hash = hash;

  set_table_size(t, size);

  return t;
}

void add_to_table(struct table *t, void *value) {
  struct table_entry *e = mk_entry();
  e->entry = value;

  printf("TODO: Inserting value at hash location\n");
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

void add_entry_at_location(struct table *t, struct table_entry *te, unsigned int location) {
  if (location >= t->size) {
    fprintf(stderr, "Location %d too large for table of size %d", location, t->size);
    exit(1);
  }

  struct table_entry* te_current = t->entries[location];

  if (!te_current) {
    t->entries[location] = te;
  } else {
    append_entry(te_current, te);
  }
}

void append_entry(struct table_entry *base, struct table_entry *te) {
  if (base->next) {
    append_entry(base->next, te);
  } else {
    base->next = te;
  }
}

