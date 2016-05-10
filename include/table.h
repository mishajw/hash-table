#ifndef TABLE
#define TABLE

struct table {
  unsigned int size;
  struct table_entry **entries;
  long (*hash)(int);
};

struct table* mk_table(int size, long (*hash)(int));
struct table_entry* mk_entry();

void add_to_table(struct table *t, void *value);

#endif

