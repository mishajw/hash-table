#ifndef TABLE
#define TABLE

#define HASH_FUNCTION(name) unsigned long (*name)(void**)

struct table {
  unsigned int size;
  struct table_entry **entries;
  HASH_FUNCTION(hash);
};

struct table* mk_table(int size, HASH_FUNCTION(hash));

void add(struct table *t, void *value);

#endif

