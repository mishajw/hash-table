#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct table {
  unsigned int size;
  struct table_entry **entries;
};

struct table_entry {
  void* entry;
  struct table_entry* next;
};

struct table* mk_table() {
  struct table *t = malloc(sizeof(struct table));
  t->size = 0;
  t->entries = NULL;

  return t;
}

struct table_entry* mk_entry() {
  struct table_entry *te = malloc(sizeof(struct table_entry));
  te->entry = NULL;
  te->next = NULL;

  return te;
}

void set_table_size(struct table *t, unsigned int size) {
  int chunk_size = sizeof(struct table_entry) * size;

  t->size = size;
  t->entries = malloc(chunk_size);
  memset(t->entries, '\0', chunk_size);
}

int main() {
  struct table* t = mk_table();
  set_table_size(t, 100);

  printf("%d", t->size);
  printf("%d", t->entries[51]);
}

