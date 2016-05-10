#ifndef TABLE
#define TABLE

struct table {
  unsigned int size;
  struct table_entry **entries;
  long (*hash)(int);
};

struct table_entry {
  void* entry;
  struct table_entry* next;
};

struct table* mk_table(int size, long (*hash)(int));
struct table_entry* mk_entry();

void set_table_size(struct table *t, unsigned int size);
void add_to_table(struct table *t, struct table_entry *te, unsigned int location);

#endif

