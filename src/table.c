#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private functions */
void    set_table_size            (struct table *t, unsigned int size);
void    add_entry_at_location     (struct table *t, struct table_entry *te, unsigned int location);
void    add_entry                 (struct table *t, struct table_entry *te);
void    add_entry_to_entry        (struct table_entry *base, struct table_entry *te);
struct table_entry*     remove_from_chain   (struct table *t, struct table_entry *te, void *key);
int     exists_in_chain           (struct table *t, struct table_entry *te, void *key);
int     count_chain               (struct table_entry *te);
void    print_entries_chained     (struct table_entry *te);
struct table_entry*     mk_entry            ();
int     get_location              (struct table *t, void *key);

struct table_entry {
  void *entry;
  void *value;
  struct table_entry* next;
};

struct table* mk_table(int size, HASH_FUNCTION(hash), EQ_FUNCTION(eq)) {
  struct table *t = malloc(sizeof(struct table));
  t->size = 0;
  t->entries = NULL;
  t->hash = hash;
  t->eq = eq;

  set_table_size(t, size);

  return t;
}

void set_table_size(struct table *t, unsigned int size) {
  int chunk_size = sizeof(struct table_entry) * size;

  t->size = size;
  t->entries = malloc(chunk_size);
  memset(t->entries, '\0', chunk_size);
}

void table_add(struct table *t, void *key, void *value) {
  struct table_entry *te = mk_entry();
  te->entry = key;
  te->value = value;

  add_entry(t, te);
}

void add_entry(struct table *t, struct table_entry *te) {
  int location = get_location(t, te->entry);
  add_entry_at_location(t, te, location);
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
    add_entry_to_entry(te_current, te);
  }
}

void add_entry_to_entry(struct table_entry *base, struct table_entry *te) {
  if (base->next) {
    add_entry_to_entry(base->next, te);
  } else {
    base->next = te;
  }
}

void table_remove(struct table *t, void *key) {
  int location = get_location(t, key);
  t->entries[location] = remove_from_chain(t, t->entries[location], key);
}

struct table_entry* remove_from_chain(struct table *t, struct table_entry *te, void *key) {
  if (!te) {
    fprintf(stderr, "Can't delete %s because doesn't exist", (char *) key);
    return NULL;
  }

  if (!t->eq(te->entry, key)) {
    struct table_entry *new_next = remove_from_chain(t, te->next, key);
    te->next = new_next;
    return te;
  }

  return te->next;
}

int table_exists(struct table *t, void *key) {
  int location = get_location(t, key);

  if (!t->entries[location]) {
    return 0;
  }

  return exists_in_chain(t, t->entries[location], key);
}

int exists_in_chain(struct table *t, struct table_entry *te, void *key) {
  if (!te) {
    return 0;
  } else if (t->eq(te->entry, key)) {
    return 1;
  } else {
    return exists_in_chain(t, te->next, key);
  }
}

int table_count(struct table *t) {
  int total = 0;

  for (unsigned int i = 0; i < t->size; i++) {
    if (!t->entries[i]) continue;

    total += count_chain(t->entries[i]);
  }

  return total;
}

int count_chain(struct table_entry *te) {
  if (te) {
    return 1 + count_chain(te->next);
  } else {
    return 0;
  }
}

void table_print_entries(struct table *t) {
  for (unsigned int i = 0; i < t->size; i++) {
    if (!t->entries[i]) {
      continue;
    }
    
    print_entries_chained(t->entries[i]);
  }
}

void print_entries_chained(struct table_entry *te) {
  printf("%s\n", (char *) te->entry);

  if (te->next) {
    print_entries_chained(te->next);
  }
}

struct table_entry* mk_entry() {
  struct table_entry *te = malloc(sizeof(struct table_entry));
  te->entry = NULL;
  te->next = NULL;

  return te;
}

int get_location(struct table *t, void *key) {
  unsigned long hash = t->hash(key);
  return (int) (hash % ((long) t->size));
}

