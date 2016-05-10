#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int eq(char *s1, char *s2) {
  if (strcmp(s1, s2) == 0) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  struct table* t = mk_table(100, (HASH_FUNCTION()) hash, (EQ_FUNCTION()) eq);
  
  table_add(t, "a", "x");
  table_add(t, "b", "y");
  table_add(t, "c", "z");
  
  table_remove(t, "c");

  table_print_entries(t);
  
  printf("%d\n", table_exists(t, "a"));
  printf("%d\n", table_exists(t, "b"));
  printf("%d\n", table_exists(t, "c"));

  printf("%s\n", (char*) table_lookup(t, "a"));
  printf("%s\n", (char*) table_lookup(t, "b"));

  printf("Count: %d\n", table_count(t));

  return 0;
}

