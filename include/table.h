#ifndef TABLE
#define TABLE

struct table {
  unsigned int size;
  struct table_entry **entries;
  long (*hash)(void*);
};

struct table* mk_table(int size, long (*hash)(void*));
struct table_entry* mk_entry();

void add_to_table(struct table *t, void *value);

#endif

