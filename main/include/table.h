#ifndef TABLE
#define TABLE

typedef unsigned long (*hash_function)(void**);
typedef int           (*eq_function)  (void**, void**);

struct table {
  unsigned int size;
  struct table_entry **entries;
  hash_function hash;
  eq_function eq;
};

struct table* mk_table(int size, hash_function hash, eq_function eq);

void    table_add             (struct table *t, void *key, void *value);
void    table_remove          (struct table *t, void *key);
int     table_exists          (struct table *t, void *key);
void*   table_lookup          (struct table *t, void *key);
int     table_count           (struct table *t);
void    table_print_entries   (struct table *t);

#endif

