#ifndef TABLE
#define TABLE

#define HASH_FUNCTION(name) unsigned long (*name)(void**)

struct table {
  unsigned int size;
  struct table_entry **entries;
  HASH_FUNCTION(hash);
};

struct table* mk_table(int size, HASH_FUNCTION(hash));

void table_add(struct table *t, void *value);
void table_remove(struct table *t, void *value);
void table_exists(struct table *t, void *value);
void table_count(struct table *t);
void table_print_entries(struct table *t);

#endif

