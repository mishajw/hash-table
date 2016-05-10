#include "../include/table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int main() {
  struct table* t = mk_table(100, (HASH_FUNCTION()) hash);

  table_add(t, "Element One");

  table_add(t, "Element Two");

  return 0;
}

