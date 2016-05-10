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

int main() {
  struct table* t = mk_table(100, (HASH_FUNCTION()) hash);
  
  char *e1 = "a";
  char *e2 = "b";
  char *e3 = "c";
  char *e4 = "d";

  table_add(t, e1);
  table_add(t, e2);
  table_add(t, e3);
  table_add(t, e4);
  
  table_remove(t, e2);

  table_print_entries(t);
  
  printf("%d\n", table_exists(t, e1));
  printf("%d\n", table_exists(t, e2));
  printf("%d\n", table_exists(t, e3));
  printf("%d\n", table_exists(t, e4));

  printf("Count: %d\n", table_count(t));

  return 0;
}

